#include "mainwindow2.h"
#include "ui_mainwindow2.h"

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    currentTime = QDateTime::currentDateTime();
    ui->labelCurrentDateAct->setText(currentTime.toString());
    ui->pushButtonBranch->hide();
    ui->pushButtonBack->hide();
    readNameListFromDisc();
    this->setStyleSheet("#warning { background-color: yellow; } #problem { background-color: red !important; } #normal { background-color: green; } #changed { background-color: green !important;}");
}

MainWindow2::~MainWindow2()
{
    saveNameListToDisc();

    foreach (Activities* item, activities)
    {
        writeBranchToDisc(item);
    }


    delete ui;
}

void MainWindow2::onActivityCreate(Activities* act)
{
    connect(act->getButton(), &QPushButton::clicked, act, &Activities::openWindow);
     connect(act, &Activities::windowOpen, this, &MainWindow2::editActivity);
}
void MainWindow2::editActivity(Activities* input)
{

    activeActivity = input;

    // переделать интерфейс сверху
    switchToBranch(input->getName());
    // поменять лайаут в боди
    clearMainLayout();
    paintBrunch(input->getBranches());


}
void MainWindow2::switchToBranch(QString branchName)
{
    ui->pushButtonAct->hide();
    ui->mainLable->setText(QString("Ветвь :").append(branchName));
    ui->pushButtonBranch->show();
    ui->pushButtonBack->show();
}


void MainWindow2::switchToMain()
{
    ui->pushButtonAct->show();

    ui->pushButtonBranch->hide();
    ui->pushButtonBack->hide();
}


void MainWindow2::on_pushButtonAct_clicked()
{
    Activities* tmp = new Activities("Открыть ветвь", "New branch");
    onActivityCreate(tmp);
    activities.push_back(tmp);
    ui->activityLayout->addLayout(activities.back()->getLayout());
}



void MainWindow2::changeLayout(QVBoxLayout* current, QVBoxLayout* replacement)
{
    QList<QWidget*> currentWidgetList = current->findChildren<QWidget*>();

    foreach (QWidget* item, currentWidgetList )
    {
        item->hide();
    }

    QList<QWidget*> replacementWidgetList = replacement->findChildren<QWidget*>();

    foreach (QWidget* item, replacementWidgetList )
    {
        item->show();
    }


}



void MainWindow2::clearMainLayout()
{
    QList<QVBoxLayout*> currentLayoutList = ui->activityLayout->findChildren<QVBoxLayout*>();
    if (currentLayoutList.size() > 0)
    {

        foreach (QVBoxLayout* item2, currentLayoutList)
        {
            QList<QHBoxLayout*> tmpLayoutList = item2->findChildren<QHBoxLayout*>();
            if (tmpLayoutList.size() > 0)
            {
                foreach (QHBoxLayout* item3, tmpLayoutList)
                {
                    while(item3->count())
                    {
                        QLayoutItem * item = item3->itemAt(0);
                        if(item)
                        {
                            item3->removeItem( item );
                            QWidget* widget = item->widget();
                            if(widget)
                            {
                                item3->removeWidget(widget);
                                delete widget;
                            }
                            delete item;
                        }
                    }

                    delete item3;
                }
            }


            while(item2->count())
            {
                QLayoutItem * item = item2->itemAt(0);
                if(item)
                {
                    item2->removeItem( item );
                    QWidget* widget = item->widget();
                    if(widget)
                    {
                        item2->removeWidget(widget);
                        delete widget;
                    }
                    delete item;
                }
            }

            delete item2;
        }
    }
    else
    {
        QList<QHBoxLayout*> currentLayoutList = ui->activityLayout->findChildren<QHBoxLayout*>();
        if (currentLayoutList.size() > 0)
        {
            foreach (QHBoxLayout* item3, currentLayoutList)
            {
                while(item3->count())
                {
                    QLayoutItem * item = item3->itemAt(0);
                    if(item)
                    {
                        item3->removeItem( item );
                        QWidget* widget = item->widget();
                        if(widget)
                        {
                            item3->removeWidget(widget);
                            delete widget;
                        }
                        delete item;
                    }
                }

                delete item3;
            }
        }
    }
}


void MainWindow2::paintActivities()
{
    foreach (Activities* item, activities)
    {
        item->repaint();
        onActivityCreate(item);
        item->update();
        ui->activityLayout->addLayout(item->getLayout());

    }
}



void MainWindow2::paintBrunch(std::list<Branch*>* inputBranch)
{
    foreach (Branch* item, *inputBranch)
    {
        item->repaint();

        on_row_create(item);

        ui->activityLayout->addLayout(item->getLayout());
        item->checkDate(QDateTime::currentDateTime());

    }
    currentBranch = inputBranch;
    myRepaint();
}



void MainWindow2::on_row_create(Branch* r)
{
    connect(r->getButton(), &QPushButton::clicked, r, &Branch::tmp);
     connect(r, &Branch::doRepaint, this, &MainWindow2::myRepaint);
//    connect(r.getButton(), &QPushButton::clicked, this, &MainWindow::forUpdate);
//    connect(this, &MainWindow::updateTime, &r, &Row::updateTime);
}



void MainWindow2::myRepaint()
{

    this->update();
    this->repaint();
    this->setStyleSheet("#warning { background-color: yellow; } #problem { background-color: red !important; } #normal { background-color: green; } #changed { background-color: green !important;}");
    QApplication::processEvents();
}

void MainWindow2::on_pushButtonBranch_clicked()
{
    Branch* tmp = new Branch("Выполненно", "Новая активность");
    on_row_create(tmp);
    currentBranch->push_back(tmp);
    ui->activityLayout->addLayout(currentBranch->back()->getLayout());
}


void MainWindow2::on_pushButtonBack_clicked()
{
    clearMainLayout();
    currentBranch = nullptr;
    ui->mainLable->setText("Список ветвей");

    paintActivities();
    activeActivity->update();
    switchToMain();
}



void MainWindow2::saveNameListToDisc()
{
    std::ofstream out;
    out.open(QString("name_list").append(FILE_EXTENSION).toStdString(), std::ios::out | std::ios::binary);

    if (out.is_open())
    {
        uint16_t globalSize = (uint16_t)activities.size();
        out.write((char*)&globalSize, sizeof(globalSize));
        foreach(Activities* item, activities)
        {
            QString name = item->getName();
            uint16_t size = name.length();
            out.write((char*)&size, sizeof(size));
            for (int i = 0; i < size; ++i)
            {
                QChar c = name[i];
                out.write((char*)&c, sizeof(c));
            }



        }
    }

}
void MainWindow2::writeBranchToDisc(Activities* input)
{
    std::ofstream out;
    out.open(CreateValidWebFileName(input->getName()).append(FILE_EXTENSION).toStdString(), std::ios::out | std::ios::binary);
    if (out.is_open())
    {
        std::list<Branch*> tmp = *input->getBranches();
        int64_t size1 = tmp.size();
//        qDebug() << size1;
        out.write((char*)&size1, sizeof(int64_t));

        for (int i = 0; i < size1; ++i)
        {
//            qDebug() << i;

            Branch* tmp2 = tmp.front();
            tmp.pop_front();
            QString name = tmp2->getName();
            QString date = tmp2->getDate().toString();
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


void MainWindow2::readBranchfromDisc(Activities* output)
{
    std::ifstream in;
    in.open(CreateValidWebFileName(output->getName()).append(FILE_EXTENSION).toStdString(), std::ios::in | std::ios::binary);

    if (in.is_open())
    {


        int64_t size = 0;
        in.read((char*)&size, sizeof(int64_t));
        for (int i = 0; i < size; ++i)
        {
            Branch* r = new Branch("Выполненно", "Новая активность");
            int64_t nameSize = 0;
            int64_t dateSize = 0;
            in.read((char*)&nameSize, sizeof(int64_t));
            QChar tmp;
            QString name;
            QString date;
            for (int64_t j = 0; j < nameSize; ++j)
            {
                in.read((char*)&tmp, sizeof(QChar));

                name += tmp;
            }

            in.read((char*)&dateSize, sizeof(int64_t));

            for (int64_t j = 0; j < dateSize; ++j)
            {
                in.read((char*)&tmp, sizeof(QChar));
                date += tmp;
            }


//            qDebug() << "here";
            r->setName(name);
            r->setDate(date);
//            on_row_create(*r);
//            r->checkDate(currentTime);
            output->addBranch(r);




        }
        in.close();
    }

}



void MainWindow2::readNameListFromDisc()
{
    std::ifstream in;
    in.open(QString("name_list").append(FILE_EXTENSION).toStdString(), std::ios::out | std::ios::binary);

    if (in.is_open())
    {
        uint16_t globalSize = 0;

        in.read((char*)&globalSize, sizeof(globalSize));
        for (int i = 0; i < globalSize; ++i)
        {
            QString name ;
            uint16_t size ;

            in.read((char*)&size, sizeof(size));
            for (int i = 0; i < size; ++i)
            {
                QChar c;

                in.read((char*)&c, sizeof(c));
                name += c;
            }
            Activities* tmp = new Activities("Открыть ветвь", "New branch");
            tmp->setName(name);
            tmp->getNameLineEdit()->setText(name);
            readBranchfromDisc(tmp);
            onActivityCreate(tmp);
            tmp->update();
            activities.push_back(tmp);
            ui->activityLayout->addLayout(activities.back()->getLayout());


        }
    }
}


QString MainWindow2::CreateValidWebFileName(QString str)
{
    QString fn;
    int i, rU, rL;
    QString validChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-_,.()[]{}<>~!@#$%^&*+=?";
    QString rusUpper = QApplication::translate("pCommon","АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЫЭЮЯ");
    QString rusLower = QApplication::translate("pCommon","абвгдеёжзийклмнопрстуфхцчшщыэюя");
    QStringList latUpper, latLower;
    latUpper <<"A"<<"B"<<"V"<<"G"<<"D"<<"E"<<"Jo"<<"Zh"<<"Z"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"
        <<"O"<<"P"<<"R"<<"S"<<"T"<<"U"<<"F"<<"H"<<"C"<<"Ch"<<"Sh"<<"Sh"<<"I"<<"E"<<"Ju"<<"Ja";
    latLower <<"a"<<"b"<<"v"<<"g"<<"d"<<"e"<<"jo"<<"zh"<<"z"<<"i"<<"j"<<"k"<<"l"<<"m"<<"n"
        <<"o"<<"p"<<"r"<<"s"<<"t"<<"u"<<"f"<<"h"<<"c"<<"ch"<<"sh"<<"sh"<<"i"<<"e"<<"ju"<<"ja";
    for (i=0; i < str.size(); ++i){
        if ( validChars.contains(str[i]) ){
            fn = fn + str[i];
        }else if (str[i] == ' '){  //replace spaces
            fn = fn + "_";
        }else{
            rU = rusUpper.indexOf(str[i]);
            rL = rusLower.indexOf(str[i]);
            if (rU > 0)         fn = fn + latUpper[rU];
            else if (rL > 0)   fn = fn + latLower[rL];
        }
    }
    if (fn.isEmpty() ) fn = "file";
    return fn;
}
