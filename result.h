#ifndef RESULT_H
#define RESULT_H

#include <QStandardItemModel>
#include <QWidget>
#include <QTableView>
#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

#include
class myResult : public QDialog
{
    Q_OBJECT
public:
    myResult(const QString& term, const QString& def, QWidget *parent=0);


signals:

public slots:

private:
    QLabel* label;
    QLabel* sublabel;
    QPushButton* okBut;
    QTableView* resView;
    resModel* mModel;
};

#endif // RESULT_H
