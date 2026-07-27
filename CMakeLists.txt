cmake_minimum_required(VERSION 3.15)
project(AZAVDIAP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)



if(UNIX AND NOT APPLE)
    find_package(PkgConfig QUIET)
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(WAYLAND wayland-client)
    endif()
    install(
    FILES default_config.json
    DESTINATION share/soundboard
    )

    if(WAYLAND_FOUND)
        message(STATUS "Wayland +X11")
        set(GLFW_BUILD_WAYLAND ON  CACHE BOOL "" FORCE)
        set(GLFW_BUILD_X11     ON  CACHE BOOL "" FORCE)
    else()
        message(STATUS "X11 only")
        set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_X11     ON  CACHE BOOL "" FORCE)
    endif()
endif()

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG        "5.5"       
    GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(raylib)


file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
list(APPEND PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)


if(WIN32)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        opengl32
        gdi32
        winmm
    )
elseif(UNIX AND NOT APPLE)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        m dl pthread GL rt X11
    )
endif()


target_compile_definitions(${PROJECT_NAME} PRIVATE
    ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
)

#target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_PATH="./Art/" )