import numpy as np
import matplotlib.pyplot as plt
import cv2


if __name__ == '__main__':
    img = cv2.imread("lena_noise.jpg")

    img_out = cv2.medianBlur(img, 3)

    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img_out = cv2.cvtColor(img_out, cv2.COLOR_BGR2RGB)

    fig, axl = plt.subplots(1,2)
    axl[0].set_title('Original')
    axl[0].imshow(img)
    axl[1].set_title('Suavizada')
    axl[1].imshow(img_out)
    plt.show()
