#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include <QSpinBox>
#include <QPushButton>
#include <readpoets.h>
#include <socketwebreader.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SocketWebReader *socketWebReader;

    ReadPoets *readPoets;
    QListWidget *listWidget;
    QLabel *count;
    QLabel *result;
    QLabel *name;
    QLabel *birthday;
    QSpinBox *nameID;
    QSpinBox *birthdayID;
    QPushButton *nameBtn;
    QPushButton *birthdayBtn;


private:
    Ui::MainWindow *ui;

public slots:
    void labelTextName();
    void labelTextBirthday();

};
#endif // MAINWINDOW_H
