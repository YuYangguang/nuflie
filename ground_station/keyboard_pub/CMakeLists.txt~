cmake_minimum_required(VERSION 2.8.3)

project(keyboard_pub)


find_package(catkin REQUIRED COMPONENTS
  ardrone_autonomy
  dynamic_reconfigure
  geometry_msgs
  roscpp
  sensor_msgs
  std_msgs

)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})





catkin_package(
   INCLUDE_DIRS include
   LIBRARIES tkb
   CATKIN_DEPENDS  ardrone_autonomy roscpp sensor_msgs std_msgs geometry_msgs dynamic_reconfigure

)




include_directories(include ${catkin_INCLUDE_DIRS})

#FILE(GLOB_RECURSE sourcefiles "src/*.cpp")
#add_executable(kbcontrol_node ${sourcefiles} )

add_executable(kbcontrol src/kbcontrol.cpp)
target_link_libraries(kbcontrol  ${catkin_LIBRARIES} ${Boost_LIBS})
add_dependencies(kbcontrol nudt_ardrone_generate_messages_cpp)



