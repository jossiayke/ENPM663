cmake_minimum_required(VERSION 3.8)
project(rwa3)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(ariac_msgs REQUIRED)

include_directories(include)

# Publisher
add_executable(order_publisher_exe src/order_publisher.cpp)
ament_target_dependencies(order_publisher_exe rclcpp ariac_msgs)

# Subscriber
add_executable(order_subscriber_exe src/order_subscriber.cpp)
ament_target_dependencies(order_subscriber_exe rclcpp ariac_msgs)

install(TARGETS
order_publisher_exe
order_subscriber_exe
DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  include
  launch
  config
  DESTINATION share/${PROJECT_NAME}
)

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

ament_package()
