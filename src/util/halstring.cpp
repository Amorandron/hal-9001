
#include "halstring.h"

unsigned long hal::String::size() const {
    return string.size();
}

void hal::String::reverse() {
    std::string new_string;

    for(long i = string.size() - 1; i >= 0; --i)
        new_string.push_back(string[i]);

    string = new_string;
}

void hal::String::trim() {
    std::string front_string;
    std::string back_string;

    bool front_found = false;
    bool back_found = false;

    for(char c : string) {
        if((c == ' ' || c == '\t' || c == '\n') && !front_found)
            continue;
        else
            front_found = true;
        front_string.push_back(c);
    }

    for(long i = front_string.size() - 1; i >= 0; --i) {
        if((front_string[i] == ' ' || front_string[i] == '\t' || front_string[i] == '\n') && !back_found)
            continue;
        else
            back_found = true;
        back_string.push_back(front_string[i]);
    }

    String new_string(back_string);
    new_string.reverse();

    string = new_string.string;
}

std::vector<hal::String> hal::String::split(const char& delimiter) const {
    std::vector<String> elements;

    std::stringstream ss(string);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        elements.emplace_back(item);
    }
    return elements;
}

std::string hal::String::get() const {
    return string;
}

bool hal::String::operator==(const hal::String& other) const {
    return string == other.string;
}

bool hal::String::operator==(const std::string& other) const {
    return string == other;
}

bool hal::String::operator==(const char* other) const {
    return string == other;
}

bool hal::String::operator!=(const hal::String& other) const {
    return !(*this == other);
}

bool hal::String::operator!=(const std::string& other) const {
    return !((*this) == other);
}

bool hal::String::operator!=(const char* other) const {
    return !((*this) == other);
}

bool hal::String::operator<(const hal::String& other) const {
    return string < other.string;
}

bool hal::String::operator>(const hal::String& other) const {
    return string > other.string;
}

hal::String hal::String::operator+(const hal::String& other) const {
    return String(string + other.string);
}

hal::String hal::String::operator+(const std::string& other) const {
    return String(string + other);
}

hal::String hal::String::operator+(const char* other) const {
    return String(string + other);
}

char hal::String::operator[](const int& index) const {
    return string[index];
}

std::ostream& operator<<(std::ostream& os, const hal::String& hs) {
    os << hs.get();
    return os;
}
