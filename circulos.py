import numpy as np
import cv2
import cv2.cv as cv
import picamera
import time

with picamera.PiCamera() as picam:
    picam.start_preview()
    time.sleep(2)
    picam.capture('figuras.jpg')
    #captura = cv2.VideoCapture(1)
    #_, imagen = captura.read()
    #time.sleep(2)
    img = cv2.imread("figuras.jpg") # Cargamos la imagen
    img = cv2.medianBlur(img,5)
    cimg = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    
    
    circles = cv2.HoughCircles(cimg,cv.CV_HOUGH_GRADIENT,1,10,np.array([]),40,80,5,100)
    
    circles = np.uint16(np.around(circles))
    
    for i in circles[0,:]:
        cv2.circle(cimg,(i[0],i[1]),i[2],(0,255,0),2)
        cv2.circle(cimg,(i[0],i[1]),2,(0,0,255),3)
            
    picam.stop_preview()
    picam.close()
    cv2.imshow("circulos", cimg)
    cv2.waitKey(0)
    cv2.destroyAllWindows()