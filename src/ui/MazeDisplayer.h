#ifndef _MAZE_DISPLAYER_
#define _MAZE_DISPLAYER_
#include <QWidget>
#include <QPushButton>
#include <types.h>
#include <MazeRenderer.h>
#include <QDialog>
#include <QWindow>
namespace MMaze
{
    class MazeDisplayer : public QDialog
    {
        Q_OBJECT
    public:
        MazeDisplayer(const MMaze::Settings &settings_, MMaze::DifficultyClass diff_, QWidget *parent = nullptr);
    public slots:
        void saveMaze();
        void isFileNameValid(const QString &) const;

    private:
        void setUpWidget();

    private:
        MMaze::Settings m_settings;
        MMaze::DifficultyClass m_difficulty;
        QPushButton *b_save;
        QPushButton *b_showSolution;
        QPushButton *b_hideSolution;
        QPushButton *b_close;
        MMaze::MazeRenderer *m_mazeRanderer;
        QString m_pathToSaveImage;
    };
}

#endif