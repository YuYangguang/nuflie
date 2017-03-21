cmake_minimum_required(VERSION 2.8.3)
project(nuflie_common)

set(CMAKE_BUILD_TYPE "Release")
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -pthread -fopenmp")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

find_package(catkin REQUIRED COMPONENTS
  message_filters
  message_generation
  roscpp
  rospy
  std_msgs
  std_srvs
  geometry_msgs
  keyboard
)


add_message_files(DIRECTORY msgs/world_model
FILES
position.msg
UAVMsg.msg
FeedbackMsg.msg
ConsensusType.msg
ConsensusMsg.msg
InstructionMsg.msg
WorldModelMsg.msg
)

add_service_files(DIRECTORY srv/world_model FILES )



add_message_files(DIRECTORY msgs/sensor_process
FILES
GPSMsg.msg
IMUMsg.msg
cameraMsg.msg
sonarMsg.msg
sensorMsg.msg
)

add_service_files(DIRECTORY srv/sensor_process FILES )
generate_messages(DEPENDENCIES std_msgs geometry_msgs keyboard)

set(nubot_common_includes
               ${catkin_INCLUDE_DIRS}
               ${PROJECT_SOURCE_DIR}/core/include 
)
include_directories(${nubot_common_includes})
catkin_package(
  INCLUDE_DIRS ${nubot_common_includes}
  INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/core/include
)
