#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <types.h>
#include <MazeDisplayer.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MMaze::Settings & settings_, QWidget *parent = nullptr);
    ~MainWindow();
private:
    void createMazeView(MMaze::DifficultyClass diff_);
private:
    Ui::MainWindow *ui;
    MMaze::Settings &m_settings;

    std::vector<std::shared_ptr<MMaze::MazeDisplayer>> m_mazes_dispal_a;
    int maxMazeDisplay = 10;
};
#endif // MAINWINDOW_H
