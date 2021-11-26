#include <QApplication>
#include <QtWidgets>
#include "dialog.h"
#include <types.h>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MMaze::Settings set;
    
    set.backgroundColor = QColor{85, 87, 83};
    set.mazeWallColor = QColor{193, 125, 17};
    set.solutionLineColor = QColor{0,0,0};
    set.mazeGenAlgo = MMaze::MazeGenAlgo::LoopErasedRandomWalk;
    set.mazeType = MMaze::MazeTypes::RectangleCombMaze;
    set.mazeSolveAlgo = MMaze::MazeSolvAlgo::AStar;
    set.lineWidthMazeWall = 2;
    set.lineWidhtSolution = 2;
    
    MainWindow w(set);
    w.show();
    return a.exec();
}
