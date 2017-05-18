#Include(/home/hauspie/CMakeToolchain-win32.cmake)

project(CODE_WAR_ASSEMBLER)


ADD_DEFINITIONS(-Wall)

IF($ENV{DEBUG})
  set(CMAKE_BUILD_TYPE Debug)
  set(DEBUG 1)
  ADD_DEFINITIONS(-D_DEBUG)
ELSE($ENV{DEBUG})
  set(CMAKE_BUILD_TYPE Release)
ENDIF($ENV{DEBUG})

find_package(Qt4 REQUIRED) # find and setup Qt4 for this project

# use network
SET(QT_USE_QGUI FALSE)

# use QT includes
include(${QT_USE_FILE})



set(SRCS
  src/main.cpp
  src/assembler.cpp
  src/instructions.cpp
  src/label.cpp
)

set(EXECUTABLE_OUTPUT_PATH "bin")

IF(DEBUG)
  set(EXECUTABLE_NAME cwasm_d)
ELSE(DEBUG)
  set(EXECUTABLE_NAME cwasm)
#  ADD_DEFINITIONS(-DQT_NO_DEBUG_OUTPUT)
  ADD_DEFINITIONS(-DCWASM_NO_DEBUG_OUTPUT)
ENDIF(DEBUG)

add_executable(${EXECUTABLE_NAME} ${SRCS})
target_link_libraries(${EXECUTABLE_NAME} ${QT_LIBRARIES})
