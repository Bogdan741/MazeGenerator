#ifndef _MAZE_
#define _MAZE_
#include <spanningtreealgo.h>
#include <vector>
namespace MMaze
{
    namespace MazeGenerators
    {
        class SpanningTreeAlogrithm;
    }
    struct Curve;
}
namespace MMaze
{
    class Maze
    {
    public:
        Maze(uint32_t nvertices_, uint32_t mazeStart_, uint32_t mazeEnd);
        void GenerateMaze(MazeGenerators::SpanningTreeAlogrithm*);
        std::vector<std::shared_ptr<Curve>> GetCurvesCoordinates() const;
        std::vector<std::pair<uint32_t, uint32_t>> GetSpanningTree() const;
        uint32_t GetStart() const;
        uint32_t GetEnd() const;
        std::tuple<int, int, int, int> GetMazeCoordinates() const;
        std::vector<Connection> GetDrawPath(const std::vector<std::pair<uint32_t, uint32_t>> & path) const;

    protected:
        virtual std::tuple<int, int, int, int> GetMazeCoordinatesImp() const = 0;
        virtual std::vector<Connection> GetDrawPathImp(const std::vector<std::pair<uint32_t, uint32_t>> & path) const = 0;
        virtual void InitializeMaze() = 0;
        void RemoveWalls();
        
    protected:
        uint32_t nvertices;
        Graph adjucencyList;
        uint32_t mazeStart;
        uint32_t mazeEnd;
        std::vector<std::pair<uint32_t, uint32_t>> spanningTree;
    };
}
#endif