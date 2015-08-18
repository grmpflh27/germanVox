#include "voxsystem.h"

voxSystem::voxSystem(QWidget *parent) :
    QMainWindow(parent)
{
    gerCard = new voxKarte(tr("ger"),this);

    engCard = new voxKarte(tr("eng"),this);
    engCard->move(QPoint(engCard->width()+ voxConst::cardAbs, 0));

    resize(QSize(gerCard->width()*2+voxConst::cardAbs,gerCard->height()));

    //box.append();
}

void voxSystem::keyPressEvent(QKeyEvent* e)
{

}
