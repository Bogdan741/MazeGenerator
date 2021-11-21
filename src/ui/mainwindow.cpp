#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <dialog.h>

MainWindow::MainWindow(MMaze::Settings &settings_, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_settings(settings_)
{
    ui->setupUi(this);
    setWindowTitle("Merator");
    connect(ui->settings_b, &QPushButton::released, this, [this]
            {SettingsDialog dial(m_settings, this);dial.exec(); });
    connect(ui->exit_b, &QPushButton::released, this, [this]
            { close(); });
    connect(ui->start_b, &QPushButton::released, this, [this]
            { ui->stackedWidget->setCurrentWidget(ui->page_2); });
    connect(ui->back_b, &QPushButton::released, this, [this]
            { ui->stackedWidget->setCurrentWidget(ui->page); });

    connect(ui->easy_b, &QPushButton::released, this, [this]
            { createMazeView(MMaze::DifficultyClass::EASY); });
    connect(ui->normal_b, &QPushButton::released, this, [this]
            { createMazeView(MMaze::DifficultyClass::NORMAL); });
    connect(ui->hard_b, &QPushButton::released, this, [this]
            { createMazeView(MMaze::DifficultyClass::HARD); });
    connect(ui->insane_b, &QPushButton::released, this, [this]
            { createMazeView(MMaze::DifficultyClass::INSANE); });
    connect(ui->extream_b, &QPushButton::released, this, [this]
            { createMazeView(MMaze::DifficultyClass::EXTREAM); });
}

MainWindow::~MainWindow()
{
    delete ui;
    for (int i = 0; i < m_mazes_dispal_a.size(); ++i)
    {
        if (m_mazes_dispal_a[i] != nullptr)
        {
            m_mazes_dispal_a[i]->close();
            delete m_mazes_dispal_a[i];
        }
    }
}

void MainWindow::createMazeView(MMaze::DifficultyClass diff_)
{
    if (m_mazes_dispal_a.size() >= maxMazeDisplay)
        return;
    MMaze::MazeDisplayer *mazeView = new MMaze::MazeDisplayer(m_settings, diff_, this);
    m_mazes_dispal_a.push_back(mazeView);
    mazeView->show();
}