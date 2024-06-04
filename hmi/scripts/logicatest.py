#!/usr/bin/env python

import rospy
from std_msgs.msg import String, UInt16



def button_callback(msg):
    button1 = bool(msg.data & 0b0001)
    button2 = bool(msg.data & 0b0010)
    button3 = bool(msg.data & 0b0100)
    button4 = bool(msg.data & 0b1000)
    

    rospy.loginfo(msg.data)
    if msg.data != 4:
        if   msg.data != 3:
            if  msg.data != 1:
                if msg.data == 2:
                    led_control_pub.publish("RUN")
                    rospy.loginfo("RUN2")
                    rospy.sleep(0.1)   
                else:
                    led_control_pub.publish("NIKS")
                    rospy.loginfo("NIKS")
                    rospy.sleep(0.1)
            elif msg.data == 1:
                led_control_pub.publish("RUN")
                rospy.loginfo("RUN")
                rospy.sleep(0.1)
        if msg.data == 3 :
            led_control_pub.publish("STOP")
            rospy.loginfo("STOP1")
            rospy.sleep(0.1)
    elif msg.data == 4:
        led_control_pub.publish("STOP")
        rospy.loginfo("STOP2")
        rospy.sleep(0.1)
    

def main():
    global led_control_pub
    rospy.init_node("button_listener")
    rospy.Subscriber("button_states", UInt16, button_callback)
    led_control_pub = rospy.Publisher("led_control", String, queue_size=10)
    rospy.spin()

if __name__ == '__main__':
    main()
