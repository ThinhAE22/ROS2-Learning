cmake_minimum_required(VERSION 3.8)
project(action_server_client_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(action_tutorials_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)

# Added 
# Server
add_library(action_server SHARED
  src/fibonacci_action_server.cpp
)
target_include_directories(action_server PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_compile_definitions(action_server
  PRIVATE "ACTION_SERVER_CLIENT_CPP_BUILDING_DLL"
)
ament_target_dependencies(action_server
  "rclcpp"
  "rclcpp_action"
  "rclcpp_components"
  "action_tutorials_interfaces"
)
rclcpp_components_register_node(action_server
  PLUGIN "action_server_client_cpp::FibonacciActionServer"
  EXECUTABLE fibonacci_action_server
)
install(TARGETS 
  action_server
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Client
add_library(action_client SHARED
  src/fibonacci_action_client.cpp
)
target_include_directories(action_client PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_compile_definitions(action_client
  PRIVATE "ACTION_SERVER_CLIENT_CPP_BUILDING_DLL"
)
ament_target_dependencies(action_client
  "rclcpp"
  "rclcpp_action"
  "rclcpp_components"
  "action_tutorials_interfaces"
)
rclcpp_components_register_node(action_client
  PLUGIN "action_server_client_cpp::FibonacciActionClient"
  EXECUTABLE fibonacci_action_client
)
install(TARGETS 
  action_client
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)


# End Added

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
