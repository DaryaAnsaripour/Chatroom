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
include CMakeFiles/database.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/database.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/database.dir/flags.make

CMakeFiles/database.dir/src/main.cpp.o: CMakeFiles/database.dir/flags.make
CMakeFiles/database.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/darya/Documents/AP/Chatroom/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/database.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/database.dir/src/main.cpp.o -c /home/darya/Documents/AP/Chatroom/server/src/main.cpp

CMakeFiles/database.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/database.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darya/Documents/AP/Chatroom/server/src/main.cpp > CMakeFiles/database.dir/src/main.cpp.i

CMakeFiles/database.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/database.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darya/Documents/AP/Chatroom/server/src/main.cpp -o CMakeFiles/database.dir/src/main.cpp.s

CMakeFiles/database.dir/src/Timestamp.cpp.o: CMakeFiles/database.dir/flags.make
CMakeFiles/database.dir/src/Timestamp.cpp.o: src/Timestamp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/darya/Documents/AP/Chatroom/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/database.dir/src/Timestamp.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/database.dir/src/Timestamp.cpp.o -c /home/darya/Documents/AP/Chatroom/server/src/Timestamp.cpp

CMakeFiles/database.dir/src/Timestamp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/database.dir/src/Timestamp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darya/Documents/AP/Chatroom/server/src/Timestamp.cpp > CMakeFiles/database.dir/src/Timestamp.cpp.i

CMakeFiles/database.dir/src/Timestamp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/database.dir/src/Timestamp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darya/Documents/AP/Chatroom/server/src/Timestamp.cpp -o CMakeFiles/database.dir/src/Timestamp.cpp.s

CMakeFiles/database.dir/src/Tablefile.cpp.o: CMakeFiles/database.dir/flags.make
CMakeFiles/database.dir/src/Tablefile.cpp.o: src/Tablefile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/darya/Documents/AP/Chatroom/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/database.dir/src/Tablefile.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/database.dir/src/Tablefile.cpp.o -c /home/darya/Documents/AP/Chatroom/server/src/Tablefile.cpp

CMakeFiles/database.dir/src/Tablefile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/database.dir/src/Tablefile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/darya/Documents/AP/Chatroom/server/src/Tablefile.cpp > CMakeFiles/database.dir/src/Tablefile.cpp.i

CMakeFiles/database.dir/src/Tablefile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/database.dir/src/Tablefile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/darya/Documents/AP/Chatroom/server/src/Tablefile.cpp -o CMakeFiles/database.dir/src/Tablefile.cpp.s

# Object files for target database
database_OBJECTS = \
"CMakeFiles/database.dir/src/main.cpp.o" \
"CMakeFiles/database.dir/src/Timestamp.cpp.o" \
"CMakeFiles/database.dir/src/Tablefile.cpp.o"

# External object files for target database
database_EXTERNAL_OBJECTS =

database: CMakeFiles/database.dir/src/main.cpp.o
database: CMakeFiles/database.dir/src/Timestamp.cpp.o
database: CMakeFiles/database.dir/src/Tablefile.cpp.o
database: CMakeFiles/database.dir/build.make
database: CMakeFiles/database.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/darya/Documents/AP/Chatroom/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable database"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/database.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/database.dir/build: database

.PHONY : CMakeFiles/database.dir/build

CMakeFiles/database.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/database.dir/cmake_clean.cmake
.PHONY : CMakeFiles/database.dir/clean

CMakeFiles/database.dir/depend:
	cd /home/darya/Documents/AP/Chatroom/server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/darya/Documents/AP/Chatroom/server /home/darya/Documents/AP/Chatroom/server /home/darya/Documents/AP/Chatroom/server /home/darya/Documents/AP/Chatroom/server /home/darya/Documents/AP/Chatroom/server/CMakeFiles/database.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/database.dir/depend

