project(blok)

find_package(KDE4 REQUIRED)
find_package(Gluon REQUIRED)

include_directories(${KDE4_INCLUDES} ${GLUON_INCLUDES})

include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(blok_SRCS 
    main.cpp 
    blokitem.cpp
    blokengine.cpp
    mainwindow.cpp
   )

kde4_add_executable(blok ${blok_SRCS})
target_link_libraries(blok ${GLUON_LIBRARY})
