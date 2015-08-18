#include "voxcard.h"

// *** statics ***

int voxCard::globalIDCnt = 0;

//[todo] multi lang support
voxCard::voxCard() : id(globalIDCnt++), sequenceNumber(1)
{
    learnTerm = "";
    nativeTerm = "";
    validDate = QDate::currentDate();
}

voxCard::voxCard(const QString &nTerm, const QString &lTerm) :
    id(globalIDCnt++), sequenceNumber(1), nativeTerm(nTerm), learnTerm(lTerm)
{
    validDate = QDate::currentDate();
}

voxCard::voxCard(const QString& nTerm, const QString& lTerm, const QDate& date, const int origId, const int seq)
{
    nativeTerm = nTerm;
    learnTerm = lTerm;
    id = origId;
    sequenceNumber = seq;
    validDate = date;
}

bool voxCard::operator==(const voxCard &other)
{
    return(this->learnTerm == other.learnTerm &&
           this->nativeTerm == other.nativeTerm);
}

QDataStream &operator<<(QDataStream &os, const voxCard &vox)
{
    os << vox.id
       << vox.sequenceNumber
       << vox.validDate.toString()
       << vox.nativeTerm
       << vox.learnTerm;

    return os;

}

QDataStream &operator>>(QDataStream &is, voxCard &vox)
{
    QString date;
    is >> vox.id;
    is >> vox.sequenceNumber;
    is >> date;
    is >> vox.nativeTerm;
    is >> vox.learnTerm;

    vox.validDate = QDate::fromString(date);
    return is;

}
