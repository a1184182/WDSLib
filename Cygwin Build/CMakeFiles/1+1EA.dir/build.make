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
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/a1184182/WDSLib-master/WDSLib-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/a1184182/WDSLib-master/Cygwin Build"

# Include any dependencies generated for this target.
include CMakeFiles/1+1EA.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/1+1EA.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1+1EA.dir/flags.make

CMakeFiles/1+1EA.dir/1+1EA.cc.o: CMakeFiles/1+1EA.dir/flags.make
CMakeFiles/1+1EA.dir/1+1EA.cc.o: /home/a1184182/WDSLib-master/WDSLib-master/1+1EA.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/a1184182/WDSLib-master/Cygwin Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1+1EA.dir/1+1EA.cc.o"
	/usr/bin/c++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/1+1EA.dir/1+1EA.cc.o -c /home/a1184182/WDSLib-master/WDSLib-master/1+1EA.cc

CMakeFiles/1+1EA.dir/1+1EA.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1+1EA.dir/1+1EA.cc.i"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/a1184182/WDSLib-master/WDSLib-master/1+1EA.cc > CMakeFiles/1+1EA.dir/1+1EA.cc.i

CMakeFiles/1+1EA.dir/1+1EA.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1+1EA.dir/1+1EA.cc.s"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/a1184182/WDSLib-master/WDSLib-master/1+1EA.cc -o CMakeFiles/1+1EA.dir/1+1EA.cc.s

CMakeFiles/1+1EA.dir/1+1EA.cc.o.requires:

.PHONY : CMakeFiles/1+1EA.dir/1+1EA.cc.o.requires

CMakeFiles/1+1EA.dir/1+1EA.cc.o.provides: CMakeFiles/1+1EA.dir/1+1EA.cc.o.requires
	$(MAKE) -f CMakeFiles/1+1EA.dir/build.make CMakeFiles/1+1EA.dir/1+1EA.cc.o.provides.build
.PHONY : CMakeFiles/1+1EA.dir/1+1EA.cc.o.provides

CMakeFiles/1+1EA.dir/1+1EA.cc.o.provides.build: CMakeFiles/1+1EA.dir/1+1EA.cc.o


# Object files for target 1+1EA
1___1EA_OBJECTS = \
"CMakeFiles/1+1EA.dir/1+1EA.cc.o"

# External object files for target 1+1EA
1___1EA_EXTERNAL_OBJECTS =

1+1EA.exe: CMakeFiles/1+1EA.dir/1+1EA.cc.o
1+1EA.exe: CMakeFiles/1+1EA.dir/build.make
1+1EA.exe: libWDSLib.a
1+1EA.exe: lib/EPANET/libEPANET.a
1+1EA.exe: lib/SuiteSparse/libcxsparse.a
1+1EA.exe: CMakeFiles/1+1EA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/a1184182/WDSLib-master/Cygwin Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 1+1EA.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/1+1EA.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1+1EA.dir/build: 1+1EA.exe

.PHONY : CMakeFiles/1+1EA.dir/build

CMakeFiles/1+1EA.dir/requires: CMakeFiles/1+1EA.dir/1+1EA.cc.o.requires

.PHONY : CMakeFiles/1+1EA.dir/requires

CMakeFiles/1+1EA.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/1+1EA.dir/cmake_clean.cmake
.PHONY : CMakeFiles/1+1EA.dir/clean

CMakeFiles/1+1EA.dir/depend:
	cd "/home/a1184182/WDSLib-master/Cygwin Build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/a1184182/WDSLib-master/WDSLib-master /home/a1184182/WDSLib-master/WDSLib-master "/home/a1184182/WDSLib-master/Cygwin Build" "/home/a1184182/WDSLib-master/Cygwin Build" "/home/a1184182/WDSLib-master/Cygwin Build/CMakeFiles/1+1EA.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/1+1EA.dir/depend

