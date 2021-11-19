#ifndef _COMB_
#define _COMB_
#include "maze.h"
#include <array>

namespace MMaze
{
    class CombMaze : public Maze
    {
        CombMaze(uint32_t size);

    protected:
        void InitializeMaze() override;

        int VertexIndex(int, int) const;
        std::pair<int, int> InverseVertexIndex(int) const; 
        virtual std::tuple<double, double, double, double> GetEdge(int, int, int) const;
        std::pair<int, int> VExtent(int);
        bool IsValidNode(int, int);

    private:
        uint32_t m_size;
        static const int neighbours[6][2];
    };
}

#endif