cmake_minimum_required(VERSION 3.16)

project(SortingAlgVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Prevent external SFML discovery
set(SFML_STATIC_LIBRARIES OFF)
set(IMGUI_SFML_FIND_SFML OFF)

# ---------------- SFML ----------------
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.x
)
FetchContent_MakeAvailable(SFML)

# ---------------- Dear ImGui ----------------
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.6
)
FetchContent_MakeAvailable(imgui)

# Tell ImGui-SFML where ImGui is
set(IMGUI_DIR ${imgui_SOURCE_DIR})

# ---------------- ImGui-SFML ----------------
FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG master
)
FetchContent_MakeAvailable(imgui-sfml)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    ImGui-SFML::ImGui-SFML
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)