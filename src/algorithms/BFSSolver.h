#ifndef _BFSSOLVER_
#define _BFSSOLVER_
#include "mazesolveralgo.h"
#include <queue>
namespace MMaze
{
    namespace MazeSolvers
    {
        class BFSSolver : public MazeSolverAlgorithm
        {
        public:
            std::vector<std::pair<uint32_t, uint32_t>> Solve(
                std::vector<std::vector<uint32_t>> spanningTree, uint32_t start, uint32_t end) override;
        };
    }
}
#endif