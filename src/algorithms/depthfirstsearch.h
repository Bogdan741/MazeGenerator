#ifndef _DEPTH_FIRST_SEARCH_
#define _DEPTH_FIRST_SEARCH_

#include "spanningtreealgo.h"

namespace MMaze
{
    namespace MazeGenerators
    {
        class DepthFirstSearch : public SpanningTreeAlogrithm
        {
        public:
            DepthFirstSearch();
            std::vector<std::pair<uint32_t, uint32_t>> FindSpanningTree(uint32_t nvertices, const Graph &adjacencylist) override;
        private:
            void DFS(uint32_t s_vertex, const Graph &graph_);
            std::vector<bool> m_visited;
        };
    }
}
#endif