#include "roster_io.h"

#include <fstream>
#include <sstream>

namespace {

/// Parses text as a whole number. Rejects empty text and trailing characters.
bool parse_int(const std::string& text, int& value) {
    std::istringstream in(text);
    int parsed = 0;
    if (in >> parsed && (in >> std::ws).eof()) {
        value = parsed;
        return true;
    }
    return false;
}

/// Turns one line into a Mech. Returns false if the line breaks the file format.
bool parse_mech(const std::string& line, Mech& mech) {
    std::vector<std::string> fields;
    std::istringstream in(line);
    std::string field;
    while (std::getline(in, field, ',')) {
        fields.push_back(field);
    }
    if (!line.empty() && line.back() == ',') {
        fields.push_back("");  // getline drops a trailing empty field
    }
    if (fields.size() != 4 || fields[0].empty()) {
        return false;
    }
    int hp = 0;
    int attack = 0;
    int armor = 0;
    if (!parse_int(fields[1], hp) || !parse_int(fields[2], attack) ||
        !parse_int(fields[3], armor)) {
        return false;
    }
    if (hp < 1 || attack < 0 || armor < 0) {
        return false;
    }
    mech = Mech(fields[0], hp, attack, armor);
    return true;
}

}  // namespace

bool save_roster(const std::vector<Mech>& roster, const std::string& path) {
    std::ofstream out(path);
    if (!out) {
        return false;
    }
    for (const Mech& mech : roster) {
        out << mech.name() << ',' << mech.hp() << ',' << mech.attack() << ','
            << mech.armor() << '\n';
    }
    return static_cast<bool>(out);
}

bool load_roster(const std::string& path, std::vector<Mech>& roster, int& skipped_lines) {
    std::ifstream in(path);
    if (!in) {
        return false;
    }
    std::vector<Mech> loaded;
    int skipped = 0;
    std::string line;
    while (std::getline(in, line)) {
        Mech mech("", 1, 0, 0);
        if (parse_mech(line, mech)) {
            loaded.push_back(mech);
        } else {
            ++skipped;
        }
    }
    roster = loaded;
    skipped_lines = skipped;
    return true;
}

bool append_line(const std::string& path, const std::string& text) {
    std::ofstream out(path, std::ios::app);
    if (!out) {
        return false;
    }
    out << text << '\n';
    return static_cast<bool>(out);
}
