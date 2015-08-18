#ifndef VOXKARTE_H
#define VOXKARTE_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QtGui>

class voxKarte : public QWidget
{
    Q_OBJECT
public:
    explicit voxKarte(QString titleT, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    QLabel* title;
    QTextEdit* cardEdit;
};

#endif // VOXKARTE_H
