cmake_minimum_required(VERSION 2.8.3)

project(pea_car)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  urdf
  xacro
  gmapping
  map_server
  amcl
  move_base
)

catkin_package()

add_executable(pea_car_control
src/pea_car_control.cpp
)
add_executable(gazebo_control src/gazebo_control.cpp)
add_executable(controller_node src/controller_node.cpp)

catkin_install_python(PROGRAMS
  cv_test/yolo_detector.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


add_dependencies(pea_car_control ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(pea_car_control
${catkin_LIBRARIES}
)
target_link_libraries(gazebo_control ${catkin_LIBRARIES})
target_link_libraries(controller_node ${catkin_LIBRARIES})


include_directories(${catkin_INCLUDE_DIRS})


find_package(roslaunch)

foreach(dir config launch meshes urdf)
	install(DIRECTORY ${dir}/
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)
