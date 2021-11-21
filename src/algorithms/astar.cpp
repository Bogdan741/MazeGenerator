#include "astar.h"
#include <cmath>
#include <list>
using namespace MMaze;
using namespace MazeSolvers;

std::vector<std::pair<uint32_t, uint32_t>> AStar::Solve(
    std::vector<std::vector<uint32_t>> spanningTree, uint32_t start, uint32_t end)
{
    std::vector<bool> visited_a(spanningTree.size(), false);
    std::vector<uint32_t> parents_a(spanningTree.size(), -1);
    std::vector<double> globalDist_a(spanningTree.size(), -1);
    std::vector<double> localDist_a(spanningTree.size(), -1);

    auto distance = [](uint32_t u, uint32_t v)
    {
        return 1;
    };

    std::list<uint32_t> notTestedNodes_a;
    localDist_a[start] = 0.0f;
    globalDist_a[start] = heurustic(start, end);
    notTestedNodes_a.push_back(start);
    

    uint32_t current = start;
    while (!notTestedNodes_a.empty())
    {
        notTestedNodes_a.sort([&](uint32_t ln, uint32_t rn)
                              { return globalDist_a[ln] < globalDist_a[rn]; });
        while (!notTestedNodes_a.empty() && visited_a[notTestedNodes_a.front()])
            notTestedNodes_a.pop_front();

        if (notTestedNodes_a.empty())
            break;

        current = notTestedNodes_a.front();
        visited_a[current] = true;

        for (auto const vertex : spanningTree[current])
        {
            if (!visited_a[vertex])
                notTestedNodes_a.push_back(vertex);

            float fPossLoverGoal = localDist_a[current] + distance(current, vertex);
            if (fPossLoverGoal < localDist_a[vertex] || localDist_a[vertex]==-1)
            {
                parents_a[vertex] = current;
                localDist_a[vertex] = fPossLoverGoal;

                globalDist_a[vertex] = localDist_a[vertex] + heurustic(vertex, end);
            }
        }
    }
    std::vector<std::pair<uint32_t, uint32_t>> res;
    uint32_t cur{end};
    while (true)
    {
        uint32_t prev = parents_a[cur];
        if (prev == -1)
            break;
        res.push_back({prev, cur});
        cur = prev;
    }
    return res;
}

int AStar::heurustic(uint32_t u, uint32_t v)
{
    // TODO:
    return fabs(u - v);
}
