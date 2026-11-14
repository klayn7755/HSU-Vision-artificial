import time
import picamera

with picamera.PiCamera() as picam:
    picam.start_preview()
    time.sleep(5)
    picam.capture('nombre.jpg')
    picam.stop_preview()
    picam.close()