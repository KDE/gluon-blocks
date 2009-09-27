project(blok)

find_package(KDE4 REQUIRED)
find_package(Gluon REQUIRED)

include_directories(${KDE4_INCLUDES} ${GLUON_INCLUDES})

include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

add_subdirectory(game)
add_subdirectory(editor)
add_subdirectory(data)
