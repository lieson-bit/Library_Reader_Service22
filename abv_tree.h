#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "headers.h"

class MainWindow ;
struct Datatype;

struct NewNode {
    std::string id,writter, title, publisher, year_publication;
    int key,totalNumberOfCopies, copiesAvailable;
};

struct Node
{
    int key;
    std::string id, writter, title, publisher, year_publication;
    int totalNumberOfCopies, copiesAvailable;
    Node* left;
    Node* right;
    int height;
};


int height(Node* N);
int max(int a, int b);
Node* newNode(NewNode a);
Node* rightRotate(Node* y);
Node* leftRotate(Node* x);
int getBalance(Node* N);
Node* insert(Node* node, NewNode a);
void preOrder(Node* root);
int extractFirstThreeDigits(const QString &input);
bool validateFormat(QString& input);
Node *deleteNode(Node *root, int key);
void inOrderTraverse(Node* node, std::vector<NewNode>& nodeList);
void insertNodeIntoDatabase(Node* node, MainWindow& conn, std::ofstream& outFile);
void Traverse(Node* root, MainWindow& conn, std::ofstream& outFile);
void downloadDataToDatabase(Node* root) ;
void deleteAllBooksData();
Node* search(Node* root, int key);
Node* searchbytitle(Node* root, const std::string& title);
bool searchByStringID(Node*& root, const  Datatype& id,std::string& file);
#endif // AVL_TREE_H


































/*#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <QRegularExpression>
#include <stack>
#include "ownerdialog.h"

struct Tree {
    int elem;
    std::string writter, title, publisher, year_publication;
    int totalNumberOfCopies, copiesAvailable;
    int height;
    Tree* Prev;
    Tree* Left;
    Tree* Right;
};

bool validateFormat(QString& input);
void ShowTree(Tree* node);
void BalanceTree(Tree*& Root, Tree*& NewElem);
void AddTreeElem(Tree*& Root, Tree* NewElem);
void LeftRotate(Tree*& x);
void RightRotate(Tree*& y);
void BigLeftRotate(Tree*& node);
void BigRightRotate(Tree*& node);
void DeleteTreeElem(Tree*& Root, Tree*& DeleteElem);
Tree* SearchTreeElem(Tree* Root, int target);


#endif // AVL_TREE_H
*/
