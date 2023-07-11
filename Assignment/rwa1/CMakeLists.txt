cmake_minimum_required(VERSION 3.8)
project(rwa1)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

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

# exercise1
add_executable(exercise1_exe src/exercise1.cpp)
ament_target_dependencies(exercise1_exe rclcpp std_msgs)

# exercise2
add_executable(exercise2_exe src/exercise2.cpp)
ament_target_dependencies(exercise2_exe rclcpp std_msgs)

# exercise3
add_executable(exercise3_exe src/exercise3.cpp)
ament_target_dependencies(exercise3_exe rclcpp std_msgs)

install(TARGETS
exercise1_exe
exercise2_exe
exercise3_exe
DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include DESTINATION share/${PROJECT_NAME})

ament_package()
