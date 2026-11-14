import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
GPIO.setup(3, GPIO.OUT)
GPIO.setup(5, GPIO.OUT)


GPIO.output(3,False)  #Pin 7
GPIO.output(5,False)  #Pin 8 
#time.sleep(5)
#GPIO.output(3, True)
#GPIO.output(5 , True)
#time.sleep(5)
    
    