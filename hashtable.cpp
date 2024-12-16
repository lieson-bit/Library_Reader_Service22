#include "hashtable.h"

int HashTable::hash(int key, int a) {
    return (key + a * a) % TABLE_SIZE;
}

void HashTable::insert(HashNode data) {
    int attempt = 0;
    static int i = 0;
    int index;

    // Check the entire hash table for an existing username
    for (int j = 0; j < TABLE_SIZE; ++j) {
        if (table[j].occupied && table[j].username == data.username) {
            // User with the same username already exists, skip insertion
            return;
        }
    }for (int j = 0; j < SIZE; ++j) {
        if (fail[j].occupied && fail[j].username == data.username) {
            // User with the same username already exists, skip insertion
            return;
        }
    }

    do {
        index = hash(data.key, attempt);
        if (!table[index].occupied) {
            table[index].key = data.key;
            table[index].username = data.username; 
            table[index].name = data.name;
            table[index].birthDate = data.birthDate;
            table[index].email = data.email;
            table[index].address = data.address;
            table[index].password = data.password;
            table[index].occupied = true;
            //QMessageBox::information(nullptr, "Insert", "Key ",  QString::fromStdString(data.username));
            return;
        }
        attempt++;
    } while (attempt < TABLE_SIZE);
    //QMessageBox::warning(nullptr, "Insert", "Unable to insert key. Hash table is full.");
    //handling collision
    if (i < SIZE && !fail[i].occupied) {
        fail[i].key = data.key;
        fail[i].username = data.username;        
        fail[i].name = data.name;
        fail[i].birthDate = data.birthDate;
        fail[i].email = data.email;
        fail[i].address = data.address;
        fail[i].password = data.password;
        fail[i].occupied = true;
        i++;
        return;
    }
}

void HashTable::search(int key) {
    int attempt = 0;
    int index;
    do {
        index = hash(key, attempt);
        if (table[index].key == key && table[index].occupied) {
            std::cout << "Key " << key << " found at index " << index << std::endl;
            return;
        }
        attempt++;
    } while (attempt < TABLE_SIZE);

    for (int i = 0; i < SIZE; i++) {
        if (fail[i].key == key && fail[i].occupied) {
            std::cout << "Key " << key << " found at index " << i << std::endl;
            return;
        }
    }

    std::cout << "Key " << key << " not found" << std::endl;
}

void HashTable::remove(int key) {
    int attempt = 0;
    int index;
    do {
        index = hash(key, attempt);
        if (table[index].key == key && table[index].occupied) {
            table[index].occupied = false;
            std::cout << "Key " << key << " deleted from index " << index << std::endl;
            return;
        }
        attempt++;
    } while (attempt < TABLE_SIZE);

    for (int i = 0; i < SIZE; i++) {
        if (fail[i].key == key && fail[i].occupied) {
            fail[i].occupied = false;
            std::cout << "Key " << key << " deleted from index " << i << std::endl;
            return;
        }
    }
    std::cout << "Key " << key << " not found in the hash table." << std::endl;
}

void HashTable::add(std::string key,std::string bookID, int num)
{

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].username == key && table[i].occupied) {
            // Create a new link with the new data
            link* newLink = new link;
            newLink->num = num;
            newLink->NNNMMM = bookID;

            // Add the new link to the beginning of the linked list
            newLink->next = table[i].bookstatus;
            table[i].bookstatus = newLink;

            return;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        if (fail[i].username == key && fail[i].occupied) {
            // Create a new link with the new data
            link* newLink = new link;
            newLink->num = num;
            newLink->NNNMMM = bookID;

            // Add the new link to the beginning of the linked list
            newLink->next = fail[i].bookstatus;
            fail[i].bookstatus = newLink;

            return;
        }
    }

    std::cout << "Key " << key << " not found" << std::endl;
}

void HashTable::displayRow(QStandardItemModel* model, const HashNode& data) {
    QList<QStandardItem*> items;
    items  << new QStandardItem(QString::fromStdString(data.username))
          << new QStandardItem(QString::fromStdString(data.name))
          << new QStandardItem(QString::fromStdString(data.birthDate))
          << new QStandardItem(QString::fromStdString(data.email))
          << new QStandardItem(QString::fromStdString(data.address))
          << new QStandardItem(QString::fromStdString(data.password));

    model->appendRow(items);
}

void HashTable::display(QTableView* tableView) {
    QStandardItemModel* model = new QStandardItemModel(0, 6, tableView);
    tableView->setModel(model);

    // Set horizontal header labels
    model->setHorizontalHeaderLabels({"ID", "Name", "Birthday", "Email", "Address","Password" });

    // Display data from the main table
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].occupied) {
            displayRow(model, table[i]);
        }
    }

    // Display data from the fail table
    for (int i = 0; i < SIZE; i++) {
        if (fail[i].occupied) {
            displayRow(model, fail[i]);
        }
    }
}

bool HashTable::isDataPresent(int key) {
    int attempt = 0;
    int index;

    // Check the main table using quadratic probing
    do {
        index = hash(key, attempt);
        if (table[index].occupied && table[index].key == key) {
            return true;
        }
        attempt++;
    } while (attempt < TABLE_SIZE);

    attempt = 0;

    // Check the fail table using quadratic probing
    do {
        index = hash(key, attempt);
        if (fail[index].occupied && fail[index].key == key) {
            return true;
        }
        attempt++;
    } while (attempt < SIZE);

    return false;
}

void HashTable::clear() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].occupied = false;
    }

    for (int i = 0; i < SIZE; i++) {
        fail[i].occupied = false;
    }
}


void HashTable::downloadToFile(std::string& fileName) {
    std::ofstream outputFile(fileName, std::ios::out);

    // Write data from the main table
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].occupied) {
            outputFile << table[i].username << ","
                       << table[i].name << ","
                       << table[i].birthDate << ","
                       << table[i].email << ","
                       << table[i].address<< ","
                       << table[i].password;
            link* currentLink = table[i].bookstatus;
            while (currentLink != nullptr) {
                outputFile << "," << currentLink->NNNMMM;
                currentLink = currentLink->next;
            }
            outputFile << std::endl;
        }
    }

    // Write data from the fail table
    for (int i = 0; i < SIZE; i++) {
        if (fail[i].occupied) {
            outputFile << fail[i].username << ","
                       << fail[i].name << ","
                       << fail[i].birthDate << ","
                       << fail[i].email << ","
                       << fail[i].address << ","
                       << fail[i].password ;
            link* currentLink = fail[i].bookstatus;
            while (currentLink != nullptr) {
                outputFile << "," << currentLink->NNNMMM;
                currentLink = currentLink->next;
            }

            outputFile << std::endl;
        }
    }

    outputFile.close();
}






void HashTable::uploadFromFile(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        qDebug() << "Error opening file.\n";
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Parse comma-separated values from the line
        std::istringstream iss(line);
        std::string username, name, birthDate, email, address, password;
        std::getline(iss, username, ',');
        std::getline(iss, name, ',');
        std::getline(iss, birthDate, ',');
        std::getline(iss, email, ',');
        std::getline(iss, address, ',');
        std::getline(iss, password, ',');

        // Create a new HashNode and copy parsed data
        HashNode newNode;
        newNode.username = username;
        newNode.name = name;
        newNode.birthDate = birthDate;
        newNode.email = email;
        newNode.address = address;
        newNode.password = password;

        // Initialize linked list to nullptr
        newNode.bookstatus = nullptr;

        // Read and insert book statuses from the line
        std::string bookStatus;
        while (std::getline(iss, bookStatus, ',')) {
            // Append book status to linked list
            link* newLink = new link;
            newLink->NNNMMM = bookStatus;
            newLink->next = newNode.bookstatus;  // Insert at the beginning
            newNode.bookstatus = newLink;
        }

        // Insert the new node into the hash table
        insert(newNode); // Assuming insertIntoHashTable exists

        qDebug() << "Data inserted from file:" << QString::fromStdString(line);
    }

    inputFile.close();
}


void HashTable::retrieveFromDatabase(HashTable& TABLE) {

    MainWindow conn;
        QSqlQuery *qry = new QSqlQuery(conn.mydbase);
        qry->prepare("select * from login_data");
        qry->exec();

        while (qry->next()) {
                HashNode data;
                data.key = qry->value("ID").toInt();
                data.username = qry->value("ID").toString().toStdString();
                data.name = qry->value("Name").toString().toStdString();
                data.birthDate = qry->value("Birthday").toString().toStdString();
                data.email = qry->value("Email").toString().toStdString();
                data.address = qry->value("Address").toString().toStdString();
                data.password = qry->value("Password").toString().toStdString();
                TABLE.insert(data);
        }
        conn.connClose();
}

bool HashTable::isUsernamePresent(const std::string& username) {
    // Check the main table
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table[i].occupied && table[i].username == username) {
            //table[i].bookstatus->num++;
            return true;
        }
    }

    // Check the fail table
    for (int i = 0; i < SIZE; ++i) {
        if (fail[i].occupied && fail[i].username == username) {
            //fail[i].bookstatus->num++;
            return true;
        }
    }

    return false;
}


void addLink(link*& head, const std::string& NNNMMM) {
    link* newLink = new link;
    newLink->NNNMMM = NNNMMM;
    newLink->next = head;
    head = newLink;
}

void deleteLinkedList(link*& head) {
    while (head != nullptr) {
        link* temp = head;
        head = head->next;
        delete temp;
    }
}

bool HashTable::editByUsername(const std::string& username, Datatype newData) {
    // Check the main table
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table[i].occupied && table[i].username == username) {
            // Found the entry, update the data
            addLink(table[i].bookstatus, newData.book_ID);
            table[i].bookstatus->num++;
            return true;
        }
    }

    // Check the fail table
    for (int i = 0; i < SIZE; ++i) {
        if (fail[i].occupied && fail[i].username == username) {
            // Found the entry, update the data
            addLink(fail[i].bookstatus, newData.book_ID);
            fail[i].bookstatus->num++;
            return true;
        }
    }

    // The specified username was not found
    return false;
}

void HashTable::freehashtablelinkedlist()
{
    for (int i = 0; i < TABLE_SIZE; ++i) {
        deleteLinkedList(table[i].bookstatus);
    }

    for (int i = 0; i < SIZE; ++i) {
        deleteLinkedList(fail[i].bookstatus);
    }
}

void HashTable::deleteLink(link*& head, const std::string& NNNMMM) {
    link* current = head;
    link* previous = nullptr;

    while (current != nullptr) {
        if (current->NNNMMM == NNNMMM) {
            if (previous == nullptr) {
                // Node to be deleted is the head
                head = current->next;
            } else {
                previous->next = current->next;
            }

            delete current;
            return;
        }

        previous = current;
        current = current->next;
    }
}

bool HashTable::deleteLinkByUsername(const std::string& username, const std::string& NNNMMM) {
    // Check the main table
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table[i].occupied && table[i].username == username) {
            // Found the entry, update the data
            deleteLink(table[i].bookstatus, NNNMMM);
            return true;
        }
    }

    // Check the fail table
    for (int i = 0; i < SIZE; ++i) {
        if (fail[i].occupied && fail[i].username == username) {
            // Found the entry, update the data
            deleteLink(fail[i].bookstatus, NNNMMM);
            return true;
        }
    }

    // The specified username was not found
    return false;
}

void displayBookData(const Node* bookNode, QLabel* label) {
    if (bookNode != nullptr) {
        // Display book data on QLabel
        std::string bookData = "Title: " + bookNode->title +
                               "\nID: " + bookNode->id +
                               "\nWritter: " + bookNode->writter +
                               "\nPublisher: " + bookNode->publisher +
                               "\nYear of Publication: " + bookNode->year_publication +
                               "\nTotal Number of Copies: " + std::to_string(bookNode->totalNumberOfCopies) +
                               "\nCopies Available: " + std::to_string(bookNode->copiesAvailable);

        label->setText(QString::fromStdString(bookData));
    } else {
        // If the title is not found, display a message
        label->setText("Book with the specified title not found.");
    }
}

void HashTable::displayUserDataHelper(const HashNode& node, QLabel* label, Node* root, std::string status,std::string book ) {
    if(status == "Users"){
        std::string userData = "Username: " + node.username +
                               "\nName: " + node.name +
                               "\nBirth Date: " + node.birthDate +
                               "\nEmail: " + node.email +
                               "\nAddress: " + node.address +
                               "\nPassword: " + node.password;

        // Display linked list data
        link* currentLink = node.bookstatus;
        while (currentLink != nullptr) {
            userData += "\nBookStatus " + std::to_string(currentLink->num) + ": " + currentLink->NNNMMM;
            currentLink = currentLink->next;
        }

        label->setText(QString::fromStdString(userData));
    }else{
        label->setText("I got her");
        Node *data = searchbytitle(root, book);
        displayBookData(data, label);
    }
}

void HashTable::displayUserData(QLabel* label, Node* root, std::string status, std::string book) {
    if(status == "Books") { // Check if the status is for displaying book data
        Node* data = searchbytitle(root, book); // Search for the book data
        if(data != nullptr) { // If book data is found
            // Call the helper function to display book data
            displayBookData(data, label);
        } else { // If book data is not found
            label->setText("Book not found"); // Set label text to indicate that the book was not found
        }
    } else { // If status is not for displaying book data
        label->setText("Invalid status"); // Set label text to indicate invalid status
    }
}

