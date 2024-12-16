 #include "abv_tree.h"


int height(Node* N)
{
    if (N == nullptr)
        return 0;
    return N->height;
}


int max(int a, int b)
{
    return (a > b) ? a : b;
}


Node* newNode(NewNode a)
{
    Node* node = new Node();
    node->id = a.id;
    node->key = a.key;
    node->writter = a.writter;
    node->title = a.title;
    node->publisher = a.publisher;
    node->year_publication = a.year_publication;
    node->totalNumberOfCopies = a.totalNumberOfCopies;
    node->copiesAvailable = a.copiesAvailable;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially
    // added at leaf
    return(node);
}


Node* rightRotate(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
        height(y->right)) + 1;
    x->height = max(height(x->left),
        height(x->right)) + 1;

    // Return new root
    return x;
}

Node* leftRotate(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left),
        height(x->right)) + 1;
    y->height = max(height(y->left),
        height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(Node* N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


Node* insert(Node* node, NewNode a)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(a));

    if (a.key < node->key)
        node->left = insert(node->left, a);
    else if (a.key > node->key)
        node->right = insert(node->right, a);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
        height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && a.key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && a.key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && a.key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && a.key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}


void preOrder(Node* root)
{
    if (root != NULL)
    {
        preOrder(root->left);
        qDebug()<< root->key << " "<< QString::fromStdString(root->writter)<<" "<< QString::fromStdString(root->title)<<" "<< QString::fromStdString(root->publisher)<<" "<< QString::fromStdString(root->year_publication)<<" "<<root->totalNumberOfCopies<<" "<<root->copiesAvailable<<" ";

        preOrder(root->right);
    }
}

int extractFirstThreeDigits(const QString &input) {
    // Take the first three characters of the input string
    QString firstThreeDigits = input.left(3);

    // Convert the extracted string to an integer
    bool conversionOk;
    int integerValue = firstThreeDigits.toInt(&conversionOk);

    // Check if the conversion was successful
    if (conversionOk) {
        return integerValue;
    } else {
        qDebug() << "Conversion to integer failed!";
        // Handle the error or return a default value
        return 0;
    }
}

bool validateFormat(QString& input) {
    // Regular expression pattern for the format NNN.NNN
    QRegularExpression pattern("\\d{3}\\.\\d{3}");
    // Check if the input matches the pattern
    return pattern.match(input).hasMatch();
}

Node *nodeWithMimumValue(Node *node) {
  Node *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

Node *deleteNode(Node *root, int key) {
  // Find the node and delete it
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == NULL) ||
      (root->right == NULL)) {
      Node *temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      Node *temp = nodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right,
                   temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));
  int balanceFactor = getBalance(root);
  if (balanceFactor > 1) {
    if (getBalance(root->left) >= 0) {
      return rightRotate(root);
    } else {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) {
    if (getBalance(root->right) <= 0) {
      return leftRotate(root);
    } else {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}


void inOrderTraverse(Node* node, std::vector<NewNode>& nodeList) {
    if (node) {
        // Traverse left subtree
        inOrderTraverse(node->left, nodeList);
        NewNode data;
        data.id=node->id;
        data.key=node->key;
        data.writter=node->writter;
        data.title=node->title;
        data.publisher=node->publisher;
        data.year_publication=node->year_publication;
        data.totalNumberOfCopies=node->totalNumberOfCopies;
        data.copiesAvailable=node->copiesAvailable;

        // Visit current node
        nodeList.push_back(data);

        // Traverse right subtree
        inOrderTraverse(node->right, nodeList);
    }
}

void insertNodeIntoDatabase(Node* node, MainWindow& conn, std::ofstream& outFile) {
    QSqlQuery qry(conn.mydbase);
    qry.prepare("INSERT INTO books_table (ID, writter, title, publisher, yearOfpublication, totalNumofCopies, NumofCopiesAvail) "
                "VALUES (:id, :writter, :title, :publisher, :yearOfPublication, :totalNumofCopies, :NumofCopiesAvail)");

    qry.bindValue(":id", QString::fromStdString(node->id));
    qry.bindValue(":writter", QString::fromStdString(node->writter));
    qry.bindValue(":title", QString::fromStdString(node->title));
    qry.bindValue(":publisher", QString::fromStdString(node->publisher));
    qry.bindValue(":yearOfPublication", QString::fromStdString(node->year_publication));
    qry.bindValue(":totalNumofCopies", node->totalNumberOfCopies);
    qry.bindValue(":NumofCopiesAvail", node->copiesAvailable);

    if (qry.exec()) {
        qDebug() << "Node with ID" << node->key << "inserted into the database";
        // Write the node's data to the file
        outFile << node->id << ","
                << node->writter << ","
                << node->title << ","
                << node->publisher << ","
                << node->year_publication << ","
                << node->totalNumberOfCopies << ","
                << node->copiesAvailable << "\n";
    } else {
        qDebug() << "Failed to insert node with ID" << node->key << "Error: " << qry.lastError().text();
    }
}


void Traverse(Node* root, MainWindow& conn, std::ofstream& outFile) {
    if (root != nullptr) {
        Traverse(root->left, conn, outFile);
        // Insert the node into the database and write to file
        insertNodeIntoDatabase(root, conn, outFile);
        Traverse(root->right, conn, outFile);
    }
}


void downloadDataToDatabase(Node* root) {
    try {
        MainWindow conn;
        if (!conn.connOpen()) {
            qDebug() << "Failed to open database connection.";
            return;
        }

        // Open the file for writing
        std::ofstream outFile("C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\books_data.txt");
        if (!outFile.is_open()) {
            qDebug() << "Failed to open file for writing.";
            return;
        }

        // Traversing the tree and inserting each node into the database
       Traverse(root, conn, outFile);
        outFile.close();
        conn.connClose();
    } catch (const std::exception& e) {
        qDebug() << "Exception caught: " << e.what();
    }
}


void deleteAllBooksData() {
    try {
        MainWindow conn;
        if (!conn.connOpen()) {
            qDebug() << "Failed to open database connection.";
            return;
        }

        QSqlQuery *qry = new QSqlQuery(conn.mydbase);
        qry->prepare("DELETE FROM books_table");

        if (qry->exec()) {
            qDebug()<<("All books data deleted successfully");
        } else {
             qDebug()<<("Error occured");
        }

        conn.connClose();
    } catch (const std::exception& e) {
        qDebug() << "Exception caught: " << e.what();
    }
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}


Node* searchbytitle(Node* root, const std::string& writter) {
    // Base Cases: root is null or key is present at the root
    if (root == NULL || root->writter == writter)
        return root;

    // Key is greater than root's key
    if (writter > root->writter)
        return searchbytitle(root->right, writter);

    // Key is smaller than root's key
    if (writter < root->writter)
        return searchbytitle(root->left, writter);
    return root;
}



bool searchByStringID(Node*& root, const Datatype& id,std::string& file) {
    // Traverse the tree
    Node* current = root;
    while (current != nullptr) {
        // Check if the current node's ID matches the target ID
        if (id.book_ID == current->id) {
            // Ensure copiesAvailable is not reduced below zero
            if (!isValidFo(id.return_date) && current->copiesAvailable > 0) {
                current->copiesAvailable--;
                return true;
            } else if (current->copiesAvailable < current->totalNumberOfCopies && isValidFo(id.return_date) && isValidFo(id.return_date)) {
                current->copiesAvailable++;
                //qDebug()<<QString::fromStdString(id.book_ID)+" " +QString::fromStdString(id.student_ID);
                deletelast(file,id);

                return true;
            }
            return false;
             // Found the node with the given ID
        }
        // If the target ID is smaller, move to the left subtree
        else if (id.book_ID < current->id) {
            current = current->left;
        }
        // If the target ID is larger, move to the right subtree
        else {
            current = current->right;
        }
    }
    // Node with the given ID not found
    //qDebug()<<"The elements are done";
    return false;
}


