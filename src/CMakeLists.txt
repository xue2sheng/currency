# this is the "object library" target: compiles the sources only once
file(GLOB SOURCES *.cpp)
file(GLOB EXTRA_SOURCES ../include/*.h *.hpp) # making happy Qt-Creator project tab
set(LIB_OBJECT_NAME "${LOCAL_CMAKE_PROJECT_NAME}_object")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_library(${LIB_OBJECT_NAME} OBJECT ${SOURCES} ${EXTRA_SOURCES})

# actual shared and static libraries built from the same object files
add_library(${LIB_STATIC_NAME} STATIC $<TARGET_OBJECTS:${LIB_OBJECT_NAME}>)
target_link_libraries(${LIB_STATIC_NAME} curl)

### Only if this the principal project 
if("${LOCAL_CMAKE_PROJECT_NAME}" STREQUAL "${CMAKE_PROJECT_NAME}")

  ### Install binaries
  install(TARGETS ${LIB_STATIC_NAME} ARCHIVE DESTINATION ${LIB_INSTALL_DIR})

  ### Install headers
  file(GLOB HEADERS ../include/*.h)
  install(FILES ${HEADERS} DESTINATION ${HEADERS_INSTALL_DIR})

endif()
