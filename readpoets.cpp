#include "readpoets.h"


#include <QDebug>

using namespace std;

ReadPoets::ReadPoets()
{
    string str;

    QString surename;
    QString birthdate;

    auto socketWebReader = new SocketWebReader("172.20.4.30", "80");

    auto ss = socketWebReader->GetStream("GET /Quellen/fi/dichter_liste.txt\r\n");



    std::string s;
    int lineIndex = 0;
    while(std::getline(*ss, s)) {
        lineIndex++;
        if(lineIndex < 10)
            continue;

       // std::cout << s << std::endl;

        QString qstr = QString::fromStdString(s).trimmed();
        qDebug() << qstr;

        surename = qstr.split(" ").at(0);
        surenames.append(surename);

        int pos = qstr.lastIndexOf(QChar('('));

        birthdate = qstr.mid(pos).remove('(').remove(')');

        birthdates.append(birthdate);
        qDebug() << birthdate;

    }


//    ifstream file("C:\\Users\\defin\\Downloads\\dichter_liste.txt");

//    while (getline (file, str)) {
//        QString qstr = QString::fromStdString(str);

//        surename = qstr.split(" ").at(0);
//        surenames.append(surename);
//        //qDebug() << surename;

//        int pos = qstr.lastIndexOf(QChar('('));

//        birthdate = qstr.mid(pos).remove('(').remove(')');
//        birthdates.append(birthdate);
//        //qDebug() << birthdate;
//    }

//    file.close();
}

QString ReadPoets::giveBirthday(int n) {
    return birthdates.at(n);
}

QString ReadPoets::giveName(int n) {
    return surenames.at(n);
}

int ReadPoets::countPoets() {
    return surenames.size();
}

void ReadPoets::blabla(int x, int y)
{
    qDebug() << "funktioniert";
}

