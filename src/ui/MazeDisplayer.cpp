#include <MazeDisplayer.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QFileDialog>
#include <QDir>
#include <saveexception.h>
#include <QMessageBox>
using namespace MMaze;

MazeDisplayer::MazeDisplayer(const MMaze::Settings & settings_, MMaze::DifficultyClass diff_, QWidget * parent)
:QDialog(parent), m_settings(settings_), m_difficulty(diff_)
{
    setUpWidget();
    connect(b_close, &QPushButton::released, this, [this]{close();});
    connect(b_save, &QPushButton::released, this, &MazeDisplayer::saveMaze);
    connect(b_hideSolution, &QPushButton::released, this, [this]{
        b_showSolution->setEnabled(true);
        b_hideSolution->setEnabled(false);
        m_mazeRanderer->setSolutionMode(false);
    });
    connect(b_showSolution, &QPushButton::released, this, [this]{
        b_showSolution->setEnabled(false);
        b_hideSolution->setEnabled(true);
        m_mazeRanderer->setSolutionMode(true);
    });
    m_pathToSaveImage = QDir::homePath();
}

void MazeDisplayer::setUpWidget()
{
    b_close = new QPushButton{tr("Close")};
    b_hideSolution = new QPushButton{tr("Hide solution")};
    b_showSolution = new QPushButton{tr("Show solution")};
    b_save = new QPushButton{tr("Save image:")};

    b_hideSolution->setEnabled(false);
    
    b_close->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    b_hideSolution->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    b_showSolution->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    b_save->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);

    
    QSpacerItem * widthRegulator = new QSpacerItem(150,0,QSizePolicy::Fixed, QSizePolicy::Fixed);
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
    m_mazeRanderer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(m_mazeRanderer);
    setLayout(mainLayout);

}


void MazeDisplayer::saveMaze() 
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save image"),m_pathToSaveImage,tr("Images (*.svg)"));

    try{
        isFileNameValid(fileName);
    }
    catch(const MMaze::SaveException & ec)
    {
        QMessageBox::warning(this, "Merator", QString::fromStdString(ec.message()));
        return;
    }
    
    m_pathToSaveImage = QFileInfo(fileName).path();
    m_mazeRanderer->getImage(fileName+".svg");
}

void MazeDisplayer::isFileNameValid(const QString & fileName ) const
{
    if(fileName.isNull())
    {
        throw MMaze::SaveException();
    }
}