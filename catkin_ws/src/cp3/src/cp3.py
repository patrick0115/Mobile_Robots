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
    state=0 #forward
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(touch_L , GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(touch_R , GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(touch_B , GPIO.IN, pull_up_down=GPIO.PUD_UP)
    rate = rospy.Rate(1) # 10hz

    while not rospy.is_shutdown():
#        if(GPIO.input(touch_L)==1):
        state=GPIO.input(touch_B)
#        elif(GPIO.input(touch_L)==1 & GPIO.input(touch_R)==0):
#            state=1 #left
#        elif(GPIO.input(touch_L)==0 & GPIO.input(touch_R)==1):
#            state=2 #right
#        else:
#            state=3 #back
        pub.publish(Int16(state))
        print(state)
        print('--------------')
        rate.sleep()


if __name__ == '__main__':
    main()       








   

