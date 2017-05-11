############################
# version generated header #
############################
string(STRIP "${HUMAN_VERSION} ${GIT_PROJECT_NAME} ${GIT_BRANCH} ${GIT_COMMIT_HASH} (${HUMAN_SYNC_VERSION})[${DATETIME}] ${CMAKE_BUILD_TYPE} ${GIT_SYSTEM}" VERSION_INFO)

set(VERSION_VAR_NAME "${LOCAL_CMAKE_PROJECT_NAME}_VERSION")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/templates/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h @ONLY)

## some info
message(STATUS "VERSION_INFO: ${VERSION_INFO}")
message(STATUS "DOXYGEN_PROJECT_NUMBER: ${DOXYGEN_PROJECT_NUMBER}")

