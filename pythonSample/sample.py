import Jetson.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
GPIO.setup(33, GPIO.OUT)
GPIO.output(33, GPIO.HIGH)
time.sleep(5)
GPIO.output(33, GPIO.LOW)
GPIO.cleanup()