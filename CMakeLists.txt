cmake_minimum_required(VERSION 3.1...3.15)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(LOCAL_PROJECT_VERSION     "0.0.1")
set(LOCAL_PROJECT_VENDOR      "Calvin University")
set(LOCAL_PROJECT_NAMESPACE   "LoTide")
set(LOCAL_PROJECT_NAME        "lotide")
set(LOCAL_PROJECT_OUTPUT_NAME "lotide")
set(LOCAL_PROJECT_DESCRIPTION "LoTide DAW")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Set the project name
project(${LOCAL_PROJECT_NAME}
		VERSION ${LOCAL_PROJECT_VERSION}
		DESCRIPTION ${LOCAL_PROJECT_DESCRIPTION}
		LANGUAGES C CXX)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
	option(GIT_SUBMODULE "Check submodules during build" ON)
	if(GIT_SUBMODULE)
		message(STATUS "Submodule update")
		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive  --remote
						WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
						RESULT_VARIABLE GIT_SUBMOD_RESULT)
		if(NOT GIT_SUBMOD_RESULT EQUAL "0")
			message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
		endif()
	endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/TSAL")
	message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/cereal")
	message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/json/")
	message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")


# list(APPEND CMAKE_PREFIX_PATH "/opt/grpc" "/opt/protobuf")

# find_package(Protobuf REQUIRED)
# find_package(GRPC REQUIRED)

add_subdirectory(tests)

add_subdirectory(extern)

add_subdirectory(src)
