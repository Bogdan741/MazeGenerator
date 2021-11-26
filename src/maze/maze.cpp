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
    spanningTree = algo->FindSpanningTree(nvertices, adjucencyList);
    RemoveWalls();
}

std::vector<std::shared_ptr<Curve>> Maze::GetCurvesCoordinates() const
{
    std::vector<std::shared_ptr<Curve>> res{};
    for (uint32_t i{0}; i < nvertices; ++i)
    {
        for (uint32_t j{0}; j < adjucencyList[i].size(); ++j)
        {
            if (i < adjucencyList[i][j].vertex)
                res.push_back(adjucencyList[i][j].curve);
        }
    }
    return res;
}

void Maze::RemoveWalls()
{
    for (auto const &edge : spanningTree)
    {
        auto it1 = std::remove_if(adjucencyList[edge.first].begin(), adjucencyList[edge.first].end(), [&edge](const Connection &con)
                                  { return con.vertex == edge.second; });
        adjucencyList[edge.first].erase(it1);

        auto it2 = std::remove_if(adjucencyList[edge.second].begin(), adjucencyList[edge.second].end(), [&edge](const Connection &con)
                                  { return con.vertex == edge.first; });
        adjucencyList[edge.second].erase(it2);
    }
}

std::vector<std::pair<uint32_t, uint32_t>> Maze::GetSpanningTree() const
{
    return spanningTree;
}

uint32_t Maze::GetStart() const
{
    return mazeStart;
}

uint32_t Maze::GetEnd() const
{
    return mazeEnd;
}


void Maze::InitializeMaze()
{
    adjucencyList.clear();
    adjucencyList.resize(nvertices);
}

std::tuple<int, int, int, int> Maze::GetMazeCoordinates() const
{
    return GetMazeCoordinatesImp();
}
std::vector<Connection> Maze::GetDrawPath(const std::vector<std::pair<uint32_t, uint32_t>> & path) const
{
    return GetDrawPathImp(path);
}
