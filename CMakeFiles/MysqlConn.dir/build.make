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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zxe/Documents/MysqlConnectionPool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zxe/Documents/MysqlConnectionPool

# Include any dependencies generated for this target.
include CMakeFiles/MysqlConn.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MysqlConn.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MysqlConn.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MysqlConn.dir/flags.make

CMakeFiles/MysqlConn.dir/MysqlConn.cpp.o: CMakeFiles/MysqlConn.dir/flags.make
CMakeFiles/MysqlConn.dir/MysqlConn.cpp.o: MysqlConn.cpp
CMakeFiles/MysqlConn.dir/MysqlConn.cpp.o: CMakeFiles/MysqlConn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zxe/Documents/MysqlConnectionPool/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MysqlConn.dir/MysqlConn.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MysqlConn.dir/MysqlConn.cpp.o -MF CMakeFiles/MysqlConn.dir/MysqlConn.cpp.o.d -o CMakeFiles/MysqlConn.dir/MysqlConn.cpp.o -c /home/zxe/Documents/MysqlConnectionPool/MysqlConn.cpp

CMakeFiles/MysqlConn.dir/MysqlConn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MysqlConn.dir/MysqlConn.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zxe/Documents/MysqlConnectionPool/MysqlConn.cpp > CMakeFiles/MysqlConn.dir/MysqlConn.cpp.i

CMakeFiles/MysqlConn.dir/MysqlConn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MysqlConn.dir/MysqlConn.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zxe/Documents/MysqlConnectionPool/MysqlConn.cpp -o CMakeFiles/MysqlConn.dir/MysqlConn.cpp.s

# Object files for target MysqlConn
MysqlConn_OBJECTS = \
"CMakeFiles/MysqlConn.dir/MysqlConn.cpp.o"

# External object files for target MysqlConn
MysqlConn_EXTERNAL_OBJECTS =

MysqlConn: CMakeFiles/MysqlConn.dir/MysqlConn.cpp.o
MysqlConn: CMakeFiles/MysqlConn.dir/build.make
MysqlConn: CMakeFiles/MysqlConn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zxe/Documents/MysqlConnectionPool/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MysqlConn"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MysqlConn.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MysqlConn.dir/build: MysqlConn
.PHONY : CMakeFiles/MysqlConn.dir/build

CMakeFiles/MysqlConn.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MysqlConn.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MysqlConn.dir/clean

CMakeFiles/MysqlConn.dir/depend:
	cd /home/zxe/Documents/MysqlConnectionPool && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zxe/Documents/MysqlConnectionPool /home/zxe/Documents/MysqlConnectionPool /home/zxe/Documents/MysqlConnectionPool /home/zxe/Documents/MysqlConnectionPool /home/zxe/Documents/MysqlConnectionPool/CMakeFiles/MysqlConn.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MysqlConn.dir/depend

