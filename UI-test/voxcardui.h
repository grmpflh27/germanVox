#ifndef VOXCARDUI_H
#define VOXCARDUI_H

#include <QMainWindow>

namespace Ui {
class voxCardUI;
}

class voxCardUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit voxCardUI(QWidget *parent = 0);
    ~voxCardUI();

private:
    Ui::voxCardUI *ui;
};

#endif // VOXCARDUI_H
