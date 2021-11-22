#include "solution.h"
using namespace MMaze;

Solution::Solution(Maze *maze_) : m_maze(maze_)
{
}

void Solution::FindSolution(MazeSolvers::MazeSolverAlgorithm * mzsa)
{
    auto spanningTree = m_maze->GetSpanningTree();
    std::vector<std::vector<uint32_t>> spanningTreeAdjucencyList(spanningTree.size()+1);
    for(auto const vertex: spanningTree)
    {
        spanningTreeAdjucencyList[vertex.first].push_back(vertex.second);
        spanningTreeAdjucencyList[vertex.second].push_back(vertex.first);
    }
    std::vector<std::pair<uint32_t, uint32_t>> path = mzsa->Solve(spanningTreeAdjucencyList,m_maze->GetStart(), m_maze->GetEnd());
    m_path = m_maze->GetDrawPath(path);
}

std::vector<std::shared_ptr<Curve>> Solution::GetPath() const
{
    std::vector<std::shared_ptr<Curve>> res;
    for(auto const edge: m_path)
    {
        res.push_back(edge.curve);
    }
    return res;
}
