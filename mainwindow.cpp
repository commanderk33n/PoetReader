#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{

    char host[12] = "172.20.4.30";
    char *host2 = host;

    auto socketWebReader = new SocketWebReader("172.20.4.30", "80");

    auto ss = socketWebReader->GetStream("GET /Quellen/fi/dichter_liste.txt\r\n");

    std::string s;
    while(std::getline(*ss, s)) {
        std::cout << s << std::endl;
    }





    readPoets = new ReadPoets();
    ui->setupUi(this);
    listWidget = new QListWidget(this);
    listWidget->setGeometry(400, 200, 400 , 400);

    count = new QLabel(this);
    count->setGeometry(400,100,50,50);
    count->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    count->setText("Count:\n " +  QString::number(readPoets->countPoets()));
    count->setAlignment(Qt::AlignRight);

    name = new QLabel(this);
    name->setGeometry(10, 80, 100, 20);
    name->setText("NameID:");
    nameID = new QSpinBox(this);
    nameID->setGeometry(10,100,100,50);
    nameBtn = new QPushButton(this);
    nameBtn->setGeometry(10, 155, 100, 35);
    nameBtn->setText("getName()");

    birthday = new QLabel(this);
    birthday->setGeometry(130, 80, 100, 20);
    birthday->setText("BrithdayID:");
    birthdayID = new QSpinBox(this);
    birthdayID->setGeometry(130, 100, 100, 50);
    birthdayBtn = new QPushButton(this);
    birthdayBtn->setGeometry(130, 155, 100, 35);
    birthdayBtn->setText("getBirthday()");

    result = new QLabel(this);
    result->setGeometry(60, 200, 100, 35);
    result->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    result->setAlignment(Qt::AlignRight);

    nameBtn->connect(nameBtn, SIGNAL( clicked() ),this, SLOT( labelTextName() ));
    birthdayBtn->connect(birthdayBtn, SIGNAL(clicked()), this, SLOT(labelTextBirthday()));

    int count = readPoets->countPoets();

    for(int i = 0; i < count; i++) {
        QString qstr = readPoets->giveName(i) + " " + readPoets->giveBirthday(i);
        //qDebug() << qstr;
        new QListWidgetItem(qstr, listWidget);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::labelTextName()
{
    result->setText(readPoets->giveName(nameID->value()));
}

void MainWindow::labelTextBirthday()
{
    result->setText(readPoets->giveBirthday(birthdayID->value()));
}

