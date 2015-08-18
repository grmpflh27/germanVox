#ifndef VOXEDITDIALOG_H
#define VOXEDITDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "voxcardsystem.h"
#include "voxspecialchars.h"

class voxEditDialog : public QDialog
{
    Q_OBJECT

public:
    voxEditDialog(const QString term, const QString def, voxcardSystem& vSys, QWidget* parent=0);

public slots:
    void saveToDict();

private:
    QString origTerm;
    QString origDef;
    QLineEdit* termEdit;
    QLineEdit* defEdit;
    QGridLayout* layout;
    QPushButton* saveB;
    QPushButton* cancelB;
    voxcardSystem& voxCardSys;
    voxSpecialChars* voxSpecialC;
    //voxUI* vUI;
};

#endif // VOXEDITDIALOG_H
