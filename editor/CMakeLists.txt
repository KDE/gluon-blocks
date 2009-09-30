set(blokeditor_SRCS 
    main.cpp 
    editor.cpp
    itemsdock.cpp
    optionsdock.cpp
    blockitem.cpp
    editorview.cpp
   )

kde4_add_executable(blokeditor ${blokeditor_SRCS})
target_link_libraries(blokeditor ${GLUON_LIBRARY})
