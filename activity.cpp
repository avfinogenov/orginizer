#include "activity.h"

Activities::Activities(QString buttonTextIn, QString eventNameIn, QWidget* parent) : QObject(parent)
{
//    ("Открыть ветвь", "New branch");
    l21 = new QHBoxLayout();
    eventNameLineEdit = new QLineEdit();
    lastEventDateLineEdit = new QLineEdit();
    setNewEventDate = new QPushButton();
    eventName = eventNameIn;
    buttonText = buttonTextIn;
    lastEventDateLineEdit->setReadOnly(true);
    eventNameLineEdit->setText(eventName);
    setNewEventDate->setText(buttonText);
    l21->addWidget(eventNameLineEdit);
    l21->addWidget(setNewEventDate);
    l21->addWidget(lastEventDateLineEdit);


    connect(eventNameLineEdit, &QLineEdit::textChanged, this, &Activities::updateName);
}
Activities::~Activities()
{

}


QString Activities::getBranchListName()
{
    return branchName;
}
std::list<Branch*>* Activities::getBranches()
{
    return &branches;
}


void Activities::update()
{
//    qDebug() << branches.size();
    int mySize = (int)branches.size();
    int sum = 0;
    foreach (Branch* item, branches)
    {
        sum += item->getDate().daysTo(QDateTime::currentDateTime());
    }
//    qDebug() << sum;
//    qDebug() << mySize;
    lastEventDateLineEdit->setReadOnly(false);
    if (sum > 0 && mySize > 0)
    {
        float tmp = sum / mySize;
//        qDebug() << tmp;
        lastEventDateLineEdit->setText( QString::number(tmp));
//        qDebug() << "3";
        lastEventDateLineEdit->setReadOnly(true);
        if (tmp > 6)
        {
            eventNameLineEdit->setObjectName(problem);
            lastEventDateLineEdit->setObjectName(problem);
            setNewEventDate->setObjectName(problem);



        }
        else if (tmp > 1)
        {
            eventNameLineEdit->setObjectName(warning);
            lastEventDateLineEdit->setObjectName(warning);
            setNewEventDate->setObjectName(warning);
        }
        else
        {
            eventNameLineEdit->setObjectName(normal);
            lastEventDateLineEdit->setObjectName(normal);
            setNewEventDate->setObjectName(normal);
        }
    }
    else
    {
        lastEventDateLineEdit->setText( QString::number(0));
        eventNameLineEdit->setObjectName(normal);
        lastEventDateLineEdit->setObjectName(normal);
        setNewEventDate->setObjectName(normal);
    }


}

void Activities::addBranch(Branch* b)
{
    branches.push_back(b);

}




void Activities::updateName()
{
    eventName = eventNameLineEdit->text();
}



QHBoxLayout* Activities::getLayout()
{
    return l21;
}


QPushButton* Activities::getButton()
{
    return setNewEventDate;
}
QLineEdit* Activities::getDateLineEdit()
{
    return lastEventDateLineEdit;
}
QLineEdit* Activities::getNameLineEdit()
{
    return eventNameLineEdit;
}
void Activities::tmp()
{
    lastEventDate = QDateTime::currentDateTime();
    lastEventDateLineEdit->setText(lastEventDate.toString());

    eventNameLineEdit->setObjectName("changed");
    lastEventDateLineEdit->setObjectName("changed");
    setNewEventDate->setObjectName("changed");
    setNewEventDate->update();
    setNewEventDate->repaint();
    emit doRepaint();

}
void Activities::updateTime(QDateTime currentTime)
{

    checkDate(currentTime);

}
void Activities::setDate(QString date)
{
    lastEventDateLineEdit->setText(date);
    lastEventDate = QDateTime::fromString(date);
}

void Activities::checkDate(QDateTime currentTime)
{
//    QDateTime placed = QDateTime::fromString(lastEventDateLineEdit->text());

//    qDebug() << placed.date().daysTo(currentTime.date());
    if (lastEventDate.date().daysTo(currentTime.date()) > 6)
    {


         eventNameLineEdit->setObjectName(problem);
         lastEventDateLineEdit->setObjectName(problem);
         setNewEventDate->setObjectName(problem);
    }
    else if (lastEventDate.date().daysTo(currentTime.date()) > 1)
    {

        eventNameLineEdit->setObjectName(warning);
        lastEventDateLineEdit->setObjectName(warning);
        setNewEventDate->setObjectName(warning);
    }
    else
    {

        eventNameLineEdit->setObjectName(normal);
        lastEventDateLineEdit->setObjectName(normal);
        setNewEventDate->setObjectName(normal);


    }
}
void Activities::openWindow()
{
    emit windowOpen(this);
}

void Activities::repaint()
{
    l21 = new QHBoxLayout();
    eventNameLineEdit = new QLineEdit();
    lastEventDateLineEdit = new QLineEdit();
    setNewEventDate = new QPushButton();
    lastEventDateLineEdit->setText(lastEventDate.toString());
    eventNameLineEdit->setText(eventName);
    setNewEventDate->setText(buttonText);
    lastEventDateLineEdit->setReadOnly(true);
    l21->addWidget(eventNameLineEdit);
    l21->addWidget(setNewEventDate);
    l21->addWidget(lastEventDateLineEdit);
    checkDate(QDateTime::currentDateTime());
    connect(eventNameLineEdit, &QLineEdit::textChanged, this, &Activities::updateName);
}
QDateTime Activities::getDate()
{
    return lastEventDate;
}


QString Activities::getName()
{
    return eventName;
}
void Activities::setName(QString name)
{
    eventName = name;
}
void Activities::mySetDate(QString dateIn)
{
    lastEventDate = QDateTime::fromString(dateIn);
}
