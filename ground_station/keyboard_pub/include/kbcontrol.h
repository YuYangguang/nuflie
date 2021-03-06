
#include <termios.h>
#include <signal.h>
#include <math.h>
#include <stdio.h>

#include <stdlib.h>
#include <sys/poll.h>
#include <iostream>
#include <boost/thread/thread.hpp>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Int32.h>


class kbcontrol_node
{
private:

	double time_start_;
/*	
	//get data
    geometry_msgs::PoseStamped tag_get;
    ardrone_autonomy::Navdata navdata_get;
    geometry_msgs::PoseArray fouldTag_;
*/

	ros::NodeHandle n_;

	ros::Publisher keyboard_pub_;
	std_msgs::Empty emp_msg;
	bool bool_vel;
	
public:
	kbcontrol_node()
	{
		
		keyboard_pub_ = n_.advertise<std_msgs::Int32>("/keyboard", 1);//take off pub node
	
		bool_vel = false;

		
	}
	
	~kbcontrol_node() { }
	void keyboardLoop();
/*
	void autotrackcontrol();  //tracking
	void autolandcontrol();  // landing
    void keyboard_detect(char c);

   void getMarkerPose(geometry_msgs::PoseArray fouldTag){
                 fouldTag_.poses = fouldTag.poses;
        
	}

	void Tagpos_get(geometry_msgs::PoseStamped tag)
	{
          tag_get.pose.position.x=tag.pose.position.x;
          tag_get.pose.position.y=tag.pose.position.y;
          tag_get.pose.position.z=tag.pose.position.z;
          tag_get.pose.orientation.z=tag.pose.orientation.z;

	}

	void Navdata_callback(ardrone_autonomy::Navdata navdataPtr)
	{
         navdata_get.altd=navdataPtr.altd;

	}

*/


	void Publish(std_msgs::Int32 c)
	{
           keyboard_pub_.publish(c);

	}
	


	private:
	kbcontrol_node* tbk;


};


