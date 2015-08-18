#ifndef VOXCARDGAME_H
#define VOXCARDGAME_H

#include <QMap>
#include "voxcardsystem.h"

class voxCardGame
{
    QMap<QString, voxCard>* gamePtr;
    QMap<QString, voxCard>::iterator curItem;

public:
    voxCardGame(voxcardSystem* vSys, QMap<QString, voxCard>* mapPtr);

    QPair<QString, QString> getNextVoc();

    void correctAnswer();
    void falseAnswer();

    voxcardSystem* vSys;
    voxcardSystem *getCardSystem() const;

    int cardsNo;
    int curCardsNo;

    friend class voxUI;
};

#endif // VOXCARDGAME_H
