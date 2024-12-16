#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "headers.h"

struct Datatype {
    std::string student_ID, book_ID, lending_date, return_date;

};

struct record {
    Datatype data;
    record* next = nullptr;
};

class HashTable;
struct HashNode;
struct Node;

void free_All_record(record** begin);
bool isCompanyNumPresent(record* tail, const std::string& name);
bool addToBeginning(record** begin, Datatype elem, HashTable& myHashTable, Node*& root,std::string& file);
void DelElem(record** begin, record* ptrCur);
void Find_Element( record* tail, const std::string& k);
record* FindElemCompany(record* tail, const std::string& elem);
void deleteByCompanyNum(record** tail, const std::string& name);
record* editByCompanyNum(record* tail, const std::string& name, const Datatype& newData);
void downloadToFile(record* tail, const std::string& fileName);
void addToEnd(record** tail, const Datatype& data);
void copyDataFromFileToCircularList(const std::string& filename, record*& head);
record* merge(record* a, record* b);
record* mid_point(record* head);
record* merge_sort(record* head);


#endif // LINKED_LIST_H
