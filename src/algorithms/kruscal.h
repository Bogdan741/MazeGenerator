#ifndef _DEEP_FIRST_SEARCH_
#define _DEEP_FIRST_SEARCH_

#include "spanningtreealgo.h"

namespace MMaze
{
    namespace MazeGenerators
    {
        class Kruscal : public SpanningTreeAlogrithm
        {
        public:
            Kruscal();
            std::vector<std::pair<uint32_t, uint32_t>> FindSpanningTree(uint32_t nvertices, const Graph &adjacencylist) override;

        private:
            std::vector<uint32_t> m_setNumbers;
            uint32_t GetSetNumber(uint32_t vertex);
        };
    }
}
#endif