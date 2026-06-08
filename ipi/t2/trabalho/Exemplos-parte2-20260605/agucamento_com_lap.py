import numpy as np
import cv2
import matplotlib.pyplot as plt


if __name__ == '__main__':
    img = cv2.imread('luisa-sonza.jpg')
    
    # Suavização para eliminar pequenos ruídos
    img_blur = cv2.GaussianBlur(img, (3,3), 0)

    # Calculo da laplaciana da imagem
    kernel_lap = np.array([[1,1,1],[1,-8,1],[1,1,1]])
    laplaciana = cv2.filter2D(img_blur, cv2.CV_64F, kernel_lap)

    # Fazendo o agucamento das bordas
    c = -3.0
    img_out = img + c*laplaciana 
    img_out[img_out < 0] = 0
    img_out[img_out > 255] = 255
    img_out = img_out.astype(np.uint8)

    # Conversão para plotagem
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img_out = cv2.cvtColor(img_out, cv2.COLOR_BGR2RGB)
    
    # Plotagem
    fig, axl = plt.subplots(1,2)
    axl[0].imshow(img)
    axl[1].imshow(img_out)
    plt.show()
