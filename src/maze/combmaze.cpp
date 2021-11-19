#include "combmaze.h"
#include <cmath>

using namespace MMaze;

const int CombMaze::neighbours[6][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 0}, {1, -1}, {0, -1}};

CombMaze::CombMaze(uint32_t size_)
    : Maze(3 * size_ * (size_ - 1) + 1, 0, 3 * size_ * (size_ - 1)), m_size(size_) {}

void CombMaze::InitializeMaze()
{
    // Maze::InitialiseGraph();
    // TODO: View
    for (int u = -m_size + 1; u < m_size; ++u)
    {
        auto vextent = VExtent(u);
        for (int v = vextent.first; v <= vextent.second; ++v)
        {
            int node = VertexIndex(u, v);
            for (int n = 0; n < 6; ++n)
            {
                int uu = u + neighbours[n][0], vv = v + neighbours[n][1];
                if (IsValidNode(uu, vv))
                {
                    int nnode = VertexIndex(uu, vv);
                    if (nnode > node)
                        continue;
                    std::shared_ptr<Line> ptr =
                        std::make_shared<Line>(GetEdge(u, v, n));
                    adjucenyList[node].push_back({nnode, ptr});
                    adjucenyList[nnode].push_back({node, ptr});
                }
                else
                {
                    if ((node == mazeStart && n == 0) or
                        (node == mazeEnd && n == 3))
                        continue;
                    adjucenyList[node].push_back(
                        {-1, std::make_shared<Line>(GetEdge(u, v, n))});
                }
            }
        }
    }
}

int CombMaze::VertexIndex(int u, int v) const
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

std::pair<int, int> CombMaze::VExtent(int u)
{
    if (u < 0)
        return {-m_size - u + 1, m_size - 1};
    else
        return {-m_size + 1, m_size - 1 - u};
}

bool CombMaze::IsValidNode(int u, int v)
{
    if (u <= -m_size || u >= m_size)
        return false;
    auto vextent = VExtent(u);
    return v >= vextent.first && v <= vextent.second;
}

// TODO: Add path line implementation

std::pair<int, int> CombMaze::InverseVertexIndex(int vertex) const
{
    int u = ceil((-4 * m_size + 1 + sqrt(4 * m_size * m_size - 4 * m_size + 9 + 8 * vertex)) / 2.0);
    int v = (3 * m_size + u) * (m_size + u - 1) / 2 - vertex;
    return {u, v};
}
