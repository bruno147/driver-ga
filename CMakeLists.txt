cmake_minimum_required(VERSION 2.8)

project(FSMDriver)
find_package(Boost REQUIRED COMPONENTS filesystem system)

# Source files:
include_directories(include FSMDriver)
set(SOURCES
	FSMDriver/FSMDriver.cpp
	# FSMDriver/StraightLine.cpp
	# FSMDriver/ApproachingCurve.cpp
	# FSMDriver/Curve.cpp
	FSMDriver/InsideTrack.cpp
	FSMDriver/TestTrack.cpp
	FSMDriver/GADriver.cpp
	FSMDriver/OutOfTrack.cpp
	FSMDriver/Stuck.cpp
	FSMDriver/Knowledge.cpp
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
add_executable(FSMDriver ${SOURCES})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(${CMAKE_SYSTEM_NAME})
    SET(OperatingSystem "Linux")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# GA Flag
 set(GA ON)

# GA
if(GA)
	include_directories(include Genetic_Algorithm)

	# set(ROULLETE ON)
	set(ELITISM ON)
	# GA source
	set(GA_SOURCES
		Genetic_Algorithm/Individual.cpp
		Genetic_Algorithm/GaAdapter.cpp
		Genetic_Algorithm/Chromosome.cpp
		Genetic_Algorithm/DriverGeneticAlgorithm.cpp
		)


	set(CMAKE_CXX_FLAGS "-g -Wall -O3 -std=c++0x -D ELITISM")

	add_executable(DriverGeneticAlgorithm ${GA_SOURCES})
	target_link_libraries(DriverGeneticAlgorithm ${Boost_LIBRARIES})
endif()
