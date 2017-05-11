####################################
# build/install/pack instructions  #
####################################

### Look for faster Ninja buid system in stead of common Unix Makefiles ###
message(STATUS "Current generator: \"${CMAKE_GENERATOR}\"")
find_program(NINJA "ninja")
if(NINJA)
  if("${CMAKE_GENERATOR}" MATCHES "Ninja")
  else()
    message(STATUS "Detected faster \"Ninja\" generator")
    message(STATUS "Invoke again from 'build' folder: rm -rf * && cmake .. -G \"Ninja\"") 
  endif()
endif()
