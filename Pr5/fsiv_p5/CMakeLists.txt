CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(fsiv_p5)
set(CMAKE_CXX_STANDARD 11) # C++11,C++14,17,20
FIND_PACKAGE(OpenCV 	REQUIRED )
include_directories ("${OpenCV_INCLUDE_DIRS}")
#Required for uco thinstation. May not be required in your own pc
OPTION(THINSTATION	"Set to OFF at home" OFF)

IF(THINSTATION)
  SET(CMAKE_CXX_FLAGS " -D_GLIBCXX_USE_CXX11_ABI=0 -m32")
  SET(XRAND Xrandr)
  link_directories(/usr/local/X11R7/lib)
  MESSAGE( STATUS "USING THINSTATION OPTIONS" )
ENDIF()

LINK_LIBRARIES(${OpenCV_LIBS} ${XRAND})

add_executable(camcalib camcalib.cpp common_code.cpp)
