#include "ValidateInput.h"


bool isValidDate(int day, int month, int year) {
    // Check if the year is valid
    if (year < 1) return false;

    // Check if the month is valid
    if (month < 1 || month > 12) return false;

    // Determine the number of days in the given month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Handle leap years for February
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        daysInMonth[1] = 29;
    }

    // Check if the day is valid
    return day > 0 && day <= daysInMonth[month - 1];
}

bool isValidEmail(const std::string& email) {
    // Define a regular expression for validating email addresses
    const std::regex emailRegex(R"(([\w\.-]+)@([\w\.-]+)\.([a-zA-Z]{2,}))");

    // Check if the email matches the regex pattern
    return std::regex_match(email, emailRegex);
}
bool isValidFo(const std::string& input) {
    // Define a regex pattern for the date format DD.MM.YYYY
    const std::regex dateRegex(R"(^(0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.(\d{4})$)");

    // Check if the input matches the date format
    if (!std::regex_match(input, dateRegex)) {
        return false;
    }

    // Extract the day, month, and year from the input string
    int day = std::stoi(input.substr(0, 2));
    int month = std::stoi(input.substr(3, 2));
    int year = std::stoi(input.substr(6, 4));

    // Use the isValidDate function to ensure the date is logically valid
    return isValidDate(day, month, year);
}
