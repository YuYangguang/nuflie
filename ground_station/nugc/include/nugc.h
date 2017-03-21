#include <iostream>
#include <fstream>
#include <sstream>
#include <signal.h>
#include <ros/ros.h>
#include <boost/thread.hpp>
#include <nuflie/world_model/station2UAVInfo.h>
#include <nuflie/world_model/UAV2stationInfo.h>
#include <nuflie/rtdb/rtdb_user.h>
#include <nuflie/rtdb/rtdb_api.h>
#include <geometry_msgs/PoseStamped.h>
#include <stdio.h>
#include <std_msgs/Float64.h>
#include <keyboard.h>
#include <nuflie/core/core.hpp>


namespace nuflie {
class nugc
{

public:
    nugc(int argc,char** argv,const char * name);
    ~nugc();
    void update(const ros::TimerEvent& event);

public:
    int  AgentID_;

/**************RTDB transfer variables*****************/
    station2UAVInfo  INSTRUCTION;
    UAV2stationInfo  FEEDBACKSTATE;
/******************************************************/
public:
    ros::Publisher localPositionPublisher[UAV_NUM];   //local position publish
    std::string localPositionTopic[UAV_NUM];

    ros::Publisher setPositionPublisher[UAV_NUM];    //SetPosition publish
    std::string setPositionTopic[UAV_NUM];

    ros::Publisher  consensusPublisher[UAV_NUM];   //consensus information publish
    std::string     consensusTopic[UAV_NUM];

    ros::Timer      nugc_update_timer_;
    ros::Subscriber commandSubscriber; 
    boost::shared_ptr<ros::NodeHandle> nodeHandle;


   

};
}



