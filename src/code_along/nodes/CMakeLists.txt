cmake_minimum_required(VERSION 3.8)
project(nodes)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)

add_library(my_component SHARED
  src/basic_node.cpp
)
target_compile_definitions(my_component
  PRIVATE "COMPOSITION_BUILDING_DLL"
)
ament_target_dependencies(my_component
  rclcpp
  rclcpp_components
)
rclcpp_components_register_nodes(
  my_component
  PLUGIN "my_component::MyClass"
  EXECUTABLE my_component_node
)
ament_export_targets(my_component)

install(
  TARGETS my_component
  EXPORT my_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install launch files
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
