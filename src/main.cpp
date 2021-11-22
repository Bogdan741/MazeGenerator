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
    //SettingsDialog w(set);
    //w.show();
    // QWidget w;
    // QGridLayout *grid = new QGridLayout(&w);

    // std::vector<QString> colors{ "red", "blue", "green", "yellow",
    //                              "magenta", "darkblue", "darkgreen", "black" };

    // static const int buttonsPerRow = 5;
    // for (int i = 0; i < 15; ++i)
    // {
    //   QPushButton *btn = new QPushButton(&w);
    //   // Customize the colour button
    //   btn->setMaximumSize(16, 16);
    //   QString qss = QString("background-color: %1").arg(colors[i % colors.size()]);
    //   btn->setStyleSheet(qss);
    //   grid->addWidget(btn, i / buttonsPerRow, i % buttonsPerRow);
    // }

    // w.show();
    return a.exec();
}
