
#include_directories(algorithms)
#include_directories(curves)
#include_directories(maze)
include_directories(ui)
add_subdirectory(ui)
add_executable(Maze
    main.cpp
)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Gui REQUIRED)

target_link_libraries(Maze PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Ui)