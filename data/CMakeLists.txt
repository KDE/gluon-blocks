FILE(GLOB SPRITE_FILES "sprites/*.png")
install(FILES ${SPRITE_FILES} DESTINATION ${DATA_INSTALL_DIR}/blokeditor/data/sprites/)
FILE(GLOB SOUND_FILES "sounds/*.wav" "sounds/*.ogg")
install(FILES ${SOUND_FILES} DESTINATION ${DATA_INSTALL_DIR}/blokeditor/data/sounds/)
