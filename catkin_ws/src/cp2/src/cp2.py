#!/usr/bin/env python
import rospy
from std_msgs.msg import Int16


def main():
    rospy.init_node('cp2')
    pub = rospy.Publisher("dir_value", Int16, queue_size = 10)
    while not rospy.is_shutdown():
        rospy.sleep(3)
        try:
            dir_value= int(raw_input("user's right:"))
            pub.publish(Int16(dir_value))
        except ValueError:
            rospy.logerr("Invalid input, set default value 0")
            intput_value_R = 0
        rospy.sleep(3)
if __name__=="__main__":
    main()
