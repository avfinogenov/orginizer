#ifndef ACTIVITYWINDOW2_H
#define ACTIVITYWINDOW2_H

#include "list"
#include "fstream"

#include <QMainWindow>
#include "QDateTime"
#include "QString"
#include "QDebug"

#include "branch.h"
#include "activity.h"

namespace Ui {
class ActivityWindow2;
}

class ActivityWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit ActivityWindow2(QString rowListName, QWidget *parent = nullptr);
    ~ActivityWindow2();

signals:
    void updateTime(QDateTime currentTime);

public slots:
    void forUpdate();

private slots:
    void on_pushButton_clicked();
    void myRepaint();
//    void on_setDate();

private:

    void on_row_create(Branch& r);
    QDateTime currentTime;
    void writeToDisc();
    void readFromDisc();
    int warning = 1;
    int problem = 6;
    std::list<Branch*> rows;
    QString m_rowListName;
    const QString FILE_EXTENSION = ".bin";
    QString addDate();
private:
    Ui::ActivityWindow2 *ui;
};

#endif // ACTIVITYWINDOW2_H
