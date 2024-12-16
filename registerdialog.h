#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include "headers.h"

namespace Ui {
class registerdialog;
}

class registerdialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerdialog(QWidget *parent = nullptr);
    ~registerdialog();
    void Show();
    void upload();
    void cleanScreen();


private slots:
    void on_enter_register_clicked();

    void on_exit_regi_clicked();

private:
    Ui::registerdialog *ui;
    std::string generateString();
    QSqlDatabase mydb;
};

#endif // REGISTERDIALOG_H
