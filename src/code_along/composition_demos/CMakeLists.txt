cmake_minimum_required(VERSION 3.8)
project(composition_demos)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(example_interfaces REQUIRED)

include_directories(include)

add_library(client_component SHARED
  src/client_component.cpp
)
target_compile_definitions(client_component
  PRIVATE "COMPOSITION_DEMOS_BUILDING_DLL"
)
ament_target_dependencies(client_component
  "example_interfaces"
  "rclcpp_components"
  "rclcpp"
)
rclcpp_components_register_nodes(client_component "composition_demos::Client")

install(TARGETS
  client_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
