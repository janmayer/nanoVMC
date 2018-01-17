cmake_minimum_required(VERSION 2.8.12)

project(nanoVMC)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -O2")

set(CMAKE_MODULE_PATH $ENV{GEANT4VMC_LIBRARY_DIR}/Geant4VMC-3.3.0/Modules ${CMAKE_MODULE_PATH})
include(UseVMC)

include_directories(
        ${VMC_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cxx)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/src/*.h)
list(REMOVE_ITEM HEADERS ${PROJECT_SOURCE_DIR}/src/LinkDef.h)

root_generate_dictionary(
        ${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}
        no_rootmap
        ${HEADERS}
        LINKDEF ${PROJECT_SOURCE_DIR}/src/LinkDef.h)

add_library(${PROJECT_NAME} ${SOURCES} ${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}_dict.cxx ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${VMC_LIBRARIES})
