# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build"

# Include any dependencies generated for this target.
include CMakeFiles/WDSLib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/WDSLib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WDSLib.dir/flags.make

CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/Simulation.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/Simulation.cc

CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/Simulation.cc > CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.i

CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/Simulation.cc -o CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.s

CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o.requires

CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o.provides: CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o.provides

CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o.provides.build: CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o


CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/ELVA.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/ELVA.cc

CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/ELVA.cc > CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.i

CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/ELVA.cc -o CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.s

CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o.requires

CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o.provides: CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o.provides

CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o.provides.build: CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o


CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/Flag.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/Flag.cc

CMakeFiles/WDSLib.dir/Simulation/Flag.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/Simulation/Flag.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/Flag.cc > CMakeFiles/WDSLib.dir/Simulation/Flag.cc.i

CMakeFiles/WDSLib.dir/Simulation/Flag.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/Simulation/Flag.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/Flag.cc -o CMakeFiles/WDSLib.dir/Simulation/Flag.cc.s

CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o.requires

CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o.provides: CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o.provides

CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o.provides.build: CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o


CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/Parameter.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/Parameter.cc

CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/Parameter.cc > CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.i

CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Simulation/Parameter.cc -o CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.s

CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o.requires

CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o.provides: CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o.provides

CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o.provides.build: CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o


CMakeFiles/WDSLib.dir/Network/Net.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/Network/Net.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Net.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/WDSLib.dir/Network/Net.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/Network/Net.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Net.cc

CMakeFiles/WDSLib.dir/Network/Net.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/Network/Net.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Net.cc > CMakeFiles/WDSLib.dir/Network/Net.cc.i

CMakeFiles/WDSLib.dir/Network/Net.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/Network/Net.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Net.cc -o CMakeFiles/WDSLib.dir/Network/Net.cc.s

CMakeFiles/WDSLib.dir/Network/Net.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/Network/Net.cc.o.requires

CMakeFiles/WDSLib.dir/Network/Net.cc.o.provides: CMakeFiles/WDSLib.dir/Network/Net.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/Network/Net.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/Network/Net.cc.o.provides

CMakeFiles/WDSLib.dir/Network/Net.cc.o.provides.build: CMakeFiles/WDSLib.dir/Network/Net.cc.o


CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Edge/PIPES/pipe.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Edge/PIPES/pipe.cc

CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Edge/PIPES/pipe.cc > CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.i

CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Edge/PIPES/pipe.cc -o CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.s

CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o.requires

CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o.provides: CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o.provides

CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o.provides.build: CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o


CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Vertex/NODE/node.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Vertex/NODE/node.cc

CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Vertex/NODE/node.cc > CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.i

CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Vertex/NODE/node.cc -o CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.s

CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o.requires

CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o.provides: CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o.provides

CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o.provides.build: CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o


CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Geometry/topology.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Geometry/topology.cc

CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Geometry/topology.cc > CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.i

CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/Network/Geometry/topology.cc -o CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.s

CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o.requires

CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o.provides: CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o.provides

CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o.provides.build: CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o


CMakeFiles/WDSLib.dir/math/Matrix.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/math/Matrix.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/math/Matrix.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/WDSLib.dir/math/Matrix.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/math/Matrix.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/math/Matrix.cc

CMakeFiles/WDSLib.dir/math/Matrix.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/math/Matrix.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/math/Matrix.cc > CMakeFiles/WDSLib.dir/math/Matrix.cc.i

CMakeFiles/WDSLib.dir/math/Matrix.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/math/Matrix.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/math/Matrix.cc -o CMakeFiles/WDSLib.dir/math/Matrix.cc.s

CMakeFiles/WDSLib.dir/math/Matrix.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/math/Matrix.cc.o.requires

CMakeFiles/WDSLib.dir/math/Matrix.cc.o.provides: CMakeFiles/WDSLib.dir/math/Matrix.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/math/Matrix.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/math/Matrix.cc.o.provides

CMakeFiles/WDSLib.dir/math/Matrix.cc.o.provides.build: CMakeFiles/WDSLib.dir/math/Matrix.cc.o


CMakeFiles/WDSLib.dir/IO/Input.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/IO/Input.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/IO/Input.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/WDSLib.dir/IO/Input.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/IO/Input.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/IO/Input.cc

CMakeFiles/WDSLib.dir/IO/Input.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/IO/Input.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/IO/Input.cc > CMakeFiles/WDSLib.dir/IO/Input.cc.i

CMakeFiles/WDSLib.dir/IO/Input.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/IO/Input.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/IO/Input.cc -o CMakeFiles/WDSLib.dir/IO/Input.cc.s

CMakeFiles/WDSLib.dir/IO/Input.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/IO/Input.cc.o.requires

CMakeFiles/WDSLib.dir/IO/Input.cc.o.provides: CMakeFiles/WDSLib.dir/IO/Input.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/IO/Input.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/IO/Input.cc.o.provides

CMakeFiles/WDSLib.dir/IO/Input.cc.o.provides.build: CMakeFiles/WDSLib.dir/IO/Input.cc.o


CMakeFiles/WDSLib.dir/hydraulic/result.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/hydraulic/result.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/result.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/WDSLib.dir/hydraulic/result.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/hydraulic/result.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/result.cc

CMakeFiles/WDSLib.dir/hydraulic/result.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/hydraulic/result.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/result.cc > CMakeFiles/WDSLib.dir/hydraulic/result.cc.i

CMakeFiles/WDSLib.dir/hydraulic/result.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/hydraulic/result.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/result.cc -o CMakeFiles/WDSLib.dir/hydraulic/result.cc.s

CMakeFiles/WDSLib.dir/hydraulic/result.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/hydraulic/result.cc.o.requires

CMakeFiles/WDSLib.dir/hydraulic/result.cc.o.provides: CMakeFiles/WDSLib.dir/hydraulic/result.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/hydraulic/result.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/hydraulic/result.cc.o.provides

CMakeFiles/WDSLib.dir/hydraulic/result.cc.o.provides.build: CMakeFiles/WDSLib.dir/hydraulic/result.cc.o


CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/solver.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/solver.cc

CMakeFiles/WDSLib.dir/hydraulic/solver.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/hydraulic/solver.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/solver.cc > CMakeFiles/WDSLib.dir/hydraulic/solver.cc.i

CMakeFiles/WDSLib.dir/hydraulic/solver.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/hydraulic/solver.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/solver.cc -o CMakeFiles/WDSLib.dir/hydraulic/solver.cc.s

CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o.requires

CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o.provides: CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o.provides

CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o.provides.build: CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o


CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/GGA/GGAsolver.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/GGA/GGAsolver.cc

CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/GGA/GGAsolver.cc > CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.i

CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/GGA/GGAsolver.cc -o CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.s

CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o.requires

CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o.provides: CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o.provides

CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o.provides.build: CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o


CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o: CMakeFiles/WDSLib.dir/flags.make
CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o: /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/RCTM/RCTMsolver.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o -c /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/RCTM/RCTMsolver.cc

CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/RCTM/RCTMsolver.cc > CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.i

CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master/hydraulic/RCTM/RCTMsolver.cc -o CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.s

CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o.requires:

.PHONY : CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o.requires

CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o.provides: CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o.requires
	$(MAKE) -f CMakeFiles/WDSLib.dir/build.make CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o.provides.build
.PHONY : CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o.provides

CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o.provides.build: CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o


# Object files for target WDSLib
WDSLib_OBJECTS = \
"CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o" \
"CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o" \
"CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o" \
"CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o" \
"CMakeFiles/WDSLib.dir/Network/Net.cc.o" \
"CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o" \
"CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o" \
"CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o" \
"CMakeFiles/WDSLib.dir/math/Matrix.cc.o" \
"CMakeFiles/WDSLib.dir/IO/Input.cc.o" \
"CMakeFiles/WDSLib.dir/hydraulic/result.cc.o" \
"CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o" \
"CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o" \
"CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o"

# External object files for target WDSLib
WDSLib_EXTERNAL_OBJECTS =

libWDSLib.a: CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/Network/Net.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/math/Matrix.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/IO/Input.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/hydraulic/result.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o
libWDSLib.a: CMakeFiles/WDSLib.dir/build.make
libWDSLib.a: CMakeFiles/WDSLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX static library libWDSLib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/WDSLib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WDSLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WDSLib.dir/build: libWDSLib.a

.PHONY : CMakeFiles/WDSLib.dir/build

CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/Simulation/Simulation.cc.o.requires
CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/Simulation/ELVA.cc.o.requires
CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/Simulation/Flag.cc.o.requires
CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/Simulation/Parameter.cc.o.requires
CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/Network/Net.cc.o.requires
CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/Network/Edge/PIPES/pipe.cc.o.requires
CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/Network/Vertex/NODE/node.cc.o.requires
CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/Network/Geometry/topology.cc.o.requires
CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/math/Matrix.cc.o.requires
CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/IO/Input.cc.o.requires
CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/hydraulic/result.cc.o.requires
CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/hydraulic/solver.cc.o.requires
CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/hydraulic/GGA/GGAsolver.cc.o.requires
CMakeFiles/WDSLib.dir/requires: CMakeFiles/WDSLib.dir/hydraulic/RCTM/RCTMsolver.cc.o.requires

.PHONY : CMakeFiles/WDSLib.dir/requires

CMakeFiles/WDSLib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WDSLib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WDSLib.dir/clean

CMakeFiles/WDSLib.dir/depend:
	cd "/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master /home/mengningqiu/Desktop/WDSLib-1.0/WDSLib-master "/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build" "/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build" "/home/mengningqiu/Desktop/WDSLib-1.0/Linux Build/CMakeFiles/WDSLib.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/WDSLib.dir/depend

