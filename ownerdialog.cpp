#include "ownerdialog.h"
#include "ui_ownerdialog.h"
#include <QComboBox>
#include <QIcon>
#include <QToolTip>
#include <QDebug>
#include "abv_tree.h"

HashTable TABLE;
record *head = nullptr;
std::vector<Datatype> uploadedData;
std::string fil = "C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\history.txt";
std::string fileName = "C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\users_datails.txt";
std::string filename2 = "C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\books_data.txt";
std::string status = " ";

ownerDialog::ownerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ownerDialog)
{
    ui->setupUi(this);
    connect(ui->functions_comboBox, &QComboBox::currentTextChanged, this, &ownerDialog::on_functions_comboBox_currentTextChanged);
    on_functions_comboBox_currentTextChanged(ui->functions_comboBox->currentText());
    ui->functions_comboBox->addItem(QIcon(":/img/Scre.png"), "Users");
    ui->functions_comboBox->addItem(QIcon(":/img/book.png"), "Books");
    ui->functions_comboBox->addItem(QIcon(":/img/receiving.png"), "Issue");
    //ui->functions_comboBox->addItem(QIcon(":/img/receiving.png"), "Receive");
    ui->comboBox_user->addItem(QIcon(":/img/file.png"), "file");
    ui->comboBox_user->addItem(QIcon(":/img/database.png"), "database");
    ui->search_comboBox->addItem(QIcon(":/img/Scre.png"), "Users");
    ui->search_comboBox->addItem(QIcon(":/img/book.png"), "Books");
    loadFromDatabase();
    TABLE.retrieveFromDatabase(TABLE);
    uploadDatatypeFromFile(fil, uploadedData,ui->listWidget);
    loadMessage();
    startPictureTimer();
}

ownerDialog::~ownerDialog()
{
    delete ui;
}

void ownerDialog::on_exit_clicked()
{
    TABLE.freehashtablelinkedlist();
    this->close();
}

QString ownerDialog::on_functions_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Users") {
           checker="Users";
           clear_inputdata();
           ui->input_1->setPlaceholderText("Name");
           ui->input_2->setPlaceholderText("Birthday");
           ui->input_3->setPlaceholderText("Email");
           ui->input_4->setPlaceholderText("Address");
           ui->input_5->setPlaceholderText("Password");
           ui->input_6->setPlaceholderText("Student ID");
           ui->input_7->setPlaceholderText("");
           ui->input_7->setStyleSheet("background-color: transparent;"
                                      "border-top: 0px solid #4f4f4f;"
                                      "border-bottom: 0px solid #4f4f4f;"
                                      "border-left: 0px solid #4f4f4f;"
                                      "border-right: 0px solid #4f4f4f;");
           ui->input_5->setStyleSheet("background-color:white");
           ui->input_6->setStyleSheet("background-color:white");
           ui->input_5->setDisabled(false);
           ui->input_6->setDisabled(false);
           ui->input_7->setDisabled(true);
       } else if (arg1 == "Books") {
           checker="Books";
           clear_inputdata();
           ui->input_1->setPlaceholderText("Book ID");
           ui->input_2->setPlaceholderText("Writter");
           ui->input_3->setPlaceholderText("Title");
           ui->input_4->setPlaceholderText("Publisher");
           ui->input_5->setPlaceholderText("Year of publication");
           ui->input_6->setPlaceholderText("Total number of copies");
           ui->input_7->setPlaceholderText("Number of copies available");
           ui->input_5->setStyleSheet("background-color:white");
           ui->input_6->setStyleSheet("background-color:white");
           ui->input_7->setStyleSheet("background-color:white");
           ui->input_5->setDisabled(false);
           ui->input_6->setDisabled(false);
           ui->input_7->setDisabled(false);

       }else if(arg1=="Issue"){
        checker = "Issuing";
        clear_inputdata();
        ui->input_1->setPlaceholderText("Student ID");
        ui->input_2->setPlaceholderText("Book ID");
        ui->input_3->setPlaceholderText("Date of Borrowing");
        ui->input_4->setPlaceholderText("Date of Return");
        ui->input_5->setPlaceholderText("");
        ui->input_5->setStyleSheet("background-color: transparent;"
                                   "border-top: 0px solid #4f4f4f;"
                                   "border-bottom: 0px solid #4f4f4f;"
                                   "border-left: 0px solid #4f4f4f;"
                                   "border-right: 0px solid #4f4f4f;");
        ui->input_5->setDisabled(true);
         ui->input_6->setPlaceholderText("");
        ui->input_6->setStyleSheet("background-color: transparent;"
                                   "border-top: 0px solid #4f4f4f;"
                                   "border-bottom: 0px solid #4f4f4f;"
                                   "border-left: 0px solid #4f4f4f;"
                                   "border-right: 0px solid #4f4f4f;");
        ui->input_6->setDisabled(true);
        ui->input_7->setPlaceholderText("");
        ui->input_7->setStyleSheet("background-color: transparent;"
                                   "border-top: 0px solid #4f4f4f;"
                                   "border-bottom: 0px solid #4f4f4f;"
                                   "border-left: 0px solid #4f4f4f;"
                                   "border-right: 0px solid #4f4f4f;");
        ui->input_5->setDisabled(true);
        ui->input_6->setDisabled(true);
        ui->input_7->setDisabled(true);

    }
    return arg1;
}

void ownerDialog::on_users_data_button_clicked()
{
    TABLE.retrieveFromDatabase(TABLE);
    TABLE.display(ui->tableView);
}

void ownerDialog::loadFromDatabase() {
    try {
        MainWindow conn;
        if (!conn.connOpen()) {
                qDebug() << "Failed to open database connection.";
                return;
    }

        QSqlQuery *qry = new QSqlQuery(conn.mydbase);
        qry->prepare("select * from books_table");
        qry->exec();

        while (qry->next()) {
            QString Name = qry->value("ID").toString();
            int ID;
            ID= extractFirstThreeDigits(Name);
            NewNode newNode ;
             newNode.key = ID;
            newNode.id = Name.toStdString();
            newNode.writter = qry->value("writter").toString().toStdString();
            newNode.title = qry->value("title").toString().toStdString();
            newNode.publisher = qry->value("publisher").toString().toStdString();
            newNode.year_publication = qry->value("yearOfPublication").toString().toStdString();
            newNode.totalNumberOfCopies = qry->value("totalNumofCopies").toInt();
            newNode.copiesAvailable = qry->value("NumofCopiesAvail").toInt();
            Root = insert(Root,newNode);
            //AddTreeElem(Root,newNode);
            qDebug() << "This was succesfull " ;
        }
        conn.connClose();
        } catch (const std::exception& e) {
            qDebug() << "Exception caught: " << e.what();
        }
}

void ownerDialog::clearTableView(QTableView* tableView) {
    QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(tableView->model());
        if (model) {
            model->removeRows(0, model->rowCount());
            model->setHorizontalHeaderLabels({"ID", "Name", "Birthday", "Email", "Address", "Password"});
            model->clear();
        }
}

void ownerDialog::loadMessage()
{
    QFile file("C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\Messages_text.txt");
       if (file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           QTextStream in(&file);
           while (!in.atEnd())
           {
               QString line = in.readLine();
               // Split the line into words
               QStringList words = line.split(' ');
               // Remove empty words
               words.removeAll("");
               if (words.size() > 1)
               {
                   words.removeFirst(); // Remove the first word (username)
                   QString remainingWords = words.join(' ');
                    ui->listWidget_2->addItem(remainingWords);
               }
           }
           file.close();
       }
}

void ownerDialog::clear_inputdata(){
   ui->input_1->clear();
   ui->input_2->clear();
   ui->input_3->clear();
   ui->input_4->clear();
   ui->input_5->clear();
   ui->input_6->clear();
   ui->input_7->clear();
}

void ownerDialog::on_clear_table_view_clicked()
{
    TABLE.clear();
    clearTableView(ui->tableView);
}

NewNode ownerDialog::createNewNode(){
    QString Name = ui->input_1->text();
    int ID;
    ID= extractFirstThreeDigits(Name);
    NewNode newNode;
    newNode.key = ID;
    newNode.id = Name.toStdString();
    newNode.writter = ui->input_2->text().toStdString();
    newNode.title = ui->input_3->text().toStdString();
    newNode.publisher = ui->input_4->text().toStdString();
    newNode.year_publication = ui->input_5->text().toStdString();
    newNode.totalNumberOfCopies = ui->input_6->text().toInt();
    newNode.copiesAvailable = ui->input_7->text().toInt();
    return newNode;
}

void DatatypeToFile(const std::string& fileName, const Datatype& elem) {
    std::ofstream outputFile(fileName, std::ios::out | std::ios::app);

    outputFile << elem.student_ID << "\t"
               << elem.book_ID << "\t"
               << elem.lending_date << "\t"
               << elem.return_date <<std::endl;

    outputFile.close();
}

void ownerDialog::uploadDatatypeFromFile(const std::string& fileName, std::vector<Datatype>& data, QListWidget* listWidget) {
    std::ifstream inputFile(fileName, std::ios::in);

    if (!inputFile) {
        // Handle file opening error
        return;
    }

    Datatype elem;
     listWidget->addItem("                                                                           ");
     listWidget->addItem("   Student_ID         Book_ID           Lending_date     Return_date   ");
    listWidget->addItem("_________________________________________________________________________");


    while (inputFile >> elem.student_ID >> elem.book_ID >> elem.lending_date >> elem.return_date ) {
        data.push_back(elem);

        // Add the item to the QListWidget
        QString listItem = QString::fromStdString("   "+elem.student_ID + "                 " + elem.book_ID + "                    " + elem.lending_date + "         " + elem.return_date)+"    ";
        listWidget->addItem(listItem);
    }

    inputFile.close();
}

void ownerDialog::displayNextPicture()
{
    static int currentIndex = 0;
    const QStringList picturePaths = {":/img_book/Obedience to God.png", ":/img_book/Welcome Home.png", ":/img_book/C++ complete course.png",":/img_book/The heart of God.png",":/img_book/Java Script done.png", ":/img_book/Money talks.png",  ":/img_book/Come back home.png"};

    if (currentIndex < picturePaths.size()) {
        QPixmap pixmap(picturePaths[currentIndex]);
        if (!pixmap.isNull()) {
            QGraphicsScene* scene = new QGraphicsScene(this);
            scene->addPixmap(pixmap);
            ui->graphicsView_3->setScene(scene);
            currentIndex = (currentIndex + 1) % picturePaths.size();
        } else {
            qDebug() << "Failed to load image at index" << currentIndex;
        }
    }
}


void ownerDialog::startPictureTimer()
{
    // Create a QTimer for updating the picture every 4 seconds
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ownerDialog::displayNextPicture);

    // Start the timer with an interval of 4 seconds (4000 milliseconds)
    timer->start(4000);
}

void ownerDialog::on_add_user_clicked()
{
    MainWindow conn;
    QString Name, Birthday, Email, Address, password, key;
    Name = ui->input_1->text();
    Birthday = ui->input_2->text();
    Email = ui->input_3->text();
    Address = ui->input_4->text();
    password = ui->input_5->text();
    key = ui->input_6->text();

    if (!conn.connOpen()) {
        qDebug() << "Failed to open the database";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;

    if (checker == "Users") {
        // Check if the username already exists before attempting to insert
        qry.prepare("SELECT * FROM login_data WHERE ID='" + key + "'");
        if (qry.exec() && !qry.next()) {
            qry.prepare("INSERT INTO login_data (ID, Name, Birthday, Email, Address, Password) "
                        "VALUES ('" + key + "','" + Name + "','" + Birthday + "','" + Email + "','" + Address + "','" + password + "')");
            if (qry.exec()) {
                ui->comments_on_inputs->setText("User saved to database");

            } else {
                QMessageBox::critical(this, tr("error::"), qry.lastError().text());
            }
        } else {
            ui->comments_on_inputs->setText("User with ID " + key + " already exists ");
        }
        clear_inputdata();
        conn.connClose();
    } else if (checker == "Books") { 
        if(validateFormat(Name)){
            NewNode newNode =createNewNode();
            Root = insert(Root,newNode);
            clear_inputdata();
            ui->comments_on_inputs->setText("The book "+Name+" is saved");
        }else{
            ui->comments_on_inputs->setText("Incorrect formate № book ID ");
        }

        qDebug() << "On books now";
    } else {
        Datatype elem;
        elem.student_ID = ui->input_1->text().toStdString();
        elem.book_ID = ui->input_2->text().toStdString();
        elem.lending_date = ui->input_3->text().toStdString();
        elem.return_date = ui->input_4->text().toStdString();
        if(addToBeginning(&head, elem, TABLE,Root,fileName)){

            if(TABLE.editByUsername(elem.student_ID, elem)){
                DatatypeToFile(fil, elem);
                //TABLE.downloadToFile(fileName);
                //TABLE.uploadFromFile(fileName);

                ui->listWidget->addItem(QString::fromStdString("   "+elem.student_ID + "                 " + elem.book_ID + "                    " + elem.lending_date + "         " + elem.return_date)+"    ");
            }
            ui->comments_on_inputs->setText("Successfully added");
             clear_inputdata();
        }else{
            ui->comments_on_inputs->setText("Username unavailable");
        }
    }
}

void ownerDialog::on_delete_user_clicked()
{
    MainWindow conn;
    QString username = ui->input_6->text();
    QString bookID = ui->input_1->text();

    if (!conn.connOpen()) {
        qDebug() << "Failed to open the database";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;

    if (checker == "Users") {
        // Check if the username exists before attempting to delete
        qry.prepare("SELECT * FROM login_data WHERE ID='" + username + "'");
        if (qry.exec() && qry.next()) {
            qry.prepare("DELETE FROM login_data WHERE ID='" + username + "'");
            if (qry.exec()) {
                ui->comments_on_inputs->setText(username + " has been deleted");

            } else {
                ui->comments_on_inputs->setText("Failed to delete " + username);
            }
        } else {
            ui->comments_on_inputs->setText(username + " not found in the database");
        }
        clear_inputdata();
        conn.connClose();
    } else if (checker == "Books") {
        int ID;
        ID= extractFirstThreeDigits(bookID);
        Root = deleteNode(Root,ID);
        clear_inputdata();
        ui->comments_on_inputs->setText(bookID +" is deleted");
        qDebug() << "On books now";
    } else {
        ui->comments_on_inputs->setText("On Issuing now");
    }
}

void ownerDialog::on_delete_user_pressed()
{
     ui->comments_on_inputs->setText("Delete the user by key");
}

void ownerDialog::on_update_user_clicked()
{
    MainWindow conn;
        QString Name, Birthday, Email, Address, password, key;
        Name = ui->input_1->text();
        Birthday = ui->input_2->text();
        Email = ui->input_3->text();
        Address = ui->input_4->text();
        password = ui->input_5->text();
        key = ui->input_6->text();

        if (!conn.connOpen()) {
            qDebug() << "Failed to open the database";
            return;
        }

        conn.connOpen();
        QSqlQuery qry;

        if (checker == "Users") {
            // Check if the user with the given ID exists
            qry.prepare("SELECT * FROM login_data WHERE ID='" + key + "'");
            if (qry.exec() && qry.next()) {
                // User with the given ID found, proceed to update information
                qry.prepare("UPDATE login_data SET Name='" + Name + "', Birthday='" + Birthday + "', "
                            "Email='" + Email + "', Address='" + Address + "', Password='" + password + "' "
                            "WHERE ID='" + key + "'");
                if (qry.exec()) {
                    ui->comments_on_inputs->setText("User information updated");
                } else {
                    QMessageBox::critical(this, tr("error::"), qry.lastError().text());
                }
            } else {
                ui->comments_on_inputs->setText("User with ID " + key + " not found in the database");
            }
             clear_inputdata();
            conn.connClose();
        } else if (checker == "Books") {
            int ID;
            ID= extractFirstThreeDigits(Name);
            Root = deleteNode(Root, ID);
            NewNode newNode =createNewNode();
                // Then, insert a new node with the new key
            Root = insert(Root, newNode);
            clear_inputdata();
            ui->comments_on_inputs->setText("updated successful");
            qDebug() << "On books now";
        } else {
            ui->comments_on_inputs->setText("On Issuing now");
        }
}

void ownerDialog::disableButton(QPushButton* button) {
    if (button) {
        button->setEnabled(false);
    }
}

void ownerDialog::on_sort_user_clicked()
{
    Datatype id;
    id.book_ID = "008.128";
    id.student_ID ="B4502-21";
    id.lending_date ="12.11.2001";
    id.return_date ="31.03.2001";
    std::string file ="C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\users_datails.txt";
    qDebug()<<QString::fromStdString(id.book_ID)+" " +QString::fromStdString(id.student_ID);
    deletelast(file,id);
}

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <sstream>
#include <string>

void removeDuplicateEntriesInLine(std::string& line) {
    std::unordered_set<std::string> seenEntries; // Set to track seen entries
    std::stringstream ss(line);
    std::string token;
    std::string cleanedLine;
    bool first = true; // Track if this is the first entry

    while (std::getline(ss, token, ',')) {
        if (seenEntries.find(token) == seenEntries.end()) {
            if (!first) {
                cleanedLine += ","; // Add comma if not the first entry
            }
            seenEntries.insert(token);  // Add token to set
            cleanedLine += token;
            first = false; // Not the first entry anymore
        }
    }

    line = cleanedLine;
}

void removeDuplicateFieldsInFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Failed to open the file for reading: " << filename << std::endl;
        return;
    }

    std::ofstream tempFile("temp.txt"); // Temporary file to store cleaned lines
    std::string line;

    while (std::getline(inputFile, line)) {
        removeDuplicateEntriesInLine(line); // Clean the line
        tempFile << line << std::endl;      // Write cleaned line to temp file
    }

    inputFile.close();
    tempFile.close();

    // Replace original file with the temp file
    std::rename("temp.txt", filename.c_str());
}


void ownerDialog::on_save_user_clicked()
{

    TABLE.downloadToFile(fileName);
    std::string file = "C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\users_datails.txt";
    removeDuplicateFieldsInFile(file);
    ui->comments_on_inputs->setText("Downloaded to file");
}

void ownerDialog::on_minimize_clicked()
{
    showMinimized();
}

void ownerDialog::on_books_data_button_clicked()
{

    try {
           std::vector<NewNode> nodeList;  // Store AVL tree nodes in a vector

           // Traverse the AVL tree and populate the vector
           inOrderTraverse(Root, nodeList);  // You need to implement inOrderTraverse

           // Create a model to hold the data
           QStandardItemModel *model = new QStandardItemModel(nodeList.size(), 7, this);

           // Set headers for the columns
           model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
           model->setHorizontalHeaderItem(1, new QStandardItem(QString("Writter")));
           model->setHorizontalHeaderItem(2, new QStandardItem(QString("Title")));
           model->setHorizontalHeaderItem(3, new QStandardItem(QString("Publisher")));
           model->setHorizontalHeaderItem(4, new QStandardItem(QString("Year of Publication")));
           model->setHorizontalHeaderItem(5, new QStandardItem(QString("Total Copies")));
           model->setHorizontalHeaderItem(6, new QStandardItem(QString("Available Copies")));

           // Populate the model with data from the vector
           for (unsigned long long row = 0; row < nodeList.size(); ++row) {
               const NewNode& node = nodeList[row];
               model->setItem(row, 0, new QStandardItem(QString::fromStdString(node.id)));
               model->setItem(row, 1, new QStandardItem(QString::fromStdString(node.writter)));
               model->setItem(row, 2, new QStandardItem(QString::fromStdString(node.title)));
               model->setItem(row, 3, new QStandardItem(QString::fromStdString(node.publisher)));
               model->setItem(row, 4, new QStandardItem(QString::fromStdString(node.year_publication)));
               model->setItem(row, 5, new QStandardItem(QString::number(node.totalNumberOfCopies)));
               model->setItem(row, 6, new QStandardItem(QString::number(node.copiesAvailable)));
           }

           // Set the model for the tableView
           ui->tableView->setModel(model);
           loadFromDatabase();

       } catch (const std::exception& e) {
           qDebug() << "Exception caught: " << e.what();
       }
}

void ownerDialog::on_save_table_view_clicked()
{
    deleteAllBooksData();
    downloadDataToDatabase(Root);
    ui->comments_on_inputs->setText("Saved in the database");
}

void ownerDialog::on_search_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Users"){
        status = "Users";
    }else if(arg1 == "Books"){
        status = "Books";
    }
}


void ownerDialog::on_searchButtononedit_clicked()
{
    std::string word = ui->search_lineEdit->text().toStdString();
    if(status =="Users"){
        uploadFromFi(fileName,word,ui->search_view);
    }else{
        uploadFromF22(filename2, word, ui->search_view);
        //TABLE.displayUserData(ui->search_view, Root, status,word);
    }
}


void ownerDialog::on_send_message_clicked()
{
    QString data = ui->Message_box->text();
    QString id = ui->idmessage->text();

    // Append data to the file
        QFile file("C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\Messages_text.txt");
        if (file.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream out(&file);
            out <<id+" libraly: "+ data << "\n";
            file.close();
        }

        // Update QListWidget
           ui->listWidget_2->addItem(" libraly: "+ data );

           ui->Message_box->clear();


}


void ownerDialog::on_pic_button_clicked()
{

    QString data = ui->sendpic_nameline->text();
    // Append data to the file
    QFile file("C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\pic_user.txt");
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << data << "\n";
        file.close();
        ui->sendpic_nameline->clear();
        qDebug() <<"updated";
    }
}





void ownerDialog::on_subcription_bar_clicked()
{
    // Hide the current ownerDialog
        this->hide();

        // Create a new instance of MainWindow and show it
        MainWindow* mainWin = new MainWindow();
        mainWin->show();
}

