cmake_minimum_required(VERSION 2.8.3)
project(nuflie_sensor)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")

#set(CMAKE_BUILD_TYPE "Release")
#if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")
#else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
#    set(CMAKE_BUILD_TYPE "Release")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -pthread -fopenmp")
#endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

find_package(catkin REQUIRED COMPONENTS
  cmake_modules
  message_generation
  roscpp
  rospy
  std_msgs
  std_srvs
  world_model
)

find_package(Eigen REQUIRED)

add_message_files(FILES

 )

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS message_generation
	         roscpp 
	         rospy  
		 std_msgs 
		 std_srvs 
		 DEPENDS
)

set(NuFlie_sensor_includes
               ${catkin_INCLUDE_DIRS}
               ${EIGEN_INCLUDE_DIRS}
               ${PROJECT_SOURCE_DIR}/include
)

include_directories(${NuFlie_sensor_includes})

add_executable(NuFlie_sensor_node src/main.cpp
                                  src/IMU.cpp
                                  src/Camera.cpp
                                  src/GPS.cpp
                                  src/info_fuse.cpp
                                  src/Sonar.cpp

)
add_dependencies(NuFlie_sensor_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(NuFlie_sensor_node
   ${catkin_LIBRARIES}
 )


