import numpy as np
import cv2
import matplotlib.pyplot as plt

# Define a funcao de transformacao;
def trans_linear_partes(img):
    r_min = np.min(img)
    r_max = np.max(img)
    diff = r_max - r_min
    img_out = (255/diff) * img - 255*r_min/diff
    return img_out

#Testa a funcao de transformacao
img = plt.imread("polen.tif")
img_out = trans_linear_partes(img)

# Plota lado a lado
fig, axs = plt.subplots(1, 2)
axs[0].axis('off')
axs[0].set_title('Original')
axs[0].imshow(img, cmap='gray', vmin=0, vmax=255)
axs[1].axis('off')
axs[1].set_title('Melhorada')
axs[1].imshow(img_out, cmap='gray', vmin=0, vmax=255)
plt.show()

