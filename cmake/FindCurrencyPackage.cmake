### Package ###
if("${LOCAL_CMAKE_PROJECT_NAME}" STREQUAL "${CMAKE_PROJECT_NAME}")
  set(CPACK_GENERATOR "TGZ")
  set(CPACK_SET_DESTDIR ON)
  set(CPACK_PACKAGE_VERSION "${DOXYGEN_PROJECT_NUMBER}")
  set(CPACK_INSTALLED_DIRECTORIES "${CMAKE_CURRENT_BINARY_DIR}/html" ${DOC_INSTALL_DIR}/html)
  set(CPACK_PACKAGE_INSTALL_PREFIX "")
  include(CPack)
endif()
