cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

## Added 
#-----------------------------------------------------
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(custom_interfaces REQUIRED) #using with custom message node

#for pub
add_executable(talker src/publisher_member_function.cpp)
ament_target_dependencies(talker
  rclcpp
  #std_msgs
  custom_interfaces 
)

#for sub
add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(listener
  rclcpp
  #std_msgs
  custom_interfaces
)

# install targets
install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})
#-----------------------------------------------------
#END Added



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
