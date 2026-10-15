#ifndef HANGAR_CHECK_HELPERS_H
#define HANGAR_CHECK_HELPERS_H

#include <iostream>
#include <sstream>
#include <string>

// Shared by the Pilot self-checks. Do not modify.

inline int checks_run = 0;
inline int checks_passed = 0;

inline void check(bool condition, const std::string& label) {
    ++checks_run;
    if (condition) {
        ++checks_passed;
        std::cout << "  PASS  " << label << '\n';
    } else {
        std::cout << "  FAIL  " << label << '\n';
    }
}

/// Runs the callable and returns everything it printed to std::cout.
template <typename Function>
std::string capture_output(Function function) {
    std::ostringstream captured;
    std::streambuf* original = std::cout.rdbuf(captured.rdbuf());
    function();
    std::cout.rdbuf(original);
    return captured.str();
}

inline int finish(const std::string& title) {
    std::cout << title << ": " << checks_passed << " of " << checks_run << " checks passed.\n";
    return checks_passed == checks_run ? 0 : 1;
}

#endif
