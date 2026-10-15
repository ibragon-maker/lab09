// Checkpoint 2 self-check. Build and run:
//   cmake --build build --target check_cp2 && ./build/check_cp2
// Needs: class Pilot with private data, constructor Pilot(std::string name, int skill),
// const getters name(), skill(), fatigue(), missions(), and the members rest(),
// fly_mission(), print() const.

#include <string>
#include <type_traits>
#include <utility>

#include "check_helpers.h"
#include "pilot.h"

int main() {
    std::cout << "Checkpoint 2: class with private data\n";

    check(!std::is_aggregate_v<Pilot>, "Pilot is no longer a plain struct (it has private data)");

    Pilot ann("Ann", 55);
    check(ann.name() == "Ann", "constructor stores the name");
    check(ann.skill() == 55, "constructor stores the skill");
    check(ann.fatigue() == 0, "a new pilot starts with fatigue 0");
    check(ann.missions() == 0, "a new pilot starts with 0 missions");

    const Pilot bo("Bo", 60);
    check(bo.name() == "Bo" && bo.skill() == 60 && bo.fatigue() == 0 && bo.missions() == 0,
          "getters can be called on a const Pilot");

    check(ann.fly_mission(), "fly_mission() still returns true for a rested pilot");
    check(ann.fatigue() == 20 && ann.missions() == 1, "fly_mission() updates fatigue and missions");
    ann.rest();
    check(ann.fatigue() == 0, "rest() still lowers fatigue by 30, minimum 0");

    Pilot cy("Cy", 40);
    for (int i = 0; i < 6; ++i) {
        cy.fly_mission();
    }
    check(!cy.fly_mission(), "a pilot at fatigue 100 is refused");
    check(cy.missions() == 5, "5 missions were flown before the refusal");

    std::string printed = capture_output([&bo] { bo.print(); });
    check(printed.find("Bo") != std::string::npos && printed.find("60") != std::string::npos,
          "print() is const and shows the pilot");

    // Getters should hand out copies or const references, never a way to change the data.
    constexpr bool name_is_safe =
        !std::is_same_v<decltype(std::declval<Pilot&>().name()), std::string&>;
    constexpr bool skill_is_safe = !std::is_same_v<decltype(std::declval<Pilot&>().skill()), int&>;
    constexpr bool fatigue_is_safe =
        !std::is_same_v<decltype(std::declval<Pilot&>().fatigue()), int&>;
    constexpr bool missions_is_safe =
        !std::is_same_v<decltype(std::declval<Pilot&>().missions()), int&>;
    check(name_is_safe && skill_is_safe && fatigue_is_safe && missions_is_safe,
          "no getter returns a non-const reference (that would leak the private data)");

    return finish("Checkpoint 2");
}
