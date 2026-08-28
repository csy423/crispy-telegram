cmake_minimum_required(VERSION 3.0.2)
project(csy_car_description)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  urdf
  xacro
)

catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs urdf xacro
)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(keyboard_teleop src/keyboard_teleop.cpp)
target_link_libraries(keyboard_teleop ${catkin_LIBRARIES})

# 安装可执行文件
install(TARGETS keyboard_teleop
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
