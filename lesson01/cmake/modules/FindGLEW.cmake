# Try to find the gmm library
# Once done this will define
#
# GLEW_FOUND         - system has gmm and it can be used
# GLEW_INCLUDE_DIRS   - directory where the header file can be found
#

message(STATUS "Looking for GLEW")

SET (GLEW_FOUND FALSE)

IF(EXISTS GLEW_INCLUDE_DIRS)  # already found

    IF( GLEW_INCLUDE_DIRS )
        SET(GLEW_FOUND TRUE)
    ENDIF( GLEW_INCLUDE_DIRS )

ELSE(EXISTS GLEW_INCLUDE_DIRS)
    FIND_PATH(GLEW_INCLUDE_DIRS GL/glew.h
        ../vendor/glew-2.0.0-win-x64/include
    )

    FIND_LIBRARY(GLEW_LIBRARY glew32s
        HINTS ${GLEW_INCLUDE_DIRS}/../lib
    )

    IF( GLEW_INCLUDE_DIRS )
        SET(GLEW_FOUND TRUE)
    ENDIF( GLEW_INCLUDE_DIRS )

    if(GLEW_INCLUDE_DIRS)
      message(STATUS "Found GLEW include directory: ${GLEW_INCLUDE_DIRS}")
    else()
      message(STATUS "Could not find GLEW include dir")
    endif()

    if(GLEW_LIBRARY)
      message(STATUS "Found GLEW library: ${GLEW_LIBRARY}")
    else()
      message(STATUS "Could not find GLEW library")
    endif()

ENDIF(EXISTS GLEW_INCLUDE_DIRS)
