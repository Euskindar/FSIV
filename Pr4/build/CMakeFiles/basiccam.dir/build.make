# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/i72pehej/FSIV_6/Pr4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/i72pehej/FSIV_6/Pr4/build

# Include any dependencies generated for this target.
include CMakeFiles/basiccam.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/basiccam.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/basiccam.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/basiccam.dir/flags.make

CMakeFiles/basiccam.dir/basiccam.cpp.o: CMakeFiles/basiccam.dir/flags.make
CMakeFiles/basiccam.dir/basiccam.cpp.o: ../basiccam.cpp
CMakeFiles/basiccam.dir/basiccam.cpp.o: CMakeFiles/basiccam.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/i72pehej/FSIV_6/Pr4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/basiccam.dir/basiccam.cpp.o"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/basiccam.dir/basiccam.cpp.o -MF CMakeFiles/basiccam.dir/basiccam.cpp.o.d -o CMakeFiles/basiccam.dir/basiccam.cpp.o -c /home/i72pehej/FSIV_6/Pr4/basiccam.cpp

CMakeFiles/basiccam.dir/basiccam.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basiccam.dir/basiccam.cpp.i"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/i72pehej/FSIV_6/Pr4/basiccam.cpp > CMakeFiles/basiccam.dir/basiccam.cpp.i

CMakeFiles/basiccam.dir/basiccam.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basiccam.dir/basiccam.cpp.s"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/i72pehej/FSIV_6/Pr4/basiccam.cpp -o CMakeFiles/basiccam.dir/basiccam.cpp.s

CMakeFiles/basiccam.dir/common_code.cpp.o: CMakeFiles/basiccam.dir/flags.make
CMakeFiles/basiccam.dir/common_code.cpp.o: ../common_code.cpp
CMakeFiles/basiccam.dir/common_code.cpp.o: CMakeFiles/basiccam.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/i72pehej/FSIV_6/Pr4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/basiccam.dir/common_code.cpp.o"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/basiccam.dir/common_code.cpp.o -MF CMakeFiles/basiccam.dir/common_code.cpp.o.d -o CMakeFiles/basiccam.dir/common_code.cpp.o -c /home/i72pehej/FSIV_6/Pr4/common_code.cpp

CMakeFiles/basiccam.dir/common_code.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basiccam.dir/common_code.cpp.i"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/i72pehej/FSIV_6/Pr4/common_code.cpp > CMakeFiles/basiccam.dir/common_code.cpp.i

CMakeFiles/basiccam.dir/common_code.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basiccam.dir/common_code.cpp.s"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/i72pehej/FSIV_6/Pr4/common_code.cpp -o CMakeFiles/basiccam.dir/common_code.cpp.s

# Object files for target basiccam
basiccam_OBJECTS = \
"CMakeFiles/basiccam.dir/basiccam.cpp.o" \
"CMakeFiles/basiccam.dir/common_code.cpp.o"

# External object files for target basiccam
basiccam_EXTERNAL_OBJECTS =

basiccam: CMakeFiles/basiccam.dir/basiccam.cpp.o
basiccam: CMakeFiles/basiccam.dir/common_code.cpp.o
basiccam: CMakeFiles/basiccam.dir/build.make
basiccam: /usr/local/lib/libopencv_dnn.so.3.4.7
basiccam: /usr/local/lib/libopencv_highgui.so.3.4.7
basiccam: /usr/local/lib/libopencv_ml.so.3.4.7
basiccam: /usr/local/lib/libopencv_objdetect.so.3.4.7
basiccam: /usr/local/lib/libopencv_shape.so.3.4.7
basiccam: /usr/local/lib/libopencv_stitching.so.3.4.7
basiccam: /usr/local/lib/libopencv_superres.so.3.4.7
basiccam: /usr/local/lib/libopencv_videostab.so.3.4.7
basiccam: /usr/local/lib/libopencv_ovis.so.3.4.7
basiccam: /usr/local/lib/libopencv_photo.so.3.4.7
basiccam: /usr/local/lib/libopencv_video.so.3.4.7
basiccam: /usr/local/lib/libopencv_videoio.so.3.4.7
basiccam: /usr/local/lib/libopencv_imgcodecs.so.3.4.7
basiccam: /usr/local/lib/libopencv_calib3d.so.3.4.7
basiccam: /usr/local/lib/libopencv_features2d.so.3.4.7
basiccam: /usr/local/lib/libopencv_flann.so.3.4.7
basiccam: /usr/local/lib/libopencv_imgproc.so.3.4.7
basiccam: /usr/local/lib/libopencv_core.so.3.4.7
basiccam: CMakeFiles/basiccam.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/i72pehej/FSIV_6/Pr4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable basiccam"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/basiccam.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/basiccam.dir/build: basiccam
.PHONY : CMakeFiles/basiccam.dir/build

CMakeFiles/basiccam.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/basiccam.dir/cmake_clean.cmake
.PHONY : CMakeFiles/basiccam.dir/clean

CMakeFiles/basiccam.dir/depend:
	cd /home/i72pehej/FSIV_6/Pr4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/i72pehej/FSIV_6/Pr4 /home/i72pehej/FSIV_6/Pr4 /home/i72pehej/FSIV_6/Pr4/build /home/i72pehej/FSIV_6/Pr4/build /home/i72pehej/FSIV_6/Pr4/build/CMakeFiles/basiccam.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/basiccam.dir/depend

