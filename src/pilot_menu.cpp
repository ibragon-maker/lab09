#include "pilot_menu.h"

#include <iostream>

#include "input.h"

namespace {

void print_pilot_menu() {
    std::cout << "\n--- PILOT OFFICE ---\n"
              << "1. List pilots\n"
              << "2. Hire a pilot\n"
              << "3. Send a pilot on a mission\n"
              << "4. Rest a pilot\n"
              << "5. Adjust a pilot's skill (training or injury)\n"
              << "6. Back\n";
}

void print_pilots(const std::vector<Pilot>& pilots) {
    if (pilots.empty()) {
        std::cout << "No pilots on staff.\n";
        return;
    }
    for (std::size_t i = 0; i < pilots.size(); ++i) {
        std::cout << (i + 1) << ". ";
        print_pilot(pilots[i]);
    }
}

/// Asks the user to pick a pilot. Returns the index, or -1 if there are no pilots
/// or input ended.
int pick_pilot(const std::vector<Pilot>& pilots) {
    if (pilots.empty()) {
        std::cout << "No pilots on staff.\n";
        return -1;
    }
    print_pilots(pilots);
    int choice = 0;
    if (!read_int("Pick a pilot: ", 1, static_cast<int>(pilots.size()), choice)) {
        return -1;
    }
    return choice - 1;
}

}  // namespace

void run_pilot_menu(std::vector<Pilot>& pilots) {
    while (true) {
        print_pilot_menu();
        int choice = 0;
        if (!read_int("> ", 1, 6, choice)) {
            return;
        }

        if (choice == 1) {
            print_pilots(pilots);

        } else if (choice == 2) {
            // NOTE: nothing here checks the values. The starter lets any name and
            // any skill through, even an empty name or a skill of -500.
            // That is the problem this lab fixes.
            std::string name;
            int skill = 0;
            if (!read_line("Name: ", name) || !read_int("Skill: ", -500, 500, skill)) {
                return;
            }
            Pilot recruit{name, skill, 0, 0};
            pilots.push_back(recruit);
            std::cout << "Hired: ";
            print_pilot(pilots.back());

        } else if (choice == 3) {
            int index = pick_pilot(pilots);
            if (index < 0) {
                continue;
            }
            Pilot& pilot = pilots[static_cast<std::size_t>(index)];
            if (fly_mission(pilot)) {
                std::cout << pilot.name << " flew a mission. Fatigue is now "
                          << pilot.fatigue << ".\n";
            } else {
                std::cout << pilot.name << " is too tired to fly (fatigue "
                          << pilot.fatigue << ").\n";
            }

        } else if (choice == 4) {
            int index = pick_pilot(pilots);
            if (index < 0) {
                continue;
            }
            Pilot& pilot = pilots[static_cast<std::size_t>(index)];
            rest(pilot);
            std::cout << pilot.name << " rested. Fatigue is now " << pilot.fatigue << ".\n";

        } else if (choice == 5) {
            int index = pick_pilot(pilots);
            if (index < 0) {
                continue;
            }
            int change = 0;
            if (!read_int("Skill change (-200 to 200): ", -200, 200, change)) {
                return;
            }
            Pilot& pilot = pilots[static_cast<std::size_t>(index)];
            pilot.skill += change;
            std::cout << pilot.name << "'s skill is now " << pilot.skill << ".\n";

        } else {
            return;
        }
    }
}
