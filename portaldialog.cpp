#include "portaldialog.h"
#include "ui_portaldialog.h"

std::string filenam = "C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\books_data.txt";


portaldialog::portaldialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::portaldialog)
{
    ui->setupUi(this);

    QString username, password;
    if (readCredentialsFromFile(username, password))
    {
       func(username,password);
    }
    else{
        qDebug() << "Failed to read credentials from file.";
    }
    loadMess();
    startPictureT();
    databasetofile();
    std::string file = "C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\books_data.txt";
    std::string name = "java";

    ui->title_book->setPlaceholderText("title");
    ui->writer_book->setPlaceholderText("writer");
    ui->year0fpublication_book->setPlaceholderText("year ie 2024");

}

portaldialog::~portaldialog()
{
    delete ui;
}

void portaldialog::func(QString username, QString password)
{
   password = "word";

    // Now query the database to retrieve other information
    MainWindow conn;
    if (!conn.connOpen()) {
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("SELECT * FROM login_data WHERE ID=:username");
    qry.bindValue(":username", username);

    if (qry.exec() && qry.next()) {
        QString Name = qry.value("Name").toString();
        QString Birthday = qry.value("Birthday").toString();
        QString Email = qry.value("Email").toString();
        QString Address = qry.value("Address").toString();
        QString password_ = qry.value("Password").toString();

        ui->name_edit->setPlaceholderText(Name);
        ui->Birthday_edit->setPlaceholderText(Birthday);
        ui->Email_edit->setPlaceholderText(Email);
        ui->Address_edit->setPlaceholderText(Address);
        ui->Password_edit->setPlaceholderText(password_);

        // You can update the fields as needed (e.g., display them in labels, etc.)
        qDebug() << "User information retrieved successfully";
    } else {
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }
    conn.connClose(); // Close the connection
}

void portaldialog::displayNextP()
{
    QString username, password;
    if (readCredentialsFromFile(username, password))
    {
       func(username,password);
    }

    static int currentIndex = 0;

    // Read picture paths from a file and append them to the picturePaths list
    QStringList picturePaths;

    // Open the file containing picture paths
    QFile file("C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\pic_user.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
        return;
    }

    // Read and process each line from the file
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList words = line.split(","); // Split the line into words
        if (words.size() > 1 && words.first() == username) {
            // Remove the first word and append the remaining words to picturePaths
            words.removeFirst();
            QString path = ":/img_book/";
            for (int i = 0; i < words.size(); ++i) {
                QString word = words.at(i);
                path.append(word);
            }
            path.append(".png");
            picturePaths.append(path);
        }
    }
    file.close();

    // Your existing code for displaying pictures
    if (currentIndex < picturePaths.size()) {
        QPixmap pixmap(picturePaths[currentIndex]);
        if (!pixmap.isNull()) {
            QGraphicsScene* scene = new QGraphicsScene(this);
            scene->addPixmap(pixmap);
            ui->pic_books->setScene(scene);
            currentIndex = (currentIndex + 1) % picturePaths.size();
        } else {
            qDebug() << "Failed to load image at index" << currentIndex;
        }
    }
}

void portaldialog::startPictureT()
{
    // Create a QTimer for updating the picture every 4 seconds
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &portaldialog::displayNextP);

    // Start the timer with an interval of 4 seconds (4000 milliseconds)
    timer->start(4000);
}

void portaldialog::databasetofile() {
    MainWindow conn;
    if (!conn.connOpen()) {
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery qry;
    if (!qry.exec("SELECT * FROM books_table")) {
        qDebug() << "Error executing query:" << qry.lastError().text();
        conn.connClose(); // Close the connection
        return;
    }

    QFile outputFile("C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\books_data.txt");
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&outputFile);

        // Fetch and write data
        while (qry.next()) {
            QStringList rowData;
            for (int i = 0; i < qry.record().count(); ++i) {
                rowData << qry.value(i).toString();
            }
            out << rowData.join(",") << "\n"; // Separate arguments by comma
        }

        outputFile.close();
        qDebug() << "Data downloaded successfully to books_data.txt";
    } else {
        qDebug() << "Error opening output file:" << outputFile.errorString();
    }

    conn.connClose(); // Close the connection
}

Book_data * portaldialog::fillform()
{
    QString title = ui->title_book->text();
    QString writer = ui->writer_book->text();
     Book_data::publisherType type = Book_data::Jmax_lim; // Default value

    switch(ui->publisher_book->currentIndex()){
        case 0:
            type = Book_data::Jmax_lim;
            break;
        case 1:
            type = Book_data::Ted_talks;
            break;
        case 2:
            type = Book_data::Guap;
            break;
        case 3:
            type = Book_data::Te_library;
            break;
        case 4:
            type = Book_data::UNZA;
        break;
    default:
        qDebug() << "Unknown publisher type selected.";
        return nullptr; // Handle unexpected index values
    }

    int year = ui->year0fpublication_book->text().toInt();
     Book_data tryit;
      Book_data *buy = nullptr;
      if(tryit.check(title)){
          buy = new Book_data(title, writer, type, year);
      } else {
          qDebug() << "Book data does not match.";
      }

    return buy;
}

void portaldialog::showCost(Book_data *value)
{
    AbstractCalc *calculator = nullptr;

    switch (value->getType()) {
    case Book_data::Jmax_lim :
        calculator = new  Jmax_limcalc();
        break;
    case Book_data::Ted_talks:
        calculator = new Ted_talkscalc();
        break;
    case Book_data::Guap:
        calculator = new Guapcalc();
        break;
    case Book_data::Te_library:
        calculator = new Te_librarycalc();
        break;
    case Book_data::UNZA:
        calculator = new UNZA();
        break;
    default:
        qDebug() << "Unknown book type.";
        return; // Handle unexpected book type
    }

    if (calculator != nullptr) {
        CalcFactory *factory = new CalcFactoryImpl(calculator);
        int cost = CalculationFacade::getCost(value, factory);
        ui->display_book->setText("Price: " + QString::number(cost));
        delete factory; // Delete factory, not calculator
    }
}



void portaldialog::on_minimize_clicked()
{
    showMinimized();
}

bool portaldialog::readCredentialsFromFile(QString &username, QString &password)
{
    QFile file("C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\credentials.txt");
       if (file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           QTextStream in(&file);
           username = in.readLine(); // Read the first line (username)
           password = in.readLine(); // Read the second line (password)
           file.close();
           return true;
       }
       return false;
}

void portaldialog::loadMess()
{
    QString username, password;
    if (readCredentialsFromFile(username, password))
    {
        func(username, password);
    }

    QFile file("C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\Messages_text.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            // Check if the line starts with the username
            if (line.startsWith(username, Qt::CaseInsensitive))
            {
                // Split the line into words
                QStringList words = line.split(' ');
                // Remove empty words
                words.removeAll("");
                if (words.size() > 1)
                {
                    words.removeFirst(); // Remove the first word (username)
                    QString remainingWords = words.join(' ');
                    ui->history_chart->addItem(remainingWords);
                }
            }
        }
        file.close();
    }
}



void portaldialog::on_message_button_clicked()
{
    QString data = ui->Message_box_2->text();

    QString username, password;
    if (readCredentialsFromFile(username, password))
    {
       func(username,password);
    }
    // Append data to the file
    QFile file("C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\Messages_text.txt");
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out <<username+" "+ username+": "+data << "\n";
        file.close();
    }

     // Update QListWidget
     ui->history_chart->addItem(username +": "+data);
     ui->Message_box_2->clear();
}


void portaldialog::on_search_button_clicked()
{
    std::string search = ui->search_edit->text().toStdString();

    uploadFromF222(filenam, search, ui->show_up_books,ui->graphicsView_search);
}





void portaldialog::on_buy_book_clicked()
{
    Book_data *value = fillform();
    if (value != nullptr) {
        showCost(value);
        delete value; // Make sure to delete the dynamically allocated object to avoid memory leaks
    } else {
        ui->display_book->setText("Not present");
        QMessageBox::warning(this, tr("Error"), tr("Failed to fill form with valid book data."));
    }
}



void portaldialog::on_exit_clicked()
{
    // Hide the current ownerDialog
        this->hide();

        // Create a new instance of MainWindow and show it
        MainWindow* mainWin = new MainWindow();
        mainWin->show();
}

