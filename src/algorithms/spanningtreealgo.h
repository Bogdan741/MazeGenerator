#ifndef _SPAPNIGTREE_ALGORITHM_
#define _SPAPNIGTREE_ALGORITHM_
// For the sake of simplicity we consider a graph to be a grid and generating a loopless maze is
// equivalent to finding random spanning tree
#include <random>
#include <utility>
#include <vector>
#include <memory>
#include "curve.h"

namespace MMaze
{
    struct Connection
    {
        Connection(uint32_t vertex_, std::shared_ptr<Curve> curve_);
        uint32_t vertex;
        std::shared_ptr<Curve> curve;
    };

    using Graph = std::vector<std::vector<Connection>>;

    namespace MazeGenerators
    {
        class SpanningTreeAlogrithm
        {
        public:
            SpanningTreeAlogrithm();
            virtual std::vector<std::pair<uint32_t, uint32_t>> FindSpanningTree(uint32_t nvertices, const Graph &adjacencylist) = 0;

        protected:
            std::vector<std::pair<uint32_t, uint32_t>> m_spanningtree;
            std::random_device m_randomdevice;
            std::mt19937 m_generator;
        };
    }
}
#endif