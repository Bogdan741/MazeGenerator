#include "rectanglecombmaze.h"
#include <cmath>
using namespace MMaze;

int RectangleCombMaze::even_neighbours[6][2] = {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {0, 1}, {-1, 0}};
int RectangleCombMaze::odd_neighbours[6][2] = {{-1, 0}, {0, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};

RectangleCombMaze::RectangleCombMaze(uint32_t width_, uint32_t height_)
    : Maze(width_ * height_, 0, width_ * height_ - 1), m_width(width_), m_height(height_)
{
}

bool RectangleCombMaze::IsValid(int uu, int vv) const
{
    return !(uu < 0 || vv < 0 || uu >= m_width || vv >= m_height);
}

uint32_t RectangleCombMaze::GetVertex(uint32_t row, uint32_t column) const
{
    return row * m_width + column;
}

void RectangleCombMaze::InitializeMaze()
{
    Maze::InitializeMaze();
    for (uint32_t y{0}; y < m_height; ++y)
    {
        for (uint32_t x{0}; x < m_width; ++x)
        {
            bool isEven{false};
            if (x % 2 == 0)
                isEven = true;

            for (int i = 0; i < 6; ++i)
            {
                int uu = x;
                int vv = y;
                if (isEven)
                {
                    uu += even_neighbours[i][0];
                    vv += even_neighbours[i][1];
                }
                else
                {
                    uu += odd_neighbours[i][0];
                    vv += odd_neighbours[i][1];
                }
                if (IsValid(uu, vv))
                {
                    auto coord = GetEdge(y, x, i);
                    uint32_t nnode = GetVertex(vv, uu);
                    uint32_t node = GetVertex(y, x);
                    if (node < nnode)
                    {
                        std::shared_ptr<Line> r2Line = std::make_shared<Line>(std::get<0>(coord), std::get<1>(coord), std::get<2>(coord), std::get<3>(coord));
                        adjucencyList[GetVertex(y, x)].push_back({GetVertex(vv, uu), r2Line});
                        adjucencyList[GetVertex(vv, uu)].push_back({GetVertex(y, x), r2Line});
                    }
                }
                else
                {
                    if (((GetVertex(y, x) == mazeStart) && (i == 0)) || ((GetVertex(y, x) == mazeEnd) && (i == 3)))
                    {
                        continue;
                    }
                    auto line = GetEdge(y, x, i);
                    adjucencyList[GetVertex(y, x)].push_back(Connection(-1, std::make_shared<Line>(std::get<0>(line), std::get<1>(line), std::get<2>(line), std::get<3>(line))));
                }
            }
        }
    }
}

std::vector<Connection> RectangleCombMaze::GetDrawPathImp(const std::vector<std::pair<uint32_t, uint32_t>> &path) const
{
    std::vector<Connection> res_path;
    for (const auto edge : path)
    {
        std::pair<uint32_t, uint32_t> u = InverseGetVertes(edge.first);
        std::pair<uint32_t, uint32_t> v = InverseGetVertes(edge.second);
        double cy1 = u.first * sqrt(3), cx1 = u.second * 1.5;
        if (u.second % 2 == 0)
        {
            cy1 -= sqrt(3) / 2;
        };
        double cy2 = v.first * sqrt(3), cx2 = v.second * 1.5;
        if (v.second % 2 == 0)
        {
            cy2 -= sqrt(3) / 2;
        };
        std::shared_ptr<Line> r2Line = std::make_shared<Line>(cx1, cy1, cx2, cy2);
        res_path.push_back(Connection(edge.second,r2Line));
    }
    return res_path;
}

std::tuple<double, double, double, double> RectangleCombMaze::GetEdge(uint32_t row, uint32_t col, int edge) const
{
    // double dx = 0.5, dy = 0.5;
    double cy = row * sqrt(3), cx = col * 1.5;
    double theta1 = (edge - 3) * M_PI / 3, theta2 = theta1 + M_PI / 3;
    double x1, x2, y1, y2;
    if (col % 2 == 0)
    {
        cy -= sqrt(3) / 2;
    }
    x1 = cx + cos(theta1);
    x2 = cx + cos(theta2);
    y1 = cy + sin(theta1);
    y2 = cy + sin(theta2);
    return std::make_tuple(x1, y1, x2, y2);
}

std::tuple<int, int, int, int> RectangleCombMaze::GetMazeCoordinatesImp() const
{
    return std::make_tuple(-1, -sqrt(3), m_width + m_width / 2, sqrt(3) * m_height);
}

std::pair<uint32_t, uint32_t> RectangleCombMaze::InverseGetVertes(uint32_t v) const
{
    int y = v / m_width;
    int x = v % m_width;
    return {y, x};
}
