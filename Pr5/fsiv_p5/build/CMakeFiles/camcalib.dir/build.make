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
CMAKE_SOURCE_DIR = /home/i72pehej/FSIV_6/Pr5/fsiv_p5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/i72pehej/FSIV_6/Pr5/fsiv_p5/build

# Include any dependencies generated for this target.
include CMakeFiles/camcalib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/camcalib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/camcalib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/camcalib.dir/flags.make

CMakeFiles/camcalib.dir/camcalib.cpp.o: CMakeFiles/camcalib.dir/flags.make
CMakeFiles/camcalib.dir/camcalib.cpp.o: ../camcalib.cpp
CMakeFiles/camcalib.dir/camcalib.cpp.o: CMakeFiles/camcalib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/i72pehej/FSIV_6/Pr5/fsiv_p5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/camcalib.dir/camcalib.cpp.o"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/camcalib.dir/camcalib.cpp.o -MF CMakeFiles/camcalib.dir/camcalib.cpp.o.d -o CMakeFiles/camcalib.dir/camcalib.cpp.o -c /home/i72pehej/FSIV_6/Pr5/fsiv_p5/camcalib.cpp

CMakeFiles/camcalib.dir/camcalib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/camcalib.dir/camcalib.cpp.i"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/i72pehej/FSIV_6/Pr5/fsiv_p5/camcalib.cpp > CMakeFiles/camcalib.dir/camcalib.cpp.i

CMakeFiles/camcalib.dir/camcalib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/camcalib.dir/camcalib.cpp.s"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/i72pehej/FSIV_6/Pr5/fsiv_p5/camcalib.cpp -o CMakeFiles/camcalib.dir/camcalib.cpp.s

CMakeFiles/camcalib.dir/common_code.cpp.o: CMakeFiles/camcalib.dir/flags.make
CMakeFiles/camcalib.dir/common_code.cpp.o: ../common_code.cpp
CMakeFiles/camcalib.dir/common_code.cpp.o: CMakeFiles/camcalib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/i72pehej/FSIV_6/Pr5/fsiv_p5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/camcalib.dir/common_code.cpp.o"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/camcalib.dir/common_code.cpp.o -MF CMakeFiles/camcalib.dir/common_code.cpp.o.d -o CMakeFiles/camcalib.dir/common_code.cpp.o -c /home/i72pehej/FSIV_6/Pr5/fsiv_p5/common_code.cpp

CMakeFiles/camcalib.dir/common_code.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/camcalib.dir/common_code.cpp.i"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/i72pehej/FSIV_6/Pr5/fsiv_p5/common_code.cpp > CMakeFiles/camcalib.dir/common_code.cpp.i

CMakeFiles/camcalib.dir/common_code.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/camcalib.dir/common_code.cpp.s"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/i72pehej/FSIV_6/Pr5/fsiv_p5/common_code.cpp -o CMakeFiles/camcalib.dir/common_code.cpp.s

# Object files for target camcalib
camcalib_OBJECTS = \
"CMakeFiles/camcalib.dir/camcalib.cpp.o" \
"CMakeFiles/camcalib.dir/common_code.cpp.o"

# External object files for target camcalib
camcalib_EXTERNAL_OBJECTS =

camcalib: CMakeFiles/camcalib.dir/camcalib.cpp.o
camcalib: CMakeFiles/camcalib.dir/common_code.cpp.o
camcalib: CMakeFiles/camcalib.dir/build.make
camcalib: /usr/local/lib/libopencv_dnn.so.3.4.7
camcalib: /usr/local/lib/libopencv_highgui.so.3.4.7
camcalib: /usr/local/lib/libopencv_ml.so.3.4.7
camcalib: /usr/local/lib/libopencv_objdetect.so.3.4.7
camcalib: /usr/local/lib/libopencv_shape.so.3.4.7
camcalib: /usr/local/lib/libopencv_stitching.so.3.4.7
camcalib: /usr/local/lib/libopencv_superres.so.3.4.7
camcalib: /usr/local/lib/libopencv_videostab.so.3.4.7
camcalib: /usr/local/lib/libopencv_ovis.so.3.4.7
camcalib: /usr/local/lib/libopencv_photo.so.3.4.7
camcalib: /usr/local/lib/libopencv_video.so.3.4.7
camcalib: /usr/local/lib/libopencv_videoio.so.3.4.7
camcalib: /usr/local/lib/libopencv_imgcodecs.so.3.4.7
camcalib: /usr/local/lib/libopencv_calib3d.so.3.4.7
camcalib: /usr/local/lib/libopencv_features2d.so.3.4.7
camcalib: /usr/local/lib/libopencv_flann.so.3.4.7
camcalib: /usr/local/lib/libopencv_imgproc.so.3.4.7
camcalib: /usr/local/lib/libopencv_core.so.3.4.7
camcalib: CMakeFiles/camcalib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/i72pehej/FSIV_6/Pr5/fsiv_p5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable camcalib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/camcalib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/camcalib.dir/build: camcalib
.PHONY : CMakeFiles/camcalib.dir/build

CMakeFiles/camcalib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/camcalib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/camcalib.dir/clean

CMakeFiles/camcalib.dir/depend:
	cd /home/i72pehej/FSIV_6/Pr5/fsiv_p5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/i72pehej/FSIV_6/Pr5/fsiv_p5 /home/i72pehej/FSIV_6/Pr5/fsiv_p5 /home/i72pehej/FSIV_6/Pr5/fsiv_p5/build /home/i72pehej/FSIV_6/Pr5/fsiv_p5/build /home/i72pehej/FSIV_6/Pr5/fsiv_p5/build/CMakeFiles/camcalib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/camcalib.dir/depend

