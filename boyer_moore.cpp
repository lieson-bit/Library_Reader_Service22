#include "boyer_moore.h"

void badCharHeurist(const std::string& pattern, std::vector<int>& badChar) {
    int m = pattern.size();

    for (int i = 0; i < 256; i++)
        badChar[i] = -1;

    for (int i = 0; i < m; i++)
        badChar[static_cast<int>(pattern[i])] = i;
}

bool searchBoyerMoore(const std::string& text, const std::string& pattern) {
    int m = pattern.size();
    int n = text.size();

    std::vector<int> badChar(256, 0);
    badCharHeurist(pattern, badChar);

    int s = 0; // shift of the pattern with respect to the text

    while (s <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j of the pattern while characters of
        // the pattern and text are matching at this shift s
        while (j >= 0 && tolower(pattern[j]) == tolower(text[s + j]))
            j--;

        // If the pattern is present at the current shift, return true
        if (j < 0) {
            return true;
        }
        else {
            // Shift the pattern to align the bad character in the text with the last occurrence in the pattern
            s += std::max(1, j - badChar[tolower(text[s + j])]);
        }
    }

    return false;
}

bool isDataPrese(const std::string& username, const std::string& fileContents) {
    // Use Boyer-Moore to check if the username is present in the fileContents
    return searchBoyerMoore(fileContents, username);
}

void displayHashNo(const HashNode& data, QLabel* label) {

    std::string bookData = "Username: " + data.username +
        "\nName: " + data.name +
        "\nDate of Birth: " + data.birthDate +
        "\nEmail: " + data.email +
        "\nAddress: " + data.address +
        "\nPassword: " + data.password
        + "\n";

    if (data.bookstatus) {
        link* currentLink = data.bookstatus;
        while (currentLink) {
            bookData += "Book_ID: " + currentLink->NNNMMM + "\n";
            currentLink = currentLink->next;
        }
    }
    bookData += "-----------------------";
    label->setText(QString::fromStdString(bookData));
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void replaceCommasWithSpaces(std::string& str) {
    for (char& ch : str) {
        if (ch == ',') {
            ch = ' '; // Replace comma with space
        }
    }
}
void replaceSpaces(std::string& str) {
    for (char& ch : str) {
        if (ch == ' ') {
            ch = ','; // Replace comma with space
        }
    }
}

void deleteSubstring(std::string& str, const std::string& substr) {
    // Find the position of the substring in the string
    size_t pos = str.find(substr);

    // If the substring is found, erase it from the string
    if (pos != std::string::npos) {
        str.erase(pos, substr.length());
    }
}
void deleteWord(std::string& str, const std::string& word) {
    // Find the position of the word in the string
    size_t pos = str.find(word);

    // If the word is found, erase it from the string
    if (pos != std::string::npos) {
        // Determine the position of the next space after the word
        size_t nextSpace = str.find(' ', pos);

        // Erase the word from the string
        if (nextSpace != std::string::npos) {
            str.erase(pos, nextSpace - pos + 1); // +1 to include the space
        } else {
            // If there's no space after the word, erase until the end of the string
            str.erase(pos);
        }
    }
}

void deletelast(std::string& file, const Datatype& target) {
    std::ifstream inputFile(file);
    if (!inputFile) {
        qDebug() << "Error opening file.\n";
        return;
    }

    std::ofstream tempFile("C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\temp.txt");
    if (!tempFile) {
        qDebug() << "Error creating temporary file.\n";
        inputFile.close();
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (searchBoyerMoore(line, target.book_ID) && searchBoyerMoore(line, target.student_ID)) {
           // replaceCommasWithSpaces(line);
           // deleteWord(line, target.book_ID);
            deleteSubstring(line,target.book_ID);
            //replaceSpaces(line);
            tempFile << line << std::endl;
            qDebug() <<QString::fromStdString(line);
        } else {
            tempFile << line << std::endl;
               qDebug() <<QString::fromStdString(line);
        }
    }

    inputFile.close();
    tempFile.close();


    if (std::remove(file.c_str()) != 0) {
        std::perror("Error removing original file");
    } else {
        qDebug() << "Original file removed successfully.\n";
    }

    if (std::rename("C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\temp.txt", file.c_str()) != 0) {
        std::perror("Error renaming temporary file");
    } else {
        qDebug() << "Temporary file renamed successfully.\n";
    }

}



void uploadFromFi(const std::string& fileName, const std::string& targetWord, QLabel* label) {
    std::ifstream inputFile(fileName, std::ios::in);

    if (!inputFile) {
        qDebug() << "Error opening file.\n";
        return;
    }

    HashNode data;
    std::string line;
    while (getline(inputFile, line)) {
        if (searchBoyerMoore(line, targetWord)) {
            // Create a new HashNode and copy basic data
            std::istringstream iss(line);
            getline(iss, data.username, ',');
            getline(iss, data.name, ',');
            getline(iss, data.birthDate, ',');
            getline(iss, data.email, ',');
            getline(iss, data.address, ',');
            getline(iss, data.password, ',');

            // Initialize the linked list to nullptr
            data.bookstatus = nullptr;

            // Read the linked list data
            link* currentLink = nullptr;
            std::string linkData;
            while (getline(iss, linkData, ',')) {
                link* newLink = new link;
                newLink->NNNMMM = linkData;
                newLink->next = nullptr;

                if (!data.bookstatus) {
                    data.bookstatus = newLink;  // Set the head of the list
                    currentLink = newLink;
                } else {
                    currentLink->next = newLink;
                    currentLink = newLink;
                }
            }

            // Display the HashNode data
            displayHashNo(data,label);

            // Reset data for the next iteration
            data = HashNode();
        }
    }

    inputFile.close();
}

void retrieveBookInfo(const std::string &fileContents, const std::string &username)
{
    // Convert username to lowercase for case-insensitive search
        std::string lowercaseUsername = username;
        std::transform(lowercaseUsername.begin(), lowercaseUsername.end(), lowercaseUsername.begin(), ::tolower);

        std::istringstream iss(fileContents);
        std::string line;

        while (std::getline(iss, line)) {
            if (searchBoyerMoore(line, lowercaseUsername)) {
              qDebug()<< "Found book information: " << QString::fromStdString(line) <<endl;
                return; // Stop searching after finding the first match
            }else{
                qDebug()<< "I didn't find any Found book information: ";
            }
        }
}


void displayBookDataFromNode(const Node& rootNode, const std::string& targetWord, QLabel* label) {
    if (rootNode.title.empty()) {
        label->setText("Node is empty.");
        return;
    }

    if (searchBoyerMoore(rootNode.title, targetWord)) {
        // Display book data on QLabel
        std::string bookData = "Title: " + rootNode.title +
                               "\nID: " + rootNode.id +
                               "\nWritter: " + rootNode.writter +
                               "\nPublisher: " + rootNode.publisher +
                               "\nYear of Publication: " + rootNode.year_publication +
                               "\nTotal Number of Copies: " + std::to_string(rootNode.totalNumberOfCopies) +
                               "\nCopies Available: " + std::to_string(rootNode.copiesAvailable);

        label->setText(QString::fromStdString(bookData));
    } else {
        // If the title is not found, display a message
        label->setText("Book with the specified title not found.");
    }
}

void displayBookDat(const Node& rootNode, const std::string& targetWord, QLabel* label, QGraphicsView* graph) {
    if (rootNode.title.empty()) {
        label->setText("Node is empty.");
        return;
    }

    if (searchBoyerMoore(rootNode.title, targetWord)) {
        // Display book data on QLabel
        std::string bookData = "Title: " + rootNode.title +
                               "\nWritter: " + rootNode.writter +
                               "\nPublisher: " + rootNode.publisher +
                               "\nYear of Publication: " + rootNode.year_publication;

        QString path = ":/img_book/" + QString::fromStdString(rootNode.title) + ".png";
        QPixmap pixmap(path);
        if (!pixmap.isNull()) {
            QGraphicsScene* scene = new QGraphicsScene();
            scene->addPixmap(pixmap);
            graph->setScene(scene);
            label->setText(QString::fromStdString(bookData));
        } else {
            // If the pixmap is null, display an error message
            label->setText("Failed to load book cover image.");
        }
    } else {
        // If the title is not found, display a message
        label->setText("Book with the specified title not found.");
    }
}



void uploadFromF22(const std::string& fileName, const std::string& targetWord, QLabel* label) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        qDebug() << "Error opening file.";
        return;
    }
    Node data ;
    std::string line;
    while (getline(inputFile, line)) {
        if (searchBoyerMoore(line, targetWord)) {
            std::istringstream iss(line);
            getline(iss, data.id, ',');
            getline(iss, data.writter, ',');
            getline(iss, data.title, ',');
            getline(iss, data.publisher, ',');
            getline(iss, data.year_publication, ',');
            std::string totalNumCopiesStr, copiesAvailStr;
            getline(iss, totalNumCopiesStr, ',');
            getline(iss, copiesAvailStr, ',');
            data.totalNumberOfCopies = std::stoi(totalNumCopiesStr);
            data.copiesAvailable = std::stoi(copiesAvailStr);

            // Display book data from the Node
            displayBookDataFromNode(data, targetWord, label);

            data = Node(); // Clean up memory if needed
        }
    }

    inputFile.close();

}


void uploadFromF222(const std::string& fileName, const std::string& targetWord, QLabel* label,QGraphicsView* graph) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        qDebug() << "Error opening file.";
        return;
    }
    Node data ;
    std::string line;
    while (getline(inputFile, line)) {
        if (searchBoyerMoore(line, targetWord)) {
            std::istringstream iss(line);
            getline(iss, data.id, ',');
            getline(iss, data.writter, ',');
            getline(iss, data.title, ',');
            getline(iss, data.publisher, ',');
            getline(iss, data.year_publication, ',');
            std::string totalNumCopiesStr, copiesAvailStr;
            getline(iss, totalNumCopiesStr, ',');
            getline(iss, copiesAvailStr, ',');
            try {
                data.totalNumberOfCopies = std::stoi(totalNumCopiesStr);
                data.copiesAvailable = std::stoi(copiesAvailStr);
            } catch (const std::invalid_argument& e) {
                qDebug() << "Error converting string to integer: " << e.what();
                // Handle the error (e.g., provide default values or skip the line)
            }


            // Display book data from the Node
            displayBookDat(data, targetWord, label,graph);

            data = Node(); // Clean up memory if needed
        }
    }

    inputFile.close();

}


