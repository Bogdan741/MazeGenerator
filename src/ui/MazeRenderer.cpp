#include <MazeRenderer.h>
#include <rectanglemaze.h>
#include <breadthfirstsearch.h>
#include <kruscal.h>
#include <depthfirstsearch.h>
#include <prim.h>
#include <QPainter>

using namespace MMaze;

MazeRenderer::MazeRenderer(const MMaze::Settings &settings_, MMaze::DifficultyClass diff_, QWidget *parent)
    : QWidget(parent), m_settings(settings_), m_difficulty(diff_)
{
    // TODO: Adjust so the size for maze type was choosed based on the difficulty

    MMaze::MazeTypes tMazeType = m_settings.mazeType;
    if (tMazeType == MMaze::MazeTypes::RectangularMaze)
    {
        m_maze = new MMaze::RectangleMaze(40, 20);
    }
    else if (tMazeType == MMaze::MazeTypes::RectangleCombMaze)
    {
        // m_maze = new MMaze::RectangleMaze(40,20);
    }
    else if (tMazeType == MMaze::MazeTypes::HoneyCombMaze)
    {
        // m_maze = new MMaze::RectangleMaze(40,20);
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
        m_mazeGenerationAlgorithm = new MMaze::MazeGenerators::Kruscal();
    }

    MMaze::MazeSolvAlgo tMazeSolvmentAlgorithm = m_settings.mazeSolveAlgo;
    if (tMazeSolvmentAlgorithm == MMaze::MazeSolvAlgo::BFS)
    {
    }
    else if (tMazeSolvmentAlgorithm == MMaze::MazeSolvAlgo::DFS)
    {
    }
    else if (tMazeSolvmentAlgorithm == MMaze::MazeSolvAlgo::AStar)
    {
    }

    m_maze->GenerateMaze(m_mazeGenerationAlgorithm);
}

void MazeRenderer::paintEvent(QPaintEvent *event)
{
    double h = 20;

    QPainter paint(this);
    QPen wallPen;
    wallPen.setColor(m_settings.mazeWallColor);
    wallPen.setWidth(m_settings.lineWidthMazeWall);

    paint.setRenderHint(QPainter::Antialiasing);
    // paint.drawLine(0,0,50,50);
    double widgetWidth = static_cast<double>(this->size().width()) - 2 * h;
    double widgetHeight = static_cast<double>(this->size().height() - 2 * h);

    std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> mazeBounds = m_maze->GetMazeCoordinates();
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
        y_offset = h;
        x_offset = (widgetWidth - K * mazeWidth)/2;
    }
    else
    {
        K = widgetWidth / mazeWidth;
        x_offset = h;
        y_offset = (widgetHeight - K * mazeHeight)/2;
    }
    paint.translate(x_offset, y_offset);
    auto lines_a = m_maze->GetCurvesCoordinates();
    for (auto const curve : lines_a)
    {
        if (curve->GetType() == CurveType::LINE)
        {
            MMaze::Line *line = static_cast<Line *>(curve.get());
            paint.drawLine(line->x1 * K, (mazeHeight - line->y1) * K, line->x2 * K, (mazeHeight - line->y2) * K);
        }
    }
}

QSize MazeRenderer::minimumSizeHint() const
{
    return QSize{500, 200};
}

QSize MazeRenderer::sizeHint() const
{
    return QSize{1000, 400};
}
