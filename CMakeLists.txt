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

# Project's Header Files
file(GLOB_RECURSE ${PROJECT_NAME}_SOURCE
	"${CMAKE_CURRENT_SOURCE_DIR}/Red/*.h"
)

# Remove Windows Headers Manually. Really Need a Better Solution to This
foreach(ITEM ${${PROJECT_NAME}_SOURCE})
	if(${ITEM} MATCHES "${PROJECT_NAME}_SOURCE/Red/Window/Windows/*.h")
		list(REMOVE_ITEM ${PROJECT_NAME}_SOURCE ${ITEM})
	endif()
endforeach()
foreach(ITEM ${${PROJECT_NAME}_SOURCE})
	if(${ITEM} MATCHES "${PROJECT_NAME}_SOURCE/Red/Thread/Windows/*.h")
		list(REMOVE_ITEM ${PROJECT_NAME}_SOURCE ${ITEM})
	endif()
endforeach()
foreach(ITEM ${${PROJECT_NAME}_SOURCE})
	if(${ITEM} MATCHES "${PROJECT_NAME}_SOURCE/Red/Debug/Windows/*.h")
		list(REMOVE_ITEM ${PROJECT_NAME}_SOURCE ${ITEM})
	endif()
endforeach()

# Windows Specific Source Files
set(${PROJECT_NAME}_WINDOWSSOURCE
	"Red/Hardware/Windows/WindowsHardware.cpp"
	"Red/Network/BSD/BSDSocket.cpp"
	"Red/Network/BSD/BSDSocketSubsystem.cpp"
	"Red/Thread/Windows/WindowsCriticalSection.cpp"
	"Red/Debug/Windows/WindowsStackTrace.cpp"
)

# Unix Specific Source Files
set(${PROJECT_NAME}_UNIXSOURCE
	"Red/Hardware/Linux/LinuxHardware.cpp"
	"Red/Network/BSD/BSDSocket.cpp"
	"Red/Network/BSD/BSDSocketSubsystem.cpp"
	"Red/Thread/POSIX/POSIXCriticalSection.cpp"
	"Red/Debug/Linux/LinuxStackTrace.cpp"
)

# Fill Master Source File List
if(UNIX)
	list(APPEND ${PROJECT_NAME}_SOURCE ${${PROJECT_NAME}_UNIXSOURCE})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	list(APPEND ${PROJECT_NAME}_SOURCE ${${PROJECT_NAME}_WINDOWSSOURCE})
endif()

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCE})

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

foreach(ITEM ${TEST_SOURCE})
	if(${ITEM} MATCHES "${CMAKE_CURRENT_SOURCE_DIR}/Test/Hardware/Windows/Test_WindowsHardware.cpp" OR
	   ${ITEM} MATCHES "${CMAKE_CURRENT_SOURCE_DIR}/Test/Thread/Windows/Test_WindowsCriticalSection.cpp" OR
	   ${ITEM} MATCHES "${CMAKE_CURRENT_SOURCE_DIR}/Test/Window/Windows/Test_WindowsWindow.cpp")
		list(REMOVE_ITEM TEST_SOURCE ${ITEM})
	endif()
endforeach()

add_executable(Test ${TEST_SOURCE})

add_dependencies(Test googletest)

target_link_libraries(Test googletest ${PROJECT_NAME} pthread)
