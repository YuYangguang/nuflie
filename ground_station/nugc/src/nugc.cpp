#include <nugc.h>
#include <std_msgs/Int32.h>

using namespace nuflie;
int end=0;
//nuflie::Key code;
// *************************
//   signal catch
// *************************


std::string num2str(int i)
{
        std::stringstream ss;
        ss<<i;
        return ss.str();
}


void sendCommand(const keyboard::Key &key)
{
    station2UAVInfo instruction;
    instruction.timestamp=key.header.stamp.toNSec();  //attach the timestamp
    ROS_INFO("timestamp is %f",instruction.timestamp);
    instruction.code=key.code;
    instruction.modifier=key.modifiers;
    if(DB_put(STATION2UAVINFO, &instruction) == -1)   //send the instructions
    {
        return;
    }
}


void nugc::update(const ros::TimerEvent& event)
{
    int lifetime;
    int i=0;
    for(i=0;i<UAV_NUM;i++)
    {
        double previousTimestamp=FEEDBACKSTATE.timestamp;
        lifetime = DB_get(i+1,UAV2STATIONINFO, &FEEDBACKSTATE);  //receive the flight state from nuflie
        geometry_msgs::PoseStamped localPosition;
        geometry_msgs::PoseStamped setPosition;
        std_msgs::Int32 consensusInfo;

        if(FEEDBACKSTATE.timestamp!=previousTimestamp)     //the information is new
        {
            /****receive the local position and publish it*************/
            localPosition.header.stamp.fromNSec(FEEDBACKSTATE.timestamp);
            localPosition.pose.position.x=FEEDBACKSTATE.local_x;
            localPosition.pose.position.x=FEEDBACKSTATE.local_y;
            localPosition.pose.position.x=FEEDBACKSTATE.local_z;
            localPositionPublisher[i].publish(localPosition);

           /****receive the set position and publish it*************/
            setPosition.header.stamp.fromNSec(FEEDBACKSTATE.timestamp);
            setPosition.pose.position.x=FEEDBACKSTATE.set_x;
            setPosition.pose.position.x=FEEDBACKSTATE.set_y;
            setPosition.pose.position.x=FEEDBACKSTATE.set_z;
            setPositionPublisher[i].publish(setPosition);


            /****receive the consensus information and publish it*************/
            consensusInfo.data=FEEDBACKSTATE.angleCount;
            consensusPublisher[i].publish(consensusInfo);


        }

        /*******************deal with the consensus information***************/


    }

}

nugc::~nugc()
{

    DB_free();  /** RTDB通信模块的释放开辟内存空间*/

}

nugc::nugc(int argc,char** argv,const char * name)
{

    ros::init(argc,argv,"nugc");

    const char * environment;
    nodeHandle= boost::make_shared<ros::NodeHandle>("nugc");
    nugc_update_timer_=nodeHandle->createTimer(ros::Duration(0.015),&nugc::update,this);
    commandSubscriber = nodeHandle->subscribe("/keyboard/keydown",10,sendCommand);
    double lifetime;
    int i=0;


    if((environment = getenv("AGENT"))==NULL)
    {
        ROS_ERROR("this agent number is not read by robot");
        return ;
    }
    if(DB_init() != 0)
    {
        ROS_WARN("RTDB doesn't init successfully");
        return ;
    }
    AgentID_ = atoi(environment);



    for(i=0;i<UAV_NUM;i++)    //initilize the name for publishers
    {
        std::string temp_str;
        temp_str=num2str(i+1);
        localPositionTopic[i]= "/nuflie0" + temp_str+ "/mavros/local_position/pose";
        localPositionPublisher[i]=nodeHandle->advertise<geometry_msgs::PoseStamped>(localPositionTopic[i],10);

        setPositionTopic[i]= "/nuflie0" + temp_str+ "/setpoint_position/local";
        setPositionPublisher[i]=nodeHandle->advertise<geometry_msgs::PoseStamped>(setPositionTopic[i],10);

        consensusTopic[i]="/nuflie0" + temp_str+ "/angleCount";
        consensusPublisher[i]=nodeHandle->advertise<std_msgs::Int32>(consensusTopic[i],10);

    }

   
}
