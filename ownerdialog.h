#ifndef OWNERDIALOG_H
#define OWNERDIALOG_H

#include "headers.h"

struct NewNode;
struct Node;
class HashTable;
struct HashNode;
struct Datatype;

namespace Ui {
class ownerDialog;
}

class ownerDialog : public QDialog
{
    Q_OBJECT

public:

    std::string checker;//global variable to check the status of the combobox on functionalities
    void disableButton(QPushButton* button);
    void clear_inputdata();
    void loadFromDatabase();
    NewNode createNewNode();
    void uploadDatatypeFromFile(const std::string& fileName, std::vector<Datatype>& data, QListWidget* listWidget);
    Node* Root = nullptr;
    void displayNextPicture();
    void startPictureTimer();

    explicit ownerDialog(QWidget *parent = nullptr);
    ~ownerDialog();


private slots:

    void on_exit_clicked();

    QString on_functions_comboBox_currentTextChanged(const QString &arg1);

    void on_users_data_button_clicked();

    void on_clear_table_view_clicked();

    void on_add_user_clicked();

    void on_delete_user_clicked();

    void on_delete_user_pressed();

    void on_update_user_clicked();

    void on_sort_user_clicked();

    void on_save_user_clicked();

    void on_minimize_clicked();

    void on_books_data_button_clicked();

    void on_save_table_view_clicked();

    void on_search_comboBox_currentTextChanged(const QString &arg1);

    void on_searchButtononedit_clicked();

    void on_send_message_clicked();

    void on_pic_button_clicked();

    void on_subcription_bar_clicked();

private:
    Ui::ownerDialog *ui;
    void clearTableView(QTableView* tableView);
    void loadMessage();
};

#endif // OWNERDIALOG_H
