cmake_minimum_required(VERSION 2.8.3)
project(udp_comm)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package()

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

 add_executable(udp_comm_node src/udp_class.cpp)
 target_link_libraries(udp_comm_node ${catkin_LIBRARIES}) 

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.hpp"
 # PATTERN ".svn" EXCLUDE
)