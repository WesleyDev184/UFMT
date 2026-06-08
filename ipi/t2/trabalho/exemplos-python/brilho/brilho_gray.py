import numpy as np
import matplotlib.pyplot as plt
import cv2

# Ajusta o brilho de uma imagem monocromatica
def ajustaBrilho(img, c):
    newImg = img.astype(float) + c #broadcasting
    newImg[newImg > 255] = 255
    newImg[newImg < 0] = 0
    return newImg.astype(np.uint8)

if __name__ == '__main__':
    
    # Le a imagem
    img = plt.imread('cat_puppy.jpg') #RGB

    # converte para escala de cinza
    img_gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    print(img_gray.shape)

    # aumenta o brilho em 50 tons
    img_brighter = ajustaBrilho(img_gray, 50)
   
    # diminui em 50 tons
    img_darker = ajustaBrilho(img_gray, -50)
    
    # para comparar colocamos as imagens lado a lado
    fig, axs = plt.subplots(1, 3)
    axs[0].axis('off')
    axs[0].set_title('Mais brilho')
    axs[0].imshow(img_brighter, cmap='gray')
    axs[1].axis('off')
    axs[1].set_title('Original')
    axs[1].imshow(img_gray, cmap='gray')
    axs[2].axis('off')
    axs[2].set_title('Menos Brilho')
    axs[2].imshow(img_darker, cmap='gray')
    plt.show()
