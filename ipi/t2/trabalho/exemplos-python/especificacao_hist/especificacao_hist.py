import numpy as np
import matplotlib.pyplot as plt
import cv2

if __name__ == '__main__':
    img_input = cv2.imread('histogram_matching_input.jpeg')   # imagem de entrada
    img_ref = cv2.imread('histogram_matching_ref1.jpeg') # imagem de referência

    chans_img = cv2.split(img_input) # separa os canais de cores
    chans_ref = cv2.split(img_ref)   # separa os canais de cores

    # iterage nos canais da imagem de entrada e calcula o histograma
    pr = np.zeros((256, 3))
    for chan, n in zip(chans_img, np.arange(3)):
        pr[:,n] = cv2.calcHist([chan], [0], None, [256], [0, 256]).ravel()

    # iterage nos canais da imagem de referencia e calcula o histograma
    pz = np.zeros((256, 3))
    for chan, n in zip(chans_ref, np.arange(3)):
        pz[:,n] = cv2.calcHist([chan], [0], None, [256], [0, 256]).ravel()
	
    # calcula as CDFs para a imagem de entrada
    cdf_input = np.zeros((256, 3))
    for i in range(3):
        cdf_input[:,i] = np.cumsum(pr[:,i]) # referencia
    
    # calcula as CDFs para a imagem de referencia
    cdf_ref = np.zeros((256,3))
    for i in range(3):
        cdf_ref[:,i] = np.cumsum(pz[:,i]) # referencia
    

    img_out = np.zeros(img_input.shape) # imagem de saida

    for c in range(3): # corre nos planos de cores
        for i in range(256): # corre na cdf de cada plano da imagem
            diff = np.absolute(cdf_ref[:,c] - cdf_input[i,c])
            indice = diff.argmin()
            img_out[img_input[:,:,c] == i, c] = indice

    img_out = img_out.astype(np.uint8)
 
    
    img_input = cv2.cvtColor(img_input, cv2.COLOR_BGR2RGB)
    img_ref = cv2.cvtColor(img_ref, cv2.COLOR_BGR2RGB)
    img_out = cv2.cvtColor(img_out, cv2.COLOR_BGR2RGB)
    
    fig, axs = plt.subplots(1,3)
    axs[0].axis('off')
    axs[0].set_title('Original')
    axs[0].imshow(img_input)
    axs[1].axis('off')
    axs[1].set_title('Referencia')
    axs[1].imshow(img_ref)
    axs[2].axis('off')
    axs[2].set_title('Saida')
    axs[2].imshow(img_out)
    plt.show()

  
