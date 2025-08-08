import numpy as np
import matplotlib.pyplot as plt
import cv2

img = cv2.imread('./images/m2.jpeg')

l, c, canal = img.shape
w_nova = int(l * 2)
h_nova = int(c * 2)
img_nova = cv2.resize(img, (h_nova, w_nova), interpolation=cv2.INTER_CUBIC)

fig, ax = plt.subplots(1, 2, figsize=(10, 5))
ax[0].set_title('Original Image')
ax[0].imshow(img)
ax[0].axis('off')
ax[1].set_title('Resized Image')
ax[1].axis('off')
ax[1].imshow(img_nova)
plt.show()