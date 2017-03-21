cmake_minimum_required(VERSION 2.8.3)
project(px4_controller)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  mavros
  mavros_extras
  geometry_msgs
  tf2_ros
  eigen_conversions
  angles
  message_generation
  world_model
  nuflie_common
  
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(Boost REQUIRED COMPONENTS system)

find_package(Eigen3)
if(NOT EIGEN3_FOUND)
  # Fallback to cmake_modules
  find_package(cmake_modules REQUIRED)
  find_package(Eigen REQUIRED)
  set(EIGEN3_INCLUDE_DIRS ${EIGEN_INCLUDE_DIRS})
  set(EIGEN3_LIBRARIES ${EIGEN_LIBRARIES})
endif()

add_message_files(
   FILES
   count.msg
   download.msg
   upload.msg
)

generate_messages( 
    DEPENDENCIES 
    geometry_msgs
    std_msgs
    
)
include(EnableCXX11)






catkin_package(
)

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${EIGEN_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)


add_executable(px4_control_node
  src/circle_bodyaxis.cpp)
target_link_libraries(px4_control_node 
                     
   ${catkin_LIBRARIES}
   ${Boost_LIBRARIES}
 )



