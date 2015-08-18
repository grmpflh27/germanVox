#include "voxkarte.h"
#include "vector"

voxKarte::voxKarte(QString titleT, QWidget *parent) :
    QWidget(parent)
{
    this->setStyleSheet("QLabel {color: blue; font-family: Verdana }");
    title = new QLabel(titleT, this);
    resize(200,150);
    title->move(x() + width()/2, height()/10);

    cardEdit = new QTextEdit(this);
    cardEdit->setFont(QFont("Segoe Script",12,QFont::Bold,false));
    cardEdit->resize(150,100);
    cardEdit->move(width()/6,height()/2);
    cardEdit->viewport()->setAutoFillBackground(false);
    cardEdit->setFrameStyle(QFrame::NoFrame);
}

void voxKarte::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);
    std::vector<int> vec {40, 10, 25, 25, 25, 25, 25, 25};

    QPen myPen(Qt::blue, 2, Qt::SolidLine);
    painter.setPen(myPen);
    QRect rect = QRect(0,0,200,150);
    painter.drawRect(rect);
    myPen.setWidth(1);
    painter.setPen(myPen);
    int sum = 0;
    for(const int x: vec){
        sum += x;
        painter.drawLine(0, sum, 200, sum);
    }
}
