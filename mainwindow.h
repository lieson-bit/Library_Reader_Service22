#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headers.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QSqlDatabase mydbase;
    QString returnname();
    void connClose(){
        mydbase.close();
        mydbase.removeDatabase(QSqlDatabase::defaultConnection);
    };
    bool connOpen(){
        mydbase = QSqlDatabase::addDatabase("QSQLITE");
        mydbase.setDatabaseName("C:/sqlite3/Usersdatabase/usersdata.db");
        if(!mydbase.open()){
            qDebug()<<("Failed to open database");
            return false;
        }else{
            return true;
        }
    }

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_cancel_login_clicked();

    void on_enter_login_clicked();

    void on_Register_Home_clicked();

    void on__checkBox_Home_clicked();

private:
    Ui::MainWindow *ui;
    //registerdialog *ptrregisterdialog;
     void updateLoginButtonState(int state);

};
#endif // MAINWINDOW_H
