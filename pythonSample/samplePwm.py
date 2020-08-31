#!/usr/bin/env python

import RPi.GPIO as GPIO
import time

output_pin1 = 32
output_pin2 = 33

def main():
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(output_pin1, GPIO.OUT, initial=GPIO.HIGH)
    p1 = GPIO.PWM(output_pin1, 40)
    GPIO.setup(output_pin2, GPIO.OUT, initial=GPIO.HIGH)
    p2 = GPIO.PWM(output_pin2, 40)

    print("PWM running. Press CTRL+C to exit.")
    try:
        while True:
            p1.start(100)
            print("p1 start at 100%")
            time.sleep(1)
            p2.start(100)
            print("p2 start at 100%")
            time.sleep(1)
            p1.start(50)
            print("p1 start at 50%")
            time.sleep(1)
            p2.start(50)
            print("p2 start at 50%")
            time.sleep(1)
            p1.start(0)
            print("p1 start at 0%")
            time.sleep(1)
            p2.start(0)
            print("p2 start at 0%")
            time.sleep(1)
    finally:
        p1.stop()
        p2.stop()
        GPIO.cleanup()

if __name__ == '__main__':
    main()