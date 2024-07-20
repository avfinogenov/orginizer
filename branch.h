#ifndef BRANCH_H
#define BRANCH_H
#include "QDateTime"
#include "QString"
#include "QMainWindow"
#include "ui_mainwindow.h"
#include <QObject>
#include <QLineEdit>
#include <QListWidget>
#include <QDebug>
#include <exception>

class Branch : public QObject
{
Q_OBJECT
public:
    Branch(QString buttonText, QString eventNameIn, QWidget *parent = nullptr);

    ~Branch();
    QVBoxLayout* getLayout();

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
    void windowOpen(Branch* self);

protected:

    QVBoxLayout* l21;
    QLineEdit* eventNameLineEdit;
    QLineEdit* lastEventDateLineEdit;
    QPushButton* setNewEventDate;


    QHBoxLayout* tmpl ;
    QVBoxLayout* tmpl2 ;

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

#endif // BRANCH_H
