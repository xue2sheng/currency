# boost
if(EXISTS ${STATIC_BOOST})

  # static compilation for builtBoost libs
  set(Boost_NO_SYSTEM_PATHS TRUE)
  set(BOOST_ROOT "${STATIC_BOOST}")
  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
  set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
  set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_MULTITHREADED ON)
  set(Boost_USE_STATIC_RUNTIME ON)

else()

  # dynamic compilation for local libs
  set(Boost_USE_STATIC_LIBS OFF)
  set(Boost_USE_MULTITHREADED ON)
  set(Boost_USE_STATIC_RUNTIME OFF)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_TEST_DYN_LINK")

endif(EXISTS ${STATIC_BOOST})

message(STATUS "Using boost at ${BOOST_ROOT} with link_dir=${Boost_LIBRARY_DIRS}")
find_package( Boost 1.54.0 REQUIRED COMPONENTS unit_test_framework )
if(Boost_FOUND)

  # using Fixer.io
  set(LIB_PATH "${CMAKE_CURRENT_BINARY_DIR}/../src")
  file(GLOB SOURCES main.cpp)
  link_directories(${LIB_PATH} ${Boost_LIBRARY_DIRS})
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include ${Boost_INCLUDE_DIRS})
  add_executable(${TEST_NAME} ${SOURCES})
  add_dependencies(${TEST_NAME} ${LIB_STATIC_NAME})
  target_link_libraries(${TEST_NAME} ${LIB_STATIC_NAME} curl ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
  add_test(UnitTest ${TEST_NAME})

  ### Only if this the principal project ###
  if("${LOCAL_CMAKE_PROJECT_NAME}" STREQUAL "${CMAKE_PROJECT_NAME}")
     install(TARGETS ${TEST_NAME} RUNTIME DESTINATION ${TEST_INSTALL_DIR})
  endif()

  # Using fake mock for Fixer.io
  file(GLOB SOURCES_FAKE fake.cpp)
  link_directories(${LIB_PATH} ${Boost_LIBRARY_DIRS})
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include ${Boost_INCLUDE_DIRS})
  add_executable(${TEST_NAME}_fake ${SOURCES_FAKE})
  add_dependencies(${TEST_NAME}_fake ${LIB_STATIC_NAME} mock${LOCAL_CMAKE_PROJECT_NAME}) # mock needed so golang needed as well
  target_link_libraries(${TEST_NAME}_fake ${LIB_STATIC_NAME} curl ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
  add_test(FakeUnitTest ${TEST_NAME}_fake)

  ### Only if this the principal project ###
  if("${LOCAL_CMAKE_PROJECT_NAME}" STREQUAL "${CMAKE_PROJECT_NAME}")
     install(TARGETS ${TEST_NAME}_fake RUNTIME DESTINATION ${TEST_INSTALL_DIR})
  endif()

else()
   message(STATUS "Missing required Boost UNIT TEST framework library. Test building skipped")
endif(Boost_FOUND)
