#ifndef VOXSYSTEM_H
#define VOXSYSTEM_H

#include <QMainWindow>
#include <QList>
#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>
#include <iostream>
#include <vector>


#include "voxkarte.h"
#include "voxConst.h"

class voxSystem : public QMainWindow
{
    Q_OBJECT
public:
    explicit voxSystem(QWidget *parent = 0);
    voxKarte* engCard;
    voxKarte* gerCard;
    QList<QList<voxKarte> > box;


protected:
    void keyPressEvent(QKeyEvent *e);
signals:

public slots:

};

#endif // VOXSYSTEM_H
