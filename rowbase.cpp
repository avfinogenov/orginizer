#include "rowbase.h"

RowBase::RowBase(QString buttonTextIn, QString eventNameIn, QWidget* parent) : QObject(parent)
{

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


    connect(eventNameLineEdit, &QLineEdit::textChanged, this, &RowBase::updateName);

}
RowBase::~RowBase()
{

}

void RowBase::updateName()
{
    eventName = eventNameLineEdit->text();
}



QHBoxLayout* RowBase::getLayout()
{
    return l21;
}


QPushButton* RowBase::getButton()
{
    return setNewEventDate;
}
QLineEdit* RowBase::getDateLineEdit()
{
    return lastEventDateLineEdit;
}
QLineEdit* RowBase::getNameLineEdit()
{
    return eventNameLineEdit;
}
void RowBase::tmp()
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
void RowBase::updateTime(QDateTime currentTime)
{

    checkDate(currentTime);

}
void RowBase::setDate(QString date)
{
    lastEventDateLineEdit->setText(date);
    lastEventDate = QDateTime::fromString(date);
}

void RowBase::checkDate(QDateTime currentTime)
{
//    QDateTime placed = QDateTime::fromString(lastEventDateLineEdit->text());

//    qDebug() << placed.date().daysTo(currentTime.date());
    if (lastEventDate.date().daysTo(currentTime.date()) > 1)
    {
         eventNameLineEdit->setObjectName(warning);
         lastEventDateLineEdit->setObjectName(warning);
         setNewEventDate->setObjectName(warning);
    }
    else if (lastEventDate.date().daysTo(currentTime.date()) > 6)
    {

        eventNameLineEdit->setObjectName(problem);
        lastEventDateLineEdit->setObjectName(problem);
        setNewEventDate->setObjectName(problem);
    }
    else
    {

        eventNameLineEdit->setObjectName(normal);
        lastEventDateLineEdit->setObjectName(normal);
        setNewEventDate->setObjectName(normal);


    }
}
void RowBase::openWindow()
{
    emit windowOpen(this);
}

void RowBase::repaint()
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
    connect(eventNameLineEdit, &QLineEdit::textChanged, this, &RowBase::updateName);
}
QDateTime RowBase::getDate()
{
    return lastEventDate;
}


QString RowBase::getName()
{
    return eventName;
}
void RowBase::setName(QString name)
{
    eventName = name;
}
void RowBase::mySetDate(QString dateIn)
{
    lastEventDate = QDateTime::fromString(dateIn);
}
