#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QMessageBox>
#include <QTimer>
#include "voxcardsystem.h"
#include "voxcardgame.h"
#include "voxwordlistmodel.h"


namespace Ui {
class voxUI;
}

class voxUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit voxUI(QWidget *parent = 0);
    ~voxUI();

    voxcardSystem vSys;

    const QList<QString>* getCurSpecialList() const;
    QLineEdit* getCurLineEdit() const;
signals:
    void specialClicked(int);


private slots:
    void on_MainNewCard_clicked();
    void on_addWindowContinueButton_clicked();
    void on_saveAndAddMoreButton_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_studyButton_clicked();
    void on_goButton_clicked();
    void on_practBackToMainB_clicked();
    void on_wordListBackToMainB_clicked();
    void on_dictBackToMainB_clicked();
    void on_practiceRB_clicked();
    void on_randomRB_clicked();
    void on_practiceYesB_clicked();
    void on_practiceNoB_clicked();
    
    //special chars
    void on_specialCharArrow_clicked();
    void specialButtonClicked();

    void on_wordTableFilter_textChanged(const QString &arg1);
    void on_wordTableDelete_clicked();
    void showEditDialog();
    void on_wordEditButton_clicked();
    void timerChangeAnswerGiven();

protected:
    void keyPressEvent(QKeyEvent* e);
    bool eventFilter(QObject *object, QEvent *e);

private:
    Ui::voxUI *ui;

    voxCardGame* vGame;

    enum Windows{mainW, addCardW, dictionaryW, practiceW, wordlistW} window;
    enum Modes{practiceM, randomM, dictionaryM, wordlistM} mode;

    voxWordListModel* vWL;

    void saveCards();
    void clearAllAddLineEdits();
    void updateUI();
    void connectFct();

    const QList<QString>* curSpecialList;
    QLineEdit* curLineEdit;
    static bool answerGiven;

    void setSpecialCharList();
    void showSpecialChars();

    void showNextTerm(voxCardGame *vGame);
    void updateWordTableView();
    void closeEvent(QCloseEvent *);

};

#endif // MAINWINDOW_H
