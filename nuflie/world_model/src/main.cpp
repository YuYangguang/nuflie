
#include "nuflie/world_model/world_model.h"

using namespace nuflie;
int main(int argc, char **argv)
{
    ROS_INFO("start world_model process");
    ros::Time::init();
    World_Model this_world_model(argc,argv,"world_model_node");
    ros::spin();
    return 0;
}
