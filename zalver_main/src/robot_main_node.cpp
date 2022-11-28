#include <ros/ros.h>
#include <math.h>
#include <std_msgs/Int32.h>

#include <darknet_ros_msgs/BoundingBox.h>
#include <motor_msgs/pwm.h>
#include <motor_msgs/rpm.h>
#include <motor_msgs/location.h>
#include <echo_tutorial/EchoDistance.h>
#include <zalver_main/state.h>
#include <zalver_main/trig.h>


int rate = 10;
int mode = 1;
//int set_rpm = 30;
int vel = 140;
int timer = 0;
int timera = 0;
int timerb = 0;
bool time_state = false;
bool turn_state = false;
int X_size = 0;
int X_size_state = 0;
int X_point = 0;
//float theta_position = 0;
//float search_theta = 0;
//bool theta_state = false;
bool detect_state = false;
bool track_state = false;
bool promotion_state = false;
bool next_level = false;

float sonic1 = 0;
float sonic2 = 0;
float sonic3 = 0;
float sonic4 = 0;
float sonic5 = 0;
float sonic6 = 0;
float son_thread = 40;
int sonic_pilter = 10;

float move_way = 0;

/*
float q1[10];
float q2[10];
float q3[10];
float q4[10];
float q5[10];
float q6[10];*/
float distance1 = 0;
float distance2 = 0;
float distance3 = 0;
float distance4 = 0;
float distance5 = 0;
float distance6 = 0;

ros::Publisher* motor_pwm;
motor_msgs::pwm PWM;

//ros::Publisher* motor_rpm;
//motor_msgs::rpm RPM;

ros::Publisher* robot_state;
zalver_main::state Robot_State;

zalver_main::trig straw_srv;

void bbox_callback(const darknet_ros_msgs::BoundingBox &bbox)
{
    //ROS_INFO("X_size %d", bbox.xmax-bbox.xmin);
    //ROS_INFO("X_point %d", (bbox.xmax+bbox.xmin)/2);
    
    X_size = bbox.xmax - bbox.xmin;
    X_point = (bbox.xmax + bbox.xmin)/2;
    
    detect_state = true;
    
    if(X_size > 350)
    {
        promotion_state = true;
    }
    
}


void location_callback(const motor_msgs::location &loc)
{
    move_way = sqrt((loc.x*loc.x) + (loc.y*loc.y));
    ROS_INFO("move_way : %f", move_way);
}




void sonic1_callback(const echo_tutorial::EchoDistance &echo1)
{   
    distance1 = echo1.Distance;
    //ROS_INFO("distance1 : %f", distance1);
    
}


void sonic2_callback(const echo_tutorial::EchoDistance &echo2)
{   
    distance2 = echo2.Distance;
    //ROS_INFO("distance2 : %f", distance2);
    
}



void sonic3_callback(const echo_tutorial::EchoDistance &echo3)
{   
    distance3 = echo3.Distance;
    //ROS_INFO("distance3 : %f", distance3);
    
}

/*
void sonic4_callback(const echo_tutorial::EchoDistance &echo4)
{   
    distance4 = echo4.Distance;
    //ROS_INFO("distance4 : %f", distance4);
    
}


void sonic5_callback(const echo_tutorial::EchoDistance &echo5)
{   
    distance5 = echo5.Distance;
    //ROS_INFO("distance5 : %f", distance5);
    
}


void sonic6_callback(const echo_tutorial::EchoDistance &echo6)
{   
    distance6 = echo6.Distance;
    //ROS_INFO("distance6 : %f", distance6);
    
}
*/


void Search_Mode()
{
    	    ROS_INFO("Search_mode");   // some only boxsize > size 
    	    Robot_State.Zalver_State = 1; // display & sound state
    	        
    	    if(X_size > 30) // person search?
    	    {
    	        ROS_INFO("Person Catch!");
    	        //PWM.pwm1 = 0;
    	        //PWM.pwm2 = 0;
    	        
    	        time_state = false;
    	        turn_state = false;
    	        mode = 3; // Tracking mode;
    	    }
    	    
    	    else
    	    {
    	        if(turn_state == false)	// turn right
    	        {
    	            if(time_state == false)
    	            {
    	                timera = timer;
    	                time_state = true;
    	            
    	                PWM.pwm1 = -85;
    	                PWM.pwm2 = -85;
    	            }
    	            else
    	            {
    	                if(timer-timera > rate*4)
    	                {
    	                    PWM.pwm1 = 0;
    	                    PWM.pwm2 = 0;
    	                    turn_state = true;
    	                    time_state = false;
    	                }
    	            }
    	        }
    	        else	// turn left
    	        {
    	            if(time_state == false)
    	            {
    	                timera = timer;
    	                time_state = true;
    	            
    	                PWM.pwm1 = 85;
    	                PWM.pwm2 = 85;
    	            }
    	            else
    	            {
    	                if(timer-timera > rate*4)
    	                {
    	                    PWM.pwm1 = 0;
    	                    PWM.pwm2 = 0;
    	                    turn_state = false;
    	                    time_state = false;
    	                }
    	            }
    	        }  
    	    }

}


/*
void Obstacle_Mode()
{
    
    if((distance1 > 0 && distance1 < 15) || (distance2 > 0 && distance2 < son_thread) || (distance3 > 0 && distance3 < son_thread) || (distance4 > 0 && distance4 < son_thread) || (distance5 > 0 && distance5 < 15) || (distance6 > 0 && distance6 < son_thread))
    {
        ROS_INFO("Obstacle mode");
        PWM.pwm1 = 0;
        PWM.pwm2 = 0;
        // speaker "please back step"
    }
    
    

    
    if(distance1 > 0 && distance1 < 30)
    {
        if(time_state == false)
        {
            timera = timer;
            time_state = true;
        }
        else
        {
            if(timer-timera > rate) // during time 
            {
                PWM.pwm1 = 0;
                PWM.pwm2 = 0;
        
            }
        
        }
        
    
        ROS_INFO("Obstacle mode");
        // speaker "please back step"
    }


}*/


void Tracking_Mode()
{
            ROS_INFO("Tracking mode");
            Robot_State.Zalver_State = 2;
    	    
    	    if(detect_state == true)
    	    {
    	    	//track_state = true;
    	        //ROS_INFO("yaho!");
    	        // tracking motor
    	        //ROS_INFO("distance5 = %f", distance5);
    	        
    	        X_size_state = X_size;
    	        
    	        if(X_size > 320)	// Promotion_Mode
    	        {
    	            PWM.pwm1 = 0;
    	            PWM.pwm2 = 0;
    	            
    	            promotion_state = true;
    	            next_level = false;
    	            mode = 5;
    	        }
    	        else
    	        {
    	        
    	        /*
    	            if((distance1 < son_thread) || (distance2 < son_thread) || (distance3 < son_thread) || (distance4 < son_thread) || (distance5 < son_thread))
    	            {
    	                PWM.pwm1 = 0;
    	                PWM.pwm2 = 0;
    	                ROS_INFO("obstacle!");
    	            
    	            }
    	            */
    	            
    	            if(distance1 < 30 || distance3 < 30)
    	            {
    	                PWM.pwm1 = 0;
    	                PWM.pwm2 = 0;
    	                ROS_INFO("obstacle!");
    	            
    	            }

    	            else
    	            {
    	            
    	            
    	            
    	                if(X_point > 240 && X_point <= 400)  // go center
    	                {
    	                    PWM.pwm1 = vel+10;
    	                    PWM.pwm2 = -vel+10;
    	                }
    	                else if(X_point > 160 && X_point <= 240) // go left_center
    	                {
    	                    PWM.pwm1 = vel+10;
    	                    PWM.pwm2 = -vel;
    	                }
    	                else if(X_point > 400 && X_point <= 480) // go right_center
    	                {
    	                    PWM.pwm1 = vel;
    	                    PWM.pwm2 = -vel-10;
    	                }
    	                else if(X_point > 480) // go right
    	                {
    	                    PWM.pwm1 = -85;
    	                    PWM.pwm2 = -85;
    	                }
    	                else if(X_point <= 160) // go left
    	                {
    	                    PWM.pwm1 = 85;
    	                    PWM.pwm2 = 85;
    	                }
    	                
    	                
    	                /*
    	                if(move_way > 500)
    	                {
    	                    PWM.pwm1 = 0;
    	                    PWM.pwm2 = 0;
    	                    mode =2;
    	                    time_state = false;
            	            X_size = 0;
    	                }
    	                */
    	            
    	            }
    	               
    	        }
    	       
    	        timera = timer;
    	        detect_state = false;
    	        // X_size = 0;
    	    }
    	    else // detect_state == false
    	    {   
    	        //ROS_INFO("detect %d", detect_state);
    	        if(X_size_state == X_size) // no person *************************************
    	        {
    	            //PWM.pwm1 = 0;
    	            //PWM.pwm2 = 0;
		    //ROS_INFO("pwm = 0");
    	        }
            	if(timer-timera > rate*1)
            	{
            	    mode = 1;
            	    time_state = false;
            	    X_size = 0;
            	                
            	}
            	
            }       
            //ROS_INFO("detect %d", detect_stae);
            //ROS_INFO("X_size_state %d", X_size_state);
            //ROS_INFO("X_size %d", X_size);l
            
}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "robot_main_node");
    ros::NodeHandle nh;
    ros::Rate loop_rate(rate);

    // client service
    ros::ServiceClient straw_client = nh.serviceClient<zalver_main::trig>("trig");

    // subscribe
    ros::Subscriber sub_bbox = nh.subscribe("max_bbox", 1000, bbox_callback);
    ros::Subscriber sub_location = nh.subscribe("current_location", 1000, location_callback);
    ros::Subscriber sub_sonic1 = nh.subscribe("/us1/echo_distance", 1000, sonic1_callback);
    ros::Subscriber sub_sonic2 = nh.subscribe("/us2/echo_distance", 1000, sonic2_callback);
    ros::Subscriber sub_sonic3 = nh.subscribe("/us3/echo_distance", 1000, sonic3_callback);
    
    //ros::Subscriber sub_sonic4 = nh.subscribe("/us4/echo_distance", 1000, sonic4_callback);
    //os::Subscriber sub_sonic5 = nh.subscribe("/us5/echo_distance", 1000, sonic5_callback);
    //ros::Subscriber sub_sonic6 = nh.subscribe("/us6/echo_distance", 1000, sonic6_callback);
                       
    //ros::Subscriber sub_location = nh.subscribe("location", 1000 location_callback);
    
    // publish
    ros::Publisher pub_motor_pwm = nh.advertise<motor_msgs::pwm>("pwm", 1000);
    motor_pwm = &pub_motor_pwm;
    
    //ros::Publisher pub_motor_rpm = nh.advertise<motor_msgs::rpm>("rpm", 1000);
    //motor_rpm = &pub_motor_rpm;
    
    
    
    
    ros::Publisher pub_robot_state = nh.advertise<zalver_main::state>("robot_state", 1000);
    robot_state = &pub_robot_state;
    
    
    
    ROS_INFO("ROBOT START");
    
    
    while(ros::ok())
    {
        //ros::Duration(2.0).sleep();
        timer++;
        //ROS_INFO("TIME %d", timer);
        //ROS_INFO("%d", PWM.pwm1);
        //ROS_INFO("%d", PWM.pwm2);
        //PWM.pwm1 = 0;
        //PWM.pwm2 = 0;
        //ROS_INFO("state : %d", Robot_State.Zalver_State);
        
        if(mode == 1)
    	{
    	    Search_Mode();  // try search person side to robot!
    	    
    	    /////straw client
            straw_srv.request.trig = 0;
            if(straw_client.call(straw_srv))
            {
                ROS_INFO("request trig : %d, response done : %d", straw_srv.request.trig, straw_srv.response.done);
            }
    	       	
    	}
    	else if(mode == 2)
    	{
    	    ROS_INFO("Boundary mode");
   	    
    	    if(time_state == false)
    	    {
                timera = timer;
                time_state = true;
                PWM.pwm1 = -vel;
                PWM.pwm2 = -vel;
            }
            else
            {
                if(timer-timera > rate*3)
                {
                    PWM.pwm1 = 0;
                    PWM.pwm2 = 0;
                    time_state = false;
                    
                    mode = 1;
                }
            }
    	    
    	    
    	}
    	else if(mode == 3)
    	{
    	    Tracking_Mode();
    	            

    	}	
    	else if(mode == 4)
    	{	
            ROS_INFO("Reset_base mode");                
    	}
    	else if(mode == 5)
    	{
            ROS_INFO("Promotion mode1");
            Robot_State.Zalver_State = 3;
            
            //ROS_INFO("promo %d", promotion_state);
            
            /////// next promotion
            if(next_level == false)
            {
                timerb = timer;
                next_level = true;
            }
            else
            {
                if(timer-timerb > rate*8)
                {
            	    mode = 6;
            	    time_state = false;
            	    next_level = false;
            	    promotion_state = true;
            	 }
            }
            
	    ////// return mode 1
            if(promotion_state == true)
    	    {
    	        timera = timer;
    	        promotion_state = false;
    	        X_size = 0;
    	        
    	        
    	    }
    	    else // detect_state == false
    	    {   
    	    
            	if(timer-timera > rate*5)
            	{
            	    mode = 1;
            	    time_state = false;
            	                
            	}
            }
                            
    	}
    	else if(mode == 6)
    	{
            ROS_INFO("Promotion mode2");
            Robot_State.Zalver_State = 4; 
            
            //ROS_INFO("promo %d", promotion_state);
            
            /////// next promotion
            if(next_level == false)
            {
                timerb = timer;
                next_level = true;
            }
            else
            {
                if(timer-timerb > rate*10)
                {
            	    mode = 7;
            	    time_state = false;
            	    next_level = false;
            	    promotion_state = true;
            	    
            	    /////straw client
            	    straw_srv.request.trig = 1;
            	    if(straw_client.call(straw_srv))
            	    {
            	        ROS_INFO("request trig : %d, response done : %d", straw_srv.request.trig, straw_srv.response.done);
            	    
            	    }
            	    
            	 }
            }
            
	    ////// return mode1
            if(promotion_state == true)
    	    {
    	        timera = timer;
    	        promotion_state = false;
    	        X_size = 0;
    	        
    	        
    	    }
    	    else // detect_state == false
    	    {   
    	    
            	if(timer-timera > rate*5)
            	{
            	    mode = 1;
            	    time_state = false;
            	                
            	}
            }
            
            
                            
    	}
    	
    	
    	else if(mode == 7)
    	{
            ROS_INFO("route information");
            Robot_State.Zalver_State = 5; // route information
            
            //ROS_INFO("promo %d", promotion_state);
            
            /////// next promotion
            if(next_level == false)
            {
                timerb = timer;
                next_level = true;
            }
            else
            {
                if(timer-timerb > rate*13)
                {
            	    mode = 1;
            	    time_state = false;
            	    next_level = false;
            	    promotion_state = true;
            	    Robot_State.Zalver_State = 1;
            	    robot_state -> publish(Robot_State);
            	    ros::Duration(15.0).sleep();
            	 }
            }
            
	    ////// return mode1
            if(promotion_state == true)
    	    {
    	        timera = timer;
    	        promotion_state = false;
    	        X_size = 0;
    	        
    	        
    	    }
    	    else // detect_state == false
    	    {   
    	    
            	if(timer-timera > rate*5)
            	{
            	    mode = 1;
            	    time_state = false;
            	    Robot_State.Zalver_State = 1;
            	    robot_state -> publish(Robot_State);
            	    ros::Duration(30.0).sleep();
            	                
            	}
            }
            
            
                            
    	}
    		
    
    
        motor_pwm -> publish(PWM);
        //motor_rpm -> publish(RPM);
        robot_state -> publish(Robot_State);
    	
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    
}




