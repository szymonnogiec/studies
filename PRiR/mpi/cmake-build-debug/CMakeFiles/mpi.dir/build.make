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
CMAKE_COMMAND = /home/simon/Pobrane/clion-2016.3.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/simon/Pobrane/clion-2016.3.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/simon/dev/studies/PRiR/mpi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/simon/dev/studies/PRiR/mpi/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mpi.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mpi.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mpi.dir/flags.make

CMakeFiles/mpi.dir/main.cpp.o: CMakeFiles/mpi.dir/flags.make
CMakeFiles/mpi.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/simon/dev/studies/PRiR/mpi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mpi.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mpi.dir/main.cpp.o -c /home/simon/dev/studies/PRiR/mpi/main.cpp

CMakeFiles/mpi.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpi.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/simon/dev/studies/PRiR/mpi/main.cpp > CMakeFiles/mpi.dir/main.cpp.i

CMakeFiles/mpi.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpi.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/simon/dev/studies/PRiR/mpi/main.cpp -o CMakeFiles/mpi.dir/main.cpp.s

CMakeFiles/mpi.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/mpi.dir/main.cpp.o.requires

CMakeFiles/mpi.dir/main.cpp.o.provides: CMakeFiles/mpi.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/mpi.dir/build.make CMakeFiles/mpi.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/mpi.dir/main.cpp.o.provides

CMakeFiles/mpi.dir/main.cpp.o.provides.build: CMakeFiles/mpi.dir/main.cpp.o


CMakeFiles/mpi.dir/FileReader.cpp.o: CMakeFiles/mpi.dir/flags.make
CMakeFiles/mpi.dir/FileReader.cpp.o: ../FileReader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/simon/dev/studies/PRiR/mpi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mpi.dir/FileReader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mpi.dir/FileReader.cpp.o -c /home/simon/dev/studies/PRiR/mpi/FileReader.cpp

CMakeFiles/mpi.dir/FileReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpi.dir/FileReader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/simon/dev/studies/PRiR/mpi/FileReader.cpp > CMakeFiles/mpi.dir/FileReader.cpp.i

CMakeFiles/mpi.dir/FileReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpi.dir/FileReader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/simon/dev/studies/PRiR/mpi/FileReader.cpp -o CMakeFiles/mpi.dir/FileReader.cpp.s

CMakeFiles/mpi.dir/FileReader.cpp.o.requires:

.PHONY : CMakeFiles/mpi.dir/FileReader.cpp.o.requires

CMakeFiles/mpi.dir/FileReader.cpp.o.provides: CMakeFiles/mpi.dir/FileReader.cpp.o.requires
	$(MAKE) -f CMakeFiles/mpi.dir/build.make CMakeFiles/mpi.dir/FileReader.cpp.o.provides.build
.PHONY : CMakeFiles/mpi.dir/FileReader.cpp.o.provides

CMakeFiles/mpi.dir/FileReader.cpp.o.provides.build: CMakeFiles/mpi.dir/FileReader.cpp.o


CMakeFiles/mpi.dir/RSA.cpp.o: CMakeFiles/mpi.dir/flags.make
CMakeFiles/mpi.dir/RSA.cpp.o: ../RSA.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/simon/dev/studies/PRiR/mpi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mpi.dir/RSA.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mpi.dir/RSA.cpp.o -c /home/simon/dev/studies/PRiR/mpi/RSA.cpp

CMakeFiles/mpi.dir/RSA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpi.dir/RSA.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/simon/dev/studies/PRiR/mpi/RSA.cpp > CMakeFiles/mpi.dir/RSA.cpp.i

CMakeFiles/mpi.dir/RSA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpi.dir/RSA.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/simon/dev/studies/PRiR/mpi/RSA.cpp -o CMakeFiles/mpi.dir/RSA.cpp.s

CMakeFiles/mpi.dir/RSA.cpp.o.requires:

.PHONY : CMakeFiles/mpi.dir/RSA.cpp.o.requires

CMakeFiles/mpi.dir/RSA.cpp.o.provides: CMakeFiles/mpi.dir/RSA.cpp.o.requires
	$(MAKE) -f CMakeFiles/mpi.dir/build.make CMakeFiles/mpi.dir/RSA.cpp.o.provides.build
.PHONY : CMakeFiles/mpi.dir/RSA.cpp.o.provides

CMakeFiles/mpi.dir/RSA.cpp.o.provides.build: CMakeFiles/mpi.dir/RSA.cpp.o


# Object files for target mpi
mpi_OBJECTS = \
"CMakeFiles/mpi.dir/main.cpp.o" \
"CMakeFiles/mpi.dir/FileReader.cpp.o" \
"CMakeFiles/mpi.dir/RSA.cpp.o"

# External object files for target mpi
mpi_EXTERNAL_OBJECTS =

mpi: CMakeFiles/mpi.dir/main.cpp.o
mpi: CMakeFiles/mpi.dir/FileReader.cpp.o
mpi: CMakeFiles/mpi.dir/RSA.cpp.o
mpi: CMakeFiles/mpi.dir/build.make
mpi: /usr/lib/x86_64-linux-gnu/libmpichcxx.so
mpi: /usr/lib/x86_64-linux-gnu/libmpich.so
mpi: CMakeFiles/mpi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/simon/dev/studies/PRiR/mpi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable mpi"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mpi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mpi.dir/build: mpi

.PHONY : CMakeFiles/mpi.dir/build

CMakeFiles/mpi.dir/requires: CMakeFiles/mpi.dir/main.cpp.o.requires
CMakeFiles/mpi.dir/requires: CMakeFiles/mpi.dir/FileReader.cpp.o.requires
CMakeFiles/mpi.dir/requires: CMakeFiles/mpi.dir/RSA.cpp.o.requires

.PHONY : CMakeFiles/mpi.dir/requires

CMakeFiles/mpi.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mpi.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mpi.dir/clean

CMakeFiles/mpi.dir/depend:
	cd /home/simon/dev/studies/PRiR/mpi/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/simon/dev/studies/PRiR/mpi /home/simon/dev/studies/PRiR/mpi /home/simon/dev/studies/PRiR/mpi/cmake-build-debug /home/simon/dev/studies/PRiR/mpi/cmake-build-debug /home/simon/dev/studies/PRiR/mpi/cmake-build-debug/CMakeFiles/mpi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mpi.dir/depend
