#ifndef VOXCARD_H
#define VOXCARD_H

#include <QDate>
#include <QString>
#include <QTextStream>
#include "voxConst.h"

class voxCard
{
public:
    voxCard();
    voxCard(const QString& nTerm, const QString& lTerm);
    voxCard(const QString& nTerm, const QString& lTerm, const QDate& date, const int origId, const int seq);

    int id;
    int sequenceNumber;
    QDate validDate;

    QString nativeTerm;
    QString learnTerm;

    static int globalIDCnt;

    bool operator==(const voxCard& other);
    friend QDataStream& operator<<(QDataStream& os, const voxCard& vox);
};

QDataStream& operator<<(QDataStream& os, const voxCard& vox);
QDataStream& operator>>(QDataStream& is, voxCard& vox);

#endif // VOXCARD_H
