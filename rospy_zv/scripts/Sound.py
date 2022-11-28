#!/usr/bin/env python3
#-*- coding: utf-8 -*-

# import glob
import rospy
import os
import cv2
#import pygame
from playsound import playsound
from multiprocessing import Process
from cv2 import *
from zalver_main.msg import state
import time

behavior = 1

sound1 = '/home/ubuntu/catkin_ws/src/rospy_zv/scripts/sounds/1ment.ogg'
sound2 = '/home/ubuntu/catkin_ws/src/rospy_zv/scripts/sounds/2ment.ogg'
sound3 = '/home/ubuntu/catkin_ws/src/rospy_zv/scripts/sounds/3ment.ogg'
sound4 = '/home/ubuntu/catkin_ws/src/rospy_zv/scripts/sounds/4ment.ogg'

'''
play1 = Process(target=playsound, args=(sound1,))
play2 = Process(target=playsound, args=(sound2,))
play3 = Process(target=playsound, args=(sound3,))
play4 = Process(target=playsound, args=(sound4,))
'''

def Soundplayer():
    global behavior 
    print("behavior", behavior)
    
    sound1 = '/home/ubuntu/catkin_ws/src/rospy_zv/scripts/sounds/1ment.ogg'
    sound2 = '/home/ubuntu/catkin_ws/src/rospy_zv/scripts/sounds/2ment.ogg'
    sound3 = '/home/ubuntu/catkin_ws/src/rospy_zv/scripts/sounds/3ment.ogg'
    sound4 = '/home/ubuntu/catkin_ws/src/rospy_zv/scripts/sounds/4ment.ogg'


    while True:
        if behavior == 1:
            print("behavior:1")
            break

        elif behavior == 2:
            print("behavior:2")
            play1 = Process(target=playsound, args=(sound1,)) #7
            play1.start()
            play1.join()
            break

        elif behavior == 3:
            print("behavior:3")
            play2 = Process(target=playsound, args=(sound2,)) #8
            play2.start()
            play2.join()
            break

        elif behavior == 4:
            print("behavior:4")
            play3 = Process(target=playsound, args=(sound3,)) #10
            play3.start()
            play3.join()
            break
            
        elif behavior == 5:
            print("behavior:5")
            play4 = Process(target=playsound, args=(sound4,)) #13
            time.sleep(1)
            play4.start()
            play4.join()
            break
            

def callback(data):
    # rate = rospy.Rate(40)
    global behavior
    behavior = data.Zalver_State
    print("state-callback", behavior)
    



def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber('/robot_state', state, callback)
    rate = rospy.Rate(4)
    
    #Soundplayer()
    while not rospy.is_shutdown():
        Soundplayer()
        rate.sleep()


if __name__ == '__main__':
    listener()
 
    
