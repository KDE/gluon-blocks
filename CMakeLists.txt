cmake_minimum_required(VERSION 2.6)
project(blok)


find_package(KDE4 REQUIRED)
find_package(Gluon REQUIRED)

include(KDE4Defaults)
include_directories(${KDE4_INCLUDES})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

add_subdirectory(game)
add_subdirectory(editor)
add_subdirectory(data)