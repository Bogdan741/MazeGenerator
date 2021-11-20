#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <types.h>
#include <array>
#include <MazeDisplayer.h>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Dialog;
}
QT_END_NAMESPACE

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(MMaze::Settings &settings_, QWidget *parent = nullptr);
    ~SettingsDialog();

private:
    void setUpDialog();

private slots:
    void apply();
    bool changeColor(QPushButton *pushB, QColor &tmpColor);

private:
    MMaze::Settings &m_settings;

    QColor m_tmpBackgroundColor;
    QColor m_tmpMazeWallColor;
    QColor m_tmpSolvLineColor;
    
    QLabel *n_mazeColor;
    QLabel *n_solColor;
    QLabel *n_backgoundColor;
    QLabel *n_lineWidthMaze;
    QLabel *n_lineWidthSol;
    QLabel *n_penCapStyle;
    QLabel *n_mazeType;
    QLabel *n_solutionAlgo;
    QLabel *n_mazeGenAlog;
    QPushButton *b_mazeColor;
    QPushButton *b_solColor;
    QPushButton *b_backgroundColor;
    QSpinBox *sb_lineWidthMaze;
    QSpinBox *sb_lineWidthSol;
    QComboBox *cb_mazeType;
    QComboBox *cb_solutionAlgo;
    QComboBox *cb_mazeGenAlgo;

    QPushButton *b_apply;
    QPushButton *b_cancel;
    
};
#endif // DIALOG_H
