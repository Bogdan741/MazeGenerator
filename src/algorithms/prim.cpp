#include "prim.h"

using namespace MMaze;
using namespace MazeGenerators;

Prim::Prim() : SpanningTreeAlogrithm{}
{
}

std::vector<std::pair<uint32_t, uint32_t>> Prim::FindSpanningTree(uint32_t nvertices, const Graph &adjacencylist)
{
    m_spanningtree.clear();
    std::vector<bool> visited_a(nvertices, false);
    std::vector<std::pair<uint32_t, uint32_t>> boundary;

    // Chooses random vertex to start
    uint32_t vertex = std::uniform_int_distribution<uint32_t>(0, vertex - 1)(m_generator);

    for (uint32_t i{0}; i < nvertices; ++i)
    {
        // Since all distances from edge to edge are equal
        // we add adjucent vertexes to the visited list if they are not visited yet
        visited_a[vertex] = true;
        for (const auto nvertex : adjacencylist[vertex])
        {
            if (nvertex.vertex != -1 && !visited_a[nvertex.vertex])
            {
                boundary.push_back({vertex, nvertex.vertex});
            }
        }

        std::pair<uint32_t, uint32_t> nextedge{-1, -1};
        do
        {
            // Picks random edge from boundary. If it is not visited add to spanning tree otherwise continue
            uint32_t i = std::uniform_int_distribution<uint32_t>(0, boundary.size() - 1)(m_generator);
            if (!visited_a[boundary[i].second])
                nextedge = boundary[i];
            boundary.erase(boundary.begin() + i);
        } while (nextedge.first == -1 && !boundary.empty());

        m_spanningtree.push_back(nextedge);
        vertex = nextedge.second;
    }
    return m_spanningtree;
}
