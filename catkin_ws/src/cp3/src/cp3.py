#!/usr/bin/env python

import rospy
import RPi.GPIO as GPIO
from std_msgs.msg import Int16

touch_L = 4 
touch_R = 14
touch_B = 15

def main():
    rospy.init_node('cp3')
    pub = rospy.Publisher('touch', Int16, queue_size = 10)
    state=4 #forward
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(touch_L , GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(touch_R , GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(touch_B , GPIO.IN, pull_up_down=GPIO.PUD_UP)

    while not rospy.is_shutdown():
        if(GPIO.input(touch_B)==0):
            state=0
            print(GPIO.input(touch_R))
            rospy.sleep(5)
        elif(GPIO.input(touch_L)==1 and GPIO.input(touch_R)==0 and GPIO.input(touch_B)==1):
            state=1 #turn left
            print(GPIO.input(touch_R))
            rospy.sleep(5)
        elif(GPIO.input(touch_L)==0 and GPIO.input(touch_R)==1 and GPIO.input(touch_B)==1):
            state=2 #turn right
            print(GPIO.input(touch_L))
            rospy.sleep(5)
        elif(GPIO.input(touch_L)==0 and GPIO.input(touch_R)==0 and GPIO.input(touch_B)==1):
            state=3 #back
            rospy.sleep(5)
        else:
            state=4 #forward
        pub.publish(Int16(state))

        print(state)
        print('--------------')
        rospy.sleep(0.5)
        

if __name__ == '__main__':
    main()       








   

