# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.3.3\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.3.3\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Work\pycharm\cglcpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Work\pycharm\cglcpp\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/conway.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/conway.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/conway.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/conway.dir/flags.make

CMakeFiles/conway.dir/main.cpp.obj: CMakeFiles/conway.dir/flags.make
CMakeFiles/conway.dir/main.cpp.obj: D:/Work/pycharm/cglcpp/main.cpp
CMakeFiles/conway.dir/main.cpp.obj: CMakeFiles/conway.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Work\pycharm\cglcpp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/conway.dir/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/conway.dir/main.cpp.obj -MF CMakeFiles\conway.dir\main.cpp.obj.d -o CMakeFiles\conway.dir\main.cpp.obj -c D:\Work\pycharm\cglcpp\main.cpp

CMakeFiles/conway.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conway.dir/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Work\pycharm\cglcpp\main.cpp > CMakeFiles\conway.dir\main.cpp.i

CMakeFiles/conway.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conway.dir/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Work\pycharm\cglcpp\main.cpp -o CMakeFiles\conway.dir\main.cpp.s

# Object files for target conway
conway_OBJECTS = \
"CMakeFiles/conway.dir/main.cpp.obj"

# External object files for target conway
conway_EXTERNAL_OBJECTS =

conway.exe: CMakeFiles/conway.dir/main.cpp.obj
conway.exe: CMakeFiles/conway.dir/build.make
conway.exe: CMakeFiles/conway.dir/linklibs.rsp
conway.exe: CMakeFiles/conway.dir/objects1.rsp
conway.exe: CMakeFiles/conway.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Work\pycharm\cglcpp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable conway.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\conway.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/conway.dir/build: conway.exe
.PHONY : CMakeFiles/conway.dir/build

CMakeFiles/conway.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\conway.dir\cmake_clean.cmake
.PHONY : CMakeFiles/conway.dir/clean

CMakeFiles/conway.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Work\pycharm\cglcpp D:\Work\pycharm\cglcpp D:\Work\pycharm\cglcpp\cmake-build-debug D:\Work\pycharm\cglcpp\cmake-build-debug D:\Work\pycharm\cglcpp\cmake-build-debug\CMakeFiles\conway.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/conway.dir/depend

