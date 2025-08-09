import numpy as np
import matplotlib.pyplot as plt
import cv2

if __name__ == '__main__':
    img = cv2.imread('luisa-sonza.jpg')

    #define um kernel laplaciano
    kernel = np.array([[1,1,1],[1,-8,1],[1,1,1]])

    laplaciana = cv2.filter2D(img, cv2.CV_64F, kernel)
    
    # Vizualização 1: laplaciana normalizada
    min = np.min(laplaciana)
    lap_norm = laplaciana - min
    max = np.max(lap_norm)
    lap_norm = (lap_norm / max) * 255
    lap_norm = np.round(lap_norm)
    lap_norm = lap_norm.astype(np.uint8)

    # Vizualização 2: valor absoluto
    lap_abs = np.abs(laplaciana)
    lap_abs[lap_abs > 255] = 255
    lap_abs = lap_abs.astype(np.uint8)


    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    lap_norm = cv2.cvtColor(lap_norm, cv2.COLOR_BGR2RGB)
    lap_abs = cv2.cvtColor(lap_abs, cv2.COLOR_BGR2RGB)
    
    fig,axl = plt.subplots(1,3)
    axl[0].imshow(img)
    axl[1].imshow(lap_norm)
    axl[2].imshow(lap_abs)
    plt.show()
