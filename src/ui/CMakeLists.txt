set(UI_FORMS 
    dialog.cpp
    mainwindow.cpp
    mainwindow.ui
    MazeDisplayer.cpp
    MazeRenderer.cpp
    application.cpp
)

add_library(Ui STATIC
${UI_FORMS}
)
target_include_directories(Ui PRIVATE src)

find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Svg REQUIRED)

target_link_libraries(Ui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Svg)
