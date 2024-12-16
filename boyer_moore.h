#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include "headers.h"

struct Datatype;
struct link;
struct HashNode;


void badCharHeurist(const std::string& pattern, std::vector<int>& badChar);

bool searchBoyerMoore(const std::string& text, const std::string& pattern);

bool isDataPrese(const std::string& username, const std::string& fileContents);

void displayHashNo(const HashNode& data, QLabel* label);

void uploadFromFi(const std::string& fileName, const std::string& targetWord, QLabel* label);

void deletelast(std::string& file , const Datatype& target);

void retrieveBookInfo(const std::string& fileContents, const std::string& username);
void uploadFromF22(const std::string& fileName, const std::string& targetWord, QLabel* label);
void uploadFromF222(const std::string& fileName, const std::string& targetWord, QLabel* label,QGraphicsView* graph);

#endif // BOYER_MOORE_H
