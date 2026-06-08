import numpy as np
import matplotlib.pyplot as plt
import cv2

def getBoxKernel(ksize): # recebe o tamanho do kernel
    kernel = np.ones((ksize, ksize))
    kernel = (1.0/(ksize*ksize)) * kernel
    return kernel


if __name__ == '__main__':
    img = cv2.imread('cat_puppy.jpg') # BGR

    #define o kernel
    box_kernel = getBoxKernel(45) 
    
    #faz a filtragem
    img_out = cv2.filter2D(img, -1, box_kernel)
    
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB) # converter RGB
    img_out = cv2.cvtColor(img_out, cv2.COLOR_BGR2RGB) # converte para RGB

    fig, axl = plt.subplots(1,2)
    axl[0].set_title('Original')
    axl[0].imshow(img)
    axl[1].set_title('Suavizada')
    axl[1].imshow(img_out)

    plt.show()
