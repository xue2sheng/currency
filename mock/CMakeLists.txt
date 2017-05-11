find_program(LOCAL_GO_COMPILER go HINTS /home /usr)
message(STATUS "Go compiler: ${LOCAL_GO_COMPILER}")

if(EXISTS ${LOCAL_GO_COMPILER})
 add_custom_target(mock${LOCAL_CMAKE_PROJECT_NAME} ${LOCAL_GO_COMPILER} build -o ${LOCAL_CMAKE_PROJECT_NAME}_mock ${CMAKE_CURRENT_SOURCE_DIR}/main.go)

 ### Only if this the principal project ###
 if("${LOCAL_CMAKE_PROJECT_NAME}" STREQUAL "${CMAKE_PROJECT_NAME}")
     install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_CMAKE_PROJECT_NAME}_mock DESTINATION ${MOCK_INSTALL_DIR})
 endif()

else(EXISTS ${LOCAL_GO_COMPILER})

  add_custom_target(mock${LOCAL_CMAKE_PROJECT_NAME} echo "No golang compiler means no mock${LOCAL_CMAKE_PROJECT_NAME}")

endif(EXISTS ${LOCAL_GO_COMPILER})
