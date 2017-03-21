#include <stdio.h>
#include <signal.h>
#include <time.h>
#include "nuflie/world_model/world_model.h"
using namespace nuflie;

std::string num2str(int i)
{
        std::stringstream ss;
        ss<<i;
        return ss.str();
}

World_Model::World_Model(int argc,char** argv,const char * name)
{
    ros::init(argc,argv,name);
    int i;
    const char * environment;
    // 读取机器人标号，并赋值.
    if((environment = getenv("AGENT"))==NULL)
    {
        ROS_ERROR("this agent number is not read by robot");
        return;
    }
    AgentID_ = atoi(environment);
    std::string uav_name;
    std::string temp_str;
    temp_str=num2str(AgentID_);
    uav_name="uav"+temp_str;

    ROS_FATAL("world_model: UAV Number:%d",AgentID_);
    nh = boost::make_shared<ros::NodeHandle>(uav_name);
    /** 读取机器人标号并赋值. 在.bashrc中输入export AGENT=1，2，3，4，等等；*/
    if((environment = getenv("AGENT"))==NULL)
    {
        ROS_ERROR("this agent number is not read by robot");
        return ;
    }
    nh = boost::make_shared<ros::NodeHandle>();
    /** RTDB通信模块的初始化，开辟内存空间*/
    if(DB_init() != 0)
    {
        ROS_WARN("RTDB没有成功初始化内存空间");
        return;
    }

    localPosSubsciber = nh->subscribe("mavros/local_position/pose", 10, &World_Model::updateLocalPos,this);
    setPosSubsciber = nh->subscribe("mavros/setpoint_position/local", 10, &World_Model::updateSetPos,this);
    consensusSubscirber=nh->subscribe("angleCount",10, &World_Model::updateConsensus,this);
    instructionPublisher=nh->advertise<keyboard::Key>("/keyboard/keydown",10);
    worldmodelinfo_pub_ =  nh->advertise<nuflie_common::WorldModelMsg>("worldmodel/worldmodelinfo",10);
    /** 30ms触发一次的定时器 */
    worldmodel_update_timer_ = nh->createTimer(ros::Duration(0.015),&World_Model::update,this);
    consensus_info_.info.resize(UAV_NUM); //开辟内存空间；
    world_model_info_.consensusinfo.resize(UAV_NUM);
    world_model_info_.UAVinfo.resize(UAV_NUM);
    consensusPublisher=nh->advertise<nuflie_common::ConsensusMsg>("consensus_info",10);


}


World_Model::~World_Model()
{

    DB_free();  /** RTDB通信模块的释放开辟内存空间*/

}


void World_Model::update(const ros::TimerEvent& event)
{
    int i=0;
    int consensusCount=1;
    double lifetime;
    for(i=1;i<UAV_NUM+1;i++)
    {
      /**********************update the consensus information****************************/

       if(i==AgentID_)    //send the Anglecount Information
        {
            if(DB_put(UAV2UAVINFO,&consensus_info_.info[AgentID_]) == -1)      //send position infomation to ground station
            {
                return;
            }
        }
        else         //receive other nuflies' angleCount and publish
        {
            UAV2UAVInfo otherAngleCount;
            lifetime = DB_get(i,UAV2UAVINFO, &otherAngleCount);
            consensus_info_.info[AgentID_].angle.data=otherAngleCount.count;



        }
        world_model_info_.consensusinfo=consensus_info_.info;
       // consensusPublisher.publish(consensus_info_.info);

        /*******************************update the instruction information***************/
        updateInstruction();


        /******************************update the feedback information******************/
        updateFeedback();

        worldmodelinfo_pub_.publish(world_model_info_);   //publish

    }

}



void World_Model::updateInstruction(void)   //receive the instructions from ground station
{
   double lifetime; 
   double previousTimestamp=INSTRUCTION.timestamp;
   lifetime = DB_get(0,STATION2UAVINFO, &INSTRUCTION);
   if(previousTimestamp!=INSTRUCTION.timestamp)   //ensure the information is new
   {
       instruction_info_.keycode.header.stamp.fromNSec(INSTRUCTION.timestamp);
       instruction_info_.keycode.code=INSTRUCTION.code;
       instruction_info_.keycode.modifiers=INSTRUCTION.modifier;
       instructionPublisher.publish(instruction_info_.keycode);      //transfer the instruction into topic form
       world_model_info_.instructioninfo=instruction_info_;
   }

   else
   {
       return;
   }
}



void World_Model::updateConsensus(std_msgs::Int32 msg)
{
    consensus_info_.info[AgentID_].angle.data=msg.data;
}

void World_Model::updateFeedback(void)     //send the UAV state to ground station
{

    ros::Time  updatetime=ros::Time::now();
    FEEDBACKSTATE.timestamp=updatetime.toNSec();     //attach the timestamp to the sent information
    FEEDBACKSTATE.local_x=world_model_info_.UAVinfo[AgentID_].localPosition.x;
    FEEDBACKSTATE.local_y=world_model_info_.UAVinfo[AgentID_].localPosition.y;
    FEEDBACKSTATE.local_z=world_model_info_.UAVinfo[AgentID_].localPosition.z;
    FEEDBACKSTATE.set_x=world_model_info_.UAVinfo[AgentID_].setPosition.x;
    FEEDBACKSTATE.set_y=world_model_info_.UAVinfo[AgentID_].setPosition.y;
    FEEDBACKSTATE.set_z=world_model_info_.UAVinfo[AgentID_].setPosition.z;
    FEEDBACKSTATE.angleCount=consensus_info_.info[AgentID_].angle.data;
    if(DB_put(UAV2STATIONINFO, &FEEDBACKSTATE) == -1)      //send position infomation to ground station
    {
        return ;
    }
}


void World_Model::updateLocalPos(const geometry_msgs::PoseStampedConstPtr& msg)
{
    world_model_info_.UAVinfo[AgentID_].localPosition.x=msg->pose.position.x;
    world_model_info_.UAVinfo[AgentID_].localPosition.y=msg->pose.position.y;
    world_model_info_.UAVinfo[AgentID_].localPosition.y=msg->pose.position.y;
}



void World_Model::updateSetPos(const geometry_msgs::PoseStampedConstPtr& msg)
{
    world_model_info_.UAVinfo[AgentID_].setPosition.x=msg->pose.position.x;
    world_model_info_.UAVinfo[AgentID_].setPosition.y=msg->pose.position.y;
    world_model_info_.UAVinfo[AgentID_].setPosition.y=msg->pose.position.y;

}
