############################
# compilation dependencies #
############################

if(EXISTS $ENV{COMPILATIONDEP})
    set(COMPILATIONDEP "$ENV{COMPILATIONDEP}")
    message(STATUS "Using environment variable COMPILATIONDEP=${COMPILATIONDEP} as compilationDep")
elseif(EXISTS "/mnt/swap/compilationDep")
    set(COMPILATIONDEP "/mnt/swap/compilationDep")
    message(STATUS "Using default mounted folder ${COMPILATIONDEP} as compilationDep")
elseif(EXISTS "/mnt/megaswap/compilationDep")
    set(COMPILATIONDEP "/mnt/megaswap/compilationDep")
    message(STATUS "Using default mounted folder ${COMPILATIONDEP} as compilationDep")
elseif(EXISTS "/opt/compilationDep")
    set(COMPILATIONDEP "/opt/compilationDep")
    message(STATUS "Using default local folder ${COMPILATIONDEP} as compilationDep")
else()
    message(STATUS "Missing compilation dependencies folder, i.e. /mnt/swap/compilationDep or /mnt/megaswap/compilationDep")
endif()

