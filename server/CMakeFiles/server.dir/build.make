# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/darya/Documents/AP/Chatroom/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/darya/Documents/AP/Chatroom/server

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/src/main.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/darya/Documents/AP/Chatroom/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/main.cpp.o -c /home/darya/Documents/AP/Chatroom/server/src/main.cpp

CMakeFiles/server.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darya/Documents/AP/Chatroom/server/src/main.cpp > CMakeFiles/server.dir/src/main.cpp.i

CMakeFiles/server.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darya/Documents/AP/Chatroom/server/src/main.cpp -o CMakeFiles/server.dir/src/main.cpp.s

CMakeFiles/server.dir/src/Timestamp.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/Timestamp.cpp.o: src/Timestamp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/darya/Documents/AP/Chatroom/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/src/Timestamp.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/Timestamp.cpp.o -c /home/darya/Documents/AP/Chatroom/server/src/Timestamp.cpp

CMakeFiles/server.dir/src/Timestamp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/Timestamp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darya/Documents/AP/Chatroom/server/src/Timestamp.cpp > CMakeFiles/server.dir/src/Timestamp.cpp.i

CMakeFiles/server.dir/src/Timestamp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/Timestamp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darya/Documents/AP/Chatroom/server/src/Timestamp.cpp -o CMakeFiles/server.dir/src/Timestamp.cpp.s

CMakeFiles/server.dir/src/Tablefile.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/Tablefile.cpp.o: src/Tablefile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/darya/Documents/AP/Chatroom/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/src/Tablefile.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/Tablefile.cpp.o -c /home/darya/Documents/AP/Chatroom/server/src/Tablefile.cpp

CMakeFiles/server.dir/src/Tablefile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/Tablefile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darya/Documents/AP/Chatroom/server/src/Tablefile.cpp > CMakeFiles/server.dir/src/Tablefile.cpp.i

CMakeFiles/server.dir/src/Tablefile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/Tablefile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darya/Documents/AP/Chatroom/server/src/Tablefile.cpp -o CMakeFiles/server.dir/src/Tablefile.cpp.s

CMakeFiles/server.dir/src/Userserver.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/Userserver.cpp.o: src/Userserver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/darya/Documents/AP/Chatroom/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/src/Userserver.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/Userserver.cpp.o -c /home/darya/Documents/AP/Chatroom/server/src/Userserver.cpp

CMakeFiles/server.dir/src/Userserver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/Userserver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darya/Documents/AP/Chatroom/server/src/Userserver.cpp > CMakeFiles/server.dir/src/Userserver.cpp.i

CMakeFiles/server.dir/src/Userserver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/Userserver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darya/Documents/AP/Chatroom/server/src/Userserver.cpp -o CMakeFiles/server.dir/src/Userserver.cpp.s

CMakeFiles/server.dir/src/User.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/User.cpp.o: src/User.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/darya/Documents/AP/Chatroom/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/server.dir/src/User.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/User.cpp.o -c /home/darya/Documents/AP/Chatroom/server/src/User.cpp

CMakeFiles/server.dir/src/User.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/User.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darya/Documents/AP/Chatroom/server/src/User.cpp > CMakeFiles/server.dir/src/User.cpp.i

CMakeFiles/server.dir/src/User.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/User.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darya/Documents/AP/Chatroom/server/src/User.cpp -o CMakeFiles/server.dir/src/User.cpp.s

CMakeFiles/server.dir/src/Group.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/Group.cpp.o: src/Group.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/darya/Documents/AP/Chatroom/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/server.dir/src/Group.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/Group.cpp.o -c /home/darya/Documents/AP/Chatroom/server/src/Group.cpp

CMakeFiles/server.dir/src/Group.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/Group.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darya/Documents/AP/Chatroom/server/src/Group.cpp > CMakeFiles/server.dir/src/Group.cpp.i

CMakeFiles/server.dir/src/Group.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/Group.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darya/Documents/AP/Chatroom/server/src/Group.cpp -o CMakeFiles/server.dir/src/Group.cpp.s

CMakeFiles/server.dir/src/Server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/Server.cpp.o: src/Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/darya/Documents/AP/Chatroom/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/server.dir/src/Server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/Server.cpp.o -c /home/darya/Documents/AP/Chatroom/server/src/Server.cpp

CMakeFiles/server.dir/src/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darya/Documents/AP/Chatroom/server/src/Server.cpp > CMakeFiles/server.dir/src/Server.cpp.i

CMakeFiles/server.dir/src/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darya/Documents/AP/Chatroom/server/src/Server.cpp -o CMakeFiles/server.dir/src/Server.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/src/main.cpp.o" \
"CMakeFiles/server.dir/src/Timestamp.cpp.o" \
"CMakeFiles/server.dir/src/Tablefile.cpp.o" \
"CMakeFiles/server.dir/src/Userserver.cpp.o" \
"CMakeFiles/server.dir/src/User.cpp.o" \
"CMakeFiles/server.dir/src/Group.cpp.o" \
"CMakeFiles/server.dir/src/Server.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/src/main.cpp.o
server: CMakeFiles/server.dir/src/Timestamp.cpp.o
server: CMakeFiles/server.dir/src/Tablefile.cpp.o
server: CMakeFiles/server.dir/src/Userserver.cpp.o
server: CMakeFiles/server.dir/src/User.cpp.o
server: CMakeFiles/server.dir/src/Group.cpp.o
server: CMakeFiles/server.dir/src/Server.cpp.o
server: CMakeFiles/server.dir/build.make
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/darya/Documents/AP/Chatroom/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/darya/Documents/AP/Chatroom/server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/darya/Documents/AP/Chatroom/server /home/darya/Documents/AP/Chatroom/server /home/darya/Documents/AP/Chatroom/server /home/darya/Documents/AP/Chatroom/server /home/darya/Documents/AP/Chatroom/server/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

