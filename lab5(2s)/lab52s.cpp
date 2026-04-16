//
// Created by Ксения on 12.04.2026.
//

#include <exception>
#include <iostream>
#include <ostream>
#include <string>

class DateException : public std::out_of_range {
private:
    const char* what_;
    int day;
    int month;
    int year;
public:
    DateException(const char* ch, int day, int month, int year)
        : out_of_range(ch), what_(ch), day(day), month(month), year(year) {}

    const char* what() const noexcept override {
        return what_;
    }

    void error_print() const {
        std::cout << what_ << ": " << day << "." << month << "." << year << std::endl;
    }
};

class Date {
private:
    int day;
    int month;
    int year;

    bool isValidDate(int day, int month, int year) const {
        if (year < 1 || month < 1 || month > 12 || day < 1) {
            return false;
        }

        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        int daysInMonth[] = {31, 28 + isLeapYear, 31, 30, 31, 30,
                             31, 31, 30, 31, 30, 31};

        return day <= daysInMonth[month - 1];
    }

public:
    Date(int day, int month, int year) : day(day), month(month), year(year) {
        if (!isValidDate(day, month, year)) {
            std::cout << "Failed to create date" << std::endl;
            throw DateException("Invalid date", day, month, year);
        }
    }

    void print() const {
        printf("%02d.%02d.%04d", day, month, year);
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << (date.day < 10 ? "0" : "") << date.day << "."
           << (date.month < 10 ? "0" : "") << date.month << "."
           << date.year;
        return os;
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
};

int main() {
    // Тест 1: Неверная дата
    try {
        Date date1(29, 2, 2013);
        std::cout << "Created: " << date1 << std::endl;
    } catch (const DateException& e) {
        e.error_print();
    }
    std::cout << std::endl;

    // Тест 2: Неверный день
    try {
        Date date2(32, 12, 2016);
        std::cout << "Created: " << date2 << std::endl;
    } catch (const DateException& e) {
        e.error_print();
    }
    std::cout << std::endl;

    // Тест 3: Корректная дата (високосный год)
    try {
        Date date3(29, 2, 2004);
        std::cout << "Created: " << date3 << std::endl;
    } catch (const DateException& e) {
        e.error_print();
    }
    std::cout << std::endl;

    // Тест 4: Демонстрация оператора <<
    try {
        Date date4(5, 3, 2024);
        std::cout << "Date using operator<<: " << date4 << std::endl;
    } catch (const DateException& e) {
        e.error_print();
    }

    return 0;
}