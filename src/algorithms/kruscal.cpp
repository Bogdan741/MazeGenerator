#include "kruscal.h"
#include <algorithm>
using namespace MMaze;
using namespace MazeGenerators;

Kruscal::Kruscal() : SpanningTreeAlogrithm{}
{
}

std::vector<std::pair<uint32_t, uint32_t>> Kruscal::FindSpanningTree(uint32_t nvertices, const Graph &adjacencylist)
{
    // All walls
    std::vector<std::pair<uint32_t, uint32_t>> edges;

    for (uint32_t vertex{0}; vertex < nvertices; ++vertex)
    {
        for (auto const adjacentVertex : adjacencylist[vertex])
        {
            if (adjacentVertex.vertex != -1 && adjacentVertex.vertex > vertex)
                edges.push_back({vertex, adjacentVertex.vertex});
        }
    }
    std::shuffle(edges.begin(), edges.end(), m_generator);

    // Provides unique number for each set
    m_setNumbers.resize(nvertices);
    std::iota(m_setNumbers.begin(), m_setNumbers.end(), 0);

    m_spanningtree.clear();

    for (const auto edge : edges)
    {
        uint32_t a{GetSetNumber(edge.first)};
        uint32_t b{GetSetNumber(edge.second)};
        if (a != b)
        {
            m_setNumbers[a] = b;
            m_spanningtree.push_back(edge);
        }
    }
    return m_spanningtree;
}

uint32_t Kruscal::GetSetNumber(uint32_t vertex)
{
    if (m_setNumbers[vertex] == vertex)
        return vertex;
    return GetSetNumber(m_setNumbers[vertex]);
}
