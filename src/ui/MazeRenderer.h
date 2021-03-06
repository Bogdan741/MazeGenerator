// MazeRandere take as parametr Settings and DisfficultyClass
#ifndef _MAZERENDERER_
#define _MAZERENDERER_

#include <QMainWindow>
#include <types.h>
#include <maze.h>
#include <mazesolveralgo.h>
#include <solution.h>

namespace MMaze
{
    class MazeRenderer : public QWidget
    {
        Q_OBJECT
    public:
        MazeRenderer(const MMaze::Settings &settigs_, MMaze::DifficultyClass diff, QWidget *parent = nullptr);
        ~MazeRenderer();
    public slots:
        void getImage(QString fileName) const;
        void setSolutionMode(bool mode);
    private:
        void paintMaze(QPainter &) const;
        void paintEvent(QPaintEvent *event) override;
        QSize sizeHint() const override;
        QSize minimumSizeHint() const override;
       
    private:
        const MMaze::Settings m_settings;
        MMaze::DifficultyClass m_difficulty;
        MMaze::Maze * m_maze{nullptr};
        MMaze::MazeGenerators::SpanningTreeAlogrithm *m_mazeGenerationAlgorithm{nullptr};
        MMaze::Solution * m_solution{nullptr};
        MMaze::MazeSolvers::MazeSolverAlgorithm * m_mazeSolvmentAlogrithm{nullptr};
        bool showSolution{false};
    };
}
#endif // MAINWINDOW_H
