#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <list>
#include <fstream>

#include <QMainWindow>
#include <QApplication>

#include "branch.h"
#include "activity.h"
#include "activitywindow2.h"

namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = nullptr);
    ~MainWindow2();

public slots:
    void editActivity(Activities* input);


private:


private slots:


    void on_pushButtonAct_clicked();

//    void on_pushButton_clicked();

//    void on_pushButton_4_clicked();

    void myRepaint();
//    void createSubBrunch();


    void on_pushButtonBranch_clicked();

    void on_pushButtonBack_clicked();

private:

    Ui::MainWindow2 *ui;
    const QString FILE_EXTENSION = ".bin";
    void onActivityCreate(Activities* r);
    QVector<Activities*> activities;
    ActivityWindow2* actW = nullptr;
    void switchToMain();
    void switchToBranch(QString branchName);
    void changeLayout(QVBoxLayout* current, QVBoxLayout* replacement);
    QDateTime currentTime;
    void clearMainLayout();
    void paintActivities();
    void paintBrunch(std::list<Branch*>* inputBranch);
    void on_row_create(Branch* r);
    std::list<Branch*>* currentBranch = nullptr;
    Activities* activeActivity = nullptr;

    void saveNameListToDisc();
    void writeBranchToDisc(Activities* input);
    void readBranchfromDisc(Activities* output);
    void readNameListFromDisc();
    QString CreateValidWebFileName(QString str);

};

#endif // MAINWINDOW2_H
