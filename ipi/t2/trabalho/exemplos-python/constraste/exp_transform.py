import numpy as np
import matplotlib.pyplot as plt

def exp_transform(img):
    c = 255.0 / np.log(256)
    imgOut = img.astype(np.float64)
    imgOut = np.exp(imgOut)**(1.0/c) - 1.0
    return imgOut.astype(np.uint8)

if __name__ == '__main__':
    # Le a imagem
    img = plt.imread('washed_out_aerial_image.tif')
    img_exp = exp_transform(img)

    # Plota lado a lado
    fig, axs = plt.subplots(1, 2)
    axs[0].axis('off')
    axs[0].set_title('Original')
    axs[0].imshow(img, cmap='gray')
    axs[1].axis('off')
    axs[1].set_title('Exp')
    axs[1].imshow(img_exp, cmap='gray')
    plt.show()