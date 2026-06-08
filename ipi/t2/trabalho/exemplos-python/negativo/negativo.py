import numpy as np
import matplotlib.pyplot as plt

def complemento(img: np.ndarray)->np.ndarray:
    return 255 - img


if __name__ == '__main__':
    # Le a imagem
    #img = plt.imread('breast_digital_Xray.tif')
   
    img = plt.imread('cat_puppy.jpg')
    print(img.shape)
    
    # Calcula o negativo vetorialmente
    negativo = complemento(img)

    # para comparar colocamos as imagens lado a lado
    fig, axs = plt.subplots(1, 2)
    axs[0].axis('off')
    axs[0].set_title('Original')
    axs[0].imshow(img)
    axs[1].axis('off')
    axs[1].set_title('Negativo')
    axs[1].imshow(negativo)
    plt.show()
