#ifndef _PRIM_
#define _PRIM_

#include "spanningtreealgo.h"

namespace MMaze
{
    namespace MazeGenerators
    {
        class Prim : public SpanningTreeAlogrithm
        {
        public:
            Prim();
            std::vector<std::pair<uint32_t, uint32_t>> FindSpanningTree(uint32_t nvertices, const Graph &adjacencylist) override;

        private:
        
        };
    }
}
#endif