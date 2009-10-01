set(blok_SRCS 
    main.cpp 
    blokitem.cpp
    blokengine.cpp
    mainwindow.cpp
   )

kde4_add_executable(blok ${blok_SRCS})
target_link_libraries(blok ${GLUON_LIBRARY})

install(TARGETS blok DESTINATION ${BIN_INSTALL_DIR})
install(FILES blokui.rc DESTINATION ${DATA_INSTALL_DIR}/blok)
