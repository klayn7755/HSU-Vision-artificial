import RPi.GPIO
pin=7
GPIO.setmode (GPIO.BOARD)
GPIO.setup(pin, GPIO.OUT)
GPIO.output(pin, GPIO.HIGH) 
