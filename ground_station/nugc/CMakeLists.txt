cmake_minimum_required(VERSION 2.8.3)
project(nugc)

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
  cmake_modules
  dynamic_reconfigure
  message_filters
  rospy
  std_srvs
  nuflie_common
  world_model

)

#find_package(world_model )

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(Boost REQUIRED COMPONENTS system)
find_package(Eigen REQUIRED)

find_package(Threads)
find_package(Eigen3)
if(NOT EIGEN3_FOUND)
  # Fallback to cmake_modules
  find_package(cmake_modules REQUIRED)
  find_package(Eigen REQUIRED)
  set(EIGEN3_INCLUDE_DIRS ${EIGEN_INCLUDE_DIRS})
  set(EIGEN3_LIBRARIES ${EIGEN_LIBRARIES})
endif()

set(nugc_includes
               include
               ${catkin_INCLUDE_DIRS}
               ${Boost_INCLUDE_DIRS}
               ${EIGEN_INCLUDE_DIRS}
               /include

)

include_directories(${nugc_includes})

include(EnableCXX11)


catkin_package(
)

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${EIGEN_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)


add_executable(nugc_node
 src/main.cpp
  src/nugc.cpp)
target_link_libraries(nugc_node 
                     
   ${catkin_LIBRARIES}
   ${Boost_LIBRARIES}
   world_model
    rtdb
   multicast
 )



