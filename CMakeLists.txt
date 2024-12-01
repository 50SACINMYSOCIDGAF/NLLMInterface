cmake_minimum_required(VERSION 3.16)
project(noahllminterface LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/mingw_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)

add_executable(noahllminterface main.cpp)

target_link_libraries(noahllminterface PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/styles"

            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_PREFIX_PATH}/bin/Qt6Core.dll"
            "${CMAKE_PREFIX_PATH}/bin/Qt6Gui.dll"
            "${CMAKE_PREFIX_PATH}/bin/Qt6Widgets.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"

            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_PREFIX_PATH}/plugins/platforms/qwindows.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/"

            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_PREFIX_PATH}/plugins/styles/qmodernwindowsstyle.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/styles/"
    )
endif()