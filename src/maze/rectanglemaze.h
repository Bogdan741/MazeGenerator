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
        std::tuple<int, int, int, int> GetMazeCoordinatesImp() const override;
        std::vector<Connection> GetDrawPathImp(const std::vector<std::pair<uint32_t, uint32_t>> & path) const override;
        void InitializeMaze() override;
        uint32_t GetVertex(uint32_t x, uint32_t y) const;
        std::pair<uint32_t, uint32_t> InverseGetVertex(uint32_t u) const;
        
    private:
        uint32_t m_width;
        uint32_t m_height;
    };
}

#endif