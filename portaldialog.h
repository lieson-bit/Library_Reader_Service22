#ifndef PORTALDIALOG_H
#define PORTALDIALOG_H

#include "headers.h"
#include "book_data.h"

namespace Ui {
class portaldialog;
}

class portaldialog : public QDialog
{
    Q_OBJECT

public:
    explicit portaldialog(QWidget *parent = nullptr);
    ~portaldialog();
    void func(QString ,QString);
    void displayNextP();
    void startPictureT();
    void databasetofile();
    Book_data * fillform();
    void showCost(Book_data *value);

private slots:
    void on_minimize_clicked();

    void on_message_button_clicked();

    void on_search_button_clicked();

    void on_buy_book_clicked();

    void on_exit_clicked();

private:
    Ui::portaldialog *ui;
    bool readCredentialsFromFile(QString &username, QString &password);
    void loadMess();
};

#endif // PORTALDIALOG_H
