include_directories(algorithms)
include_directories(maze)
include_directories(ui)

add_subdirectory(ui)
add_subdirectory(maze)
add_subdirectory(algorithms)

add_executable(Merator
    main.cpp
)
find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

target_link_libraries(Merator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Ui Algorithms MazeTypes)


set_target_properties(Merator PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)
install(TARGETS Merator DESTINATION app COMPONENT binaries)