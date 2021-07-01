#ifndef READPOETS_H
#define READPOETS_H

#include <QString>
#include <QStringList>


class ReadPoets
{
public:
    ReadPoets();

    QStringList surenames;
    QStringList birthdates;

    QString giveName(int n);
    QString giveBirthday(int n);
    int countPoets();

    void blabla(int x, int y);

};

#endif // READPOETS_H
