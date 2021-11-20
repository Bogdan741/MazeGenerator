#include "breadthfirstsearch.h"
#include <algorithm>
using namespace MMaze;
using namespace MazeGenerators;

BreadthFirstSearch::BreadthFirstSearch() : SpanningTreeAlogrithm{}
{
}

std::vector<std::pair<uint32_t, uint32_t>> BreadthFirstSearch::FindSpanningTree(uint32_t nvertices, const Graph &adjacencylist)
{
    std::vector<bool> visited_a(nvertices, false);
    std::vector<uint32_t> currentlevel;
    std::vector<uint32_t> nextlevel;

    m_spanningtree.clear();

    uint32_t startvertex = std::uniform_int_distribution<uint32_t>(0, nvertices - 1)(m_generator);
    currentlevel.push_back(startvertex);
    visited_a[startvertex] = true;

    while (!currentlevel.empty())
    {
        for (auto vertex : currentlevel)
        {
            for (const auto &edge : adjacencylist[vertex])
            {
                uint32_t nextvertex = edge.vertex;
                if (nextvertex == -1 || visited_a[nextvertex])
                    continue;
                visited_a[nextvertex] = true;
                m_spanningtree.push_back({vertex, nextvertex});
                nextlevel.push_back(nextvertex);
            }
        }

        currentlevel.clear();
        std::swap(currentlevel, nextlevel);
        std::shuffle(currentlevel.begin(), currentlevel.end(), m_generator);
    }
    return m_spanningtree;
}
