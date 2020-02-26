# CMakeFile based off https://github.com/retifrav/sdl-imgui-example/blob/master/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

project(bitchin-dev-tool)

# for filesystem functionality from C++17
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

if (WIN32)
    set(WHERE-IS-SDL "c:/programs/sdl/lib/x64")
    set(WHERE-IS-SDL-HEADERS "c:/programs/sdl/include")
    set(WHERE-IS-GLAD "c:/programs/glad/src/glad.c")
    set(WHERE-IS-GLAD-HEADERS "c:/programs/glad/include")
endif()

if (UNIX)
    set(WHERE-IS-GLAD "./glad/src/glad.c")
    set(WHERE-IS-GLAD-HEADERS "./glad/include")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(SDL2 REQUIRED)
find_package(SDL2IMAGE REQUIRED)
find_package(SDL2TTF REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2TTF_INCLUDE_DIR})

#message(${WHERE-IS-SDL})
#message(${WHERE-IS-SDL-HEADERS})
#message(${WHERE-IS-GLAD})
#message(${WHERE-IS-GLAD-HEADERS})

if (WIN32 OR APPLE)
    find_library(SDL SDL2 PATHS ${WHERE-IS-SDL})
    if (WIN32)
        find_library(SDLmain SDL2main PATHS ${WHERE-IS-SDL})
    endif()

    include_directories(
        "${WHERE-IS-SDL-HEADERS}"
    )
endif()


add_library("glad" ${WHERE-IS-GLAD})
include_directories(
        "${WHERE-IS-GLAD-HEADERS}"
    )

set(sources
	imgui/imconfig.h
    imgui/imgui.cpp
    imgui/imgui.h
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_internal.h
    imgui/imgui_widgets.cpp
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui_impl_opengl3.h
    imgui/imgui_impl_sdl.cpp
    imgui/imgui_impl_sdl.h

    engine/AffineTransform.cpp
	engine/AffineTransform.h
	engine/AnimatedSprite.cpp
	engine/AnimatedSprite.h
	engine/Animations.cpp
	engine/Animations.h
	engine/DevTool.cpp
	engine/DevTool.h
	engine/DisplayObjectContainer.cpp
	engine/DisplayObjectContainer.h
	engine/DisplayObject.cpp
	engine/DisplayObject.h
	engine/Event.cpp
	engine/EventDispatcher.cpp
	engine/EventDispatcher.h
	engine/Event.h
	engine/EventListener.h
	engine/Game.cpp
	engine/Game.h
	engine/jsonConversions.h
	engine/Mouse.cpp
	engine/Mouse.h
	engine/myCoin.h
	engine/QuestManager.cpp
	engine/QuestManager.h
	engine/Scene.cpp
	engine/Scene.h
	engine/Sprite.cpp
	engine/Sprite.h
)

if (WIN32)
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${sources})
    target_link_libraries(${CMAKE_PROJECT_NAME}
        "glad"
        ${SDL}
        ${SDLmain}
        ${OPENGL_gl_LIBRARY}
        )
else()
    add_executable(${CMAKE_PROJECT_NAME} ${sources})
    target_link_libraries(${CMAKE_PROJECT_NAME}
            "glad"
            ${OPENGL_gl_LIBRARY}
            )
    if (APPLE)
        target_link_libraries(${CMAKE_PROJECT_NAME}
            ${SDL}
            )
    endif()
    if (UNIX AND NOT APPLE)
        target_link_libraries(${CMAKE_PROJECT_NAME}
            ${SDL2_LIBRARY}
            ${SDL2IMAGE_LIBRARY}
            ${SDL2TTF_LIBRARY}
            ${CMAKE_DL_LIBS}
            )
    endif()
endif()