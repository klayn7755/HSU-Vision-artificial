import serial
import time

ser = serial.Serial('COM1',9600)
time.sleep(2)

while True:
    ser.write(b"LED1 on\n")
    time.sleep(1)

    while ser.in_waiting>0:
        received_data=ser.readline().decode('utf-8').rstrip()
        print(f"received:{received_data}")

    time.sleep(0.5)
ser.close()

