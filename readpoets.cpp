#include "readpoets.h"


#include <QDebug>

using namespace std;

ReadPoets::ReadPoets()
{
    string str;

    QString surename;
    QString birthdate;

    ifstream file("C:\\Users\\defin\\Downloads\\dichter_liste.txt");

    while (getline (file, str)) {
        QString qstr = QString::fromStdString(str);

        surename = qstr.split(" ").at(0);
        surenames.append(surename);
        //qDebug() << surename;

        int pos = qstr.lastIndexOf(QChar('('));

        birthdate = qstr.mid(pos).remove('(').remove(')');
        birthdates.append(birthdate);
        //qDebug() << birthdate;
    }

    file.close();
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

