# Try to find the gmm library
# Once done this will define
#
# PNG_FOUND         - system has gmm and it can be used
# PNG_INCLUDE_DIRS   - directory where the header file can be found
#

message(STATUS "Looking for PNG")

SET (PNG_FOUND FALSE)

IF(EXISTS PNG_INCLUDE_DIRS)  # already found

    IF( PNG_INCLUDE_DIRS )
        SET(PNG_FOUND TRUE)
    ENDIF( PNG_INCLUDE_DIRS )

ELSE(EXISTS PNG_INCLUDE_DIRS)
    FIND_PATH(PNG_INCLUDE_DIRS png.h
        ../vendor/libpng-1.6.28-win-x64/include
    )

    FIND_LIBRARY(PNG_LIBRARIES libpng
        HINTS ${PNG_INCLUDE_DIRS}/../lib
    )

    IF( PNG_INCLUDE_DIRS )
        SET(PNG_FOUND TRUE)
    ENDIF( PNG_INCLUDE_DIRS )

    if(PNG_INCLUDE_DIRS)
      message(STATUS "Found PNG include directory: ${PNG_INCLUDE_DIRS}")
    else()
      message(STATUS "Could not find PNG include dir")
    endif()

    if(PNG_LIBRARIES)
      message(STATUS "Found PNG library: ${PNG_LIBRARIES}")
    else()
      message(STATUS "Could not find PNG library")
    endif()

ENDIF(EXISTS PNG_INCLUDE_DIRS)
