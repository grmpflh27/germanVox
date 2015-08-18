#include "voxcardsystem.h"
#include "voxConst.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>

/* statics */
int voxcardSystem::globalCnt = 0;


voxcardSystem::voxcardSystem() : nativeLang(voxConst::eng)
{
}


void voxcardSystem::addCard(const voxCard& vCard)
{
    //voxcardSystem::globalCnt++;
    dict.insert(vCard.learnTerm, vCard);
}

void voxcardSystem::editCard(const voxCard &editCard, const QString& newTerm, const QString& newDef)
{
    if(editCard.learnTerm == newTerm){
        dict[editCard.learnTerm].nativeTerm = newDef;
    }
    else{
       dict.insert(newTerm, voxCard(newDef, newTerm, editCard.validDate, editCard.id, editCard.sequenceNumber));
       dict.remove(editCard.learnTerm);
    }
}


void voxcardSystem::removeCard(const voxCard &vCard)
{
    //voxcardSystem::globalCnt--;
}

void voxcardSystem::removeCard(const QString& removeTerm)
{
    //voxcardSystem::globalCnt--;
    dict.remove(removeTerm);
}

void voxcardSystem::readDictionary(QMap<QString, voxCard>& map)
{

    QDir dir(QDir::currentPath() + "/meta/");
    if(!dir.exists()){
        dir.mkpath(dir.path());
    }
    else{
        QFile file(QDir::currentPath() + voxConst::dictFile + QString("%1").arg(learnLang));
        if(!file.open(QIODevice::ReadOnly)){
                return;
        }

        QDataStream readIN(&file);
        QString header;
        readIN >> header;

        if(header != voxConst::voxHeader){
            qDebug() << "header mismatch" << header << "!=" << voxConst::voxHeader;
            return;
        }
        int natL, learnL;
        readIN /*>> voxcardSystem::globalCnt*/ >> natL >> learnL;

        nativeLang = static_cast<voxConst::natLanguages>(natL);
        learnLang = static_cast<voxConst::languages>(learnL);


        while(!readIN.atEnd()){
        //for(int i = 0; i < voxcardSystem::globalCnt; i++){
            voxCard v;
            readIN >> v;
            map.insert(v.learnTerm, v);
        }
        file.close();
    }

}

void voxcardSystem::writeDictionary()
{
    QFile file(QDir::currentPath() + voxConst::dictFile + QString("%1").arg(learnLang));

    if(!file.open(QIODevice::WriteOnly))
        return;
    QDataStream writeOUT(&file);

    //write header
    writeOUT << voxConst::voxHeader /*<< voxcardSystem::globalCnt*/ << nativeLang << learnLang << dict;
    file.close();
}

void voxcardSystem::moveCardToNextStage(const QString& term)
{
    dict[term].sequenceNumber *= 2;
    dict[term].validDate = QDate::currentDate().addDays(dict[term].sequenceNumber);
}

void voxcardSystem::moveCardToNextStage(const voxCard &vCard)
{

}

void voxcardSystem::moveCardToFirstStage(const QString& term)
{
    dict[term].sequenceNumber = 1;
    dict[term].validDate = QDate::currentDate().addDays(dict[term].sequenceNumber);
}

int voxcardSystem::calcDueCards()
{
    dueCards.clear();
    QMap<QString, voxCard>::iterator itr;
    for(itr = dict.begin(); itr != dict.end(); itr++){
        if((*itr).validDate <= QDate::currentDate()){
            dueCards.insert((*itr).learnTerm, *itr);
        }
    }
    return dueCards.size();
}

void voxcardSystem::calcRandomSeries(int items)
{
    int maxIndex = dict.size();
    QList<int> addedIdx;

    if(!randomCards.empty()){
        randomCards.clear();
    }

    while(addedIdx.size() < items){
        int randInt = qrand() % maxIndex;
        if(!addedIdx.contains(randInt)){
            QMap<QString,voxCard>::iterator iter = dict.begin();
            addedIdx.append(randInt);
            iter += randInt;
            qDebug() << iter.key();
            randomCards.insert(iter.key(), iter.value());
        }
    }
    qDebug() << "Change map to dict!!!";
}


QDataStream &operator>>(QDataStream &is, QMap<QString, voxCard> &map)
{
    QMap<QString, voxCard>::iterator iter;
    for(iter = map.begin(); iter != map.end(); iter++){
        is >> *iter;
    }
    return is;
}


QDataStream &operator<<(QDataStream &os, const QMap<QString, voxCard> &map)
{
    foreach(const voxCard& v, map){
        os << v;
    }

    return os;
}
