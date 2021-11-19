#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialog.h>

MainWindow::MainWindow(MMaze::Settings &settings_, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_settings(settings_)
{
    ui->setupUi(this);
    connect(ui->settings_b, &QPushButton::released, this, [this]
            {SettingsDialog dial(m_settings, this);dial.exec(); });
    connect(ui->exit_b, &QPushButton::released, this, [this]{close();});
}

MainWindow::~MainWindow()
{
    delete ui;
}
