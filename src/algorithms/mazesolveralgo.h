#ifndef _MAZE_SOLLVER_ALGORITHM_
#define _MAZE_SOLLVER_ALGORITHM_
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>
#include <random>
namespace MMaze
{
    namespace MazeSolvers
    {
        class MazeSolverAlgorithm
        {
        public:
            MazeSolverAlgorithm();
            virtual std::vector<std::pair<uint32_t, uint32_t>> Solve(
                            std::vector<std::vector<uint32_t>> spanningTree, uint32_t start, uint32_t end) = 0;
        protected:
            std::random_device m_randomdivece;
            std::mt19937 m_generator;
        };
    }
}
#endif