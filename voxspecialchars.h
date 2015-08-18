#ifndef VOXSPECIALCHARS_H
#define VOXSPECIALCHARS_H

#include "voxConst.h"
#include "voxUI.h"
#include <QWidget>
#include <QRegExp>
#include <QList>
#include <QDebug>

namespace Ui {
class voxSpecialChars;
}

class voxSpecialChars : public QWidget
{
    Q_OBJECT

public:
    explicit voxSpecialChars(voxUI* vUI, QWidget *parent = 0);
    ~voxSpecialChars();

private slots:
    //special chars
    void on_specialCharArrow_clicked();
    void specialButtonClicked();

private:
    Ui::voxSpecialChars *ui;
    void showSpecialChars();
    voxUI* vUI;
};

#endif // VOXSPECIALCHARS_H
