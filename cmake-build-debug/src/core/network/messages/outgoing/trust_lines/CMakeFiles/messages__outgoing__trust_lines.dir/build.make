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
include src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/depend.make

# Include the progress variables for this target.
include src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/progress.make

# Include the compile flags for this target's objects.
include src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/flags.make

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/flags.make
src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o: ../src/core/network/messages/outgoing/trust_lines/CloseTrustLineMessage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/denis/Projects/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o -c /home/denis/Projects/client/src/core/network/messages/outgoing/trust_lines/CloseTrustLineMessage.cpp

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.i"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/denis/Projects/client/src/core/network/messages/outgoing/trust_lines/CloseTrustLineMessage.cpp > CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.i

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.s"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/denis/Projects/client/src/core/network/messages/outgoing/trust_lines/CloseTrustLineMessage.cpp -o CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.s

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o.requires:

.PHONY : src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o.requires

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o.provides: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o.requires
	$(MAKE) -f src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/build.make src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o.provides.build
.PHONY : src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o.provides

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o.provides.build: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o


src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/flags.make
src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o: ../src/core/network/messages/outgoing/trust_lines/OpenTrustLineMessage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/denis/Projects/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o -c /home/denis/Projects/client/src/core/network/messages/outgoing/trust_lines/OpenTrustLineMessage.cpp

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.i"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/denis/Projects/client/src/core/network/messages/outgoing/trust_lines/OpenTrustLineMessage.cpp > CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.i

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.s"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/denis/Projects/client/src/core/network/messages/outgoing/trust_lines/OpenTrustLineMessage.cpp -o CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.s

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o.requires:

.PHONY : src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o.requires

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o.provides: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o.requires
	$(MAKE) -f src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/build.make src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o.provides.build
.PHONY : src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o.provides

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o.provides.build: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o


src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/flags.make
src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o: ../src/core/network/messages/outgoing/trust_lines/SetTrustLineMessage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/denis/Projects/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o -c /home/denis/Projects/client/src/core/network/messages/outgoing/trust_lines/SetTrustLineMessage.cpp

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.i"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/denis/Projects/client/src/core/network/messages/outgoing/trust_lines/SetTrustLineMessage.cpp > CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.i

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.s"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/denis/Projects/client/src/core/network/messages/outgoing/trust_lines/SetTrustLineMessage.cpp -o CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.s

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o.requires:

.PHONY : src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o.requires

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o.provides: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o.requires
	$(MAKE) -f src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/build.make src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o.provides.build
.PHONY : src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o.provides

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o.provides.build: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o


# Object files for target messages__outgoing__trust_lines
messages__outgoing__trust_lines_OBJECTS = \
"CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o" \
"CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o" \
"CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o"

# External object files for target messages__outgoing__trust_lines
messages__outgoing__trust_lines_EXTERNAL_OBJECTS =

src/core/network/messages/outgoing/trust_lines/libmessages__outgoing__trust_lines.a: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o
src/core/network/messages/outgoing/trust_lines/libmessages__outgoing__trust_lines.a: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o
src/core/network/messages/outgoing/trust_lines/libmessages__outgoing__trust_lines.a: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o
src/core/network/messages/outgoing/trust_lines/libmessages__outgoing__trust_lines.a: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/build.make
src/core/network/messages/outgoing/trust_lines/libmessages__outgoing__trust_lines.a: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/denis/Projects/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libmessages__outgoing__trust_lines.a"
	cd /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines && $(CMAKE_COMMAND) -P CMakeFiles/messages__outgoing__trust_lines.dir/cmake_clean_target.cmake
	cd /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/messages__outgoing__trust_lines.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/build: src/core/network/messages/outgoing/trust_lines/libmessages__outgoing__trust_lines.a

.PHONY : src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/build

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/requires: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/CloseTrustLineMessage.cpp.o.requires
src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/requires: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/OpenTrustLineMessage.cpp.o.requires
src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/requires: src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/SetTrustLineMessage.cpp.o.requires

.PHONY : src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/requires

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/clean:
	cd /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines && $(CMAKE_COMMAND) -P CMakeFiles/messages__outgoing__trust_lines.dir/cmake_clean.cmake
.PHONY : src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/clean

src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/depend:
	cd /home/denis/Projects/client/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/denis/Projects/client /home/denis/Projects/client/src/core/network/messages/outgoing/trust_lines /home/denis/Projects/client/cmake-build-debug /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines /home/denis/Projects/client/cmake-build-debug/src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/core/network/messages/outgoing/trust_lines/CMakeFiles/messages__outgoing__trust_lines.dir/depend

