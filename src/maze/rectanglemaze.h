#ifndef _RECTANGLEMAZE_
#define _RECTANGLEMAZE_
#include "maze.h"
namespace MMaze
{
    class RectangleMaze : public Maze
    {
    public:
        RectangleMaze(uint32_t width_, uint32_t height_);

    protected:
        void InitializeMaze() override;
        uint32_t GetIndex(uint32_t x, uint32_t y);
        std::pair<uint32_t, uint32_t> GetPosition(uint32_t u);
        std::vector<Connection> GetDrawPath(std::vector<std::pair<uint32_t, uint32_t>> & path) override;

    private:
        uint32_t m_width;
        uint32_t m_height;
    };
}

#endif