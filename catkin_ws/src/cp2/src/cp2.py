#!/usr/bin/env python
import rospy
from std_msgs.msg import Int16

def main():
    rospy.init_node('cp2')
    pub_r = rospy.Publisher("right_pwm", Int16, queue_size = 10)
    pub_l = rospy.Publisher("left_pwm", Int16, queue_size = 10)
    while not rospy.is_shutdown():
        try:
            pwm_r = int(raw_input("user's right:"))
        except ValueError:
            rospy.logerr("Invalid input, set default value 0")
            pwm_r = 0
        try:
            pwm_l = int(raw_input("user's left:"))
        except ValueError:
            rospy.logerr("Invalid input, set default value 0")
            pwm_l = 0
        pub_r.publish(Int16(pwm_r))
        pub_l.publish(Int16(pwm_l))
        rospy.sleep(6.5)
if __name__=="__main__":
    main()
