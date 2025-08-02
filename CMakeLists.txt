cmake_minimum_required(VERSION 3.8)
project(dummy)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


set(PACKAGE_DEPENDENCIES
  behaviortree_ros2
)

find_package(ament_cmake REQUIRED)


foreach(Dependency IN ITEMS ${PACKAGE_DEPENDENCIES})
  find_package(${Dependency} REQUIRED)
endforeach()

# add_library adds a library
# add_executable used to add nodes
add_executable(bt_executor 
  src/bt_executor.cpp
)

ament_target_dependencies(bt_executor ${PACKAGE_DEPENDENCIES})


add_library(print_plugin SHARED 
  src/print.cpp 
)


set(PACKAGE_PLUGINS
  print_plugin
)

foreach(Plugin IN ITEMS ${PACKAGE_PLUGINS})
  target_compile_definitions(${Plugin}  PRIVATE BT_PLUGIN_EXPORT)
  ament_target_dependencies(${Plugin} ${PACKAGE_DEPENDENCIES})

  target_include_directories(${Plugin} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/dummy>
  )

  # install the plugin
  INSTALL(TARGETS
    ${Plugin}
    LIBRARY DESTINATION share/${PROJECT_NAME}/bt_plugins
    ARCHIVE DESTINATION share/${PROJECT_NAME}/bt_plugins
    RUNTIME DESTINATION share/${PROJECT_NAME}/bt_plugins
  )

endforeach()

install(
  DIRECTORY include/
  DESTINATION include/dummy
)

install(
  DIRECTORY config launch behavior_trees
  DESTINATION share/${PROJECT_NAME}
)


install(TARGETS
  bt_executor
  DESTINATION lib/${PROJECT_NAME}
)


ament_export_dependencies(${PACKAGE_DEPENDENCIES})

ament_package()
