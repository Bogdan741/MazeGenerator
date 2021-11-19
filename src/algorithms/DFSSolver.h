#ifndef _DFSSOLVER_
#define _DFSSOLVER_
#include "mazesolveralgo.h"
#include <stack>
namespace MMaze
{
    namespace MazeSolvers
    {
        class DFSSolver : public MazeSolverAlgorithm
        {
        public:
            std::vector<std::pair<uint32_t, uint32_t>> Solve(
                std::vector<std::vector<uint32_t>> spanningTree, uint32_t start, uint32_t end) override;
        };
    }
}

#endif