#!/usr/bin/env python

import rospy
import RPi.GPIO as GPIO
from std_msgs.msg import Bool
from std_msgs.msg import Int16
from time import sleep

touch_pin = 4 

def main():
    rospy.init_node('cp3')

    pub = rospy.Publisher('cp3_topic', Bool, queue_size = 10)

    GPIO.setmode(GPIO.BCM)
    GPIO.setup(touch_pin , GPIO.IN, pull_up_down=GPIO.PUD_UP)
    while not rospy.is_shutdown():
        while True:
             print(GPIO.input(touch_pin))
             print('--------------')
             rospy.sleep(0.5)


if __name__ == '__main__':
    main()       








   

