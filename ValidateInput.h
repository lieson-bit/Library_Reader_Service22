#ifndef VALIDATEINPUT_H
#define VALIDATEINPUT_H
#include <string>
#include <regex>

bool isValidDate(int day, int month, int year);

bool isValidEmail(const std::string& email);

bool isValidFo(const std::string& input);
#endif // VALIDATEINPUT_H
