//
// Created by Ксения on 17.11.2025.
//
#include <iostream>
#include <cstring>  // для memcpy
char* CopyString(const char* str) {
    if (str == nullptr) {
        return nullptr;
    }
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    char* copy = new char[length + 1]; //память для копии
    for (int i = 0; i <= length; i++) {
        copy[i] = str[i];
    }
    return copy;
}
char* ConcatinateStrings(const char* a, const char* b) {
    if (a == nullptr && b == nullptr) {
        return nullptr;
    }
    if (a == nullptr) {
        return CopyString(b);
    }
    if (b == nullptr) {
        return CopyString(a);
    }
    int lenA = 0;
    while (a[lenA] != '\0') {
        lenA++;
    }
    int lenB = 0;
    while (b[lenB] != '\0') {
        lenB++;
    }
    char* result = new char[lenA + lenB + 1];
    for (int i = 0; i < lenA; i++) {
        result[i] = a[i];
    }
    for (int i = 0; i < lenB; i++) {
        result[lenA + i] = b[i];
    }
    result[lenA + lenB] = '\0';
    return result;
}
char* ConcatinateStringsWithMemcpy(const char* a, const char* b) {
    if (a == nullptr && b == nullptr) {
        return nullptr;
    }
    if (a == nullptr) {
        return CopyString(b);
    }
    if (b == nullptr) {
        return CopyString(a);
    }
    int lenA = 0;
    while (a[lenA] != '\0') {
        lenA++;
    }
    int lenB = 0;
    while (b[lenB] != '\0') {
        lenB++;
    }
    char* result = new char[lenA + lenB + 1];
    std::memcpy(result, a, lenA);
    std::memcpy(result + lenA, b, lenB);
    result[lenA + lenB] = '\0';
    return result;
}
void FreeString(char* str) {
    delete[] str;
}
void PrintStringInfo(const char* str, const char* description) {
    std::cout << description << ": ";
    if (str == nullptr) {
        std::cout << "nullptr";
    } else {
        std::cout << "\"" << str << "\"";
        int length = 0;
        if (str != nullptr) {
            while (str[length] != '\0') {
                length++;
            }
        }
        std::cout << " (length: " << length << ")";
    }
    std::cout << std::endl;
}
//примеры
int main() {
    const char* original1 = "Hello, World!";
    char* copy1 = CopyString(original1);
    PrintStringInfo(original1, "Original");
    PrintStringInfo(copy1, "Copy");
    FreeString(copy1);
    std::cout << std::endl;

    const char* part1 = "C++ ";
    const char* part2 = "Programming";
    char* full = ConcatinateStringsWithMemcpy(part1, part2);
    PrintStringInfo(part1, "1");
    PrintStringInfo(part2, "2");
    PrintStringInfo(full, "Result (memcpy)");
    FreeString(full);
    std::cout << std::endl;
    return 0;
}