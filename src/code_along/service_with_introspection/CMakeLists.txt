cmake_minimum_required(VERSION 3.8)
project(service_with_introspection)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(server src/server.cpp)
target_link_libraries(server PRIVATE
  rclcpp::rclcpp
  ${example_interfaces_TARGETS}
)

add_executable(client src/client.cpp)
target_link_libraries(client PRIVATE
  rclcpp::rclcpp
  ${example_interfaces_TARGETS}
)

install(TARGETS client server
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
