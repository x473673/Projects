# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /packages/run.64/cmake-3.6.2/bin/cmake

# The command to remove a file.
RM = /packages/run.64/cmake-3.6.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/x473673/pb071/hw03

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/x473673/pb071/hw03/build

# Include any dependencies generated for this target.
include CMakeFiles/playground.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/playground.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/playground.dir/flags.make

CMakeFiles/playground.dir/playground.c.o: CMakeFiles/playground.dir/flags.make
CMakeFiles/playground.dir/playground.c.o: ../playground.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/x473673/pb071/hw03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/playground.dir/playground.c.o"
	/usr/lib64/ccache/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/playground.dir/playground.c.o   -c /home/x473673/pb071/hw03/playground.c

CMakeFiles/playground.dir/playground.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/playground.dir/playground.c.i"
	/usr/lib64/ccache/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/x473673/pb071/hw03/playground.c > CMakeFiles/playground.dir/playground.c.i

CMakeFiles/playground.dir/playground.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/playground.dir/playground.c.s"
	/usr/lib64/ccache/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/x473673/pb071/hw03/playground.c -o CMakeFiles/playground.dir/playground.c.s

CMakeFiles/playground.dir/playground.c.o.requires:

.PHONY : CMakeFiles/playground.dir/playground.c.o.requires

CMakeFiles/playground.dir/playground.c.o.provides: CMakeFiles/playground.dir/playground.c.o.requires
	$(MAKE) -f CMakeFiles/playground.dir/build.make CMakeFiles/playground.dir/playground.c.o.provides.build
.PHONY : CMakeFiles/playground.dir/playground.c.o.provides

CMakeFiles/playground.dir/playground.c.o.provides.build: CMakeFiles/playground.dir/playground.c.o


# Object files for target playground
playground_OBJECTS = \
"CMakeFiles/playground.dir/playground.c.o"

# External object files for target playground
playground_EXTERNAL_OBJECTS =

playground: CMakeFiles/playground.dir/playground.c.o
playground: CMakeFiles/playground.dir/build.make
playground: libmvm.a
playground: CMakeFiles/playground.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/x473673/pb071/hw03/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable playground"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/playground.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/playground.dir/build: playground

.PHONY : CMakeFiles/playground.dir/build

CMakeFiles/playground.dir/requires: CMakeFiles/playground.dir/playground.c.o.requires

.PHONY : CMakeFiles/playground.dir/requires

CMakeFiles/playground.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/playground.dir/cmake_clean.cmake
.PHONY : CMakeFiles/playground.dir/clean

CMakeFiles/playground.dir/depend:
	cd /home/x473673/pb071/hw03/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/x473673/pb071/hw03 /home/x473673/pb071/hw03 /home/x473673/pb071/hw03/build /home/x473673/pb071/hw03/build /home/x473673/pb071/hw03/build/CMakeFiles/playground.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/playground.dir/depend

