#!/usr/bin/env python

import rospy
import RPi.GPIO as GPIO
from std_msgs.msg import Int16

touch_L = 4 
touch_R = 14
touch_B = 15

def main():
    rospy.init_node('cp4')
    pub = rospy.Publisher('touch', Int16, queue_size = 10)
 #   rospy.Subscriber("light_value", Int16, cb_light , queue_size=1)
    rospy.Subscriber("ir_value", Int16, cb_ir , queue_size=1)

    state=4 #forward
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(touch_L , GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(touch_R , GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(touch_B , GPIO.IN, pull_up_down=GPIO.PUD_UP)

    while not rospy.is_shutdown():
        if(GPIO.input(touch_B)==0):
            state=0
            print("buttom")
            pub.publish(Int16(state))
            rospy.sleep(5)
        elif(GPIO.input(touch_L)==1 and GPIO.input(touch_R)==0 and GPIO.input(touch_B)==1):
            state=1 #turn left
            print("turn left")
            pub.publish(Int16(state))
            rospy.sleep(5)
        elif(GPIO.input(touch_L)==0 and GPIO.input(touch_R)==1 and GPIO.input(touch_B)==1):
            state=2 #turn right
            print("turn right")
            pub.publish(Int16(state))
            rospy.sleep(5)
        elif(GPIO.input(touch_L)==0 and GPIO.input(touch_R)==0 and GPIO.input(touch_B)==1):
            state=3 #back
            print("go back")
            pub.publish(Int16(state))
            rospy.sleep(5)
        else:
            state=4 #forward
            print("go straight")
            pub.publish(4)
            rospy.sleep(3)
        rospy.sleep(0.1)
   #     rospy.spin()        


def cb_ir(msg_i):
    rospy.loginfo(rospy.get_caller_id() + "ir value is %d", msg_i.data)



def cb_light(msg_l):
    rospy.loginfo(rospy.get_caller_id() + "light value is %d", msg_l.data)

if __name__ == '__main__':
    main()       








   

