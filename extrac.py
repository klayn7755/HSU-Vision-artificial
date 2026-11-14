import cv2 
import numpy as np

image=cv2.imread('imagen.png')
gray=cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

canny=cv2.Canny(gray,10,150)
canny=cv2.dilate(canny, None,iterations=1)

cnts=cv2.findContours(canny, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]
cnts= sorted(cnts, key=cv2.contourArea, reverse=True)[:1]

for c in cnts:
    epsilon=0.01*cv2.arcLength(c,True)
    approx=cv2.approxPolyDP(c,epsilon,True)
    print=('approx=',approx)

cv2.imshow('image',image)
cv2.imshow('canny',canny)
cv2.waitKey(0)
cv2.destroyAllWindows()