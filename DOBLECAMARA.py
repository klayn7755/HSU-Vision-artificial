#Algoritmo de deteccion de colores
#Por Glar3
#www.robologs.net
#
#Detecta objetos verdes y amarillos
  
import cv2
import numpy as np
  
#Iniciar la camara
captura = cv2.VideoCapture(0)
captura2 = cv2.VideoCapture(2)
  
while(1):
      
    #Capturamos una imagen y la convertimos de RGB -> HSV
    _, imagen = captura.read()
    hsv = cv2.cvtColor(imagen, cv2.COLOR_BGR2HSV)
  
    #Rango de colores detectados:
    #Verdes:
    verde_bajos = np.array([49,50,50], dtype=np.uint8)
    verde_altos = np.array([100, 255, 210], dtype=np.uint8)
    #Amarillos:
    amarillo_bajos = np.array([16,76,72], dtype=np.uint8)
    amarillo_altos = np.array([30, 255, 210], dtype=np.uint8)
    
    rojo_bajos = np.array([120,55,55], dtype=np.uint8)
    rojo_altos = np.array([255, 240, 240], dtype=np.uint8)
  
    #Detectar los pixeles de la imagen que esten dentro del rango de verdes
    mascara_verde = cv2.inRange(hsv, verde_bajos, verde_altos)
     
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

    moments = cv2.moments(mascara_verde)
    area = moments['m00']
 
    #Descomentar para ver el area por pantalla
    print (area)
    #if(area > 2000000):
    if(area > 200000):
        
        print ("Se detecto Verde")
        
    moments = cv2.moments(mascara_amarillo)
    area2 = moments['m00']
 
    #Descomentar para ver el area por pantalla
    print (area2)
    #if(area > 2000000):
    if(area2 > 200000):
        
        print ("Se detecto Amarillo")
        

    moments = cv2.moments(mascara_rojo)
    area3 = moments['m00']
 
    #Descomentar para ver el area por pantalla
    print (area3)
    #if(area > 2000000):
    if(area3 > 200000):
        
        print ("Se detecto rojo")
    
     #Capturamos una imagen y la convertimos de RGB -> HSV
    _, imagen2 = captura2.read()
    hsv = cv2.cvtColor(imagen2, cv2.COLOR_BGR2HSV)
  
    #Rango de colores detectados:
    #Verdes:
    verde_bajos2 = np.array([49,50,50], dtype=np.uint8)
    verde_altos2 = np.array([100, 255, 210], dtype=np.uint8)
    #Amarillos:
    amarillo_bajos2 = np.array([16,76,72], dtype=np.uint8)
    amarillo_altos2 = np.array([30, 255, 210], dtype=np.uint8)
    
    rojo_bajos2 = np.array([120,55,55], dtype=np.uint8)
    rojo_altos2 = np.array([255, 240, 240], dtype=np.uint8)
  
    #Detectar los pixeles de la imagen que esten dentro del rango de verdes
    mascara_verde2 = cv2.inRange(hsv, verde_bajos2, verde_altos2)
     
    #Detectar los pixeles de la imagen que esten dentro del rango de amarillos
    mascara_amarillo2 = cv2.inRange(hsv, amarillo_bajos2, amarillo_altos2)
    
    mascara_rojo2 = cv2.inRange(hsv, rojo_bajos2, rojo_altos2)
  
    #Filtrar el ruido aplicando un OPEN seguido de un CLOSE
    kernel = np.ones((6,6),np.uint8)
    mascara_verde2 = cv2.morphologyEx(mascara_verde2, cv2.MORPH_CLOSE, kernel)
    mascara_verde2 = cv2.morphologyEx(mascara_verde2, cv2.MORPH_OPEN, kernel)
    mascara_amarillo2 = cv2.morphologyEx(mascara_amarillo2, cv2.MORPH_CLOSE, kernel)
    mascara_amarillo2 = cv2.morphologyEx(mascara_amarillo2, cv2.MORPH_OPEN, kernel)
    mascara_rojo2 = cv2.morphologyEx(mascara_rojo2, cv2.MORPH_CLOSE, kernel)
    mascara_rojo2 = cv2.morphologyEx(mascara_rojo2, cv2.MORPH_OPEN, kernel)

    moments = cv2.moments(mascara_verde2)
    areaC2 = moments['m00']
 
    #Descomentar para ver el area por pantalla
    
    #if(area > 2000000):
    if(areaC2 > 200000):
        
        print ("Se detecto Verde2")
        
    moments = cv2.moments(mascara_amarillo2)
    areaC22 = moments['m00']
 
    #Descomentar para ver el area por pantalla
    print (areaC22)
    #if(area > 2000000):
    if(areaC22 > 200000):
        
        print ("Se detecto Amarillo2")
        

    moments = cv2.moments(mascara_rojo2)
    areaC23 = moments['m00']
 
    #Descomentar para ver el area por pantalla
   
    #if(area > 2000000):
    if(areaC23 > 200000):
        
        print ("Se detecto rojo2")
    
         
     
 #Unir las dos mascaras con el comando cv2.add()
    
    '''mask = cv2.add(mascara_amarillo, mascara_verde)
 
    #Mostrar la imagen de la webcam y la mascara verde
    cv2.imshow('verde y amarillo', mask)
    cv2.imshow('Camara', imagen)
    tecla = cv2.waitKey(5) & 0xFF
    if tecla == 27:
        break'''
  
cv2.destroyAllWindows()