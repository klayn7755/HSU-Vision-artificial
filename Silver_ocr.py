import numba
from numba import jit
import numpy as np
import math
import random
import cv2 #imporntsmos open cv
import tensorflow as tf

@tf.function(jit_compile=True)
def Silver_ocr():
    import keras_ocr#importa keras-ocr
    from matplotlib import pyplot as plt#importa matplotlib
    import numpy as np#importa numpy
    from PIL import Image

    pipeline = keras_ocr.pipeline.Pipeline();

    images = [keras_ocr.tools.read(img) for img in [
        '/home/piocho/Desktop/foto.png'#lla la fotos y/o fotos
        ]
    ]

    print(np.shape(images))
 

    fig = plt.figure(figsize=(20, 10))

    rows = 1
    columns = 2

    Image3 = Image.open('/home/piocho/Desktop/foto.png')

    fig.add_subplot(rows, columns, 1)
    plt.imshow(Image3)
    plt.axis('off')
    plt.title("Image with text")

    prediction_groups = pipeline.recognize(images)
    mi_lista = []
    predicted_image_3 = prediction_groups[0]
    for text, box in predicted_image_3:
        print(text)

cap = cv2.VideoCapture(0)#llamamos a la camara

leido, frame = cap.read()#toma la foto

if leido == True:#si se tomo la foto
    cv2.imwrite("foto.png", frame)#guardala como foto.png
    print("Foto tomada correctamente")#e imprime foto tomada correctamente
else:#de lo contrario
    print("Error al acceder a la cámara")#imprime error en la camara

cap.release()#desactiva la camara

Silver_ocr()