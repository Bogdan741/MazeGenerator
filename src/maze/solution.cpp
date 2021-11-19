#include "solution.h"
using namespace MMaze;

Solution::Solution(Maze *maze_) : m_maze(maze_)
{
}

void Solution::FindSolution(MazeSolvers::MazeSolverAlgorithm * mzsa)
{
    auto spanningTree = m_maze->GetSpanningTree();
    std::vector<std::vector<uint32_t>> spanningTreeAdjucencyList(spanningTree.size());
    for(auto const vertex: spanningTree)
    {
        spanningTreeAdjucencyList[vertex.first].push_back(vertex.second);
        spanningTreeAdjucencyList[vertex.second].push_back(vertex.first);
    }
    std::vector<std::pair<uint32_t, uint32_t>> path = mzsa->Solve(spanningTreeAdjucencyList,m_maze->GetStart(), m_maze->GetEnd());
    //TODO: Find the lines for solution representation
    m_path = m_maze->GetDrawPath(path);
}
