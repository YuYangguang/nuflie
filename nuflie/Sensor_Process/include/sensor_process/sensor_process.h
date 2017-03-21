#include <stdio.h>
#include <sensor_process/camera.h>
#include <sensor_process/GPS.h>
#include <sensor_process/IMU.h>
#include <sensor_process/sonar.h>
#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <nuflie_common/sensorMsg.h>
namespace nuflie {
class sensor_process
{
public:
    sensor_process(int argc,char** argv,const char * name);
    ~sensor_process();

public:
    ros::Publisher  sensorInfo_pub_;
    ros::Timer      sensor_update_timer_;
    boost::shared_ptr<ros::NodeHandle> nh;
    nuflie_common::sensorMsg  sensorInfo;
    void sensorFuse();
    void update(const ros::TimerEvent& event);

/*****************here is for GPS********************/
    GPSInfo GPS;
    ros::Subscriber GPSSubscriber;
    void GPSReceived(const std_msgs::Int32ConstPtr& data);   //receive data from driver package

/********************here is for camera**************/
    cameraInfo camera;
    ros::Subscriber imageSubscriber;
    void imageReceived(const std_msgs::Int32ConstPtr& data);  //receive data from driver package

/********************here is for IMU**************/
    IMUInfo IMU;
    ros::Subscriber IMUSubscriber;
    void IMUReceived(const std_msgs::Int32ConstPtr& data);    //receive data from driver package

/********************here is for sonar**************/
    SonarInfo sonar;
    ros::Subscriber sonarSubscriber;
    void sonarReceived(const std_msgs::Int32ConstPtr& data);   //receive data from driver package

};


}

