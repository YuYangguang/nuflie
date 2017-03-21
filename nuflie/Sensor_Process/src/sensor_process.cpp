#include <sensor_process/sensor_process.h>

using namespace nuflie;
sensor_process::sensor_process(int argc,char** argv,const char * name)
{
    ros::init(argc,argv,name);
    nh = boost::make_shared<ros::NodeHandle>();
    sensorInfo_pub_ =  nh->advertise<nuflie_common::sensorMsg>("sensor_process/sensorInfo",10);
    /** 30ms触发一次的定时器 */
    sensor_update_timer_ = nh->createTimer(ros::Duration(0.015),&sensor_process::update,this);
}

sensor_process::~sensor_process()
{
}

void sensor_process::sensorFuse()
{

}



void sensor_process::GPSReceived(const std_msgs::Int32ConstPtr &data)
{

}

void sensor_process::imageReceived(const std_msgs::Int32ConstPtr &data)
{

}

void sensor_process::IMUReceived(const std_msgs::Int32ConstPtr &data)
{

}

void sensor_process::sonarReceived(const std_msgs::Int32ConstPtr &data)
{

}


void sensor_process::update(const ros::TimerEvent &event)
{
    sensorFuse();
    sensorInfo_pub_.publish(sensorInfo);
}
