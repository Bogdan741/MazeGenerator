#include <MazeRenderer.h>
#include <rectanglemaze.h>
#include <combmaze.h>
#include <rectanglecombmaze.h>
#include <breadthfirstsearch.h>
#include <kruscal.h>
#include <depthfirstsearch.h>
#include <prim.h>
#include <astar.h>
#include <BFSSolver.h>
#include <DFSSolver.h>
#include <QPainter>
#include <QPainterPath>
#include <application.h>
#include <QtSvg/QSvgGenerator>

using namespace MMaze;

MazeRenderer::MazeRenderer(const MMaze::Settings &settings_, MMaze::DifficultyClass diff_, QWidget *parent)
    : QWidget(parent), m_settings(settings_), m_difficulty(diff_)
{
    MMaze::MazeTypes tMazeType = m_settings.mazeType;
    if (tMazeType == MMaze::MazeTypes::RectangularMaze)
    {
        std::pair<uint32_t, uint32_t> diffSize = Application::GetRectangleMazeSizeDifficulty(diff_);
        m_maze = new MMaze::RectangleMaze(diffSize.first, diffSize.second);
    }
    else if (tMazeType == MMaze::MazeTypes::RectangleCombMaze)
    {
        std::pair<uint32_t, uint32_t> diffSize = Application::GetRectangleCombMazeSizeDifficulty(diff_);
        m_maze = new MMaze::RectangleCombMaze(diffSize.first, diffSize.second);
    }
    else if (tMazeType == MMaze::MazeTypes::HoneyCombMaze)
    {
        uint32_t diffSize = Application::GetHoneyCombMazeSizeDifficulty(diff_);
        m_maze = new MMaze::CombMaze(diffSize);
    }

    MMaze::MazeGenAlgo tMazeGenerationAlgorithm = m_settings.mazeGenAlgo;
    if (tMazeGenerationAlgorithm == MMaze::MazeGenAlgo::BFS)
    {
        m_mazeGenerationAlgorithm = new MMaze::MazeGenerators::BreadthFirstSearch();
    }
    else if (tMazeGenerationAlgorithm == MMaze::MazeGenAlgo::DFS)
    {
        m_mazeGenerationAlgorithm = new MMaze::MazeGenerators::DepthFirstSearch();
    }
    else if (tMazeGenerationAlgorithm == MMaze::MazeGenAlgo::Kruscal)
    {
        m_mazeGenerationAlgorithm = new MMaze::MazeGenerators::Kruscal();
    }
    else if (tMazeGenerationAlgorithm == MMaze::MazeGenAlgo::Prim)
    {
        m_mazeGenerationAlgorithm = new MMaze::MazeGenerators::Prim();
    }

    MMaze::MazeSolvAlgo tMazeSolvmentAlgorithm = m_settings.mazeSolveAlgo;
    if (tMazeSolvmentAlgorithm == MMaze::MazeSolvAlgo::BFS)
    {
        m_mazeSolvmentAlogrithm = new MMaze::MazeSolvers::BFSSolver;
    }
    else if (tMazeSolvmentAlgorithm == MMaze::MazeSolvAlgo::DFS)
    {
        m_mazeSolvmentAlogrithm = new MMaze::MazeSolvers::DFSSolver;
    }
    else if (tMazeSolvmentAlgorithm == MMaze::MazeSolvAlgo::AStar)
    {
        m_mazeSolvmentAlogrithm = new MMaze::MazeSolvers::AStar;
    }

    m_maze->GenerateMaze(m_mazeGenerationAlgorithm);
    m_solution = new MMaze::Solution(m_maze);
    m_solution->FindSolution(m_mazeSolvmentAlogrithm);
}

void MazeRenderer::paintEvent(QPaintEvent *event)
{

    QPainter paint(this);
    paintMaze(paint);
}

QSize MazeRenderer::minimumSizeHint() const
{
    return QSize{500, 300};
}

QSize MazeRenderer::sizeHint() const
{
    return QSize{1000, 600};
}

void MazeRenderer::paintMaze(QPainter &paint) const
{
    double h = 20.0;
    QPainterPath path;
    path.addRect(0, 0, width(), height());
    paint.setBrush(m_settings.backgroundColor);
    paint.drawPath(path);

    QPen wallPen;
    QPen solutionPen;

    wallPen.setColor(m_settings.mazeWallColor);
    wallPen.setWidth(m_settings.lineWidthMazeWall);

    solutionPen.setWidth(m_settings.lineWidhtSolution);
    solutionPen.setColor(m_settings.solutionLineColor);

    paint.setRenderHint(QPainter::Antialiasing);
    paint.setPen(wallPen);

    double widgetWidth = static_cast<double>(this->size().width()) - 2 * h;
    double widgetHeight = static_cast<double>(this->size().height() - 2 * h);

    std::tuple<int, int, int, int> mazeBounds = m_maze->GetMazeCoordinates();
    double mazeWidth = static_cast<double>(std::get<2>(mazeBounds) - std::get<0>(mazeBounds));
    double mazeHeight = static_cast<double>(std::get<3>(mazeBounds) - std::get<1>(mazeBounds));

    double kw = widgetWidth / widgetHeight;
    double km = mazeWidth / mazeHeight;

    double K;
    double x_offset;
    double y_offset;

    if (kw > km)
    {
        K = widgetHeight / mazeHeight;
        y_offset = (widgetHeight - K * mazeHeight) / 2 + h;
        x_offset = (widgetWidth - K * mazeWidth) / 2 + h;
    }
    else
    {
        K = widgetWidth / mazeWidth;
        x_offset = (widgetWidth - K * mazeWidth) / 2 + h;
        y_offset = (widgetHeight - K * mazeHeight) / 2 + h;
    }
    paint.translate(x_offset - K * std::get<0>(mazeBounds), y_offset + K * std::get<1>(mazeBounds));
    // paint.translate(-std::get<0>(mazeBounds) * K, std::get<1>(mazeBounds) * K);
    auto lines_a = m_maze->GetCurvesCoordinates();
    for (auto const curve : lines_a)
    {
        if (curve->GetType() == CurveType::LINE)
        {
            MMaze::Line *line = static_cast<Line *>(curve.get());
            paint.drawLine(line->x1 * K, (mazeHeight - line->y1) * K, line->x2 * K, (mazeHeight - line->y2) * K);
        }
    }

    paint.setPen(solutionPen);

    if (showSolution)
    {
        auto pathLines = m_solution->GetPath();
        for (auto const edge : pathLines)
        {
            if (edge->GetType() == CurveType::LINE)
            {
                MMaze::Line *line = static_cast<Line *>(edge.get());
                paint.drawLine(line->x1 * K, (mazeHeight - line->y1) * K, line->x2 * K, (mazeHeight - line->y2) * K);
            }
        }
    }
}

void MazeRenderer::getImage(QString fileName) const
{
    // TODO:
    QSvgGenerator generator;
    generator.setFileName(fileName);
    generator.setSize(size());
    generator.setViewBox(QRect(0, 0, size().width(), size().height()));
    generator.setTitle(tr("Maze"));
    generator.setDescription(tr("Instance of the maze"));
    QPainter painter;
    painter.begin(&generator);
    paintMaze(painter);
    painter.end();
}

void MazeRenderer::setSolutionMode(bool mode)
{
    showSolution = mode;
    update();
}