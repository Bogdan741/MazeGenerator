#include "rectanglemaze.h"
using namespace MMaze;

RectangleMaze::RectangleMaze(uint32_t width_, uint32_t height_)
    : Maze(width_ * height_, 0, width_ * height_ - 1), m_width(width_), m_height(height_)
{
}

uint32_t RectangleMaze::GetIndex(uint32_t y, uint32_t x) const
{
    return y * m_width + x;
}

void RectangleMaze::InitializeMaze()
{

    //Top and button
    Maze::InitializeMaze();
    for (uint32_t i{0}; i < m_width; ++i)
    {
        adjucenyList[GetIndex(0, i)].push_back(Connection(-1, std::make_shared<Line>(i, 0, i + 1, 0)));
        adjucenyList[GetIndex(m_height - 1, i)].push_back(Connection(-1, std::make_shared<Line>(i, m_height, i + 1, m_height)));
    }

    // Right and left (bottom-left is a start top-right are a finish)
    for (uint32_t i{0}; i < m_height; ++i)
    {
        if (i != 0)
            adjucenyList[GetIndex(i, 0)].push_back(Connection(-1, std::make_shared<Line>(0, i, 0, i + 1)));
        if (i != m_height-1)
            adjucenyList[GetIndex(i, m_width - 1)].push_back(Connection(-1, std::make_shared<Line>(m_width, i, m_width, i + 1)));
    }

    for (uint32_t i{0}; i < m_height; ++i)
    {
        for (uint32_t j{0}; j < m_width - 1; ++j)
        {
            adjucenyList[GetIndex(i, j)].push_back({GetIndex(i, j + 1), std::make_shared<Line>(j + 1, i, j + 1, i + 1)});
            adjucenyList[GetIndex(i, j + 1)].push_back({GetIndex(i, j), std::make_shared<Line>(j + 1, i, j + 1, i + 1)});
        }
    }

    for (uint32_t i{0}; i < m_height - 1; ++i)
    {
        for (uint32_t j{0}; j < m_width; ++j)
        {
            adjucenyList[GetIndex(i, j)].push_back({GetIndex(i + 1, j), std::make_shared<Line>(j, i + 1, j + 1, i + 1)});
            adjucenyList[GetIndex(i + 1, j)].push_back({GetIndex(i, j), std::make_shared<Line>(j, i + 1, j + 1, i + 1)});
        }
    }
}

std::vector<Connection> RectangleMaze::GetDrawPath(std::vector<std::pair<uint32_t, uint32_t>> &path) const
{
    std::vector<Connection> res_path;
    for (auto const &edge : path)
    {
        uint32_t x1, y1, x2, y2;
        auto coord1 = GetPosition(edge.first);
        auto coord2 = GetPosition(edge.second);
        x1 = coord1.second;
        y1 = coord1.first;
        x2 = coord2.second;
        y2 = coord2.first;
        res_path.push_back({edge.second, std::make_shared<Line>(x1 + 0.5, y1 + 0.5, x2 + 0.5, y2 + 0.5)});
    }
    return res_path;
}

std::pair<uint32_t, uint32_t> RectangleMaze::GetPosition(uint32_t u) const
{
    uint32_t row = u / m_width;
    uint32_t column = u % m_width;

    return {row, column};
}

std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> RectangleMaze::GetMazeCoordinates() const
{
    return std::make_tuple(0, 0, m_width, m_height);
}


