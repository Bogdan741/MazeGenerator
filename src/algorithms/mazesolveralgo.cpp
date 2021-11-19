#include "mazesolveralgo.h"

using namespace MMaze;
using namespace MazeSolvers;

MazeSolverAlgorithm::MazeSolverAlgorithm()
{
    m_generator = std::mt19937(m_randomdivece());
}