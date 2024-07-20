#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "QDateTime"
#include "QString"
#include "QMainWindow"
#include "ui_mainwindow.h"
#include <QObject>
#include <QLineEdit>
#include <QDebug>
#include <exception>

#include "branch.h"

class Activities : public QObject
{
Q_OBJECT

public:
    Activities(QString buttonText, QString eventNameIn, QWidget *parent = nullptr);
    ~Activities();
    QString getBranchListName();
    std::list<Branch*>* getBranches();
    void update();
    void addBranch(Branch* b);

private:
    QString branchName = "new branch";
    std::list<Branch*> branches;

public:
    QHBoxLayout* getLayout();

    QPushButton* getButton();
    QLineEdit* getNameLineEdit();
    QLineEdit* getDateLineEdit();
    void checkDate(QDateTime currentTime);
    void setDate(QString date);
    void repaint();
    QDateTime getDate();
    QString getName();
    void setName(QString name);
    void mySetDate(QString dateIn);
public slots:
    void openWindow();

signals:
    void windowOpen(Activities* self);

protected:

    QHBoxLayout* l21;
    QLineEdit* eventNameLineEdit;
    QLineEdit* lastEventDateLineEdit;
    QPushButton* setNewEventDate;
    QString eventName;
    QDateTime lastEventDate;
    const QString warning = "warning";
    const QString problem = "problem";
    const QString normal = "normal";
    QString buttonText;
public slots:
    void tmp();
    void updateTime(QDateTime currentTime);
    void updateName();

signals:
    void doRepaint();





};

#endif // ACTIVITY_H

