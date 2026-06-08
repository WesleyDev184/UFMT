import numpy as np
import matplotlib.pyplot as plt
import cv2
import sys

if __name__ == '__main__':
    img = cv2.imread('low_contrast_pollen.tif', cv2.IMREAD_GRAYSCALE) 
    
    R, C = img.shape # recupera numero de linhas e colunas da imagem

    #calculo do histograma normalizado (pr)
    hist = cv2.calcHist([img], [0], None, [256], [0, 256]) 
    pr = hist/(R*C) 

    # cummulative distribution function (CDF)
    cdf = pr.cumsum()
    sk = 255 * cdf
    sk = np.round(sk)

    # criando a imagem de saída
    img_out = np.zeros(img.shape, dtype=np.uint8)
    for i in range(256):
        img_out[img == i] = sk[i]
    
    #plota lado a lado
    fig, axs = plt.subplots(1,2)
    axs[0].axis('off')
    axs[0].set_title('Original')
    axs[0].imshow(img, cmap = 'gray', vmin=0, vmax=255)
    axs[1].axis('off')
    axs[1].set_title('Equalizada')
    axs[1].imshow(img_out, cmap='gray', vmin=0, vmax=255)
    plt.show()

    fig1, axs1 = plt.subplots(1,2)
    axs1[0].axis('off')
    axs1[0].set_title('Original')
    axs1[0].hist(img.ravel(), 256, [0,256])
    axs1[1].axis('off')
    axs1[1].set_title('Equalizada')
    axs1[1].hist(img_out.ravel(), 256, [0,256])
    plt.show()