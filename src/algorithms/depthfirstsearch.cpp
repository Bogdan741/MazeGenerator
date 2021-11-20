#include "depthfirstsearch.h"
#include <algorithm>

using namespace MMaze;
using namespace MazeGenerators;

DepthFirstSearch::DepthFirstSearch() : SpanningTreeAlogrithm{}
{
}

std::vector<std::pair<uint32_t, uint32_t>> DepthFirstSearch::FindSpanningTree(
    uint32_t nvertices, const Graph &adjacencylist)
{
    m_spanningtree.clear();
    m_visited = std::vector<bool>(nvertices, 0);
    DFS(std::uniform_int_distribution<uint32_t>(0, nvertices - 1)(m_generator),
        adjacencylist);
    return m_spanningtree;
}

void DepthFirstSearch::DFS(uint32_t vertex, const Graph &adjacencylist)
{
    m_visited[vertex] = 1;
    std::vector<int> nodeorder(adjacencylist[vertex].size());
    std::iota(nodeorder.begin(), nodeorder.end(), 0);
    shuffle(nodeorder.begin(), nodeorder.end(), m_generator);

    for (auto index : nodeorder)
    {
        uint32_t nextvertex = adjacencylist[vertex][index].vertex;
        if (nextvertex < 0 || m_visited[nextvertex])
            continue;
        m_spanningtree.push_back({vertex, nextvertex});
        DFS(nextvertex, adjacencylist);
    }
}
