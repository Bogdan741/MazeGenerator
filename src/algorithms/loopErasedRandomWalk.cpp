#include <loopErasedRandomWalk.h>
#include <algorithm>
using namespace MMaze::MazeGenerators;
using namespace MMaze;
LoopErasedRandomWalk::LoopErasedRandomWalk()
    : SpanningTreeAlogrithm()
{
}

std::vector<std::pair<uint32_t, uint32_t>> LoopErasedRandomWalk::FindSpanningTree(uint32_t nvertices, const Graph &adjacencylist)
{

    std::vector<uint32_t> visited_a(adjacencylist.size(), false);
    std::vector<uint32_t> nnodes_a(adjacencylist.size());
    std::iota(nnodes_a.begin(), nnodes_a.end(), 0);
    std::shuffle(nnodes_a.begin(), nnodes_a.end(), m_generator);
    visited_a[nnodes_a[0]] = 1;
    for (int step = 1, i = 0; i < nnodes_a.size(); ++i)
    {
        if (visited_a[nnodes_a[i]])
            continue;
        ++step;
        Walk(nnodes_a[i], step, adjacencylist, visited_a);
    }
    return m_spanningtree;
}

void LoopErasedRandomWalk::Walk(uint32_t vertex, uint32_t step, const Graph &adjucencyList, std::vector<uint32_t> &visited)
{
    std::vector<uint32_t> path_a;
    while (!visited[vertex])
    {
        visited[vertex] = step;
        path_a.push_back(vertex);
        // Pick a random neigbour
        uint32_t nextVertex;
        do
        {
            nextVertex = adjucencyList[vertex][std::uniform_int_distribution<int>(0, adjucencyList[vertex].size() - 1)(m_generator)].vertex;
        } while (nextVertex == -1);

        // Erase a loop if one is exists
        if (visited[nextVertex] == step)
        {
            do
            {
                vertex = path_a.back();
                visited[vertex] = 0;
                path_a.pop_back();
            } while (vertex != nextVertex);
        }
        vertex = nextVertex;
    }
    path_a.push_back(vertex);
    for(int i = 0; i < path_a.size() - 1; ++i)
    {
        m_spanningtree.push_back({path_a[i],path_a[i+1]});
    }
}
