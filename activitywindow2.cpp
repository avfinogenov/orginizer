#include "activitywindow2.h"
#include "ui_activitywindow2.h"

ActivityWindow2::ActivityWindow2(QString rowListName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivityWindow2)
{
    ui->setupUi(this);
    m_rowListName = rowListName;
    currentTime = QDateTime::currentDateTime();
    ui->labelCurrentDate->setText(currentTime.toString());
    readFromDisc();


    this->setStyleSheet("#warning { background-color: yellow; } #problem { background-color: red; } #normal { background-color: green; } #changed { background-color: green !important;}");

}







ActivityWindow2::~ActivityWindow2()
{

    writeToDisc();
    delete ui;
}


void ActivityWindow2::on_pushButton_clicked()
{
//    Branch* tmp = new Branch();
//    on_row_create(*tmp);
//    rows.push_back(tmp);
//    ui->l1->addLayout(rows.back()->getLayout());


}

QString ActivityWindow2::addDate()
{
    QDateTime current = QDateTime::currentDateTime();
    return current.toString();
}


void ActivityWindow2::on_row_create(Branch& r)
{
    connect(r.getButton(), &QPushButton::clicked, &r, &Branch::tmp);
     connect(&r, &Branch::doRepaint, this, &ActivityWindow2::myRepaint);
//    connect(r.getButton(), &QPushButton::clicked, this, &MainWindow::forUpdate);
//    connect(this, &MainWindow::updateTime, &r, &Row::updateTime);
}



void ActivityWindow2::writeToDisc()
{
    std::ofstream out;
    out.open(m_rowListName.append(FILE_EXTENSION).toStdString(), std::ios::out | std::ios::binary);
    if (out.is_open())
    {

        int64_t size1 = rows.size();
//        qDebug() << size1;
        out.write((char*)&size1, sizeof(int64_t));

        for (int i = 0; i < size1; ++i)
        {
//            qDebug() << i;
            Branch* tmp = rows.front();
            rows.pop_front();
            QString name = tmp->getNameLineEdit()->text();
            QString date = tmp->getDateLineEdit()->text();
            int64_t nameSize = (int64_t)name.length();
            int64_t dateSize = (int64_t)date.length();
//            qDebug() <<nameSize;
//            qDebug() <<dateSize;
            out.write((char*)&nameSize, sizeof(int64_t));
            for (int j = 0; j < nameSize; ++j)
            {
                QChar tmp = name[j];
                out.write((char*)&tmp, sizeof(QChar));
            }

            out.write((char*)&dateSize, sizeof(int64_t));
            for (int j = 0; j < dateSize; ++j)
            {
                QChar tmp = date[j];
                out.write((char*)&tmp, sizeof(QChar));
            }



        }

    out.close();
    }

}
void ActivityWindow2::readFromDisc()
{
//    std::ifstream in;
//    in.open(m_rowListName.append(FILE_EXTENSION).toStdString(), std::ios::in | std::ios::binary);

//    if (in.is_open())
//    {


//        int64_t size = 0;
//        in.read((char*)&size, sizeof(int64_t));
//        for (int i = 0; i < size; ++i)
//        {
//            Branch* r = new Branch();
//            int64_t nameSize = 0;
//            int64_t dateSize = 0;
//            in.read((char*)&nameSize, sizeof(int64_t));
//            QChar tmp;
//            QString name;
//            QString date;
//            for (int64_t j = 0; j < nameSize; ++j)
//            {
//                in.read((char*)&tmp, sizeof(QChar));

//                name += tmp;
//            }

//            in.read((char*)&dateSize, sizeof(int64_t));

//            for (int64_t j = 0; j < dateSize; ++j)
//            {
//                in.read((char*)&tmp, sizeof(QChar));
//                date += tmp;
//            }


////            qDebug() << "here";
//            r->getNameLineEdit()->setText(name);
//            r->getDateLineEdit()->setText(date);
//            on_row_create(*r);
//            r->checkDate(currentTime);
//            rows.push_back(r);


//            ui->l1->addLayout(rows.back()->getLayout());

//        }
//        in.close();
//    }

}

void ActivityWindow2::forUpdate()
{
    emit updateTime(currentTime);



}

void ActivityWindow2::myRepaint()
{

    this->update();
    this->repaint();
    this->setStyleSheet("#warning { background-color: yellow; } #problem { background-color: red; } #normal { background-color: green; } #changed { background-color: green !important;}");
    QApplication::processEvents();
}
