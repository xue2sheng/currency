################
# Version info #
################
string(TIMESTAMP FILE_SYNC_VERSION "%Y_%m_%d_%H_%M" UTC)
string(REPLACE "_" "'" HUMAN_SYNC_VERSION ${FILE_SYNC_VERSION})
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/Version.txt" HUMAN_VERSION)
string(STRIP "${HUMAN_VERSION}" HUMAN_VERSION)
message(STATUS "${LOCAL_CMAKE_PROJECT_NAME} ${HUMAN_SYNC_VERSION} ${HUMAN_VERSION}")

