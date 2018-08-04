# Try to find the gmm library
# Once done this will define
#
# GLFW3_FOUND         - system has gmm and it can be used
# GLFW3_INCLUDE_DIRS   - directory where the header file can be found
#

message(STATUS "Looking for GLFW3")

SET (GLFW3_FOUND FALSE)

IF(EXISTS GLFW3_INCLUDE_DIRS)  # already found

    IF( GLFW3_INCLUDE_DIRS )
        SET(GLFW3_FOUND TRUE)
    ENDIF( GLFW3_INCLUDE_DIRS )

ELSE(EXISTS GLFW3_INCLUDE_DIRS)
    FIND_PATH(GLFW3_INCLUDE_DIRS GLFW/glfw3.h
        ../vendor/glfw-3.2.1-win-x64/include
    )

    FIND_LIBRARY(GLFW3_LIBRARY glfw3
        HINTS ${GLFW3_INCLUDE_DIRS}/../lib
    )

    IF( GLFW3_INCLUDE_DIRS )
        SET(GLFW3_FOUND TRUE)
    ENDIF( GLFW3_INCLUDE_DIRS )

    if(GLFW3_INCLUDE_DIRS)
      message(STATUS "Found GLFW3 include directory: ${GLFW3_INCLUDE_DIRS}")
    else()
      message(STATUS "Could not find GLFW3 include dir")
    endif()

    if(GLFW3_LIBRARY)
      message(STATUS "Found GLFW3 library: ${GLFW3_LIBRARY}")
    else()
      message(STATUS "Could not find GLFW3 library")
    endif()

ENDIF(EXISTS GLFW3_INCLUDE_DIRS)
