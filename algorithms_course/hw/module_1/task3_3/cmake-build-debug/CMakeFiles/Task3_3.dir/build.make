# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /opt/jetBrains/clion-2017.3.4/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/jetBrains/clion-2017.3.4/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mks/Tehnopark/Algorithms_course/HW/Module_1/Task3_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mks/Tehnopark/Algorithms_course/HW/Module_1/Task3_3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Task3_3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Task3_3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Task3_3.dir/flags.make

CMakeFiles/Task3_3.dir/main.cpp.o: CMakeFiles/Task3_3.dir/flags.make
CMakeFiles/Task3_3.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mks/Tehnopark/Algorithms_course/HW/Module_1/Task3_3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Task3_3.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Task3_3.dir/main.cpp.o -c /home/mks/Tehnopark/Algorithms_course/HW/Module_1/Task3_3/main.cpp

CMakeFiles/Task3_3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Task3_3.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mks/Tehnopark/Algorithms_course/HW/Module_1/Task3_3/main.cpp > CMakeFiles/Task3_3.dir/main.cpp.i

CMakeFiles/Task3_3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Task3_3.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mks/Tehnopark/Algorithms_course/HW/Module_1/Task3_3/main.cpp -o CMakeFiles/Task3_3.dir/main.cpp.s

CMakeFiles/Task3_3.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Task3_3.dir/main.cpp.o.requires

CMakeFiles/Task3_3.dir/main.cpp.o.provides: CMakeFiles/Task3_3.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Task3_3.dir/build.make CMakeFiles/Task3_3.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Task3_3.dir/main.cpp.o.provides

CMakeFiles/Task3_3.dir/main.cpp.o.provides.build: CMakeFiles/Task3_3.dir/main.cpp.o


# Object files for target Task3_3
Task3_3_OBJECTS = \
"CMakeFiles/Task3_3.dir/main.cpp.o"

# External object files for target Task3_3
Task3_3_EXTERNAL_OBJECTS =

Task3_3: CMakeFiles/Task3_3.dir/main.cpp.o
Task3_3: CMakeFiles/Task3_3.dir/build.make
Task3_3: CMakeFiles/Task3_3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mks/Tehnopark/Algorithms_course/HW/Module_1/Task3_3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Task3_3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Task3_3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Task3_3.dir/build: Task3_3

.PHONY : CMakeFiles/Task3_3.dir/build

CMakeFiles/Task3_3.dir/requires: CMakeFiles/Task3_3.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Task3_3.dir/requires

CMakeFiles/Task3_3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Task3_3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Task3_3.dir/clean

CMakeFiles/Task3_3.dir/depend:
	cd /home/mks/Tehnopark/Algorithms_course/HW/Module_1/Task3_3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mks/Tehnopark/Algorithms_course/HW/Module_1/Task3_3 /home/mks/Tehnopark/Algorithms_course/HW/Module_1/Task3_3 /home/mks/Tehnopark/Algorithms_course/HW/Module_1/Task3_3/cmake-build-debug /home/mks/Tehnopark/Algorithms_course/HW/Module_1/Task3_3/cmake-build-debug /home/mks/Tehnopark/Algorithms_course/HW/Module_1/Task3_3/cmake-build-debug/CMakeFiles/Task3_3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Task3_3.dir/depend

