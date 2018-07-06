cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)

set(COMMON_CPPS PhysicalLeg.cpp Legs.cpp Leg.cpp RemoteLeg.cpp Max7219.cpp HcSr04.cpp)
set(COMMON_HS PhysicalLeg.h Legs.h LegState.h Side.h Leg.h RemoteLeg.h Max7219.h Motor.h HcSr04.h)

set(PROJECT_BOARD pro)


#pro.upload.tool=avrdude
#pro.upload.protocol=arduino
#
#pro.bootloader.tool=avrdude
#pro.bootloader.unlock_bits=0x3F
#pro.bootloader.lock_bits=0x0F
#
#pro.build.board=AVR_PRO
#pro.build.core=arduino
#pro.build.variant=eightanaloginputs

set(${PROJECT_BOARD}.bootloader.tool avrdude)
set(${PROJECT_BOARD}.bootloader.unlock_bits 63)
set(${PROJECT_BOARD}.bootloader.lock_bits 15)
set(${PROJECT_BOARD}.bootloader.low_fuses 255)
set(${PROJECT_BOARD}.bootloader.high_fuses 218)
set(${PROJECT_BOARD}.bootloader.extended_fuses 5)
set(${PROJECT_BOARD}.bootloader.file atmega/ATmegaBOOT_168_atmega328.hex)

set(${PROJECT_BOARD}.build.mcu atmega328p)
set(${PROJECT_BOARD}.build.f_cpu 16000000L)
set(${PROJECT_BOARD}.build.board AVR_PRO)
set(${PROJECT_BOARD}.build.core arduino)
set(${PROJECT_BOARD}.build.variant eightanaloginputs)

set(${PROJECT_BOARD}.upload.tool avrdude)
set(${PROJECT_BOARD}.upload.protocol arduino) # wiring/stk500/arduino
set(${PROJECT_BOARD}.upload.speed 57600)
set(${PROJECT_BOARD}.upload.maximum_size 30720)
set(${PROJECT_BOARD}.upload.maximum_data_size 2048)


set(PORT COM15)

# ==================== MarvinTest : BEGIN ====================
set(PROJECT_NAME_TEST MarvinTest)
project(${PROJECT_NAME_TEST})

print_board_list()
#### Uncomment below additional settings as needed.
set(${PROJECT_NAME_TEST}_SRCS testMoteur.cpp ${COMMON_CPPS})
set(${PROJECT_NAME_TEST}_HDRS ${COMMON_HS})
set(${PROJECT_NAME_TEST}_BOARD ${PROJECT_BOARD})
set(${PROJECT_NAME_TEST}_PORT ${PORT})
set(${PROJECT_NAME_TEST}_ARDLIBS Servo)

generate_arduino_firmware(${PROJECT_NAME_TEST})
# ==================== MarvinTest : END ====================

# ==================== MarvinTestLed : BEGIN ====================
set(PROJECT_NAME_TEST_LED MarvinTestLed)
project(${PROJECT_NAME_TEST_LED})

#### Uncomment below additional settings as needed.
set(${PROJECT_NAME_TEST_LED}_SRCS testMatriceLed.cpp ${COMMON_CPPS})
set(${PROJECT_NAME_TEST_LED}_HDRS ${COMMON_HS})
set(${PROJECT_NAME_TEST_LED}_BOARD ${PROJECT_BOARD})
set(${PROJECT_NAME_TEST_LED}_PORT ${PORT})
set(${PROJECT_NAME_TEST_LED}_ARDLIBS Servo)

generate_arduino_firmware(${PROJECT_NAME_TEST_LED})
# ==================== MarvinTestLed : END ====================

# ==================== MarvinTestUS : BEGIN ====================
set(PROJECT_NAME_TEST_US MarvinTestUs)
project(${PROJECT_NAME_TEST_US})

#### Uncomment below additional settings as needed.
set(${PROJECT_NAME_TEST_US}_SRCS testUltraSon.cpp ${COMMON_CPPS})
set(${PROJECT_NAME_TEST_US}_HDRS ${COMMON_HS})
set(${PROJECT_NAME_TEST_US}_BOARD ${PROJECT_BOARD})
set(${PROJECT_NAME_TEST_US}_PORT ${PORT})
set(${PROJECT_NAME_TEST_US}_ARDLIBS Servo)

generate_arduino_firmware(${PROJECT_NAME_TEST_US})
# ==================== MarvinTestUS : END ====================

# ==================== MarvinBis : BEGIN ====================
set(PROJECT_NAME_BIS MarvinBis)
project(${PROJECT_NAME_BIS})

#### Uncomment below additional settings as needed.
set(${PROJECT_NAME_BIS}_SRCS main2.cpp ${COMMON_CPPS})
set(${PROJECT_NAME_BIS}_HDRS ${COMMON_HS})
set(${PROJECT_NAME_BIS}_BOARD ${PROJECT_BOARD})
set(${PROJECT_NAME_BIS}_PORT ${PORT})
set(${PROJECT_NAME_BIS}_ARDLIBS Servo)
generate_arduino_firmware(${PROJECT_NAME_BIS})
# ==================== MarvinBis : END ====================

# ==================== Marvin : BEGIN ====================
set(PROJECT_NAME Marvin)
project(${PROJECT_NAME})

#### Uncomment below additional settings as needed.
set(${CMAKE_PROJECT_NAME}_SRCS main1.cpp ${COMMON_CPPS})
set(${CMAKE_PROJECT_NAME}_HDRS ${COMMON_HS})
set(${CMAKE_PROJECT_NAME}_BOARD ${PROJECT_BOARD})
set(${CMAKE_PROJECT_NAME}_PORT ${PORT})
set(${CMAKE_PROJECT_NAME}_ARDLIBS Servo)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
# ==================== Marvin : END ====================


