#include "voxcardgame.h"

#include <QDebug>



voxCardGame::voxCardGame(voxcardSystem *mSys, QMap<QString, voxCard> *mapPtr) : vSys(mSys), gamePtr(mapPtr), curCardsNo(0)
{
    curItem = gamePtr->begin();
}

QPair<QString, QString> voxCardGame::getNextVoc()
{
    QPair<QString, QString> voc;
    if(curItem != gamePtr->end()){
        voc.first = (*curItem).learnTerm;
        voc.second = (*curItem).nativeTerm;
    }
    else{
        voc.first = "";
        voc.second = "";
    }
    return voc;
}

void voxCardGame::correctAnswer()
{
    vSys->moveCardToNextStage((*curItem).learnTerm);
    curItem++;
    vSys->writeDictionary();
}

void voxCardGame::falseAnswer()
{
    vSys->moveCardToFirstStage((*curItem).learnTerm);
    curItem++;
    vSys->writeDictionary();
}

voxcardSystem* voxCardGame::getCardSystem() const
{
    return this->vSys;
}
