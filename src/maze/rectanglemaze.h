#ifndef _RECTANGLEMAZE_
#define _RECTANGLEMAZE_
#include "maze.h"
namespace MMaze
{
    class RectangleMaze : public Maze
    {
    public:
        RectangleMaze(uint32_t width_, uint32_t height_);
        std::vector<Connection> GetDrawPath(std::vector<std::pair<uint32_t, uint32_t>> & path) const override;
        std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> GetMazeCoordinates() const override;

    protected:
        void InitializeMaze() override;
        uint32_t GetIndex(uint32_t x, uint32_t y) const;
        std::pair<uint32_t, uint32_t> GetPosition(uint32_t u) const;
        
    private:
        uint32_t m_width;
        uint32_t m_height;
    };
}

#endif