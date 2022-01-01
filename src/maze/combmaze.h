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

    protected:
        std::tuple<int, int, int, int> GetMazeCoordinatesImp() const override;
        std::vector<Connection> GetDrawPathImp(const std::vector<std::pair<uint32_t, uint32_t>> &path) const override;
        void InitializeMaze() override;

        int GetVertex(int, int) const;
        std::pair<int, int> InverseGetVertex(int) const;
        virtual std::tuple<double, double, double, double> GetEdge(int, int, int) const;
        std::pair<int, int> VExtent(int) const;
        bool IsValidNode(int, int) const;

    private:
        int m_size;
        static const int neighbours[6][2];
    };
}

#endif