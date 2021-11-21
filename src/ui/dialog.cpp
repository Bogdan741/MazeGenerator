#include "dialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QDebug>

#define DEBUG

SettingsDialog::SettingsDialog(MMaze::Settings &settings_, QWidget *parent)
    : QDialog(parent), m_settings(settings_)
{
    setUpDialog();
    setCurrentState();
    connect(b_cancel, &QPushButton::released, this, &QDialog::close);
    connect(b_apply, &QPushButton::released, this, &SettingsDialog::apply);
    connect(b_mazeColor, &QPushButton::released, this, [this]
            { this->changeColor(b_mazeColor, m_tmpMazeWallColor); });
    connect(b_solColor, &QPushButton::released, this, [this]
            { this->changeColor(b_solColor, m_tmpSolvLineColor); });
    connect(b_backgroundColor, &QPushButton::released, this, [this]
            { this->changeColor(b_backgroundColor, m_tmpBackgroundColor); });
}

SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::setUpDialog()
{
    setWindowTitle("Maze settings");
    n_mazeColor = new QLabel("Maze line color:");
    n_solColor = new QLabel("Solution line color:");
    n_backgoundColor = new QLabel("Background color:");
    n_lineWidthMaze = new QLabel("Maze line width:");
    n_lineWidthSol = new QLabel("Solution line width:");
    n_penCapStyle = new QLabel("Style of line edges:");
    n_mazeType = new QLabel("Maze type:");
    n_solutionAlgo = new QLabel("Maze solution algorithm:");
    n_mazeGenAlog = new QLabel("Maze generation alogrithms:");

    b_mazeColor = new QPushButton();
    b_solColor = new QPushButton();
    b_backgroundColor = new QPushButton();

    b_mazeColor->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    b_solColor->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    b_backgroundColor->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    b_mazeColor->setMaximumSize(40, 20);
    b_backgroundColor->setMaximumSize(40, 20);
    b_solColor->setMaximumSize(40, 20);

    b_mazeColor->setStyleSheet(QString("background-color: %1;").arg(m_settings.mazeWallColor.name()));
    m_tmpMazeWallColor = m_settings.mazeWallColor;

    b_backgroundColor->setStyleSheet(QString("background-color: %1;").arg(m_settings.backgroundColor.name()));
    m_tmpBackgroundColor = m_settings.backgroundColor;

    b_solColor->setStyleSheet(QString("background-color: %1;").arg(m_settings.solutionLineColor.name()));
    m_tmpSolvLineColor = m_settings.solutionLineColor;

    int lineWidthMin = 0;
    int lineWidthMax = 20;

    sb_lineWidthMaze = new QSpinBox();
    sb_lineWidthSol = new QSpinBox();

    sb_lineWidthMaze->setMinimum(lineWidthMin);
    sb_lineWidthMaze->setMaximum(lineWidthMax);
    sb_lineWidthMaze->setValue(lineWidthMin);

    sb_lineWidthSol->setMinimum(lineWidthMin);
    sb_lineWidthSol->setMaximum(lineWidthMax);
    sb_lineWidthSol->setValue(lineWidthMin);

    cb_mazeType = new QComboBox();

    cb_mazeType->addItem(tr("Rectangular Maze"), static_cast<int>(MMaze::MazeTypes::RectangularMaze));
    cb_mazeType->addItem(tr("Honey Comb Maze"), static_cast<int>(MMaze::MazeTypes::HoneyCombMaze));
    cb_mazeType->addItem(tr("Rectangular Comb maze"), static_cast<int>(MMaze::MazeTypes::RectangleCombMaze));

    cb_solutionAlgo = new QComboBox();
    cb_solutionAlgo->addItem(tr("BFS"), static_cast<int>(MMaze::MazeSolvAlgo::BFS));
    cb_solutionAlgo->addItem(tr("DFS"), static_cast<int>(MMaze::MazeSolvAlgo::DFS));
    cb_solutionAlgo->addItem(tr("AStar"), static_cast<int>(MMaze::MazeSolvAlgo::AStar));

    cb_mazeGenAlgo = new QComboBox();
    cb_mazeGenAlgo->addItem(tr("DFS"), static_cast<int>(MMaze::MazeGenAlgo::DFS));
    cb_mazeGenAlgo->addItem(tr("BFS"), static_cast<int>(MMaze::MazeGenAlgo::BFS));
    cb_mazeGenAlgo->addItem(tr("Kruscal"), static_cast<int>(MMaze::MazeGenAlgo::Kruscal));
    cb_mazeGenAlgo->addItem(tr("Prim"), static_cast<int>(MMaze::MazeGenAlgo::Prim));

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(n_mazeGenAlog, cb_mazeGenAlgo);
    formLayout->addRow(n_mazeType, cb_mazeType);
    formLayout->addRow(n_solutionAlgo, cb_solutionAlgo);

    formLayout->addRow(n_mazeColor, b_mazeColor);
    formLayout->addRow(n_solColor, b_solColor);
    formLayout->addRow(n_backgoundColor, b_backgroundColor);

    formLayout->addRow(n_lineWidthMaze, sb_lineWidthMaze);
    formLayout->addRow(n_lineWidthSol, sb_lineWidthSol);

    b_apply = new QPushButton(tr("Apply"));
    b_cancel = new QPushButton(tr("Cancel"));

    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->addWidget(b_cancel);
    horizontalLayout->addSpacerItem(spacer);
    horizontalLayout->addWidget(b_apply);

    formLayout->addRow(horizontalLayout);
    QVBoxLayout *cenLayout = new QVBoxLayout();
    cenLayout->addLayout(formLayout);
    setLayout(cenLayout);
}

void SettingsDialog::apply()
{
    m_settings.backgroundColor = m_tmpBackgroundColor;
    m_settings.solutionLineColor = m_tmpSolvLineColor;
    m_settings.mazeWallColor = m_tmpMazeWallColor;

    m_settings.mazeGenAlgo = static_cast<MMaze::MazeGenAlgo>(cb_mazeGenAlgo->itemData(cb_mazeGenAlgo->currentIndex(), Qt::UserRole).toInt());

    m_settings.mazeSolveAlgo = static_cast<MMaze::MazeSolvAlgo>(cb_solutionAlgo->itemData(cb_solutionAlgo->currentIndex(), Qt::UserRole).toInt());

    m_settings.mazeType = static_cast<MMaze::MazeTypes>(cb_mazeType->itemData(cb_mazeType->currentIndex(), Qt::UserRole).toInt());

    m_settings.lineWidhtSolution = sb_lineWidthSol->value();
    m_settings.lineWidthMazeWall = sb_lineWidthMaze->value();

#ifdef DEBUG
    qDebug() << "Maze type: " << (int)m_settings.mazeType << '\n'
             << "Maze generation algo: " << (int)m_settings.mazeGenAlgo << '\n'
             << "Maze solvment algo: " << (int)m_settings.mazeSolveAlgo << '\n'
             << "Wall color: " << m_settings.mazeWallColor.name() << '\n'
             << "Line color: " << m_settings.solutionLineColor.name() << '\n'
             << "Background color: " << m_settings.backgroundColor.name() << '\n'
             << "Wall width : " << m_settings.lineWidthMazeWall << '\n'
             << "Line width : " << m_settings.lineWidhtSolution;
#endif
}

bool SettingsDialog::changeColor(QPushButton *pushB, QColor &tmpColor)
{
    QColor color = QColorDialog::getColor(tmpColor, this);
    if (color.isValid())
    {
        tmpColor = color;
        pushB->setStyleSheet(QString("background-color: %1;").arg(tmpColor.name()));
        return true;
    }
    return false;
}

void SettingsDialog::setCurrentState()
{
    // * Setting maze generation algorithm option
    int iMazeGenAlgo = -1;
    if (m_settings.mazeGenAlgo == MMaze::MazeGenAlgo::BFS)
        iMazeGenAlgo = cb_mazeGenAlgo->findData(static_cast<int>(MMaze::MazeGenAlgo::BFS));
    else if (m_settings.mazeGenAlgo == MMaze::MazeGenAlgo::DFS)
        iMazeGenAlgo = cb_mazeGenAlgo->findData(static_cast<int>(MMaze::MazeGenAlgo::DFS));
    else if (m_settings.mazeGenAlgo == MMaze::MazeGenAlgo::Kruscal)
        iMazeGenAlgo = cb_mazeGenAlgo->findData(static_cast<int>(MMaze::MazeGenAlgo::Kruscal));
    else if (m_settings.mazeGenAlgo == MMaze::MazeGenAlgo::Prim)
        iMazeGenAlgo = cb_mazeGenAlgo->findData(static_cast<int>(MMaze::MazeGenAlgo::Prim));

    if(iMazeGenAlgo != -1)
        cb_mazeGenAlgo->setCurrentIndex(iMazeGenAlgo);

    // * Setting maze solving algorithm option
    int iMazeSolvAlgo = -1;
    if (m_settings.mazeSolveAlgo == MMaze::MazeSolvAlgo::BFS)
        iMazeSolvAlgo = cb_solutionAlgo->findData(static_cast<int>(MMaze::MazeSolvAlgo::BFS));
    else if (m_settings.mazeSolveAlgo == MMaze::MazeSolvAlgo::DFS)
        iMazeSolvAlgo = cb_solutionAlgo->findData(static_cast<int>(MMaze::MazeSolvAlgo::DFS));
    else if (m_settings.mazeSolveAlgo == MMaze::MazeSolvAlgo::AStar)
        iMazeSolvAlgo = cb_solutionAlgo->findData(static_cast<int>(MMaze::MazeSolvAlgo::AStar));
    
    if(iMazeSolvAlgo != -1)
        cb_solutionAlgo->setCurrentIndex(iMazeSolvAlgo);
    
    // * Setting maze type option
    int iMazeType = -1;
    if(m_settings.mazeType == MMaze::MazeTypes::HoneyCombMaze)
        iMazeType = cb_mazeType->findData(static_cast<int>(MMaze::MazeTypes::HoneyCombMaze));
    else if(m_settings.mazeType == MMaze::MazeTypes::RectangularMaze)
        iMazeType = cb_mazeType->findData(static_cast<int>(MMaze::MazeTypes::RectangularMaze));
    else if(m_settings.mazeType == MMaze::MazeTypes::RectangleCombMaze)
        iMazeType = cb_mazeType->findData(static_cast<int>(MMaze::MazeTypes::RectangleCombMaze));

    if(iMazeType != -1)
        cb_mazeType->setCurrentIndex(iMazeType);

    
    // * Settings the colors options
    b_mazeColor->setStyleSheet(QString("background-color: %1;").arg(m_settings.mazeWallColor.name()));
    m_tmpMazeWallColor = m_settings.mazeWallColor;

    b_backgroundColor->setStyleSheet(QString("background-color: %1;").arg(m_settings.backgroundColor.name()));
    m_tmpBackgroundColor = m_settings.backgroundColor;

    b_solColor->setStyleSheet(QString("background-color: %1;").arg(m_settings.solutionLineColor.name()));
    m_tmpSolvLineColor = m_settings.solutionLineColor;

    // * Settings the line width color
    sb_lineWidthMaze->setValue(m_settings.lineWidthMazeWall);
    sb_lineWidthSol->setValue(m_settings.lineWidhtSolution);
}