#ifndef _COMB_
#define _COMB_
#include "maze.h"
#include <array>

namespace MMaze
{
    class CombMaze : public Maze
    {
    public:
        CombMaze(uint32_t size);
        std::tuple<int, int, int, int> GetMazeCoordinates() const override;
        std::vector<Connection> GetDrawPath(std::vector<std::pair<uint32_t, uint32_t>> &path) const override;

    protected:
        void InitializeMaze() override;

        int VertexIndex(int, int) const;
        std::pair<int, int> InverseVertexIndex(int) const;
        virtual std::tuple<double, double, double, double> GetEdge(int, int, int) const;
        std::pair<int, int> VExtent(int);
        bool IsValidNode(int, int);

    private:
        int m_size;
        static const int neighbours[6][2];
    };
}

#endif