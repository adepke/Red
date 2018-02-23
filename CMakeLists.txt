cmake_minimum_required(VERSION 3.0)

project(Red)

option(ASSERTIONS "Use compile time and runtime assertions when possible" ON)
option(FORCEDINLINES "Force all inlines" OFF)
option(VEC_DOUBLE "Vectors allocate each component as doubles, increasing accuracy" OFF)
option(PRECOMPUTED_RAY "Precompute ray components to reduce execution overhead" OFF)

set (CMAKE_CXX_STANDARD 14)

option(COVERAGE "Build for code coverage analysis" OFF)

if(COVERAGE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

message(STATUS "System Name: ${CMAKE_SYSTEM}")
message(STATUS "System Processor: ${CMAKE_SYSTEM_PROCESSOR}")

set(${PROJECT_NAME}_SOURCE "")

set(${PROJECT_NAME}_WINDOWSSOURCE
	"Red/Hardware/Windows/WindowsHardware.cpp"
	"Red/Network/BSD/BSDSocket.cpp"
	"Red/Network/BSD/BSDSocketSubsystem.cpp"
	"Red/Thread/Windows/WindowsCriticalSection.cpp"
)

set(${PROJECT_NAME}_UNIXSOURCE
	"Red/Hardware/Linux/LinuxHardware.cpp"
	"Red/Network/BSD/BSDSocket.cpp"
	"Red/Network/BSD/BSDSocketSubsystem.cpp"
	"Red/Thread/POSIX/POSIXCriticalSection.cpp"
)

if(UNIX)
	list(APPEND ${PROJECT_NAME}_SOURCE ${${PROJECT_NAME}_UNIXSOURCE})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	list(APPEND ${PROJECT_NAME}_SOURCE ${${PROJECT_NAME}_WINDOWSSOURCE})
endif()

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCE})

#target_link_libraries(${PROJECT_NAME} ${SOLUTION_STATIC_LIB_DEPS} ${SOLUTION_GENERAL_DEPS})