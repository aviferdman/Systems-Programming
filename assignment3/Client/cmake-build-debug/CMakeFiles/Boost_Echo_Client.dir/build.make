# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /users/studs/bsc/2020/skidanov/Desktop/clion-2019.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /users/studs/bsc/2020/skidanov/Desktop/clion-2019.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Boost_Echo_Client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Boost_Echo_Client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Boost_Echo_Client.dir/flags.make

CMakeFiles/Boost_Echo_Client.dir/src/connectionHandler.cpp.o: CMakeFiles/Boost_Echo_Client.dir/flags.make
CMakeFiles/Boost_Echo_Client.dir/src/connectionHandler.cpp.o: ../src/connectionHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Boost_Echo_Client.dir/src/connectionHandler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Boost_Echo_Client.dir/src/connectionHandler.cpp.o -c /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/src/connectionHandler.cpp

CMakeFiles/Boost_Echo_Client.dir/src/connectionHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boost_Echo_Client.dir/src/connectionHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/src/connectionHandler.cpp > CMakeFiles/Boost_Echo_Client.dir/src/connectionHandler.cpp.i

CMakeFiles/Boost_Echo_Client.dir/src/connectionHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boost_Echo_Client.dir/src/connectionHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/src/connectionHandler.cpp -o CMakeFiles/Boost_Echo_Client.dir/src/connectionHandler.cpp.s

CMakeFiles/Boost_Echo_Client.dir/src/echoClient.cpp.o: CMakeFiles/Boost_Echo_Client.dir/flags.make
CMakeFiles/Boost_Echo_Client.dir/src/echoClient.cpp.o: ../src/echoClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Boost_Echo_Client.dir/src/echoClient.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Boost_Echo_Client.dir/src/echoClient.cpp.o -c /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/src/echoClient.cpp

CMakeFiles/Boost_Echo_Client.dir/src/echoClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boost_Echo_Client.dir/src/echoClient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/src/echoClient.cpp > CMakeFiles/Boost_Echo_Client.dir/src/echoClient.cpp.i

CMakeFiles/Boost_Echo_Client.dir/src/echoClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boost_Echo_Client.dir/src/echoClient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/src/echoClient.cpp -o CMakeFiles/Boost_Echo_Client.dir/src/echoClient.cpp.s

CMakeFiles/Boost_Echo_Client.dir/src/IOThread.cpp.o: CMakeFiles/Boost_Echo_Client.dir/flags.make
CMakeFiles/Boost_Echo_Client.dir/src/IOThread.cpp.o: ../src/IOThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Boost_Echo_Client.dir/src/IOThread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Boost_Echo_Client.dir/src/IOThread.cpp.o -c /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/src/IOThread.cpp

CMakeFiles/Boost_Echo_Client.dir/src/IOThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boost_Echo_Client.dir/src/IOThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/src/IOThread.cpp > CMakeFiles/Boost_Echo_Client.dir/src/IOThread.cpp.i

CMakeFiles/Boost_Echo_Client.dir/src/IOThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boost_Echo_Client.dir/src/IOThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/src/IOThread.cpp -o CMakeFiles/Boost_Echo_Client.dir/src/IOThread.cpp.s

CMakeFiles/Boost_Echo_Client.dir/src/ServerThread.cpp.o: CMakeFiles/Boost_Echo_Client.dir/flags.make
CMakeFiles/Boost_Echo_Client.dir/src/ServerThread.cpp.o: ../src/ServerThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Boost_Echo_Client.dir/src/ServerThread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Boost_Echo_Client.dir/src/ServerThread.cpp.o -c /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/src/ServerThread.cpp

CMakeFiles/Boost_Echo_Client.dir/src/ServerThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boost_Echo_Client.dir/src/ServerThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/src/ServerThread.cpp > CMakeFiles/Boost_Echo_Client.dir/src/ServerThread.cpp.i

CMakeFiles/Boost_Echo_Client.dir/src/ServerThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boost_Echo_Client.dir/src/ServerThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/src/ServerThread.cpp -o CMakeFiles/Boost_Echo_Client.dir/src/ServerThread.cpp.s

# Object files for target Boost_Echo_Client
Boost_Echo_Client_OBJECTS = \
"CMakeFiles/Boost_Echo_Client.dir/src/connectionHandler.cpp.o" \
"CMakeFiles/Boost_Echo_Client.dir/src/echoClient.cpp.o" \
"CMakeFiles/Boost_Echo_Client.dir/src/IOThread.cpp.o" \
"CMakeFiles/Boost_Echo_Client.dir/src/ServerThread.cpp.o"

# External object files for target Boost_Echo_Client
Boost_Echo_Client_EXTERNAL_OBJECTS =

Boost_Echo_Client: CMakeFiles/Boost_Echo_Client.dir/src/connectionHandler.cpp.o
Boost_Echo_Client: CMakeFiles/Boost_Echo_Client.dir/src/echoClient.cpp.o
Boost_Echo_Client: CMakeFiles/Boost_Echo_Client.dir/src/IOThread.cpp.o
Boost_Echo_Client: CMakeFiles/Boost_Echo_Client.dir/src/ServerThread.cpp.o
Boost_Echo_Client: CMakeFiles/Boost_Echo_Client.dir/build.make
Boost_Echo_Client: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
Boost_Echo_Client: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
Boost_Echo_Client: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
Boost_Echo_Client: /usr/lib/x86_64-linux-gnu/libboost_system.so
Boost_Echo_Client: /usr/lib/x86_64-linux-gnu/libboost_regex.so
Boost_Echo_Client: CMakeFiles/Boost_Echo_Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Boost_Echo_Client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Boost_Echo_Client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Boost_Echo_Client.dir/build: Boost_Echo_Client

.PHONY : CMakeFiles/Boost_Echo_Client.dir/build

CMakeFiles/Boost_Echo_Client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Boost_Echo_Client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Boost_Echo_Client.dir/clean

CMakeFiles/Boost_Echo_Client.dir/depend:
	cd /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/cmake-build-debug /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/cmake-build-debug /users/studs/bsc/2020/skidanov/Downloads/Boost_Echo_Clientv3/Boost_Echo_Client/cmake-build-debug/CMakeFiles/Boost_Echo_Client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Boost_Echo_Client.dir/depend

