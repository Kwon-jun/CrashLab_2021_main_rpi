#include <ros/ros.h>
#include <std_msgs/Int16.h>
#include <darknet_ros_msgs/BoundingBox.h>

int a = 2;

void NumberCallback(const darknet_ros_msgs::BoundingBox &bbox)
{   
    if(a==0)
    {
        ROS_INFO("box_Xsize %d", bbox.xmax-bbox.xmin);
        
    }
    else
    {
        ROS_INFO("box_Xmid %d", (bbox.xmax+bbox.xmin)/2);
    }
    
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "cam_sub_node");
    ros::NodeHandle nh;

    ros::Subscriber sub_number = nh.subscribe("max_bbox", 10, NumberCallback);
    
    
    ros::spin();
}
