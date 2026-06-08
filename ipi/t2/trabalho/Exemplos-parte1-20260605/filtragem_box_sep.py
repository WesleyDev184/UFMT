import numpy as np
import matplotlib.pyplot as plt
import cv2

def getBoxKernelxy(ksize):
    kernelx = np.ones((ksize,1))
    kernelx = (1.0/ksize) * kernelx
    kernely = np.ones((1, ksize))
    kernely = (1.0/ksize) * kernely
    return (kernelx, kernely)


if __name__ == '__main__':
    img = cv2.imread('cat_puppy.jpg')

    #define o kernel
    box_kernelx, box_kernely = getBoxKernelxy(35) 
    
    #faz a filtragem
    img_out = cv2.sepFilter2D(img, -1, box_kernelx, box_kernely)
    
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img_out = cv2.cvtColor(img_out, cv2.COLOR_BGR2RGB)

    fig, axl = plt.subplots(1,2)
    axl[0].set_title('Original')
    axl[0].imshow(img)
    axl[1].set_title('Suavizada')
    axl[1].imshow(img_out)

    plt.show()
