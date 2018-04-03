
#ifndef HAL_9001_HALSTRING_H
#define HAL_9001_HALSTRING_H

#include <string>
#include <sstream>
#include <vector>
#include <ostream>

namespace hal {
    class String {
    public:
        String()
            : string("") {}
        String(const std::string& string)
            : string(string) {}
        String(const char* string)
            : string(string) {}

        unsigned long size() const;
        void reverse();
        void trim();
        std::vector<String> split(const char& delimiter = ' ') const;

        std::string get() const;

        bool operator==(const String& other) const;
        bool operator==(const std::string& other) const;
        bool operator==(const char* other) const;
        bool operator!=(const String& other) const;
        bool operator!=(const std::string& other) const;
        bool operator!=(const char* other) const;
        bool operator<(const String& other) const;
        bool operator>(const String& other) const;
        String operator+(const String& other) const;
        String operator+(const std::string& other) const;
        String operator+(const char* other) const;
        char operator[](const int& index) const;

    private:
        std::string string;
    };

    typedef String string;
}

std::ostream& operator<<(std::ostream& os, const hal::string& string);

#endif
