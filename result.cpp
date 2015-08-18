#include "result.h"

#include <QHeaderView>
#include <QDebug>

//result for test
myResult::myResult(const QList<bandaFlags::ctry>& countryL,
                   const QList<int>& perm,
                   QString picPath,
                   const QStringList& subset,
                   const QStringList& answers,
                   const QList<bool>& hintsUsed,
                   int right,
                   int total,
                   QWidget *parent) :
    QDialog(parent)
{
    resView = new QTableView(this);
    mModel = new resModel(countryL, perm, picPath, subset, answers, hintsUsed, this);

    resView->setModel(mModel);

    setupResult(QList<int>() << right, total);

}

myResult::myResult(const QList<bandaFlags::ctry> &countryL,
                   const QList<int> &perm,
                   const QList<bandaFlags::ctry> &subset,
                   QList<bandaFlags::quizAnswer>& quizAnswers,
                   const QList<int> &quizRightIdx,
                   int total,
                   int noOfOptions,
                   const QList<bandaPlayerData *> &bandaPlayers,
                   QWidget *parent) :
    QDialog(parent)
{
    resView = new QTableView(this);
    mModel = new resModel(countryL, perm, subset, quizAnswers, quizRightIdx, noOfOptions, bandaPlayers, this);
    resView->setModel(mModel);

    QList<int> scores;
    foreach(bandaPlayerData* bP, bandaPlayers){
        scores.append(bP->correctAnswers);
    }

    setupResult(scores, total, bandaPlayers);
}

void myResult::setupResult(QList<int>& right, int total, const QList<bandaPlayerData *> &bandaPlayers)
{
    setWindowIcon(QIcon(":/cfg/res/Icon.png"));
    resView->setModel(mModel);
    QFont bandaFont = QFont("Georgia",-1,QFont::Bold,false);
    QHeaderView* vertHeader = resView->verticalHeader();
    vertHeader->setDefaultSectionSize(50);

    resView->setVerticalHeader(vertHeader);
    resView->setFont(bandaFont);
    resView->horizontalHeader()->setFont(bandaFont);
    resView->resizeColumnsToContents();

    okBut = new QPushButton(tr("Ok"),this);
    if(right.size() == 1){
        label = new QLabel(tr("%1 out of %2 answers correct.").arg(right.at(0)).arg(total));
    }
    // 2 Player game
    else if(right.size() == 2){
        QString ans;
        if(right.at(0) == right.at(1)){
            ans = tr("Draw!\n\nBoth Players have %1 out of %2 answers correct.").arg(right.at(0)).arg(total);
        }else{
            int winnerID = ((right.at(0) > right.at(1)) ? 0 : 1);
            ans = tr("%1 wins!\n\n%2: %3 answers correct.\n%4: %5 answers correct.").arg(bandaPlayers.at(winnerID)->name).arg(bandaPlayers[0]->name).arg(right.at(0)).arg(bandaPlayers[1]->name).arg(right.at(1));
        }
        label = new QLabel(ans);
    }
    label->setFont(QFont("Georgia",12,QFont::Bold,false));
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout* vLay = new QVBoxLayout(this);
    vLay->addWidget(label);
    vLay->addWidget(resView);
    vLay->addWidget(okBut);
    setLayout(vLay);
    setWindowTitle(tr("Results"));

    connect(okBut,SIGNAL(clicked()),this,SLOT(accept()));
}
