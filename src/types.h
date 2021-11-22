#ifndef _TYPES_
#define _TYPES_
#include <QColor>
namespace MMaze
{

    enum class MazeGenAlgo : char
    {
        BFS=0,
        DFS,
        Kruscal,
        Prim,
        LoopErasedRandomWalk,
    };

    enum class MazeSolvAlgo: char
    {
        BFS=0,
        DFS,
        AStar,
    };

    enum class MazeTypes: char
    {
        RectangularMaze=0,
        HoneyCombMaze,
        RectangleCombMaze
    };

    enum class DifficultyClass : char
    {
        EASY = 0,
        NORMAL,
        HARD,
        EXTREAM,
        INSANE,
    };

    //POD-like structure
    struct Settings
    {
        QColor backgroundColor;
        QColor mazeWallColor;
        QColor solutionLineColor;
        int lineWidthMazeWall;
        int lineWidhtSolution;
        MazeGenAlgo mazeGenAlgo;
        MazeSolvAlgo mazeSolveAlgo;
        MazeTypes mazeType;
    };

}


#endif