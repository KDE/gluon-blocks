set(blokeditor_SRCS 
    main.cpp 
    editor.cpp
    optionsdock.cpp
    blockitem.cpp
    editorview.cpp
)

kde4_add_executable(blokeditor ${blokeditor_SRCS})
target_link_libraries(blokeditor ${GLUON_LIBRARY})

install(TARGETS blokeditor DESTINATION ${BIN_INSTALL_DIR})
install(FILES blokeditorui.rc DESTINATION ${DATA_INSTALL_DIR}/blokeditor)
