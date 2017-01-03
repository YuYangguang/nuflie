#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/tf.h>
#include <std_srvs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int32.h>



int key;
geometry_msgs::PoseStamped goal_;


void key_Callback(const std_msgs::Int32ConstPtr &key_)
{
  key = key_->data;

  switch (key_->data)
     {

          case 113:   //q
          {
              ROS_INFO_STREAM("up");
              goal_.pose.position.z += 0.05;
              break;

          }
        case 97:   //a
        {
          ROS_INFO_STREAM("down");
          goal_.pose.position.z -= 0.05;

          break;
        }
          case 106:  //j
          {
              ROS_INFO_STREAM("left");
              goal_.pose.position.x += 0.05;

              break;
          }
          case 108:   //l
          {
              ROS_INFO_STREAM("right");
              goal_.pose.position.x -= 0.05;

              break;
          }
        case 105:  //i
        {
          ROS_INFO_STREAM("forward");
          goal_.pose.position.y-= 0.051;
          break;
        }
        case 107: //k
        {
          ROS_INFO_STREAM("backward");
          goal_.pose.position.y += 0.05;

          break;
        }
        /*case 117:  //u
        {
          ROS_INFO_STREAM("rotate left");
          goal_.pose.position.y -= 0.1;
          goal_publisher_.publish(goal_);
          break;
        }
        case 111:  //o
        {
          ROS_INFO_STREAM("rotate right");
          vs.twist.angular.z -= 1;
          break;
        }*/





         default:
          {

          }

     }
}
int main(int argc, char **argv)
{
  std::string worldFrame;
  std_srvs::Empty srv1;
  std_srvs::Empty srv2;
  std_srvs::Empty srv3;

  ros::Subscriber key_subscriber_;
  ros::Publisher goal_publisher_;
  ros::Subscriber px4_pose;


  int flag =0;

  ros::init(argc, argv, "nuflie01_control_node");
  
  ros::NodeHandle n;
  
  key_subscriber_ = n.subscribe<std_msgs::Int32>("/keyboard", 50, key_Callback);
  goal_publisher_ = n.advertise<geometry_msgs::PoseStamped>("nuflie01/goal", 50);
  n.param<std::string>("worldFrame", worldFrame, "/world");

 /******************Set the Initial Target Point****************/
  goal_.pose.position.x = 0;
  goal_.pose.position.y = 0;
  goal_.pose.position.z = 1.6;
  tf::Quaternion q;
  q = tf::createQuaternionFromRPY(0,0,0);
  tf::quaternionTFToMsg(q, goal_.pose.orientation);

/***************************************************************/


   ros::Rate loop_rate(2);
   while (ros::ok())
  {
       if(key==50)      //number 2  take off
       {
         ros::ServiceClient takeoff_client = n.serviceClient<std_srvs::Empty>("nuflie01/takeoff");
         takeoff_client.call(srv1);
         key=0;
       }

     if(key==54)      //number 6 landing
       {
         ros::ServiceClient land_client = n.serviceClient<std_srvs::Empty>("nuflie01/land");
         land_client.call(srv2);
         key=0;
       }
     if(key==48)
     {
         ros::ServiceClient emergency_client = n.serviceClient<std_srvs::Empty>("nuflie01/emergency");
         emergency_client.call(srv3);
         key=0;

     }

     else if(flag != 1)
     {
       //goal_.header.seq +=1;

       goal_.header.stamp =ros::Time::now();
       goal_.header.frame_id= worldFrame;

       goal_publisher_.publish(goal_);
       //ROS_INFO("Hovering2!");
     }
   ros::spinOnce();
      
   loop_rate.sleep();
  }

  return 0;
}
