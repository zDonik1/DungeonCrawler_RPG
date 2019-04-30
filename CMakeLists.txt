cmake_minimum_required(VERSION 2.8)

project(DungeonCrawler_RPG)

set(SOURCE_FILES
    main.cpp
    game.h
    game.cpp
    state.h
    state.cpp
    state_game.h
    state_game.cpp
    state_mainmenu.h
    state_mainmenu.cpp
    state_editor.h
    state_editor.cpp
    state_settings.h
    state_settings.cpp
    entity.h
    entity.cpp
    player.h
    player.cpp
    gui.h
    gui.cpp
    component_movement.h
    component_movement.cpp
    component_animation.h
    component_animation.cpp
    component_hitbox.h
    component_hitbox.cpp
    component_attribute.h
    component_attribute.cpp
    movementstate.h
    tile.h
    tile.cpp
    tilemap.h
    tilemap.cpp
    pausemenu.h
    pausemenu.cpp
    graphicssettings.h
    graphicssettings.cpp
    playergui.h
    playergui.cpp
)

set(SFML_DIR "C:/work/SFML-2.5.1/lib/cmake/SFML")
#set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
