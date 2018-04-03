
#include <iostream>
#include <string>
#include <vector>

#include "bot.h"

int main() {
    std::cerr << "Starting bot.." << std::endl;

    hal::Bot bot;
    return bot.read();
}