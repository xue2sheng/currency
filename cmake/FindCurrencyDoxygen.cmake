#####################
### Documentation ###
#####################

# maybe QT needed for documentation .qch 
# Get the higher version if possible
if(EXISTS $ENV{QT_GCC_64_DIR})
     set(LOCAL_QT_GCC_64_DIR "$ENV{QT_GCC_64_DIR}")
elseif(EXISTS /opt/Qt/5.8/gcc_64)
     set(LOCAL_QT_GCC_64_DIR "/opt/Qt/5.8/gcc_64")
elseif(EXISTS /opt/Qt/5.7/gcc_64)
     set(LOCAL_QT_GCC_64_DIR "/opt/Qt/5.7/gcc_64")
elseif(EXISTS /home/$ENV{USER}/Qt/5.8/gcc_64)
     set(LOCAL_QT_GCC_64_DIR "/home/$ENV{USER}/Qt/5.8/gcc_64")
elseif(EXISTS /home/$ENV{USER}/Qt/5.7/gcc_64)
     set(LOCAL_QT_GCC_64_DIR "/home/$ENV{USER}/Qt/5.7/gcc_64")
else()
     message(STATUS "Qt library directory not found")
endif()
message(STATUS "Local Qt gcc_64: ${LOCAL_QT_GCC_64_DIR}")

# General Doxygen template info
set(DOXYGEN_PROJECT_NAME "${LOCAL_CMAKE_PROJECT_NAME}")
set(DOXYGEN_INCLUDE_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(DOXYGEN_SRC_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(DOXYGEN_TEST_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/test")
set(DOXYGEN_MOCK_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/mock")
set(DOXYGEN_MAINPAGE_INPUT "${CMAKE_CURRENT_SOURCE_DIR}")
set(DOXYGEN_IMAGE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/images")

# qt creator help generator location
if(EXISTS ${COMPILATIONDEP}/tools/qhelpgenerator)
    set(QT_HELP_GENERATOR "${COMPILATIONDEP}/tools/qhelpgenerator")
elseif(EXISTS ${LOCAL_QT_GCC_64_DIR}/bin/qhelpgenerator)
    set(QT_HELP_GENERATOR "${LOCAL_QT_GCC_64_DIR}/bin/qhelpgenerator")
else()
    message(STATUS "Missing QT help generator")
endif()

# Qt Doxygen template info
if(EXISTS ${QT_HELP_GENERATOR})
    message(STATUS "Generating QT Help")
 set(DOXYGEN_GENERATE_QHP "YES")
 set(DOXYGEN_QT_AUTOBRIEF "YES")
 set(DOXYGEN_QCH_FILE "${LOCAL_CMAKE_PROJECT_NAME}.qch")
 set(DOXYGEN_QHP_NAMESPACE "ad.chameleon.${LOCAL_CMAKE_PROJECT_NAME}")
 set(DOXYGEN_QHP_VIRTUAL_FOLDER "${LOCAL_CMAKE_PROJECT_NAME}.vrt")
 set(DOXYGEN_QHP_CUST_FILTER_NAME "${LOCAL_CMAKE_PROJECT_NAME}")
 set(DOXYGEN_QHP_CUST_FILTER_ATTRS "${LOCAL_CMAKE_PROJECT_NAME}")
 set(DOXYGEN_QHP_SECT_FILTER_ATTRS "${LOCAL_CMAKE_PROJECT_NAME}")
 set(DOXYGEN_QHG_LOCATION "${QT_HELP_GENERATOR}")
else()
    message(STATUS "Skipping QT Help")
 set(DOXYGEN_GENERATE_QHP "NO")
 set(DOXYGEN_QT_AUTOBRIEF "NO")
endif()

# Doxygen version info
string(STRIP "${HUMAN_VERSION}_${GIT_COMMIT_HASH}_${FILE_SYNC_VERSION}" DOXYGEN_PROJECT_NUMBER)

# Create the configuration file out of its template
find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/templates/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc${LOCAL_CMAKE_PROJECT_NAME} ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating API documentation with Doxygen" VERBATIM)
        add_custom_target(installDoc${LOCAL_CMAKE_PROJECT_NAME}
                COMMAND ${CMAKE_COMMAND} -E echo "Copying Doxygen pages to ${DOC_INSTALL_DIR}/html"
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_BINARY_DIR}/html ${DOC_INSTALL_DIR}/html
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Deploying Doxygen documentation" VERBATIM)
        add_dependencies(installDoc${LOCAL_CMAKE_PROJECT_NAME} doc${LOCAL_CMAKE_PROJECT_NAME})
endif(DOXYGEN_FOUND)

