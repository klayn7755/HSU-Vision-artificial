from gpiozero import AngularServo
from time import sleep

servo =AngularServo(18, min_angle=0, max_angle=360, min_pulse_width=0.0000, max_pulse_width=0.0025)
i = 0
while (i < 3):
    
    servo.angle = 90
    sleep(0.41)
    servo.angle = 20
    sleep(0.41)
    i = i+1