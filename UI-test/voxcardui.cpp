#include "voxcardui.h"
#include "ui_voxcardui.h"

voxCardUI::voxCardUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::voxCardUI)
{
    ui->setupUi(this);
}

voxCardUI::~voxCardUI()
{
    delete ui;
}
