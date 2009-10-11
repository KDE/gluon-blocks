set(blok_SRCS 
    main.cpp 
    blokitem.cpp
    blokengine.cpp
    mainwindow.cpp
   )

kde4_add_executable(blok ${blok_SRCS})
include_directories(${GLEW_INCLUDE_DIR}/.. ${ALUT_INCLUDE_DIR})
target_link_libraries(blok ${GLUON_LIBRARY} ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KGL_LIBRARY}
                      ${KAL_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_gl_LIBRARY})

install(TARGETS blok DESTINATION ${BIN_INSTALL_DIR})
install(FILES blokui.rc DESTINATION ${DATA_INSTALL_DIR}/blok)
