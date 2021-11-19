#include "spanningtreealgo.h"

using namespace MMaze;
using namespace MazeGenerators;

SpanningTreeAlogrithm::SpanningTreeAlogrithm()
{
    m_generator = std::mt19937(m_randomdevice());
}
Connection::Connection(uint32_t vertex_, std::shared_ptr<Curve> curve_)
    : vertex(vertex_), curve(curve_)
{
}