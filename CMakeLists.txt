cmake_minimum_required(VERSION 3.1)

project(Red)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message(FATAL_ERROR "Windows Builds with CMake is Not Currently Supported. Use Build.bat Instead")
endif()

# Currently Overridden in Code
option(ASSERTIONS "Use compile time and runtime assertions when possible" ON)
option(FORCEDINLINES "Force all inlines" OFF)
option(VEC_DOUBLE "Vectors allocate each component as doubles, increasing accuracy" OFF)
option(PRECOMPUTED_RAY "Precompute ray components to reduce execution overhead" OFF)

# C++ 14 Required
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Apply Platform
set(PLATFORM "x64")
if(${PLATFORM} STREQUAL "x64")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
endif()

# Build For GCC Coverage?
option(COVERAGE "Build for code coverage analysis" OFF)
if(COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES GNU)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

message(STATUS "System Name: ${CMAKE_SYSTEM}")
message(STATUS "System Processor: ${CMAKE_SYSTEM_PROCESSOR}")

# Grab All Base Source Files. Don't Recursively Search
file(GLOB ${PROJECT_NAME}_SOURCE_BASE
	"${CMAKE_CURRENT_SOURCE_DIR}/Red/*/*.h"
)

# Declare Platform-Specific Source File Variable
set(${PROJECT_NAME}_SOURCE_PLATFORM "")

if(WIN32)
	# Windows Platform
	set(${PROJECT_NAME}_SOURCE_PLATFORM
		"Red/*/Windows/*.*"
		"Red/Network/BSD/*.*"
	)
elseif(APPLE)
	# Darwin Platform
	set(${PROJECT_NAME}_SOURCE_PLATFORM
		"Red/*/Darwin/*.*"
		"Red/*/BSD/*.*"
		"Red/*/POSIX/*.*"
		# Some Linux Sources Are Compatible, Include These
		"Red/Hardware/Linux/*.*"
		"Red/Debug/Linux/LinuxStackTrace.*"
	)
else(UNIX)
	# Linux Platform
	set(${PROJECT_NAME}_SOURCE_PLATFORM
		"Red/*/Linux/*.*"
		"Red/*/BSD/*.*"
		"Red/*/POSIX/*.*"
	)
endif()

# Combine Source File Lists
list(APPEND ${PROJECT_NAME}_SOURCE_BASE ${${PROJECT_NAME}_SOURCE_PLATFORM})

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCE_BASE})

add_custom_target(
	Update3rdParty
	COMMAND git submodule init
	COMMAND git submodule update
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set(GTEST_ROOT 3rdParty/googletest/googletest CACHE STRING "Google Test Root")

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/${GTEST_ROOT}"
	"${CMAKE_CURRENT_SOURCE_DIR}/${GTEST_ROOT}/include"
)

set(GTEST_SOURCE
	"${CMAKE_CURRENT_SOURCE_DIR}/${GTEST_ROOT}/src/gtest-all.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/${GTEST_ROOT}/src/gtest_main.cc"
)

# Mark Google Test Sources as Generated
foreach(SOURCE ${GTEST_SOURCE})
	set_source_files_properties(${SOURCE} PROPERTIES GENERATED 1)
endforeach()

add_library(googletest ${GTEST_SOURCE})

add_dependencies(googletest Update3rdParty)

# Find all Unit Tests
file(GLOB_RECURSE TEST_SOURCE
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/*.cpp"
)

# Manually Remove Windows Unit Tests
foreach(ITEM ${TEST_SOURCE})
	if(${ITEM} MATCHES "${CMAKE_CURRENT_SOURCE_DIR}/Test/**/Windows/*.cpp")
		list(REMOVE_ITEM TEST_SOURCE ${ITEM})
	endif()
endforeach()

add_executable(Test ${TEST_SOURCE})

add_dependencies(Test googletest)

target_link_libraries(Test googletest ${PROJECT_NAME} pthread)
