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
CMAKE_SOURCE_DIR = /home/x473673/pb071/hw01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/x473673/pb071/hw01/build

# Include any dependencies generated for this target.
include CMakeFiles/spellcheck.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/spellcheck.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/spellcheck.dir/flags.make

CMakeFiles/spellcheck.dir/hw01.c.o: CMakeFiles/spellcheck.dir/flags.make
CMakeFiles/spellcheck.dir/hw01.c.o: ../hw01.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/x473673/pb071/hw01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/spellcheck.dir/hw01.c.o"
	/usr/lib64/ccache/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spellcheck.dir/hw01.c.o   -c /home/x473673/pb071/hw01/hw01.c

CMakeFiles/spellcheck.dir/hw01.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spellcheck.dir/hw01.c.i"
	/usr/lib64/ccache/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/x473673/pb071/hw01/hw01.c > CMakeFiles/spellcheck.dir/hw01.c.i

CMakeFiles/spellcheck.dir/hw01.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spellcheck.dir/hw01.c.s"
	/usr/lib64/ccache/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/x473673/pb071/hw01/hw01.c -o CMakeFiles/spellcheck.dir/hw01.c.s

CMakeFiles/spellcheck.dir/hw01.c.o.requires:

.PHONY : CMakeFiles/spellcheck.dir/hw01.c.o.requires

CMakeFiles/spellcheck.dir/hw01.c.o.provides: CMakeFiles/spellcheck.dir/hw01.c.o.requires
	$(MAKE) -f CMakeFiles/spellcheck.dir/build.make CMakeFiles/spellcheck.dir/hw01.c.o.provides.build
.PHONY : CMakeFiles/spellcheck.dir/hw01.c.o.provides

CMakeFiles/spellcheck.dir/hw01.c.o.provides.build: CMakeFiles/spellcheck.dir/hw01.c.o


CMakeFiles/spellcheck.dir/hw01_main.c.o: CMakeFiles/spellcheck.dir/flags.make
CMakeFiles/spellcheck.dir/hw01_main.c.o: ../hw01_main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/x473673/pb071/hw01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/spellcheck.dir/hw01_main.c.o"
	/usr/lib64/ccache/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/spellcheck.dir/hw01_main.c.o   -c /home/x473673/pb071/hw01/hw01_main.c

CMakeFiles/spellcheck.dir/hw01_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/spellcheck.dir/hw01_main.c.i"
	/usr/lib64/ccache/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/x473673/pb071/hw01/hw01_main.c > CMakeFiles/spellcheck.dir/hw01_main.c.i

CMakeFiles/spellcheck.dir/hw01_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/spellcheck.dir/hw01_main.c.s"
	/usr/lib64/ccache/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/x473673/pb071/hw01/hw01_main.c -o CMakeFiles/spellcheck.dir/hw01_main.c.s

CMakeFiles/spellcheck.dir/hw01_main.c.o.requires:

.PHONY : CMakeFiles/spellcheck.dir/hw01_main.c.o.requires

CMakeFiles/spellcheck.dir/hw01_main.c.o.provides: CMakeFiles/spellcheck.dir/hw01_main.c.o.requires
	$(MAKE) -f CMakeFiles/spellcheck.dir/build.make CMakeFiles/spellcheck.dir/hw01_main.c.o.provides.build
.PHONY : CMakeFiles/spellcheck.dir/hw01_main.c.o.provides

CMakeFiles/spellcheck.dir/hw01_main.c.o.provides.build: CMakeFiles/spellcheck.dir/hw01_main.c.o


# Object files for target spellcheck
spellcheck_OBJECTS = \
"CMakeFiles/spellcheck.dir/hw01.c.o" \
"CMakeFiles/spellcheck.dir/hw01_main.c.o"

# External object files for target spellcheck
spellcheck_EXTERNAL_OBJECTS =

spellcheck: CMakeFiles/spellcheck.dir/hw01.c.o
spellcheck: CMakeFiles/spellcheck.dir/hw01_main.c.o
spellcheck: CMakeFiles/spellcheck.dir/build.make
spellcheck: CMakeFiles/spellcheck.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/x473673/pb071/hw01/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable spellcheck"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/spellcheck.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/spellcheck.dir/build: spellcheck

.PHONY : CMakeFiles/spellcheck.dir/build

CMakeFiles/spellcheck.dir/requires: CMakeFiles/spellcheck.dir/hw01.c.o.requires
CMakeFiles/spellcheck.dir/requires: CMakeFiles/spellcheck.dir/hw01_main.c.o.requires

.PHONY : CMakeFiles/spellcheck.dir/requires

CMakeFiles/spellcheck.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/spellcheck.dir/cmake_clean.cmake
.PHONY : CMakeFiles/spellcheck.dir/clean

CMakeFiles/spellcheck.dir/depend:
	cd /home/x473673/pb071/hw01/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/x473673/pb071/hw01 /home/x473673/pb071/hw01 /home/x473673/pb071/hw01/build /home/x473673/pb071/hw01/build /home/x473673/pb071/hw01/build/CMakeFiles/spellcheck.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/spellcheck.dir/depend

