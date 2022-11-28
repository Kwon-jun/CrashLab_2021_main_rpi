cmake_minimum_required(VERSION 3.0.2)
project(zalver_main)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  darknet_ros_msgs
  motor_msgs
  echo_tutorial
)

## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   state.msg
   
 )

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   trig.srv
 )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
 generate_messages(
    DEPENDENCIES
#    darknet_ros_msgs
    std_msgs
#    motor_msgs	
 )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES zalver_main
#  CATKIN_DEPENDS darknet_ros_msgs roscpp std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(robot_main_node src/robot_main_node.cpp)
add_dependencies(robot_main_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(robot_main_node ${catkin_LIBRARIES})


