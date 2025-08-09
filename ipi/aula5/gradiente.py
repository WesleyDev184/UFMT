import numpy as np
import matplotlib.pyplot as plt
import cv2

if __name__ == '__main__':
    img = cv2.imread('luisa-sonza.jpg')

    #define os filtros de Sobel para calculo das derivadas parciais
    Gy = np.array([[-1,0,1],[-2,0,2],[-1,0,1]])
    Gx = np.array([[-1, -2, -1],[0, 0, 0],[1, 2, 1]])

    gx_img = cv2.filter2D(img, cv2.CV_64F, Gx)
    gy_img = cv2.filter2D(img, cv2.CV_64F, Gy)
    
    # Para vizualizacao da magnitude do vetor gradiente
    grad_mag = np.sqrt(gx_img**2 + gy_img**2)
    img_mag_grad = np.abs(grad_mag)
    img_mag_grad[img_mag_grad > 255] = 255
    img_mag_grad = img_mag_grad.astype(np.uint8)

    # Para vizualizacao das derivadas parciais
    gx_img = np.abs(gx_img)
    gx_img[gx_img > 255] = 255
    gx_img = gx_img.astype(np.uint8)

    gy_img = np.abs(gy_img)
    gy_img[gy_img > 255] = 255
    gy_img = gy_img.astype(np.uint8)

    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img_mag_grad = cv2.cvtColor(img_mag_grad, cv2.COLOR_BGR2RGB)
    gx_img = cv2.cvtColor(gx_img, cv2.COLOR_BGR2RGB)
    gy_img = cv2.cvtColor(gy_img, cv2.COLOR_BGR2RGB)
   
    
    fig,axl = plt.subplots(2,2)
    axl[0][0].imshow(img)
    axl[0][1].imshow(img_mag_grad)
    axl[1][0].imshow(gx_img)
    axl[1][1].imshow(gy_img)
    plt.show()
