#include "rectanglecombmaze.h"

using namespace MMaze;

RectangleCombMaze::RectangleCombMaze(uint32_t width_, uint32_t height_)
    : Maze(width_ * height_, 0, width_ * height_ - 1), m_width(width_), m_height(height_)
{
}

bool RectangleCombMaze::IsValid(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
    bool res{false};
    do
    {
        if (x1 == 0)
            if (x2 == x1 - 1)
                break;

        if (x1 == m_width - 1)
            if (x2 == m_width)
                break;

        if (y1 == 0)
            if (y2 == y1 - 1)
                break;

        if (y1 == m_height - 1)
            if (y2 == m_height)
                break;

        res = true;
    } while (false);
    return res;
}

uint32_t RectangleCombMaze::GetVertex(uint32_t row, uint32_t column)
{
    return row * m_width + column;
}

void RectangleCombMaze::InitializeMaze()
{
    //TODO: Do some adjustments connected to calculating points
    for (uint32_t y{0}; y < m_height; ++y)
    {
        for (uint32_t x{0}; x < m_width; ++x)
        {
            uint32_t adjucentVertex;
            //-----------------------------------------------------------------
            // Connect point 5 and 6
            if (GetVertex(y, x) != mazeStart)
            {
                adjucentVertex = IsValid(x, y, x - 1, y) ? GetVertex(y, x - 1) : -1;
                if (x % 2 != 0)
                    adjucenyList[GetVertex(y, x)]
                        .push_back({adjucentVertex, std::make_shared<Line>(x, y + 0.5, x - 0.25, y + 1)});
                else
                    adjucenyList[GetVertex(y, x)]
                        .push_back({adjucentVertex, std::make_shared<Line>(x + 0.25, y, x, y + 0.5)});
            }
            //-----------------------------------------------------------------
            // Connect point 3 and 4
            adjucentVertex = IsValid(x, y, x + 1, y) ? GetVertex(y, x + 1) : -1;
            if (x % 2 != 0)
                adjucenyList[GetVertex(y, x)]
                    .push_back({adjucentVertex, std::make_shared<Line>(x + 0.75, y + 1, x + 0.5, y + 0.5)});
            else
                adjucenyList[GetVertex(y, x)]
                    .push_back({adjucentVertex, std::make_shared<Line>(x + 1, y + 0.5, x + 0.75, y)});
            //-----------------------------------------------------------------
            // Connect point 5 and 4
            adjucentVertex = IsValid(x, y, x, y - 1) ? GetVertex(y - 1, x) : -1;
            if (x % 2 != 0)
                adjucenyList[GetVertex(y, x)]
                    .push_back({adjucentVertex, std::make_shared<Line>(x, y + 0.5, x + 0.5, y + 0.5)});
            else
                adjucenyList[GetVertex(y, x)]
                    .push_back({adjucentVertex, std::make_shared<Line>(x + 0.25, y, x + 0.75, y)});
            //-----------------------------------------------------------------
            // Connect point 1 and 2
            adjucentVertex = IsValid(x, y, x, y + 1) ? GetVertex(y + 1, x) : -1;
            if (x % 2 != 0)
                adjucenyList[GetVertex(y, x)]
                    .push_back({adjucentVertex, std::make_shared<Line>(x, y + 1.5, x + 0.5, y + 1.5)});
            else
                adjucenyList[GetVertex(y, x)]
                    .push_back({adjucentVertex, std::make_shared<Line>(x + 0.25, y + 1, x + 0.75, y + 1)});
            //-----------------------------------------------------------------
            // Connect point 6 and 1
            adjucentVertex = IsValid(x, y, x - 1, y + 1) ? GetVertex(y + 1, x - 1) : -1;
            if (x % 2 != 0)
                adjucenyList[GetVertex(y, x)]
                    .push_back({adjucentVertex, std::make_shared<Line>(x, y + 1.5, x - 0.25, y + 1)});
            else
                adjucenyList[GetVertex(y, x)]
                    .push_back({adjucentVertex, std::make_shared<Line>(x + 0.25, y + 1, x, y + 0.5)});
            //-----------------------------------------------------------------
            // Connect point 2 and 3
            if (GetVertex(y, x) != mazeEnd)
            {
                adjucentVertex = IsValid(x, y, x + 1, y + 1) ? GetVertex(y + 1, x + 1) : -1;
                if (x % 2 != 0)
                    adjucenyList[GetVertex(y, x)]
                        .push_back({adjucentVertex, std::make_shared<Line>(x + 0.5, y + 1.5, x + 0.75, y + 1)});
                else
                    adjucenyList[GetVertex(y, x)]
                        .push_back({adjucentVertex, std::make_shared<Line>(x + 0.75, y + 1, x + 1, y + 0.5)});
            }
        }
    }
}

std::vector<Connection> RectangleCombMaze::GetDrawPath(std::vector<std::pair<uint32_t, uint32_t>> & path)
{
    //TODO: Add path line implementation
}