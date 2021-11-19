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
        void InitializeMaze() override;
        uint32_t GetVertex(uint32_t x, uint32_t y);
        bool IsValid(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);

        std::vector<Connection> GetDrawPath(std::vector<std::pair<uint32_t, uint32_t>> & path) override;
    private:
        uint32_t m_width;
        uint32_t m_height;
    };
}
#endif