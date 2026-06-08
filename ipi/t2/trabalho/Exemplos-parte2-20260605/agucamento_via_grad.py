import numpy as np
import matplotlib.pyplot as plt
import cv2

if __name__ == '__main__':
    img = cv2.imread('luisa-sonza.jpg')

    # filtros de sobel para calculo das derivadas parciais
    sobX = np.array([[-1, -2, -1],[0, 0, 0],[1, 2, 1]])
    sobY = np.array([[-1, 0, 1],[-2, 0, 2],[-1, 0, 1]])

    # Obtendo as derivadas parciais
    Gx = cv2.filter2D(img, cv2.CV_64F, sobX) # na direcao X (linhas)
    Gy = cv2.filter2D(img, cv2.CV_64F, sobY) # na direcao Y (colunas)

    mag = np.sqrt(Gx**2 + Gy**2) # magnitude do vetor gradiente
    
    # Aguçando a imagem
    img_agucada = img + 0.4 * mag
    img_agucada[img_agucada > 255] = 255
    img_agucada = img_agucada.astype(np.uint8)
    
    # Visualizando
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img_agucada = cv2.cvtColor(img_agucada, cv2.COLOR_BGR2RGB)
    
    fig,axl = plt.subplots(1,2)
    axl[0].imshow(img)
    axl[1].imshow(img_agucada)
    plt.show()


    
