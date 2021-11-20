#include <MazeDisplayer.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QtSvg/QSvgGenerator>

using namespace MMaze;

MazeDisplayer::MazeDisplayer(const MMaze::Settings & settings_, MMaze::DifficultyClass diff_, QWidget * parent)
:QDialog(parent), m_settings(settings_), m_difficulty(diff_)
{
    setUpWidget();
    //TODO: Implement slots
}

void MazeDisplayer::setUpWidget()
{
    b_close = new QPushButton{tr("Close")};
    b_hideSolution = new QPushButton{tr("Hide solution")};
    b_showSolution = new QPushButton{tr("Show solution")};
    b_save = new QPushButton{tr("Save image:")};

    
    QSpacerItem * widthRegulator = new QSpacerItem(80,0,QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSpacerItem * heightRegulator = new QSpacerItem(0,200, QSizePolicy::Fixed, QSizePolicy::Expanding);

    QVBoxLayout *leftLayout = new QVBoxLayout{};

    leftLayout->addSpacerItem(widthRegulator);
    leftLayout->addWidget(b_showSolution);
    leftLayout->addWidget(b_hideSolution);
    leftLayout->addWidget(b_save);

    leftLayout->addSpacerItem(heightRegulator);
    leftLayout->addWidget(b_close);
    QHBoxLayout * mainLayout = new QHBoxLayout();
    mainLayout->addLayout(leftLayout);

    m_mazeRanderer = new MMaze::MazeRenderer(m_settings, m_difficulty);
    mainLayout->addWidget(m_mazeRanderer);
    setLayout(mainLayout);

}