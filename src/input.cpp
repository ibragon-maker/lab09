#include "input.h"

#include <iostream>
#include <sstream>

bool read_int(const std::string& prompt, int low, int high, int& result) {
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) {
            return false;
        }
        std::istringstream in(line);
        int value = 0;
        if (in >> value && (in >> std::ws).eof() && value >= low && value <= high) {
            result = value;
            return true;
        }
        std::cout << "Enter a number from " << low << " to " << high << ".\n";
    }
}

bool read_line(const std::string& prompt, std::string& result) {
    std::cout << prompt;
    return static_cast<bool>(std::getline(std::cin, result));
}
