#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <types.h>

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
    Ui::MainWindow *ui;
    MMaze::Settings &m_settings;
};
#endif // MAINWINDOW_H
