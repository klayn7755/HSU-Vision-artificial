#Algoritmo de deteccion de colores
#Por Glar3
#www.robologs.net
#
#Detecta objetos verdes y amarillos
import RPi.GPIO as GPIO
import time
import cv2
import numpy as np

#Iniciar la camara
captura = cv2.VideoCapture(0)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(3, GPIO.OUT) #7
GPIO.setup(5, GPIO.OUT) #8

while(1):
    GPIO.output(3,False)  #Pin 7
    GPIO.output(5,False)  #Pin 8 
    #Capturamos una imagen y la convertimos de RGB -> HSV
    _, imagen = captura.read()
    hsv = cv2.cvtColor(imagen, cv2.COLOR_BGR2HSV)
  
    #Rango de colores detectados:
    #Verdes:
    verde_bajos = np.array([49,50,50], dtype=np.uint8)
    verde_altos = np.array([100, 255, 210], dtype=np.uint8)
    
    negro_bajos = np.array([0,0,0], dtype=np.uint8)
    negro_altos = np.array([90, 90, 90], dtype=np.uint8)
    #Amarillos:
    amarillo_bajos = np.array([16,76,72], dtype=np.uint8)
    amarillo_altos = np.array([30, 255, 210], dtype=np.uint8)
    
    rojo_bajos = np.array([120,55,55], dtype=np.uint8)
    rojo_altos = np.array([255, 240, 240], dtype=np.uint8)
  
    #Detectar los pixeles de la imagen que esten dentro del rango de verdes
    mascara_verde = cv2.inRange(hsv, verde_bajos, verde_altos)
    
    mascara_negro = cv2.inRange(hsv, negro_bajos, negro_altos)
     
    #Detectar los pixeles de la imagen que esten dentro del rango de amarillos
    mascara_amarillo = cv2.inRange(hsv, amarillo_bajos, amarillo_altos)
    
    mascara_rojo = cv2.inRange(hsv, rojo_bajos, rojo_altos)
  
    #Filtrar el ruido aplicando un OPEN seguido de un CLOSE
    kernel = np.ones((6,6),np.uint8)
    mascara_verde = cv2.morphologyEx(mascara_verde, cv2.MORPH_CLOSE, kernel)
    mascara_verde = cv2.morphologyEx(mascara_verde, cv2.MORPH_OPEN, kernel)
    mascara_amarillo = cv2.morphologyEx(mascara_amarillo, cv2.MORPH_CLOSE, kernel)
    mascara_amarillo = cv2.morphologyEx(mascara_amarillo, cv2.MORPH_OPEN, kernel)
    mascara_rojo = cv2.morphologyEx(mascara_rojo, cv2.MORPH_CLOSE, kernel)
    mascara_rojo = cv2.morphologyEx(mascara_rojo, cv2.MORPH_OPEN, kernel)
    mascara_negro = cv2.morphologyEx(mascara_negro, cv2.MORPH_CLOSE, kernel)
    mascara_negro = cv2.morphologyEx(mascara_negro, cv2.MORPH_OPEN, kernel)
    
    
    moments = cv2.moments(mascara_negro)
    area4 = moments['m00']
 
    #Descomentar para ver el area por pantalla

    #if(area > 2000000):
    if(area4 > 200000):
        
        print ("Se detecto NEGRO")
        
        
        
    moments = cv2.moments(mascara_verde)
    area = moments['m00']
 
    #Descomentar para ver el area por pantalla

    #if(area > 2000000):
    if(area > 200000):
        
        print ("Se detecto Verde")
        
        GPIO.output(3,True)  #Pin 7
        GPIO.output(5,True)  #Pin 8 
        
        
        
    moments = cv2.moments(mascara_amarillo)
    area2 = moments['m00']
 
    #Descomentar para ver el area por pantalla

    #if(area > 2000000):
    if(area2 > 200000):
        
        print ("Se detecto Amarillo")
        
        GPIO.output(3,False)  #Pin 7
        GPIO.output(5,True)  #Pin 8 

    moments = cv2.moments(mascara_rojo)
    area3 = moments['m00']
 
    #Descomentar para ver el area por pantalla

    #if(area > 2000000):
    if(area3 > 200000):
        
        print ("Se detecto rojo")
        GPIO.output(3,True)  #Pin 7
        GPIO.output(5,False) #Pin 8 
      
        
        
          
    
         
 #Unir las dos mascaras con el comando cv2.add()
    print ("")
    #mask = cv2.add(mascara_negro, mascara_negro)
 
    #Mostrar la imagen de la webcam y la mascara verde
    #cv2.imshow('verde y amarillo', mask)
    #cv2.imshow('Camara', imagen)
#     tecla = cv2.waitKey(5) & 0xFF
    #if tecla == 27:
     #   break
  
#cv2.destroyAllWindows()