import numpy as np
import matplotlib.pyplot as plt
import cv2

# Ajusta o brilho de uma imagem monocromatica
def ajustaBrilho(img, c):
    newImg = img.astype(float) + c
    newImg[newImg > 255] = 255
    newImg[newImg < 0] = 0
    return newImg.astype(np.uint8)

if __name__ == '__main__':
    
    # Le a imagem
    img = plt.imread('cat_puppy.jpg')

    # aumenta o brilho em 50 tons
    img_brighter = ajustaBrilho(img, 50)
   
    # diminui em 50 tons
    img_darker = ajustaBrilho(img, -50)
    
    # para comparar colocamos as imagens lado a lado
    fig, axs = plt.subplots(1, 3)
    axs[0].axis('off')
    axs[0].set_title('Mais brilho')
    axs[0].imshow(img_brighter)
    axs[1].axis('off')
    axs[1].set_title('Original')
    axs[1].imshow(img)
    axs[2].axis('off')
    axs[2].set_title('Menos Brilho')
    axs[2].imshow(img_darker)
    plt.show()
