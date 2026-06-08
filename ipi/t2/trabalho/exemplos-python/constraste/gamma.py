import numpy as np
import matplotlib.pyplot as plt

def gamma_transform(img, gamma):
    c = 255.0 / (255.0**gamma)
    imgGamma =img.astype(np.float64)
    imgGamma = c * (imgGamma) ** gamma
    imgGamma = imgGamma.astype(np.uint8)
    return imgGamma

if __name__ == '__main__':
    # Le a imagem
    img = plt.imread('fractured_spine.tif')
    
    img_gamma1 = gamma_transform(img, 0.2)
    img_gamma2 = gamma_transform(img, 5.0)


    # Plota lado a lado
    fig, axs = plt.subplots(1, 3)
    axs[0].axis('off')
    axs[0].set_title('Original')
    axs[0].imshow(img, cmap='gray')
    axs[1].axis('off')
    axs[1].set_title('Gamma 0.2')
    axs[1].imshow(img_gamma1, cmap='gray')
    axs[2].axis('off')
    axs[2].set_title('Gamma 5.0')
    axs[2].imshow(img_gamma2, cmap='gray')
    plt.show()
