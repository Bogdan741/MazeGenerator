#ifndef DIALOGEXCEPTION
#define DIALOGEXCEPTION
#include "mazeexception.h"
namespace MMaze
{
    class DialogException : public MazeException
    {
    public:
        DialogException(){}
        std::string message() const override
        {
            return "Too many dialog has been opened. Please close any if you want to open new.";
        }
    };
}
#endif