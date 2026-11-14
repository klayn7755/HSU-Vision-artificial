import pytesseract
from PIL import Image

pytesseract.pytesseract.tesseract_cmd=r'C:\Users\Alumno OT\AppData\Local\Programs\Tesseract-OCR\tesseract.exe'

image_path='imagen.png'
img=Image.open(image_path)
text=pytesseract.image_to_string(img)
with open("texto_extraido.txt","w")as file:
    file.write(text)