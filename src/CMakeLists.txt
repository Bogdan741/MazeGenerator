include_directories(algorithms)
include_directories(maze)
include_directories(ui)

add_subdirectory(ui)
add_subdirectory(maze)
add_subdirectory(algorithms)

add_executable(Maze
    main.cpp
)
find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

target_link_libraries(Maze PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Ui Algorithms MazeTypes)