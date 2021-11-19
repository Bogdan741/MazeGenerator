#include "BFSSolver.h"

using namespace MMaze;
using namespace MazeSolvers;

std::vector<std::pair<uint32_t, uint32_t>> BFSSolver::Solve(
    std::vector<std::vector<uint32_t>> spanningTree, uint32_t start, uint32_t end)
{
    // std::vector<bool> visited(false, spanningTree.size());
    std::vector<uint32_t> parents(-1, spanningTree.size());
    std::queue<uint32_t> bfs_queue;
    bfs_queue.push(start);
    uint32_t cur_vertex = bfs_queue.back();
    while (!bfs_queue.empty())
    {
        // TODO: Add imp
        std::vector<uint32_t> unvisited;
        bool state{false};
        for (auto const v : spanningTree[cur_vertex])
        {
            if (parents[v] != -1)
                unvisited.push_back(v);
            parents[v] = cur_vertex;
            if (v == end)
            {
                state = true;
                break;
            }
        }
        if (state)
            break;

        std::shuffle(unvisited.begin(), unvisited.end(), m_generator);
        for (auto const v : unvisited)
        {
            bfs_queue.push(v);
        }
        bfs_queue.pop();
        cur_vertex = bfs_queue.front();
    }
    std::vector<std::pair<uint32_t, uint32_t>> res;
    uint32_t cur{end};
    while(true)
    {
        uint32_t prev = parents[cur];
        if(prev==-1)
            break;
        res.push_back({prev, cur});
        cur = prev;
    }
    return res;
}
