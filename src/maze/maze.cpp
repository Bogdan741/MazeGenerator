#include "maze.h"
#include <algorithm>

using namespace MMaze;

Maze::Maze(uint32_t nvertices_, uint32_t mazeStart_, uint32_t mazeEnd)
    : nvertices(nvertices_), mazeStart(mazeStart_), mazeEnd(mazeEnd)
{
}

void Maze::GenerateMaze(MazeGenerators::SpanningTreeAlogrithm *algo)
{
    InitializeMaze();
    m_spanningTree = algo->FindSpanningTree(nvertices, adjucenyList);
    RemoveWalls();
}

std::vector<std::shared_ptr<Curve>> Maze::GetCurvesCoordinates() const
{
    std::vector<std::shared_ptr<Curve>> res{};
    for (uint32_t i{0}; i < nvertices; ++i)
    {
        for (uint32_t j{0}; j < adjucenyList[i].size(); ++j)
        {
            if (i < adjucenyList[i][j].vertex)
                res.push_back(adjucenyList[i][j].curve);
        }
    }
    return res;
}

void Maze::RemoveWalls()
{
    for (auto const &edge : m_spanningTree)
    {
        auto it1 = std::remove_if(adjucenyList[edge.first].begin(), adjucenyList[edge.first].end(), [&edge](const Connection &con)
                                  { return con.vertex == edge.second; });
        adjucenyList[edge.first].erase(it1);

        auto it2 = std::remove_if(adjucenyList[edge.second].begin(), adjucenyList[edge.second].end(), [&edge](const Connection &con)
                                  { return con.vertex == edge.first; });
        adjucenyList[edge.second].erase(it2);
    }
}

std::vector<std::pair<uint32_t, uint32_t>> Maze::GetSpanningTree() const
{
    return m_spanningTree;
}

uint32_t Maze::GetStart() const
{
    return mazeStart;
}

uint32_t Maze::GetEnd() const
{
    return mazeEnd;
}

// std::vector<std::shared_ptr<Curve>> Maze::GetCurvesCoordinates() const
// {
//     std::vector<std::shared_ptr<Curve>> res;
//     for (const auto vertexList : adjucenyList)
//     {
//         for (const auto connection : vertexList)
//         {
//             res.push_back(connection.curve);
//         }
//     }
//     return res;
// }

void Maze::InitializeMaze()
{
    adjucenyList.clear();
    adjucenyList.resize(nvertices);
}
