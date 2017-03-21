
#include <ros/ros.h>
#include <semaphore.h>
#include "string"
#include <iostream>
#include <fstream>
#include <sstream>
#include <signal.h>
#include <boost/thread.hpp>
#include <nuflie/world_model/keyboard.h>
#include "nuflie/rtdb/rtdb_api.h"
#include "nuflie/rtdb/rtdb_user.h"
#include "nuflie/world_model/station2UAVInfo.h"
#include "nuflie/world_model/UAV2UAVInfo.h"
#include "nuflie/world_model/UAV2stationInfo.h"
#include "geometry_msgs/PoseStamped.h"
#include "stdio.h"
#include  "stdlib.h"
#include  "std_msgs/Float64.h"
#include <nuflie_common/WorldModelMsg.h>
#include <nuflie_common/ConsensusMsg.h>
#include <nuflie_common/ConsensusType.h>
#include <nuflie_common/FeedbackMsg.h>
#include <nuflie_common/InstructionMsg.h>
#include <std_msgs/Int32.h>
#include "nuflie/core/core.hpp"


namespace nuflie {
class World_Model
{

public:
    World_Model(int argc,char** argv,const char * name);
    ~World_Model();
    void update(const ros::TimerEvent& event); 
    void updateInstruction(void);
    void updateConsensus(std_msgs::Int32 msg);
    void updateFeedback(void);
    void updateLocalPos(const geometry_msgs::PoseStampedConstPtr& msg);
    void updateSetPos(const geometry_msgs::PoseStampedConstPtr& msg);
public:
    int  AgentID_;
    nuflie_common::WorldModelMsg world_model_info_;
    nuflie_common::InstructionMsg instruction_info_;
    nuflie_common::ConsensusMsg   consensus_info_;
    

/**************RTDB transfer variables*****************/
    station2UAVInfo  INSTRUCTION;
    UAV2UAVInfo      CONSENSUSSTATE;
    UAV2stationInfo  FEEDBACKSTATE;
/******************************************************/
public:
    //std::vector<ros::Publisher> teammatesinfo_;
    ros::Subscriber localPosSubsciber;    //receive local position of own
    ros::Subscriber setPosSubsciber;     //receive set position of own
    ros::Subscriber consensusSubscirber;  //receive consensus info of own

    ros::Publisher  instructionPublisher;    //transfer the instruction into topic form
    ros::Publisher  consensusPublisher;      //transfer the consensus into topic form
    ros::Publisher  worldmodelinfo_pub_;
    ros::Timer      worldmodel_update_timer_;
    boost::shared_ptr<ros::NodeHandle> nh;


   

};
}



