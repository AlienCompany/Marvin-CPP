cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)

set(COMMON_CPPS PhysicalLeg.cpp Legs.cpp Leg.cpp RemoteLeg.cpp)
set(COMMON_HS PhysicalLeg.h Legs.h LegState.h Side.h Leg.h RemoteLeg.h)

set(PROJECT_NAME_BIS MarvinBis)
project(${PROJECT_NAME_BIS})

#### Uncomment below additional settings as needed.
set(${PROJECT_NAME_BIS}_SRCS main2.cpp ${COMMON_CPPS})
set(${PROJECT_NAME_BIS}_HDRS ${COMMON_HS})
set(${PROJECT_NAME_BIS}_BOARD uno)
set(${PROJECT_NAME_BIS}_PORT COM7)
set(mega.build.mcu atmega2560)
set(mega.upload.protocol wiring)
set(mega.upload.speed 115200)

generate_arduino_firmware(${PROJECT_NAME_BIS})


set(PROJECT_NAME Marvin)
project(${PROJECT_NAME})

#### Uncomment below additional settings as needed.
set(${CMAKE_PROJECT_NAME}_SRCS main1.cpp ${COMMON_CPPS})
set(${CMAKE_PROJECT_NAME}_HDRS ${COMMON_HS})
set(${CMAKE_PROJECT_NAME}_BOARD uno)
set(${CMAKE_PROJECT_NAME}_PORT COM7)
set(mega.build.mcu atmega2560)
set(mega.upload.protocol wiring)
set(mega.upload.speed 115200)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})


