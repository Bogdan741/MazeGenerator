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
    std::vector<uint32_t> currentlevel_a;
    std::vector<uint32_t> nextlevel_a;

    m_spanningtree.clear();

    uint32_t startvertex = std::uniform_int_distribution<uint32_t>(0, nvertices - 1)(m_generator);
    currentlevel_a.push_back(startvertex);
    visited_a[startvertex] = true;


    while (!currentlevel_a.empty())
    {
        
        uint32_t number = std::uniform_int_distribution<uint32_t>(0, currentlevel_a.size())(m_generator);
        for(uint32_t i = 0; i < number; ++i)
        {
            for (const auto &edge : adjacencylist[currentlevel_a[i]])
            {
                uint32_t nextvertex = edge.vertex;
                if (nextvertex == -1 || visited_a[nextvertex])
                    continue;
                visited_a[nextvertex] = true;
                m_spanningtree.push_back({currentlevel_a[i], nextvertex});
                nextlevel_a.push_back(nextvertex);
            }
        }
        for(;number < currentlevel_a.size();++number)
        {
            nextlevel_a.push_back(currentlevel_a[number]);
        }

        //Version 1
        // for (auto vertex1 : currentlevel)
        // {
        //     for (const auto &edge : adjacencylist[vertex1])
        //     {
        //         uint32_t nextvertex = edge.vertex;
        //         if (nextvertex == -1 || visited_a[nextvertex])
        //             continue;
        //         visited_a[nextvertex] = true;
        //         m_spanningtree.push_back({vertex1, nextvertex});
        //         nextlevel.push_back(nextvertex);
        //     }
        // }

        
        currentlevel_a.clear();
        std::swap(currentlevel_a, nextlevel_a);
        std::shuffle(currentlevel_a.begin(), currentlevel_a.end(), m_generator);
    }
    return m_spanningtree;
}
