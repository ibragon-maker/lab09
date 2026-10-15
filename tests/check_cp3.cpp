// Checkpoint 3 self-check. Build and run:
//   cmake --build build --target check_cp3 && ./build/check_cp3
// Needs everything from Checkpoint 2, plus:
//   bool Pilot::set_name(const std::string& new_name)   - false and no change if empty
//   void Pilot::change_skill(int change)                - adds change, result kept in 1..100
// and a constructor that repairs bad input: empty name becomes "Unnamed",
// skill is clamped into 1..100.

#include <string>

#include "check_helpers.h"
#include "pilot.h"

int main() {
    std::cout << "Checkpoint 3: invariants\n";

    Pilot blank("", 50);
    check(blank.name() == "Unnamed", "constructor: an empty name becomes \"Unnamed\"");

    Pilot too_high("Ace", 500);
    check(too_high.skill() == 100, "constructor: skill above 100 is clamped to 100");
    Pilot too_low("Rookie", -40);
    check(too_low.skill() == 1, "constructor: skill below 1 is clamped to 1");
    Pilot zero("Zed", 0);
    check(zero.skill() == 1, "constructor: skill 0 is clamped to 1");
    Pilot edge_low("Lo", 1);
    Pilot edge_high("Hi", 100);
    check(edge_low.skill() == 1 && edge_high.skill() == 100, "constructor: 1 and 100 are kept as given");

    Pilot ann("Ann", 50);
    check(!ann.set_name(""), "set_name(\"\") returns false");
    check(ann.name() == "Ann", "a rejected set_name() leaves the name unchanged");
    check(ann.set_name("Annabel"), "set_name(\"Annabel\") returns true");
    check(ann.name() == "Annabel", "an accepted set_name() changes the name");

    ann.change_skill(-500);
    check(ann.skill() == 1, "change_skill(-500) stops at 1");
    ann.change_skill(25);
    check(ann.skill() == 26, "change_skill(25) adds normally");
    ann.change_skill(500);
    check(ann.skill() == 100, "change_skill(500) stops at 100");

    Pilot bo("Bo", 60);
    for (int i = 0; i < 10; ++i) {
        bo.rest();
    }
    check(bo.fatigue() == 0, "fatigue stays at 0 after repeated rests");

    int flown = 0;
    for (int i = 0; i < 20; ++i) {
        if (bo.fly_mission()) {
            ++flown;
        }
    }
    check(flown == 5, "exactly 5 missions fit before fatigue blocks the pilot");
    check(bo.fatigue() == 100, "fatigue stops at exactly 100");
    check(bo.fatigue() >= 0 && bo.fatigue() <= 100, "fatigue is within 0..100");
    check(bo.missions() == 5, "refused missions are not counted");

    return finish("Checkpoint 3");
}
