#include "DFSSolver.h"

using namespace MMaze;
using namespace MazeSolvers;

std::vector<std::pair<uint32_t, uint32_t>> DFSSolver::Solve(
    std::vector<std::vector<uint32_t>> spanningTree, uint32_t start, uint32_t end)
{
    std::stack<uint32_t> dfs_stack;
    std::vector<bool> visited(false, spanningTree.size());

    dfs_stack.push(start);
    uint32_t cur_vertex = dfs_stack.top();
    while (dfs_stack.top() != end || dfs_stack.empty())
    {
        do
        {
            uint32_t next_vertex = std::uniform_int_distribution<uint32_t>(0, spanningTree[cur_vertex].size() - 1)(m_generator);
            if (!visited[next_vertex])
            {
                visited[next_vertex] = true;
                dfs_stack.push(next_vertex);
                cur_vertex = next_vertex;
                break;
            }
            for (const auto v : spanningTree[cur_vertex])
            {
                if (!visited[v])
                    break;
            }
            dfs_stack.pop();
            cur_vertex = dfs_stack.top();
        } while (false);
    }

    std::vector<std::pair<uint32_t, uint32_t>> res;
    auto n = dfs_stack.size();
    res.resize(n);
    for (uint32_t i = 0; i < n - 1; ++i)
    {
        auto second = dfs_stack.top();
        dfs_stack.pop();
        auto first = dfs_stack.top();
        res[n - i] = std::make_pair(first, second);
    }
    return res;
}
