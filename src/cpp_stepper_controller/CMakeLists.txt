cmake_minimum_required(VERSION 3.8)
project(cpp_stepper_controller)

set(CMAKE_CPP_COMPILER gcc)

add_compile_options(-Wall -Wextra -Wpedantic -pthread)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.

find_library(PIGPIO_LIBRARY pigpio)
find_library(RT_LIBRARY rt)

file(GLOB SOURCES "src/*.cpp")


add_executable(cpp_stepper_controller ${SOURCES})
ament_target_dependencies(cpp_stepper_controller rclcpp std_msgs)
target_include_directories(cpp_stepper_controller PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(cpp_stepper_controller PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_link_libraries(cpp_stepper_controller ${PIGPIO_LIBRARY} ${RT_LIBRARY})



install(TARGETS cpp_stepper_controller
  DESTINATION lib/${PROJECT_NAME})
  
 

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
