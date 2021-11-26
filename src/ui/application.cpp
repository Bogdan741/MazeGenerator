#include <application.h>

using namespace MMaze;

std::pair<uint32_t, uint32_t> Application::GetRectangleMazeSizeDifficulty(MMaze::DifficultyClass diff_)
{
    std::pair<uint32_t, uint32_t> res;
    if (diff_ == MMaze::DifficultyClass::EASY)
    {
        res = std::make_pair(10, 10);
    }
    else if (diff_ == MMaze::DifficultyClass::NORMAL)
    {
        res = std::make_pair(20, 10);
    }
    else if (diff_ == MMaze::DifficultyClass::HARD)
    {
        res = std::make_pair(40, 20);
    }
    else if (diff_ == MMaze::DifficultyClass::INSANE)
    {
        res = std::make_pair(70, 30);
    }
    else if (diff_ == MMaze::DifficultyClass::EXTREAM)
    {
        res = std::make_pair(110, 40);
    }
    return res;
}

std::pair<uint32_t, uint32_t> Application::GetRectangleCombMazeSizeDifficulty(MMaze::DifficultyClass diff_)
{
    std::pair<uint32_t, uint32_t> res;
    if (diff_ == MMaze::DifficultyClass::EASY)
    {
        res = std::make_pair(15, 5);
    }
    else if (diff_ == MMaze::DifficultyClass::NORMAL)
    {
        res = std::make_pair(30, 10);
    }
    else if (diff_ == MMaze::DifficultyClass::HARD)
    {
        res = std::make_pair(50, 20);
    }
    else if (diff_ == MMaze::DifficultyClass::INSANE)
    {
        res = std::make_pair(70, 20);
    }
    else if (diff_ == MMaze::DifficultyClass::EXTREAM)
    {
        res = std::make_pair(100, 30);
    }

    return res;
}

uint32_t Application::GetHoneyCombMazeSizeDifficulty(MMaze::DifficultyClass diff_)
{
    uint32_t res;
    if (diff_ == MMaze::DifficultyClass::EASY)
    {
        res = 6;
    }
    else if (diff_ == MMaze::DifficultyClass::NORMAL)
    {
        res = 10;
    }
    else if (diff_ == MMaze::DifficultyClass::HARD)
    {
        res = 15;
    }
    else if (diff_ == MMaze::DifficultyClass::EXTREAM)
    {
        res = 27;
    }
    else if (diff_ == MMaze::DifficultyClass::INSANE)
    {
        res = 21;
    }
    return res;
}
