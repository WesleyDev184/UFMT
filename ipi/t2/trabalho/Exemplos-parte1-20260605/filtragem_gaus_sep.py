import numpy as np
import matplotlib.pyplot as plt
import cv2

def getGaussKernelxy(ksize, sigma):
    kernel = cv2.getGaussianKernel(ksize, sigma) # vetor coluna
    return (kernel, kernel.T) # dois kernels lineares (clununa e linha), 
                              # amostrados de uma gaussiana


if __name__ == '__main__':
    img = cv2.imread('cat_puppy.jpg')

    #define o kernel
    gauss_kernelx, gauss_kernely = getGaussKernelxy(61, 10.0) 
    
    #faz a filtragem
    img_out = cv2.sepFilter2D(img, -1, gauss_kernelx, gauss_kernely) # faz a convolucao com
                                                                     # kernel separavel
    
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img_out = cv2.cvtColor(img_out, cv2.COLOR_BGR2RGB)

    fig, axl = plt.subplots(1,2)
    axl[0].set_title('Original')
    axl[0].imshow(img)
    axl[1].set_title('Suavizada')
    axl[1].imshow(img_out)

    plt.show()
