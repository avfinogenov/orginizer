#ifndef ROWBASE_H
#define ROWBASE_H

#include "QDateTime"
#include "QString"
#include "QMainWindow"
#include "ui_mainwindow.h"
#include <QObject>
#include <QLineEdit>
#include <QDebug>
#include <exception>

class RowBase : public QObject
{
Q_OBJECT
public:
    RowBase(QString buttonText, QString eventNameIn, QWidget *parent = nullptr);
    ~RowBase();
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
    void windowOpen(RowBase* self);

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

#endif // ROWBASE_H
