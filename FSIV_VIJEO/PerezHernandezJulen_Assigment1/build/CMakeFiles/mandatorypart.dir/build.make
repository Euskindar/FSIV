# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/i72pehej/UNI_4/FSIV/PerezHernandezJulen_Assigment1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/i72pehej/UNI_4/FSIV/PerezHernandezJulen_Assigment1/build

# Include any dependencies generated for this target.
include CMakeFiles/mandatorypart.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mandatorypart.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mandatorypart.dir/flags.make

CMakeFiles/mandatorypart.dir/mandatorypart.cpp.o: CMakeFiles/mandatorypart.dir/flags.make
CMakeFiles/mandatorypart.dir/mandatorypart.cpp.o: ../mandatorypart.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/i72pehej/UNI_4/FSIV/PerezHernandezJulen_Assigment1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mandatorypart.dir/mandatorypart.cpp.o"
	/usr/local/opt/gcc-5.3.0-32/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mandatorypart.dir/mandatorypart.cpp.o -c /home/i72pehej/UNI_4/FSIV/PerezHernandezJulen_Assigment1/mandatorypart.cpp

CMakeFiles/mandatorypart.dir/mandatorypart.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mandatorypart.dir/mandatorypart.cpp.i"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/i72pehej/UNI_4/FSIV/PerezHernandezJulen_Assigment1/mandatorypart.cpp > CMakeFiles/mandatorypart.dir/mandatorypart.cpp.i

CMakeFiles/mandatorypart.dir/mandatorypart.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mandatorypart.dir/mandatorypart.cpp.s"
	/usr/local/opt/gcc-5.3.0-32/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/i72pehej/UNI_4/FSIV/PerezHernandezJulen_Assigment1/mandatorypart.cpp -o CMakeFiles/mandatorypart.dir/mandatorypart.cpp.s

# Object files for target mandatorypart
mandatorypart_OBJECTS = \
"CMakeFiles/mandatorypart.dir/mandatorypart.cpp.o"

# External object files for target mandatorypart
mandatorypart_EXTERNAL_OBJECTS =

mandatorypart: CMakeFiles/mandatorypart.dir/mandatorypart.cpp.o
mandatorypart: CMakeFiles/mandatorypart.dir/build.make
mandatorypart: /usr/local/lib/libopencv_stitching.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_superres.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_videostab.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_aruco.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_bgsegm.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_bioinspired.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_ccalib.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_dnn_objdetect.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_dpm.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_face.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_freetype.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_fuzzy.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_hfs.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_img_hash.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_line_descriptor.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_optflow.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_reg.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_rgbd.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_saliency.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_stereo.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_structured_light.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_surface_matching.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_tracking.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_xfeatures2d.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_ximgproc.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_xobjdetect.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_xphoto.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_shape.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_phase_unwrapping.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_video.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_datasets.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_plot.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_text.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_dnn.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_highgui.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_ml.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_videoio.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_imgcodecs.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_objdetect.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_calib3d.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_features2d.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_flann.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_photo.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_imgproc.so.3.4.7
mandatorypart: /usr/local/lib/libopencv_core.so.3.4.7
mandatorypart: CMakeFiles/mandatorypart.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/i72pehej/UNI_4/FSIV/PerezHernandezJulen_Assigment1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mandatorypart"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mandatorypart.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mandatorypart.dir/build: mandatorypart

.PHONY : CMakeFiles/mandatorypart.dir/build

CMakeFiles/mandatorypart.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mandatorypart.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mandatorypart.dir/clean

CMakeFiles/mandatorypart.dir/depend:
	cd /home/i72pehej/UNI_4/FSIV/PerezHernandezJulen_Assigment1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/i72pehej/UNI_4/FSIV/PerezHernandezJulen_Assigment1 /home/i72pehej/UNI_4/FSIV/PerezHernandezJulen_Assigment1 /home/i72pehej/UNI_4/FSIV/PerezHernandezJulen_Assigment1/build /home/i72pehej/UNI_4/FSIV/PerezHernandezJulen_Assigment1/build /home/i72pehej/UNI_4/FSIV/PerezHernandezJulen_Assigment1/build/CMakeFiles/mandatorypart.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mandatorypart.dir/depend

