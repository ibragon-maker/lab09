#ifndef HANGAR_INPUT_H
#define HANGAR_INPUT_H

#include <string>

/// Prompts until the user enters a whole number in [low, high].
/// Returns false if input ends (Ctrl-D) before a valid number is entered.
/// Provided for you; do not modify.
bool read_int(const std::string& prompt, int low, int high, int& result);

/// Prompts once and reads a whole line (it may be empty).
/// Returns false if input ends (Ctrl-D).
/// Provided for you; do not modify.
bool read_line(const std::string& prompt, std::string& result);

#endif
