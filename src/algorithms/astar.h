#ifndef _A_STAR_ALGORITHM_
#define _A_STAR_ALGORITHM_
#include "mazesolveralgo.h"

namespace MMaze
{
    namespace MazeSolvers
    {
        class AStar : public MazeSolverAlgorithm
        {
        public:
            std::vector<std::pair<uint32_t, uint32_t>> Solve(
                std::vector<std::vector<uint32_t>> spanningTree, uint32_t start, uint32_t end) override;

        private:
            int heurustic(uint32_t u, uint32_t v);
        };
    }
}
#endif