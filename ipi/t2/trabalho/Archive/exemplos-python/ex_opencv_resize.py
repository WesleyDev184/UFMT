import cv2
import matplotlib.pyplot as plt

if __name__ == '__main__':
    img = plt.imread('cat_puppy.jpg') # RGB
    print('Dimensoes originais : ',img.shape)
    
    width = img.shape[1] * 2  #dobra a dimensao
    height = img.shape[0] * 2 #dobra a dimensao
    dim = (width, height) # tupla
    
    # redimensiona
    img_resized = cv2.resize(img, dim, interpolation = cv2.INTER_CUBIC)
    print('Dimensoes da nova imagem : ',img_resized.shape)
    
    fig, axs = plt.subplots(1, 2)
    axs[0].set_title("Original")
    axs[0].imshow(img)
    axs[1].set_title("Reamostrada")
    axs[1].imshow(img_resized)
    plt.show()
