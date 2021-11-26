#ifndef SETTINGSEXCEPTION
#define SETTINGSEXCEPTION
#include "mazeexception.h"

namespace MMaze
{
    class SettingsException : public MazeException
    {
    public:
        SettingsException(){}
        std::string message() const override
        {
            return "Same colors. Please change colors. Every color should be unique.";
        }
    };
}
#endif