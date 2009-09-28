set(blokeditor_SRCS 
    main.cpp 
    editor.cpp
    itemsdock.cpp
    optiondock.cpp
    blockitem.cpp
    blockengine.cpp
   )

kde4_add_executable(blokeditor ${blokeditor_SRCS})
target_link_libraries(blokeditor ${GLUON_LIBRARY})
