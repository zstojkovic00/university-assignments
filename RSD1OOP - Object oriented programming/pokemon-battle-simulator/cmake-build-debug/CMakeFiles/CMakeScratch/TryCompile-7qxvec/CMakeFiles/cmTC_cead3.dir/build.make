# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.25

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "E:\Zeljko\Singidunum\Druga Godina\Object Oriented Programming 2\ZeljkoStojkovic\FinalExam\pokemon-battle-simulator\cmake-build-debug\CMakeFiles\CMakeScratch\TryCompile-7qxvec"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "E:\Zeljko\Singidunum\Druga Godina\Object Oriented Programming 2\ZeljkoStojkovic\FinalExam\pokemon-battle-simulator\cmake-build-debug\CMakeFiles\CMakeScratch\TryCompile-7qxvec"

# Include any dependencies generated for this target.
include CMakeFiles/cmTC_cead3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cmTC_cead3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cmTC_cead3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmTC_cead3.dir/flags.make

CMakeFiles/cmTC_cead3.dir/CMakeCXXCompilerABI.cpp.obj: CMakeFiles/cmTC_cead3.dir/flags.make
CMakeFiles/cmTC_cead3.dir/CMakeCXXCompilerABI.cpp.obj: C:/Program\ Files/JetBrains/CLion\ 2023.1/bin/cmake/win/x64/share/cmake-3.25/Modules/CMakeCXXCompilerABI.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir="E:\Zeljko\Singidunum\Druga Godina\Object Oriented Programming 2\ZeljkoStojkovic\FinalExam\pokemon-battle-simulator\cmake-build-debug\CMakeFiles\CMakeScratch\TryCompile-7qxvec\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cmTC_cead3.dir/CMakeCXXCompilerABI.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cmTC_cead3.dir\CMakeCXXCompilerABI.cpp.obj -c "C:\Program Files\JetBrains\CLion 2023.1\bin\cmake\win\x64\share\cmake-3.25\Modules\CMakeCXXCompilerABI.cpp"

CMakeFiles/cmTC_cead3.dir/CMakeCXXCompilerABI.cpp.i: cmake_force
	@echo Preprocessing CXX source to CMakeFiles/cmTC_cead3.dir/CMakeCXXCompilerABI.cpp.i
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files\JetBrains\CLion 2023.1\bin\cmake\win\x64\share\cmake-3.25\Modules\CMakeCXXCompilerABI.cpp" > CMakeFiles\cmTC_cead3.dir\CMakeCXXCompilerABI.cpp.i

CMakeFiles/cmTC_cead3.dir/CMakeCXXCompilerABI.cpp.s: cmake_force
	@echo Compiling CXX source to assembly CMakeFiles/cmTC_cead3.dir/CMakeCXXCompilerABI.cpp.s
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files\JetBrains\CLion 2023.1\bin\cmake\win\x64\share\cmake-3.25\Modules\CMakeCXXCompilerABI.cpp" -o CMakeFiles\cmTC_cead3.dir\CMakeCXXCompilerABI.cpp.s

# Object files for target cmTC_cead3
cmTC_cead3_OBJECTS = \
"CMakeFiles/cmTC_cead3.dir/CMakeCXXCompilerABI.cpp.obj"

# External object files for target cmTC_cead3
cmTC_cead3_EXTERNAL_OBJECTS =

cmTC_cead3.exe: CMakeFiles/cmTC_cead3.dir/CMakeCXXCompilerABI.cpp.obj
cmTC_cead3.exe: CMakeFiles/cmTC_cead3.dir/build.make
cmTC_cead3.exe: CMakeFiles/cmTC_cead3.dir/objects1
cmTC_cead3.exe: CMakeFiles/cmTC_cead3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir="E:\Zeljko\Singidunum\Druga Godina\Object Oriented Programming 2\ZeljkoStojkovic\FinalExam\pokemon-battle-simulator\cmake-build-debug\CMakeFiles\CMakeScratch\TryCompile-7qxvec\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cmTC_cead3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cmTC_cead3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmTC_cead3.dir/build: cmTC_cead3.exe
.PHONY : CMakeFiles/cmTC_cead3.dir/build

CMakeFiles/cmTC_cead3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cmTC_cead3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cmTC_cead3.dir/clean

CMakeFiles/cmTC_cead3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "E:\Zeljko\Singidunum\Druga Godina\Object Oriented Programming 2\ZeljkoStojkovic\FinalExam\pokemon-battle-simulator\cmake-build-debug\CMakeFiles\CMakeScratch\TryCompile-7qxvec" "E:\Zeljko\Singidunum\Druga Godina\Object Oriented Programming 2\ZeljkoStojkovic\FinalExam\pokemon-battle-simulator\cmake-build-debug\CMakeFiles\CMakeScratch\TryCompile-7qxvec" "E:\Zeljko\Singidunum\Druga Godina\Object Oriented Programming 2\ZeljkoStojkovic\FinalExam\pokemon-battle-simulator\cmake-build-debug\CMakeFiles\CMakeScratch\TryCompile-7qxvec" "E:\Zeljko\Singidunum\Druga Godina\Object Oriented Programming 2\ZeljkoStojkovic\FinalExam\pokemon-battle-simulator\cmake-build-debug\CMakeFiles\CMakeScratch\TryCompile-7qxvec" "E:\Zeljko\Singidunum\Druga Godina\Object Oriented Programming 2\ZeljkoStojkovic\FinalExam\pokemon-battle-simulator\cmake-build-debug\CMakeFiles\CMakeScratch\TryCompile-7qxvec\CMakeFiles\cmTC_cead3.dir\DependInfo.cmake"
.PHONY : CMakeFiles/cmTC_cead3.dir/depend

