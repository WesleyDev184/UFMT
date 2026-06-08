import numpy as np
import matplotlib.pyplot as plt

def log_transform(img):
    imgOut = img.astype(np.float64)
    imgOut = (255.0 / np.log(256)) * np.log(imgOut + 1)
    return imgOut.astype(np.uint8)

if __name__ == '__main__':
    # Le a imagem
    img = plt.imread('fractured_spine.tif')

    img_log = log_transform(img)

    # Plota lado a lado
    fig, axs = plt.subplots(1, 2)
    axs[0].axis('off')
    axs[0].set_title('Original')
    axs[0].imshow(img, cmap='gray')
    axs[1].axis('off')
    axs[1].set_title('Log')
    axs[1].imshow(img_log, cmap='gray')
    plt.show()
