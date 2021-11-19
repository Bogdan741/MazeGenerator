#ifndef _BREAD_FIRST_SEARCH
#define _BREAD_FIRST_SEARCH
#include "spanningtreealgo.h"

namespace MMaze
{
    namespace MazeGenerators
    {
        class BreadthFirstSearch : public SpanningTreeAlogrithm
        {
        public:
            BreadthFirstSearch();
            std::vector<std::pair<uint32_t, uint32_t>> FindSpanningTree(uint32_t nvertices, const Graph &adjacencylist) override;

        private:
        };
    }
}

#endif