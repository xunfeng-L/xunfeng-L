# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = "D:\CLion\CLion 2021.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion\CLion 2021.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Code\duodao

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Code\duodao\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/duodao.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/duodao.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/duodao.dir/flags.make

CMakeFiles/duodao.dir/main.cpp.obj: CMakeFiles/duodao.dir/flags.make
CMakeFiles/duodao.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\duodao\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/duodao.dir/main.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\duodao.dir\main.cpp.obj -c D:\Code\duodao\main.cpp

CMakeFiles/duodao.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/duodao.dir/main.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\duodao\main.cpp > CMakeFiles\duodao.dir\main.cpp.i

CMakeFiles/duodao.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/duodao.dir/main.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\duodao\main.cpp -o CMakeFiles\duodao.dir\main.cpp.s

# Object files for target duodao
duodao_OBJECTS = \
"CMakeFiles/duodao.dir/main.cpp.obj"

# External object files for target duodao
duodao_EXTERNAL_OBJECTS =

duodao.exe: CMakeFiles/duodao.dir/main.cpp.obj
duodao.exe: CMakeFiles/duodao.dir/build.make
duodao.exe: CMakeFiles/duodao.dir/linklibs.rsp
duodao.exe: CMakeFiles/duodao.dir/objects1.rsp
duodao.exe: CMakeFiles/duodao.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Code\duodao\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable duodao.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\duodao.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/duodao.dir/build: duodao.exe

.PHONY : CMakeFiles/duodao.dir/build

CMakeFiles/duodao.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\duodao.dir\cmake_clean.cmake
.PHONY : CMakeFiles/duodao.dir/clean

CMakeFiles/duodao.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Code\duodao D:\Code\duodao D:\Code\duodao\cmake-build-debug D:\Code\duodao\cmake-build-debug D:\Code\duodao\cmake-build-debug\CMakeFiles\duodao.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/duodao.dir/depend
