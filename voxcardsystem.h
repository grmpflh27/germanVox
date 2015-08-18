#ifndef VOXCARDSYSTEM_H
#define VOXCARDSYSTEM_H

#include "voxcard.h"
#include <QMap>

class voxcardSystem
{
public:

    voxcardSystem();

    voxConst::natLanguages nativeLang;
    voxConst::languages learnLang;
    QMap<QString, voxCard> dict;
    QMap<QString, voxCard> dueCards;
    QMap<QString, voxCard> randomCards;

    void addCard(const voxCard& vCard);
    void editCard(const voxCard &editCard, const QString& newTerm, const QString& newDef);
    void removeCard(const voxCard &vCard);
    void removeCard(const QString &removeTerm);

    void readDictionary(QMap<QString, voxCard> &map);
    void writeDictionary();

    //logic for system
    void moveCardToNextStage(const QString& term);
    void moveCardToNextStage(const voxCard& vCard);
    void moveCardToFirstStage(const QString& term);
    void moveCardToFirstStage(const voxCard& vCard);
    int calcDueCards();
    void calcRandomSeries(int items);

    static int globalCnt;
};

QDataStream& operator<<(QDataStream& os, const QMap<QString, voxCard> &map);
QDataStream& operator>>(QDataStream& is, QMap<QString, voxCard> &map);

#endif // VOXCARDSYSTEM_H
