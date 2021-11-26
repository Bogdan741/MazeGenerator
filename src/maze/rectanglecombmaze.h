#ifndef _RECTANGLE_COMB_
#define _RECTANGLE_COMB_
#include "maze.h"
namespace MMaze
{
    class RectangleCombMaze : public Maze
    {
    public:
        RectangleCombMaze(uint32_t width, uint32_t height);
    protected:
        std::tuple<int, int, int, int> GetMazeCoordinatesImp() const override;
        std::vector<Connection> GetDrawPathImp(const std::vector<std::pair<uint32_t, uint32_t>> &path) const override;
        void InitializeMaze() override;
        uint32_t GetVertex(uint32_t x, uint32_t y) const;
        std::pair<uint32_t, uint32_t> InverseGetVertes(uint32_t u) const;
        bool IsValid(int uu, int vv) const;
        std::tuple<double, double, double, double> GetEdge(uint32_t row, uint32_t col, int edge) const;

    private:
        uint32_t m_width;
        uint32_t m_height;
        static int even_neighbours[6][2];
        static int odd_neighbours[6][2];
    };
}
#endif