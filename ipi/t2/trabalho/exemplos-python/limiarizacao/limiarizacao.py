import numpy as np
import matplotlib.pyplot as plt

def limiariza(img, a, b):
    img_th = np.zeros(img.shape, dtype=np.uint8)
    img_th[(img > a) & (img < b)] = 255
    return img_th

if __name__ == '__main__':
    img = plt.imread("brigther_pollen.tif")
    img_out = limiariza(img, 180, 230)

     #plota lado a lado
    fig, axs = plt.subplots(1,2)
    axs[0].axis('off')
    axs[0].set_title('Original')
    axs[0].imshow(img, cmap = 'gray', vmin=0, vmax=255)
    axs[1].axis('off')
    axs[1].set_title('Equalizada')
    axs[1].imshow(img_out, cmap='gray', vmin=0, vmax=255)
    plt.show()
