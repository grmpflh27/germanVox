#include "voxEditDialog.h"

voxEditDialog::voxEditDialog(const QString term, const QString def, voxcardSystem& vSys, QWidget* parent)
    : voxCardSys(vSys), origTerm(term), origDef(def)
{
    //vUI = static_cast<voxUI*>(parent);
    termEdit = new QLineEdit(term, this);
    defEdit = new QLineEdit(def, this);
    termEdit->home(true);
    defEdit->home(true);
    saveB = new QPushButton("&save", this);
    cancelB = new QPushButton("&cancel", this);
    //voxSpecialC = new voxSpecialChars(vUI, this);
    layout = new QGridLayout(this);
    setLayout(layout);
    layout->addWidget(new QLabel("Term:",this),0,0);
    layout->addWidget(new QLabel("Definition:",this),1,0);
    layout->addWidget(termEdit,0,1);
    layout->addWidget(defEdit,1,1);
    layout->addWidget(saveB,2,0);
    layout->addWidget(cancelB,2,1);
    //layout->addWidget(voxSpecialC,3,0,1,2);

    connect(saveB,SIGNAL(clicked()),this,SLOT(saveToDict()));
    connect(cancelB,SIGNAL(clicked()),this,SLOT(reject()));
}

void voxEditDialog::saveToDict()
{
    voxCardSys.editCard(voxCard(origDef, origTerm), termEdit->text(), defEdit->text());
    voxCardSys.writeDictionary();
    this->accept();
}
