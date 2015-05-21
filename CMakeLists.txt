cmake_minimum_required(VERSION 2.8)

project(FSMDriver)
find_package(Boost REQUIRED COMPONENTS filesystem system)

# Source files:
include_directories(include FSMDriver)
set(SOURCES
	FSMDriver/FSM.h
	FSMDriver/FSMDriver.h
	FSMDriver/FSMDriver.cpp
	FSMDriver/InsideTrack.cpp
	FSMDriver/OutOfTrack.cpp
	FSMDriver/TestTrack.cpp
	FSMDriver/Knowledge.cpp
	FSMDriver/Stuck.cpp
	FSMDriver/GADriver.cpp
	src/CarControl.cpp
	src/CarState.cpp
	src/client.cpp
	src/SimpleParser.cpp
	src/WrapperBaseDriver.cpp)

# Compiler flags
set(DRIVER FSMDriver)
set(EXTFLAGS "-D __DRIVER_CLASS__=${DRIVER} -D __DRIVER_INCLUDE__='\"${CMAKE_SOURCE_DIR}/${DRIVER}/${DRIVER}.h\"'")	
add_definitions(-g -O3 -Wall -std=c++0x ${EXTFLAGS})

# Executable
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(${DRIVER} ${SOURCES})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(${CMAKE_SYSTEM_NAME})
    SET(OperatingSystem "Linux")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# GA Flag
 set(GA ON)

# GA
if(GA)
	include_directories(include FSMDriver_Genetic_Algorithm)

	# set(ROULLETE ON)
	set(ELITISM ON)
	# GA source
	set(GA_SOURCES
		FSMDriver_Genetic_Algorithm/VEGA.cpp
		FSMDriver_Genetic_Algorithm/Chromosome.cpp
		FSMDriver_Genetic_Algorithm/DriverGeneticAlgorithm.cpp
		)


	set(CMAKE_CXX_FLAGS "-g -Wall -O3 -std=c++0x -D ELITISM")

	add_executable(DriverGeneticAlgorithm ${GA_SOURCES})
	target_link_libraries(DriverGeneticAlgorithm ${Boost_LIBRARIES})
endif()
