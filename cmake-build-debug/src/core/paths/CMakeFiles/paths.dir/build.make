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
CMAKE_COMMAND = /home/denis/Downloads/clion-2016.3.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/denis/Downloads/clion-2016.3.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/denis/Projects/client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/denis/Projects/client/cmake-build-debug

# Include any dependencies generated for this target.
include src/core/paths/CMakeFiles/paths.dir/depend.make

# Include the progress variables for this target.
include src/core/paths/CMakeFiles/paths.dir/progress.make

# Include the compile flags for this target's objects.
include src/core/paths/CMakeFiles/paths.dir/flags.make

src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.o: src/core/paths/CMakeFiles/paths.dir/flags.make
src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.o: ../src/core/paths/PathsManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/denis/Projects/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.o"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/paths && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/paths.dir/PathsManager.cpp.o -c /home/denis/Projects/client/src/core/paths/PathsManager.cpp

src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/paths.dir/PathsManager.cpp.i"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/paths && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/denis/Projects/client/src/core/paths/PathsManager.cpp > CMakeFiles/paths.dir/PathsManager.cpp.i

src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/paths.dir/PathsManager.cpp.s"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/paths && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/denis/Projects/client/src/core/paths/PathsManager.cpp -o CMakeFiles/paths.dir/PathsManager.cpp.s

src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.o.requires:

.PHONY : src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.o.requires

src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.o.provides: src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.o.requires
	$(MAKE) -f src/core/paths/CMakeFiles/paths.dir/build.make src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.o.provides.build
.PHONY : src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.o.provides

src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.o.provides.build: src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.o


# Object files for target paths
paths_OBJECTS = \
"CMakeFiles/paths.dir/PathsManager.cpp.o"

# External object files for target paths
paths_EXTERNAL_OBJECTS =

src/core/paths/libpaths.a: src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.o
src/core/paths/libpaths.a: src/core/paths/CMakeFiles/paths.dir/build.make
src/core/paths/libpaths.a: src/core/paths/CMakeFiles/paths.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/denis/Projects/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libpaths.a"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/paths && $(CMAKE_COMMAND) -P CMakeFiles/paths.dir/cmake_clean_target.cmake
	cd /home/denis/Projects/client/cmake-build-debug/src/core/paths && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/paths.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/core/paths/CMakeFiles/paths.dir/build: src/core/paths/libpaths.a

.PHONY : src/core/paths/CMakeFiles/paths.dir/build

src/core/paths/CMakeFiles/paths.dir/requires: src/core/paths/CMakeFiles/paths.dir/PathsManager.cpp.o.requires

.PHONY : src/core/paths/CMakeFiles/paths.dir/requires

src/core/paths/CMakeFiles/paths.dir/clean:
	cd /home/denis/Projects/client/cmake-build-debug/src/core/paths && $(CMAKE_COMMAND) -P CMakeFiles/paths.dir/cmake_clean.cmake
.PHONY : src/core/paths/CMakeFiles/paths.dir/clean

src/core/paths/CMakeFiles/paths.dir/depend:
	cd /home/denis/Projects/client/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/denis/Projects/client /home/denis/Projects/client/src/core/paths /home/denis/Projects/client/cmake-build-debug /home/denis/Projects/client/cmake-build-debug/src/core/paths /home/denis/Projects/client/cmake-build-debug/src/core/paths/CMakeFiles/paths.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/core/paths/CMakeFiles/paths.dir/depend

