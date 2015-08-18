#include "voxspecialchars.h"
#include "ui_voxspecialchars.h"

voxSpecialChars::voxSpecialChars(voxUI* vUI, QWidget *parent) :
    vUI(vUI), QWidget(parent),
    ui(new Ui::voxSpecialChars)
{
    ui->setupUi(this);
    qDebug() << "dict" << vUI->vSys.dict.size();
}

voxSpecialChars::~voxSpecialChars()
{
    delete ui;
}

void voxSpecialChars::on_specialCharArrow_clicked()
{
    //!! todo: adapt to other languages
//    qDebug() << vUI.getCurSpecialList();
//    //(vUI.getCurSpecialList() == &voxConst::umGermanLC) ? vUI.getCurSpecialList() = &voxConst::umGermanUC : vUI.getCurSpecialList() = &voxConst::umGermanLC ;
//    showSpecialChars();
}

void voxSpecialChars::specialButtonClicked()
{
//    QPushButton *button = (QPushButton *)sender();
//    QLineEdit* curEdit = voxUI.getCurLineEdit();
//    curEdit->setText(curEdit->text() + button->text());
//    curEdit->setFocus();
}

void voxSpecialChars::showSpecialChars()
{
//    QRegExp rx("specialChar_(\\d+)");
//    QList<QPushButton*> allPushButtons = findChildren<QPushButton*>();
//    QListIterator<QPushButton*> pBIter(allPushButtons);

//    while(pBIter.hasNext()){
//        QPushButton* next = pBIter.next();
//        if(next->objectName().contains(rx)){
//            if(rx.cap(1).toInt() < vUI.getCurSpecialList()->size()){
//                next->setText(vUI.getCurSpecialList()->at(rx.cap(1).toInt()));
//            }
//            else{
//                next->hide();
//            }
//        }
//    }

}
