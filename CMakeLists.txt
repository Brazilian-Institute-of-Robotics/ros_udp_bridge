cmake_minimum_required(VERSION 2.8.3)
project(udp_bridge)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package()

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

 add_executable(udp_bridge_receive src/udp_comm.cpp)
 add_executable(udp_bridge_send src/udp_send.cpp)
 target_link_libraries(udp_bridge_receive ${catkin_LIBRARIES}) 
 target_link_libraries(udp_bridge_send ${catkin_LIBRARIES})

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.hpp"
 # PATTERN ".svn" EXCLUDE
)