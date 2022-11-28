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

behavior = [1,1]

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
    print("current behavior", behavior)
    
    sound1 = '/home/ubuntu/catkin_ws/src/rospy_zv/scripts/sounds/1ment.ogg'
    sound2 = '/home/ubuntu/catkin_ws/src/rospy_zv/scripts/sounds/2ment.ogg'
    sound3 = '/home/ubuntu/catkin_ws/src/rospy_zv/scripts/sounds/3ment.ogg'
    sound4 = '/home/ubuntu/catkin_ws/src/rospy_zv/scripts/sounds/4ment.ogg'

    play1 = Process(target=playsound, args=(sound1,)) #7
    play2 = Process(target=playsound, args=(sound2,)) #8
    play3 = Process(target=playsound, args=(sound3,)) #10
    play4 = Process(target=playsound, args=(sound4,)) #13
    
    while True:
        if behavior[-1] == 1:
            print("behavior:1")
            break

        if behavior[-1] == 2:
            if behavior[0] != 2:
                if play1.is_alive():
                    play1.terminate()
                continue
            print("behavior:2")
            play1.start()
            play1.join()
            break

        if behavior[-1] == 3:
            if behavior[0] == 3:
                if play2.is_alive():
                    play2.terminate()
                continue
            print("behavior:3")
            play2.start()
            play2.join(9)
            if play2.is_alive():
                play2.terminate()
            break

        if behavior[-1] == 4:
            if behavior[0] == 4:
                if play3.is_alive():
                    play3.terminate()
                continue
            print("behavior:4")

            play3.start()
            play3.join(11)
            if play3.is_alive():
                play3.terminate()
            break
            
        if behavior[-1] == 5:
            if behavior[0] == 5:
                if play4.is_alive():
                    play4.terminate()
                continue
            print("behavior:5")
            
            play4.start()
            play4.join(14)
            if play4.is_alive():
                play4.terminate()
            break
            

def callback(data):
    # rate = rospy.Rate(40)
    global behavior
    behavior.append(data.Zalver_State)
    behavior.pop(0)
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
 
    
