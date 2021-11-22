set(SOURCES
    combmaze.cpp
    rectanglecombmaze.cpp
    rectanglemaze.cpp
    solution.cpp
    maze.cpp
    curve.cpp
)

add_library(MazeTypes STATIC ${SOURCES})