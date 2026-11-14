#Detecta objetos naranja, elimina el ruido y busca su centro
import sys
import RPi.GPIO as GPIO
import time
import cv2
import numpy as np
 
#Iniciamos la camara
captura = cv2.VideoCapture(0)
GPIO.cleanup()
GPIO.setmode(GPIO.BOARD)
GPIO.setup(21,GPIO.OUT)
GPIO.setup(22,GPIO.OUT)
GPIO.setup(23,GPIO.OUT)
GPIO.setup(24,GPIO.OUT)

while(1):
     
    #Capturamos una imagen y la convertimos de RGB -> HSV
    _, imagen = captura.read()
    hsv = cv2.cvtColor(imagen, cv2.COLOR_BGR2HSV)
 
    #Establecemos el rango de colores que vamos a detectar
    #Ahora es el naranja
    #naranja_bajos = np.array([01,150,200], dtype=np.uint8)  #perfectos con camara de lap
    #naranja_altos = np.array([20, 255, 255], dtype=np.uint8)  #perfectos con camara de lap
    naranja_bajos = np.array([05,90,140], dtype=np.uint8)  #perfectos con camara USB azul
    naranja_altos = np.array([25, 255, 255], dtype=np.uint8)  #perfectos con camara USB azul
 
    #Crear una mascara con solo los pixeles dentro del rango de naranjas
    mask = cv2.inRange(hsv, naranja_bajos, naranja_altos)
 
    #Encontrar el area de los objetos que detecta la camara
    moments = cv2.moments(mask)
    area = moments['m00']
 
    #Descomentar para ver el area por pantalla
    print area
    #if(area > 2000000):
    if(area > 20000):
         
        #Buscamos el centro x, y del objeto
        x = int(moments['m10']/moments['m00'])
        y = int(moments['m01']/moments['m00'])
         
        #Mostramos sus coordenadas por pantalla
        print "x = ", x
        print "y = ", y
 
        #Dibujamos una marca en el centro del objeto
        cv2.rectangle(imagen, (x, y), (x+2, y+2),(0,0,255), 2)

        if (x<260):
            GPIO.output(21,False)
            GPIO.output(22,True)
            GPIO.output(23,False)
            GPIO.output(24,True)

        if (x>320):
            GPIO.output(21,True)
            GPIO.output(22,False)
            GPIO.output(23,True)
            GPIO.output(24,False)

        if (x==0):
            GPIO.output(21,False)
            GPIO.output(22,False)
            GPIO.output(23,False)
            GPIO.output(24,False)

        if (x>260 and x<320):
            GPIO.output(21,True)
            GPIO.output(22,False)
            GPIO.output(23,False)
            GPIO.output(24,True)
     
    #Mostramos la imagen original con la marca del centro y
    #la mascara
    cv2.imshow('mask', mask)
    cv2.imshow('Camara', imagen)
    tecla = cv2.waitKey(5) & 0xFF
    if tecla == 27:
        break
 
cv2.destroyAllWindows()