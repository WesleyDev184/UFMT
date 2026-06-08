import numpy as np
import matplotlib.pyplot as plt
import cv2


if __name__ == '__main__':
    img = plt.imread('darker_pollen.tif')
    print(img.shape)
    #cv2.calcHist(images, channels, mask, bins, ranges)
    hist = cv2.calcHist([img], [0], None, [256], [0, 256])
    
    fig, axs = plt.subplots()
    axs.plot(np.arange(256), hist)
    plt.show()