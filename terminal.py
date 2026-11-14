from PIL import Image
from pytesseract import *

pytesseract.tesseract_cmd= r'C:\Users\kevin\AppData\Local\Programs\Tesseract-OCR\tesseract.exe'

img=Image.open("Prueba.jpg")

resultado=pytesseract.image_to_string(img,lang='spa')

print(resultado)
