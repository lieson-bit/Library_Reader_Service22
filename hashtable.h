#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <unordered_set>
#include <string>

#include "headers.h"

const int TABLE_SIZE = 20;
const int SIZE = 10;
struct Datatype;
struct Node;
struct NewNode;

struct link{
    int num=0;
    std::string NNNMMM;
    link* next = nullptr;
};

struct HashNode {
    int key;
    std::string username;
    std::string name;
    std::string birthDate;
    std::string email;
    std::string address;
    std::string password;
    link* bookstatus;
    bool occupied;
    HashNode() : key(-1), occupied(false) {}
};

class HashTable {
private:
    HashNode table[TABLE_SIZE];
    HashNode fail[SIZE];

    // Hash function using quadratic probing
    int hash(int key, int a);

public:
    void insert(HashNode data);
    void search(int key);
    void remove(int key);
    void add(std::string key,std::string bookID, int num);
    void clear();
    void displayRow(QStandardItemModel* model, const HashNode& data);
    void display(QTableView* tableView);
    bool isDataPresent(int key);
    void downloadToFile(std::string& fileName);
    //void uploadFromFile(const std::string& fileName,const std::string& pattern);
    void retrieveFromDatabase(HashTable& TABLE);
    bool isUsernamePresent(const std::string& username);
    bool editByUsername(const std::string& username, Datatype newData);
    void freehashtablelinkedlist();
    void deleteLink(link*& head, const std::string& NNNMMM);
    bool deleteLinkByUsername(const std::string& username, const std::string& NNNMMM);
    void displayUserDataHelper(const HashNode& node, QLabel* label, Node* head,std::string status,std::string book);
    void displayUserData(QLabel* label, Node* root, std::string status,std::string book);
    void uploadFromFile(const std::string& fileName) ;
};

#endif // HASHTABLE_H
