import keras_ocr
from matplotlib import pyplot as plt

pipeline = keras_ocr.pipeline.Pipeline();

images = [keras_ocr.tools.read(img) for img in [
    '/home/piocho/Desktop/foto.png'
    ]
]
import numpy as np
print(np.shape(images))
 
from PIL import Image
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
    
'''if(len(mi_lista) == 0):
    print('No text')

else:
    print(text)'''