#ifndef _APPLICATIONAPP_
#define _APPLICATIONAPP_
#include <utility>
#include <cstdint>
#include <types.h>

namespace MMaze
{
    class Application
    {
    public:
        static std::pair<uint32_t, uint32_t> GetRectangleMazeSizeDifficulty(MMaze::DifficultyClass diff_);
        static std::pair<uint32_t, uint32_t> GetRectangleCombMazeSizeDifficulty(MMaze::DifficultyClass diff_);
        static uint32_t GetHoneyCombMazeSizeDifficulty(MMaze::DifficultyClass diff_);
    };
}

#endif