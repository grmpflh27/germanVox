#include "voxUI.h"
#include "voxEditDialog.h"
#include "ui_voxUI.h"

#include <QListIterator>
#include <QDebug>
#include <QDialog>
#include <QKeyEvent>
#include <QDateTime>
#include <QScrollBar>
#include <QSortFilterProxyModel>

bool voxUI::answerGiven = false;

voxUI::voxUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::voxUI)
{
    ui->setupUi(this);
    qsrand(QDateTime::currentMSecsSinceEpoch());
    window = voxUI::mainW;
    ui->dateLabel->setText(QDate::currentDate().toString());
    ui->practiceRB->setChecked(true);
    //determine learn language
    vSys.learnLang = static_cast<voxConst::languages>(ui->comboBox->currentIndex());
    //set specialCharList
    setSpecialCharList();
    vSys.readDictionary(vSys.dict);
    updateUI();

    connectFct();

    qApp->installEventFilter(this);
}

voxUI::~voxUI()
{
    delete ui;
}

const QList<QString> *voxUI::getCurSpecialList() const
{
    return curSpecialList;
}

QLineEdit *voxUI::getCurLineEdit() const
{
    return curLineEdit;
}

void voxUI::on_MainNewCard_clicked()
{
    window = voxUI::addCardW;
    updateUI();
}

void voxUI::updateUI()
{
    ui->stackedWidget->setCurrentIndex(window);

    switch(window){

    case mainW:
        ui->mainCardsDue->display(vSys.calcDueCards());
        ui->wordlistRB->setChecked(true);
        if(vSys.dueCards.empty()){
            ui->practiceRB->setEnabled(false);
            ui->mainCardsDue->setPalette(QPalette(Qt::red));
        }
        else{
            ui->mainCardsDue->setPalette(QPalette(Qt::green));
            ui->practiceRB->setEnabled(true);
            ui->randomRB->setEnabled(true);
            ui->studyButton->setEnabled(true);
            ui->practiceRB->isChecked() ? on_practiceRB_clicked() : on_randomRB_clicked();
        }
        break;

    case addCardW:
        //ui->AddTermL->setPixmap(QPixmap("://res/Germany.png"));
        //ui->AddTermL->resize(voxConst::homeFlagSize);
        ui->term1_LEdit->setFocus();
        curLineEdit = ui->term1_LEdit;
        showSpecialChars();
        break;

    case dictionaryW:

        break;

    case practiceW:

        break;

    case wordlistW:
        ui->wordTableFilter->setText("");
        ui->wordTableFilter->setFocus();
        this->vWL = new voxWordListModel(vSys, this);
        ui->wordTableView->setModel(vWL);
        updateWordTableView();
        break;
    }
}

void voxUI::connectFct()
{
    // unsauber aber funktioniert - bitte ändern
    QList<QPushButton*> allPBs = ui->addP->findChildren<QPushButton*>();
    QList<QLineEdit*> allLineEdit = ui->addP->findChildren<QLineEdit*>();
    QListIterator<QPushButton*> lPBitIter(allPBs);
    QListIterator<QLineEdit*> lEditIter(allLineEdit);
    QRegExp specLabel("^specialChar_(\\d+)$");

    while(lPBitIter.hasNext()){
        QPushButton* next = lPBitIter.next();
        if(next->objectName().contains(specLabel)){
            connect(next, SIGNAL(clicked()), this, SLOT(specialButtonClicked()));
        }
    }

    //    while(lEditIter.hasNext()){
    //        QWidget* next = lEditIter.next();
    ////        connect(next, SIGNAL(), this, SLOT(specialButtonClicked()));
    //    }
    //connect(ui->wordTableView, SIGNAL(activated(QModelIndex)), this, SLOT(specialButtonClicked()));
    connect(ui->practToWordListB, SIGNAL(clicked()), this, SLOT(on_goButton_clicked()));
}

void voxUI::setSpecialCharList()
{
    curSpecialList = &voxConst::umGermanLC;
}

void voxUI::showSpecialChars()
{
    QRegExp rx("specialChar_(\\d+)");
    QList<QPushButton*> allPushButtons = ui->addP->findChildren<QPushButton*>();
    QListIterator<QPushButton*> pBIter(allPushButtons);

    while(pBIter.hasNext()){
        QPushButton* next = pBIter.next();
        if(next->objectName().contains(rx)){
            if(rx.cap(1).toInt() < curSpecialList->size()){
                next->setText(curSpecialList->at(rx.cap(1).toInt()));
            }
            else{
                next->hide();
            }
        }
    }

}


void voxUI::showNextTerm(voxCardGame* vGame)
{
    vGame->curCardsNo++;
    QPair<QString, QString> voc = vGame->getNextVoc();
    //go back to main
    if(voc.first.isEmpty() && voc.second.isEmpty()){
        window = mainW;
        updateUI();
    }
    ui->practiceTermLabel->setText(voc.first);
    ui->practiceDefLabel->setText(voc.second);
    ui->practiceDefLabel->hide();
}

void voxUI::updateWordTableView()
{
    ui->wordTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int halfWidth = (ui->wordTableView->size().width())/2;
    ui->wordTableView->setColumnWidth(0, halfWidth);
    ui->wordTableView->setColumnWidth(1, halfWidth-20);
    ui->wordTableView->horizontalScrollBar()->hide();
    ui->wordTableView->verticalHeader()->setVisible( false );
    ui->wordTableView->sortByColumn(0,Qt::AscendingOrder);
    ui->wordTableView->setSortingEnabled(true);
    ui->wordTableView->verticalScrollBar()->scroll(100,100);
    ui->wordTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->wordTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->wordTableView->selectRow(0);
}

void voxUI::closeEvent(QCloseEvent *)
{
    vSys.writeDictionary();
}

void voxUI::on_addWindowContinueButton_clicked()
{
    saveCards();
    clearAllAddLineEdits();
    window = mainW;
    updateUI();
}

void voxUI::on_saveAndAddMoreButton_clicked()
{
    saveCards();
    clearAllAddLineEdits();
}

void voxUI::saveCards()
{
    QList<QLineEdit*> allLineEdits = ui->addP->findChildren<QLineEdit*>();
    QListIterator<QLineEdit*> lEditIter(allLineEdits);

    QRegExp termLabel("^term(\\d{1})_LEdit$");
    QRegExp defLabel("^definition(\\d{1})_LEdit$");

    QList<voxCard> vCardList;
    vCardList.reserve(sizeof(voxCard)*voxConst::SIZE_TO_ADD);

    for(int i = 0; i < voxConst::SIZE_TO_ADD; i++){
        vCardList.append(voxCard());
    }

    //!! todo think about languages for voxCards
    while(lEditIter.hasNext()){
        QLineEdit* next = lEditIter.next();
        if(next->objectName().contains(termLabel)){
            int ID = termLabel.cap(1).toInt();
            next->text().isEmpty() ?
                        vCardList[ID-1].learnTerm = "" :
                    vCardList[ID-1].learnTerm = next->text().trimmed();
        }
        else if(next->objectName().contains(defLabel)){
            int ID = defLabel.cap(1).toInt();
            next->text().isEmpty() ?
                        vCardList[ID-1].nativeTerm = "" :
                    vCardList[ID-1].nativeTerm = next->text().trimmed();
        }
    }

    int added = 0;
    for(int i = 0; i < voxConst::SIZE_TO_ADD; i++){
        //don't add if def or term is empty
        if(vCardList[i].learnTerm.isEmpty() || vCardList[i].nativeTerm.isEmpty())
            continue;
        vSys.addCard(vCardList[i]);
        added++;
    }
    if(added > 0){
        vSys.writeDictionary();
        QString msg;
        if(added > 1){
            msg = tr("%1 terms added!").arg(added);
        }
        else{
            msg = tr("%1 term added!").arg(added);
        }
        statusBar()->showMessage(msg, 2000);
    }
}

void voxUI::clearAllAddLineEdits()
{
    QList<QLineEdit*> allLineEdits = ui->addP->findChildren<QLineEdit*>();
    QListIterator<QLineEdit*> lEditIter(allLineEdits);

    while(lEditIter.hasNext()){
        QLineEdit* next = lEditIter.next();
        next->clear();
    }
}

void voxUI::on_comboBox_currentIndexChanged(int index)
{
    vSys.learnLang = static_cast<voxConst::languages>(index);
    vSys.readDictionary(vSys.dict);
}

void voxUI::on_studyButton_clicked()
{
    ui->practiceRB->isChecked() ? mode = practiceM : mode = randomM;
    window = practiceW;
    updateUI();
    QMap<QString, voxCard>* mapPtr = NULL;

    if(mode == practiceM){
        mapPtr = &vSys.dueCards;
    }
    else if(mode == randomM){
        vSys.calcRandomSeries(ui->mainNrOfCardsSB->value());
        mapPtr = &vSys.randomCards;

        //generate randomness
    }
    vGame = new voxCardGame(&vSys, mapPtr);
    vGame->cardsNo = ui->mainNrOfCardsSB->value();

    showNextTerm(vGame);
}

void voxUI::on_goButton_clicked()
{
    if(ui->wordlistRB->isChecked()){
        window = wordlistW;
        mode = wordlistM;
    }
    else{
        window = dictionaryW;
        mode = dictionaryM;
    }
    updateUI();

    if(mode == practiceM){

    }
    else if(mode == randomM){

    }
}

//Go back to main

void voxUI::on_practBackToMainB_clicked()
{
    window = mainW;
    updateUI();
}

void voxUI::on_wordListBackToMainB_clicked()
{
    on_practBackToMainB_clicked();
}

void voxUI::on_dictBackToMainB_clicked()
{
    on_practBackToMainB_clicked();
}

//Set spinbox

void voxUI::on_practiceRB_clicked()
{
    ui->mainNrOfCardsSB->setMinimum(1);
    ui->mainNrOfCardsSB->setMaximum(vSys.dueCards.size());
    ui->mainNrOfCardsSB->setValue(vSys.dueCards.size());
}

//To do: Set default value for random (options tab)
void voxUI::on_randomRB_clicked()
{
    ui->mainNrOfCardsSB->setMinimum(1);
    ui->mainNrOfCardsSB->setMaximum(vSys.dict.size());
    ui->mainNrOfCardsSB->setValue(std::min(vSys.dict.size(), 10));
}


// key input
void voxUI::keyPressEvent(QKeyEvent *e)
{
    //    if(mode == practiceM || mode == randomM){
    //        if(e->key() == Qt::Key_Up || e->key() == Qt::Key_Down )
    //        {
    //            ui->practiceDefLabel->show();
    //        }
    //        else{

    //            //now pass the keyEvent up to the parent widget,
    QMainWindow::keyPressEvent(e);
    //        }
    //    }
}

bool voxUI::eventFilter(QObject *object, QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        static bool defShown = false;
        if(mode == practiceM || mode == randomM){
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
            int key = keyEvent->key();
            if(key == Qt::Key_Up || key == Qt::Key_Down){
                ui->practiceDefLabel->show();
                defShown = true;
            }
            else if(key == Qt::Key_Left || key == Qt::Key_Right){
                if(defShown){
                    (key == Qt::Key_Left) ? on_practiceYesB_clicked() : on_practiceNoB_clicked();
                    if(vGame->cardsNo <= vGame->curCardsNo){
                        window = mainW;
                        updateUI();
                    }
                    defShown = false;
                }
            }
        }
        //del items with del
        else if(mode == wordlistM){
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
            if(keyEvent->key() == Qt::Key_Delete){
                if(!voxUI::answerGiven){
                    on_wordTableDelete_clicked();
                    voxUI::answerGiven = true;
                    //this is because of a bug - del key gets send to event queue several times
                    QTimer *timer = new QTimer(this);
                    connect(timer, SIGNAL(timeout()), this, SLOT(timerChangeAnswerGiven()));
                    timer->start(100);
                }
            }
        }
    }
    //make sure the special character gets put into correct line edit
    if (e->type() == QEvent::FocusIn){
        if (object->objectName().contains(voxConst::rxLEdit)){
            curLineEdit = (QLineEdit*)object;
        }
    }
    return false;
}


void voxUI::on_practiceYesB_clicked()
{
    if(ui->practiceDefLabel->isVisible()){
        if(mode == practiceM){
             vGame->correctAnswer();
        }
        if(vGame->cardsNo > vGame->curCardsNo){
            vGame->curItem++;
            showNextTerm(vGame);
        }
    }
}


void voxUI::on_practiceNoB_clicked()
{
    if(ui->practiceDefLabel->isVisible()){
        if(mode == practiceM){
            vGame->falseAnswer();
        }
        if(vGame->cardsNo > vGame->curCardsNo){
            showNextTerm(vGame);
        }
    }
}

void voxUI::on_specialCharArrow_clicked()
{
    //!! todo: adapt to other languages
    (curSpecialList == &voxConst::umGermanLC) ? curSpecialList = &voxConst::umGermanUC : curSpecialList = &voxConst::umGermanLC ;
    showSpecialChars();
}

void voxUI::specialButtonClicked()
{
    QPushButton *button = (QPushButton *)sender();
    curLineEdit->setText(curLineEdit->text() + button->text());
    curLineEdit->setFocus();
}

void voxUI::on_wordTableFilter_textChanged(const QString &arg1)
{
    if(!vSys.dict.isEmpty()){
        if(!arg1.isEmpty()){
            QRegExp rx(arg1);
            QList<voxCard> filteredCards;
            for(int i=0; i < vSys.dict.values().size(); i++){
                if(vSys.dict.values().at(i).learnTerm.contains(arg1, Qt::CaseInsensitive) || vSys.dict.values().at(i).nativeTerm.contains(arg1, Qt::CaseInsensitive)){
                    filteredCards.append(vSys.dict.values()[i]);
                }
            }

            //change model
            vWL->updateModel(filteredCards);
        }
        else{
            vWL->updateModel(vSys.dict.values());
        }
    }
    updateWordTableView();
}

void voxUI::on_wordTableDelete_clicked()
{
    if(vWL->filterItems){
        QString toDel;
        //delete when there is only one entry

        if(vWL->filterItems == 1){
            toDel = ui->wordTableView->model()->index(0,0).data().toString();
        }
        else{
            if(ui->wordTableView->currentIndex().row() != -1){
                if(ui->wordTableView->currentIndex().column() == 0){
                    toDel = ui->wordTableView->currentIndex().data().toString();
                }
                else{
                    int row = ui->wordTableView->currentIndex().row();
                    toDel = ui->wordTableView->currentIndex().sibling(row,0).data().toString();
                }
            }

        }
        QMessageBox::StandardButton std;
        std=QMessageBox::question(this, tr("Delete"), tr("Do you really want to delete this card?"), QMessageBox::Yes | QMessageBox::No);
        if(std == QMessageBox::Yes){
            vSys.removeCard(toDel);
            vSys.writeDictionary();

            on_wordTableFilter_textChanged(ui->wordTableFilter->text());

            //del msg
            QString msg;
            msg = tr("Deleted card '%1'").arg(toDel);
            statusBar()->showMessage(msg, 2000);
        }
    }
}

void voxUI::showEditDialog()
{
    QString termStr = vWL->data(ui->wordTableView->selectionModel()->selectedRows(0)[0], Qt::DisplayRole).toString();
    QString defStr = vWL->data(ui->wordTableView->selectionModel()->selectedRows(1)[0], Qt::DisplayRole).toString();
    voxEditDialog vEdit(termStr, defStr, vSys, this);
    vEdit.setModal(true);
    vEdit.exec();
}

void voxUI::on_wordEditButton_clicked()
{
    if(vWL->filterItems){
        showEditDialog();
        on_wordTableFilter_textChanged(ui->wordTableFilter->text());
    }
}

void voxUI::timerChangeAnswerGiven()
{
    voxUI::answerGiven=false;
}
