cmake_minimum_required(VERSION 3.16)
project(rpi_lcd_game)

set(CMAKE_CXX_STANDARD 14)

add_executable(rpi_lcd_game main.cpp GameClasses/Player.cpp GameClasses/Player.h GameClasses/Item.cpp GameClasses/Item.h GameClasses/Smudge.cpp GameClasses/Smudge.h)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(rpi_lcd_game ${WIRINGPI_LIBRARIES})
find_library(LCD_LIBRARIES NAMES wiringPiDev)
target_link_libraries(rpi_lcd_game ${LCD_LIBRARIES})