cmake_minimum_required(VERSION 3.8)
project(av_camera)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

include_directories(include)

# camera1
add_executable(camera1_exe src/camera1.cpp)
ament_target_dependencies(camera1_exe rclcpp std_msgs sensor_msgs)

# camera2
add_executable(camera2_exe src/camera2.cpp)
ament_target_dependencies(camera2_exe rclcpp std_msgs sensor_msgs)

# camera3
add_executable(camera3_exe src/camera3.cpp)
ament_target_dependencies(camera3_exe rclcpp std_msgs sensor_msgs)

# camera4
add_executable(camera4_exe src/camera4.cpp)
ament_target_dependencies(camera4_exe rclcpp std_msgs sensor_msgs)

install(TARGETS
camera1_exe
camera2_exe
camera3_exe
camera4_exe
DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  include 
  launch 
  DESTINATION share/${PROJECT_NAME})

# Install Python modules
ament_python_install_package(${PROJECT_NAME})

# # Install Python executables
# install(PROGRAMS
#   #nodes/parameter_demo_exe.py
#   DESTINATION lib/${PROJECT_NAME}
# )

ament_package()
