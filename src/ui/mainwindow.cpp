#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <dialog.h>
#include <dialogexception.h>

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
}

void MainWindow::createMazeView(MMaze::DifficultyClass diff_)
{
    for (auto dis : m_mazes_displ_a)
    {
        if (dis && dis->isHidden())
            m_mazes_displ_a.erase(std::remove_if(m_mazes_displ_a.begin(), m_mazes_displ_a.end(), [&dis](const std::shared_ptr<MMaze::MazeDisplayer> i)
                                                 { return i == dis; }));
    }

    try
    {
        isNewWindowAlloved();
    }
    catch (const MMaze::DialogException &ec)
    {
        QMessageBox::warning(this, "Merator", QString{"Too much maze windows have been created. Max number: %1. Please close some of the windows if you want to open new."}.arg(maxMazeDisplay));
        return;
    }

    std::shared_ptr<MMaze::MazeDisplayer> mazeView = std::make_shared<MMaze::MazeDisplayer>(m_settings, diff_, this);
    m_mazes_displ_a.push_back(mazeView);
    mazeView->show();
}

void MainWindow::isNewWindowAlloved() const
{
    if (m_mazes_displ_a.size() > maxMazeDisplay)
        throw MMaze::DialogException();
}