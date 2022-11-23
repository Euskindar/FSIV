CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(histopathology_classifier)
ENABLE_LANGUAGE(CXX)
SET (CMAKE_CXX_STANDARD 11) 

FIND_PACKAGE(OpenCV	REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")

add_executable(train_val train_val.cpp common_code.cpp common_code.hpp metrics.cpp metrics.hpp)
add_executable(test_image test_image.cpp common_code.cpp common_code.hpp )
