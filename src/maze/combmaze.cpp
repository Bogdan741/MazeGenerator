#include "combmaze.h"
#include <cmath>

using namespace MMaze;

const int CombMaze::neighbours[6][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 0}, {1, -1}, {0, -1}};

CombMaze::CombMaze(uint32_t size_)
    : Maze(3 * size_ * (size_ - 1) + 1, 0, 3 * size_ * (size_ - 1)), m_size(size_) {}

void CombMaze::InitializeMaze()
{
    Maze::InitializeMaze();

    for (int u = -m_size + 1; u < m_size; ++u)
    {
        auto vextent = VExtent(u);
        for (int v = vextent.first; v <= vextent.second; ++v)
        {
            int node = GetVertex(u, v);
            for (int n = 0; n < 6; ++n)
            {
                int uu = u + neighbours[n][0], vv = v + neighbours[n][1];
                if (IsValidNode(uu, vv))
                {
                    int nnode = GetVertex(uu, vv);
                    if (nnode > node)
                        continue;

                    auto edge = GetEdge(u, v, n);
                    std::shared_ptr<Line> ptr =
                        std::make_shared<Line>(std::get<0>(edge), std::get<1>(edge), std::get<2>(edge), std::get<3>(edge));
                    adjucencyList[node].push_back({static_cast<uint32_t>(nnode), ptr});
                    adjucencyList[nnode].push_back({static_cast<uint32_t>(node), ptr});
                }
                else
                {
                    if ((node == mazeStart && n == 0) ||
                        (node == mazeEnd && n == 3))
                        continue;

                    auto edge = GetEdge(u, v, n);
                    adjucencyList[node].push_back(
                        Connection(-1, std::make_shared<Line>(std::get<0>(edge), std::get<1>(edge), std::get<2>(edge), std::get<3>(edge))));
                }
            }
        }
    }
}

int CombMaze::GetVertex(int u, int v) const
{
    if (u <= 0)
        return ((3 * m_size + u) * (m_size + u - 1)) / 2 + v;
    else
        return (3 * m_size * (m_size - 1) + (4 * m_size - u - 1) * u) / 2 + v;
}

std::tuple<double, double, double, double> CombMaze::GetEdge(
    int u, int v, int edge) const
{
    double dxu = sqrt(3) / 2, dyu = 1.5, dxv = sqrt(3), dyv = 0;
    double cx = dxu * u + dxv * v, cy = dyu * u + dyv * v;

    double theta1 = (edge - 2.5) * M_PI / 3, theta2 = theta1 + M_PI / 3;
    return std::make_tuple(cx + cos(theta1), cy + sin(theta1), cx + cos(theta2),
                           cy + sin(theta2));
}

std::pair<int, int> CombMaze::VExtent(int u) const
{
    if (u < 0)
        return {-m_size - u + 1, m_size - 1};
    else
        return {-m_size + 1, m_size - 1 - u};
}

bool CombMaze::IsValidNode(int u, int v) const
{
    if (u <= -m_size || u >= m_size)
        return false;
    auto vextent = VExtent(u);
    return v >= vextent.first && v <= vextent.second;
}

std::pair<int, int> CombMaze::InverseGetVertex(int vertex) const
{
    std::pair<int, int> res;
    int u, v;
    if (vertex < nvertices / 2)
    {
        u = ceil((-4 * m_size + 1 + sqrt(4 * m_size * m_size - 4 * m_size + 9 + 8 * vertex)) / 2.0);
        v = vertex - (3 * m_size + u) * (m_size + u - 1) / 2;
    }
    else
    {
        u = ceil((4 * m_size - 3 - sqrt(28 * m_size * m_size - 28 * m_size + 1 - 8 * vertex)) / 2.0);
        v = vertex - (3 * m_size * (m_size - 1) + (4 * m_size - u - 1) * u) / 2;
    }
    res = std::make_pair(u, v);
    return res;
}

std::vector<Connection> CombMaze::GetDrawPathImp(const std::vector<std::pair<uint32_t, uint32_t>> &path) const
{
    std::vector<Connection> res_path;
    for (const auto edge : path)
    {
        std::pair<int, int> coord1 = InverseGetVertex(edge.first);
        std::pair<int, int> coord2 = InverseGetVertex(edge.second);

        double dxu = sqrt(3) / 2, dyu = 1.5, dxv = sqrt(3), dyv = 0;
        double cx1 = dxu * coord1.first + dxv * coord1.second, cy1 = dyu * coord1.first + dyv * coord1.second;

        double dx2u = sqrt(3) / 2, dy2u = 1.5, dx2v = sqrt(3), dy2v = 0;
        double cx2 = dx2u * coord2.first + dx2v * coord2.second, cy2 = dy2u * coord2.first + dy2v * coord2.second;

        res_path.push_back({edge.second, std::make_shared<Line>(cx1, cy1, cx2, cy2)});
    }
    return res_path;
}

std::tuple<int, int, int, int> CombMaze::GetMazeCoordinatesImp() const
{
    double xlim = sqrt(3) * (m_size - 0.5), ylim = 1.5 * m_size - 0.5;
    return std::make_tuple(-xlim, -ylim, xlim, ylim);
}
