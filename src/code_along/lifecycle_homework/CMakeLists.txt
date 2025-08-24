cmake_minimum_required(VERSION 3.8)
project(lifecycle_homework)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(lifecycle_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(std_srvs REQUIRED)

include_directories(
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set(DEPENDENCIES
  rclcpp::rclcpp
  rclcpp_lifecycle::rclcpp_lifecycle
  rclcpp_components::component
  ${lifecycle_msgs_TARGETS}
  ${std_srvs_TARGETS}
)

# Manager Node
add_library(manager SHARED
  src/manager.cpp
)
target_compile_definitions(manager
  PRIVATE "COMPOSITION_BUILDING_DLL"
)
target_link_libraries(manager PRIVATE
  "${DEPENDENCIES}"
)

# Managed Node
add_library(managed_node SHARED
  src/managed_node.cpp
)
target_compile_definitions(managed_node
  PRIVATE "COMPOSITION_BUILDING_DLL"
)
target_link_libraries(managed_node PRIVATE
  "${DEPENDENCIES}"
)

rclcpp_components_register_nodes(manager "lifecycle_homework::Manager")
rclcpp_components_register_nodes(managed_node "lifecycle_homework::ManagedNode")

install(TARGETS manager
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(TARGETS managed_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME}/)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
