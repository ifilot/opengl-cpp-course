# Try to find the gmm library
# Once done this will define
#
# ZLIB_FOUND         - system has gmm and it can be used
# ZLIB_INCLUDE_DIRS   - directory where the header file can be found
#

message(STATUS "Looking for ZLIB")

SET (ZLIB_FOUND FALSE)

IF(EXISTS ZLIB_INCLUDE_DIRS)  # already found

    IF( ZLIB_INCLUDE_DIRS )
        SET(ZLIB_FOUND TRUE)
    ENDIF( ZLIB_INCLUDE_DIRS )

ELSE(EXISTS ZLIB_INCLUDE_DIRS)
    FIND_PATH(ZLIB_INCLUDE_DIRS ZLIB.h
        ../vendor/zlib-1.2.1-win-x64/include
    )

    FIND_LIBRARY(ZLIB_LIBRARY zlib
        HINTS ${ZLIB_INCLUDE_DIRS}/../lib
    )

    IF( ZLIB_INCLUDE_DIRS )
        SET(ZLIB_FOUND TRUE)
    ENDIF( ZLIB_INCLUDE_DIRS )

    if(ZLIB_INCLUDE_DIRS)
      message(STATUS "Found ZLIB include directory: ${ZLIB_INCLUDE_DIRS}")
    else()
      message(STATUS "Could not find ZLIB include dir")
    endif()

    if(ZLIB_LIBRARY)
      message(STATUS "Found ZLIB library: ${ZLIB_LIBRARY}")
    else()
      message(STATUS "Could not find ZLIB library")
    endif()

ENDIF(EXISTS ZLIB_INCLUDE_DIRS)
