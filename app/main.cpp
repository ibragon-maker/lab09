#include <iostream>
#include <string>
#include <vector>

#include "battle_sim.h"
#include "input.h"
#include "mech.h"
#include "pilot_menu.h"
#include "roster_io.h"

#ifndef HANGAR_DATA_DIR
#define HANGAR_DATA_DIR "data"
#endif

namespace {

const std::string roster_path = std::string(HANGAR_DATA_DIR) + "/roster.csv";
const std::string battle_log_path = std::string(HANGAR_DATA_DIR) + "/battle_log.txt";
const std::string graveyard_path = std::string(HANGAR_DATA_DIR) + "/graveyard.txt";

void print_menu() {
    std::cout << "\n=== MECH HANGAR ===\n"
              << "1. List mechs\n"
              << "2. Salvage a new mech\n"
              << "3. Save roster\n"
              << "4. Load roster\n"
              << "5. Training duel\n"
              << "6. Pilot office\n"
              << "7. Quit\n";
}

void print_roster(const std::vector<Mech>& roster) {
    if (roster.empty()) {
        std::cout << "The hangar is empty.\n";
        return;
    }
    for (std::size_t i = 0; i < roster.size(); ++i) {
        std::cout << (i + 1) << ". ";
        roster[i].print();
    }
}

}  // namespace

int main() {
    std::vector<Mech> roster;
    std::vector<Pilot> pilots;
    roster.push_back(make_random_mech());
    roster.push_back(make_random_mech());

    while (true) {
        print_menu();
        int choice = 0;
        if (!read_int("> ", 1, 7, choice)) {
            break;
        }

        if (choice == 1) {
            print_roster(roster);

        } else if (choice == 2) {
            roster.push_back(make_random_mech());
            std::cout << "Salvaged: ";
            roster.back().print();

        } else if (choice == 3) {
            if (save_roster(roster, roster_path)) {
                std::cout << "Roster saved.\n";
            } else {
                std::cout << "Could not write " << roster_path << ".\n";
            }

        } else if (choice == 4) {
            int skipped = 0;
            if (load_roster(roster_path, roster, skipped)) {
                std::cout << "Loaded " << roster.size() << " mechs (" << skipped
                          << " lines skipped).\n";
            } else {
                std::cout << "Could not open " << roster_path << ".\n";
            }

        } else if (choice == 5) {
            if (roster.empty()) {
                std::cout << "No mechs to send into the arena.\n";
                continue;
            }
            print_roster(roster);
            int index = 0;
            if (!read_int("Pick a mech: ", 1, static_cast<int>(roster.size()), index)) {
                break;
            }
            Mech& fighter = roster[static_cast<std::size_t>(index - 1)];
            Mech challenger = make_random_mech();
            std::cout << "Challenger: ";
            challenger.print();

            DuelResult result = simulate_duel(fighter, challenger);
            std::cout << result.summary << '\n';

            if (!append_line(battle_log_path, timestamp() + " " + result.summary)) {
                std::cout << "Warning: could not write the battle log.\n";
            }
            if (fighter.is_destroyed()) {
                std::string epitaph = timestamp() + " " + fighter.name() +
                                      " was destroyed by " + result.opponent_name;
                if (!append_line(graveyard_path, epitaph)) {
                    std::cout << "Warning: could not write the graveyard.\n";
                }
                roster.erase(roster.begin() + (index - 1));
            }

        } else if (choice == 6) {
            run_pilot_menu(pilots);

        } else {
            break;
        }
    }

    std::cout << "Hangar closed.\n";
    return 0;
}
