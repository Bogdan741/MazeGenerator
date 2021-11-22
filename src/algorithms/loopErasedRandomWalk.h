#ifndef LOOP_ERASED_RANDOM_WALK
#define LOOP_ERASED_RANDOM_WALK
#include "spanningtreealgo.h"

namespace MMaze
{
    namespace MazeGenerators
    {
        class LoopErasedRandomWalk : public SpanningTreeAlogrithm
        {
        public:
            LoopErasedRandomWalk();
            std::vector<std::pair<uint32_t, uint32_t>> FindSpanningTree(uint32_t nvertices, const Graph &adjacencylist) override;

        private:
            void Walk(uint32_t vertex, uint32_t step, const Graph & adjucencyList, std::vector<uint32_t> & visited);
        };
    }
}

#endif