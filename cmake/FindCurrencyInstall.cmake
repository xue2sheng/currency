### Install ###
if(DEFINED ENV{INSTALL_PREFIX})
  set(INTERNAL_INSTALL_PREFIX "$ENV{INSTALL_PREFIX}")
elseif(EXISTS /opt/compilationDep)
  set(INTERNAL_INSTALL_PREFIX "/opt/compilationDep")
else()
  set(INTERNAL_INSTALL_PREFIX "/tmp/${LOCAL_CMAKE_PROJECT_NAME}")
endif()
message(STATUS "Using installing folder ${INTERNAL_INSTALL_PREFIX}")

set(CMAKE_INSTALL_PREFIX ${INTERNAL_INSTALL_PREFIX})
set(HEADERS_INSTALL_DIR "${INTERNAL_INSTALL_PREFIX}/headers")
set(LIB_INSTALL_DIR "${INTERNAL_INSTALL_PREFIX}/a")
set(TEST_INSTALL_DIR "${INTERNAL_INSTALL_PREFIX}/test")
set(MOCK_INSTALL_DIR "${INTERNAL_INSTALL_PREFIX}/mock")
set(DOC_INSTALL_DIR "${INTERNAL_INSTALL_PREFIX}/doc/currency")
