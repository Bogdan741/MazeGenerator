#ifndef SAVEEXCEPTION
#define SAVEEXCEPTION
#include "mazeexception.h"

namespace MMaze
{
    class SaveException : public MazeException
    {
    public:
        SaveException(){}
        std::string message() const override
        {
            return "No filename has been chosen.";
        }
    };
}
#endif