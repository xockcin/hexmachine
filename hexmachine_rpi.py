#################################################
# Title: 
# hexmachine_rpi.py
#
# Description:
# That is, HexMachine, Raspberry Pi version.
# HexMachine is a machine with four buttons
# representing four binary digits, and one
# seven-segment display which shows the
# corresponding hexadecimal value. The original 
# version is a very simple Arduino sketch that 
# uses 11 GPIO pins, seven for the display and
# four for the buttons. This program differs from
# the original in two ways. First, it is for 
# Raspberry Pi instead of Arduino, and therefore
# is written in Python instead of C++. Second, it
# controls the display using a 74HC595 shift
# register chip instead of directly, which uses
# only 3 GPIO pins instead of 7.
#
# Note: Shift register elements are borrowed from:
# https://learn.pimoroni.com/tutorial/170pt-projects/the-shift-register-170pt

#!/usr/bin/env python3

import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)

PIN_DATA = 22
PIN_LATCH = 27
PIN_CLOCK = 17
GPIO.setup(PIN_DATA, GPIO.OUT)
GPIO.setup(PIN_LATCH, GPIO.OUT)
GPIO.setup(PIN_CLOCK, GPIO.OUT)

BUTTONS = [5, 6, 13, 19]
DIGITS = [0x3f, 0x09, 0x5e, 0x5b, 0x69, 0x73, 0x77, 0x19, 0x7f, 0x7b, 0x7d, 0x67, 0x36, 0x4f, 0x76, 0x74]
STATE = 0

for i in range(3):
    GPIO.setup(BUTTONS[i], GPIO.OUT)

def shiftout(number):
    GPIO.output(PIN_LATCH, 0)
    for i in range(8):
        GPIO.output(PIN_DATA, (number >> i) & 1)
        GPIO.output(PIN_CLOCK, 1)
        GPIO.output(PIN_CLOCK, 0)
    GPIO.output(PIN_LATCH, 0)

while True:
    number = 0

    for i in range(3):
    STATE = GPIO.input(BUTTONS[i])
    if STATE == True:
        number += 1<<i

    shiftout(DIGITS[number])
