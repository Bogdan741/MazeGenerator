#ifndef _SOLUTION_
#define _SOLUTION_
#include "mazesolveralgo.h"
#include "maze.h"
namespace MMaze
{
    class Solution
    {
    public:
        Solution(Maze *maze_);
        void FindSolution(MazeSolvers::MazeSolverAlgorithm *mzsa);
        std::vector<std::shared_ptr<Curve>> GetPath() const;

    private:
        Maze *m_maze;
        std::vector<Connection> m_path;
    };
}

#endif