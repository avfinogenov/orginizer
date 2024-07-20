#include "branch.h"

Branch::Branch(QString buttonTextIn, QString eventNameIn, QWidget* parent) : QObject(parent)
{
    qDebug() << "1";
    eventName = eventNameIn;
    buttonText = buttonTextIn;


    tmpl = new QHBoxLayout();
    l21 = new QVBoxLayout();

    eventNameLineEdit = new QLineEdit();
    lastEventDateLineEdit = new QLineEdit();
    setNewEventDate = new QPushButton();
    lastEventDateLineEdit->setText(lastEventDate.toString());
    eventNameLineEdit->setText(eventName);
    setNewEventDate->setText(buttonText);
    lastEventDateLineEdit->setReadOnly(true);
//    lastEventDateLineEdit->setReadOnly(true);
    tmpl->addWidget(eventNameLineEdit);
    tmpl->addWidget(setNewEventDate);
    tmpl->addWidget(lastEventDateLineEdit);

    l21->addLayout(tmpl);

    QListWidget* tmp = new QListWidget();

    tmp->addItem("1");
    tmp->addItem("2");
    tmp->addItem("3");
    l21->addWidget(tmp);

    checkDate(QDateTime::currentDateTime());
    connect(eventNameLineEdit, &QLineEdit::textChanged, this, &Branch::updateName);
    qDebug() << "2";
}
Branch::~Branch()
{

}


void Branch::updateName()
{
    eventName = eventNameLineEdit->text();
}



QVBoxLayout* Branch::getLayout()
{
    return l21;
}


QPushButton* Branch::getButton()
{
    return setNewEventDate;
}
QLineEdit* Branch::getDateLineEdit()
{
    return lastEventDateLineEdit;
}
QLineEdit* Branch::getNameLineEdit()
{
    return eventNameLineEdit;
}
void Branch::tmp()
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
void Branch::updateTime(QDateTime currentTime)
{

    checkDate(currentTime);

}
void Branch::setDate(QString date)
{
    lastEventDateLineEdit->setText(date);
    lastEventDate = QDateTime::fromString(date);
}

void Branch::checkDate(QDateTime currentTime)
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
void Branch::openWindow()
{
    emit windowOpen(this);
}

void Branch::repaint()
{
    tmpl = new QHBoxLayout();
    l21 = new QVBoxLayout();

    eventNameLineEdit = new QLineEdit();
    lastEventDateLineEdit = new QLineEdit();
    setNewEventDate = new QPushButton();
    lastEventDateLineEdit->setText(lastEventDate.toString());
    eventNameLineEdit->setText(eventName);
    setNewEventDate->setText(buttonText);
    lastEventDateLineEdit->setReadOnly(true);
//    lastEventDateLineEdit->setReadOnly(true);
    tmpl->addWidget(eventNameLineEdit);
    tmpl->addWidget(setNewEventDate);
    tmpl->addWidget(lastEventDateLineEdit);

    l21->addLayout(tmpl);

    QListWidget* tmp = new QListWidget();

    tmp->addItem("1");
    tmp->addItem("2");
    tmp->addItem("3");
    l21->addWidget(tmp);

    checkDate(QDateTime::currentDateTime());
    connect(eventNameLineEdit, &QLineEdit::textChanged, this, &Branch::updateName);
}
QDateTime Branch::getDate()
{
    return lastEventDate;
}


QString Branch::getName()
{
    return eventName;
}
void Branch::setName(QString name)
{
    eventName = name;
}
void Branch::mySetDate(QString dateIn)
{
    lastEventDate = QDateTime::fromString(dateIn);
}
