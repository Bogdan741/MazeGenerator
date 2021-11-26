#ifndef MAZEEXCEPTION
#define MAZEEXCEPTION
#include <string>

namespace MMaze
{
    class MazeException
    {
    public:
        virtual std::string message() const = 0;
    };
}
#endif