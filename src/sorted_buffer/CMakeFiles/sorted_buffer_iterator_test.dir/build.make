# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.1.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.1.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alex/brook

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alex/brook

# Include any dependencies generated for this target.
include src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/depend.make

# Include the progress variables for this target.
include src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/progress.make

# Include the compile flags for this target's objects.
include src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/flags.make

src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o: src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/flags.make
src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o: src/sorted_buffer/sorted_buffer_iterator_test.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/alex/brook/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o"
	cd /Users/alex/brook/src/sorted_buffer && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o -c /Users/alex/brook/src/sorted_buffer/sorted_buffer_iterator_test.cc

src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.i"
	cd /Users/alex/brook/src/sorted_buffer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/alex/brook/src/sorted_buffer/sorted_buffer_iterator_test.cc > CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.i

src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.s"
	cd /Users/alex/brook/src/sorted_buffer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/alex/brook/src/sorted_buffer/sorted_buffer_iterator_test.cc -o CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.s

src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o.requires:
.PHONY : src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o.requires

src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o.provides: src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o.requires
	$(MAKE) -f src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/build.make src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o.provides.build
.PHONY : src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o.provides

src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o.provides.build: src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o

# Object files for target sorted_buffer_iterator_test
sorted_buffer_iterator_test_OBJECTS = \
"CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o"

# External object files for target sorted_buffer_iterator_test
sorted_buffer_iterator_test_EXTERNAL_OBJECTS =

src/sorted_buffer/sorted_buffer_iterator_test: src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o
src/sorted_buffer/sorted_buffer_iterator_test: src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/build.make
src/sorted_buffer/sorted_buffer_iterator_test: src/gtest/libgtest_main.a
src/sorted_buffer/sorted_buffer_iterator_test: src/sorted_buffer/libsorted_buffer.a
src/sorted_buffer/sorted_buffer_iterator_test: src/strutil/libstrutil.a
src/sorted_buffer/sorted_buffer_iterator_test: src/base/libbase.a
src/sorted_buffer/sorted_buffer_iterator_test: src/gtest/libgtest.a
src/sorted_buffer/sorted_buffer_iterator_test: src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable sorted_buffer_iterator_test"
	cd /Users/alex/brook/src/sorted_buffer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sorted_buffer_iterator_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/build: src/sorted_buffer/sorted_buffer_iterator_test
.PHONY : src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/build

src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/requires: src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/sorted_buffer_iterator_test.cc.o.requires
.PHONY : src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/requires

src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/clean:
	cd /Users/alex/brook/src/sorted_buffer && $(CMAKE_COMMAND) -P CMakeFiles/sorted_buffer_iterator_test.dir/cmake_clean.cmake
.PHONY : src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/clean

src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/depend:
	cd /Users/alex/brook && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alex/brook /Users/alex/brook/src/sorted_buffer /Users/alex/brook /Users/alex/brook/src/sorted_buffer /Users/alex/brook/src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/sorted_buffer/CMakeFiles/sorted_buffer_iterator_test.dir/depend

