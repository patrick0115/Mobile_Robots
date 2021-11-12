#!/usr/bin/env python
import rospy
from std_msgs.msg import Int16


def main():
    rospy.init_node('cp2')
    pub_R = rospy.Publisher("pwm_value_R", Int16, queue_size = 10)
    pub_L = rospy.Publisher("pwm_value_L", Int16, queue_size = 10)
    while not rospy.is_shutdown():
        rospy.sleep(3)
        try:
            input_value_R= int(raw_input("user's right:"))
            pub_R.publish(Int16(input_value_R))
        except ValueError:
            rospy.logerr("Invalid input, set default value 0")
            intput_value_R = 0
        try:
            input_value_L = int(raw_input("user's left:"))
            pub_L.publish(Int16(input_value_L))
        except ValueError:
            rospy.logerr("Invalid input, set default value 0")
            intput_value_L = 0

        rospy.sleep(3)
if __name__=="__main__":
    main()
