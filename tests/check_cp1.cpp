// Checkpoint 1 self-check. Build and run:
//   cmake --build build --target check_cp1 && ./build/check_cp1
// Needs: rest(), fly_mission() and print() as MEMBER functions of Pilot,
// with the data still public.

#include <string>

#include "check_helpers.h"
#include "pilot.h"

int main() {
    std::cout << "Checkpoint 1: member functions\n";

    Pilot ann{"Ann", 50, 50, 0};
    ann.rest();
    check(ann.fatigue == 20, "rest() lowers fatigue by 30");
    ann.rest();
    check(ann.fatigue == 0, "rest() never drops fatigue below 0");

    Pilot bo{"Bo", 60, 0, 0};
    bool flew = bo.fly_mission();
    check(flew, "fly_mission() returns true for a rested pilot");
    check(bo.fatigue == 20 && bo.missions == 1, "fly_mission() adds 20 fatigue and 1 mission");

    Pilot cy{"Cy", 70, 81, 3};
    bool refused = !cy.fly_mission();
    check(refused, "fly_mission() returns false when fatigue is above 80");
    check(cy.fatigue == 81 && cy.missions == 3, "a refused mission changes nothing");

    Pilot di{"Di", 70, 80, 0};
    check(di.fly_mission() && di.fatigue == 100, "fatigue of exactly 80 can still fly");

    Pilot ed{"Ed", 42, 10, 7};
    const Pilot& view = ed;
    std::string printed = capture_output([&view] { view.print(); });
    check(printed.find("Ed") != std::string::npos &&
              printed.find("42") != std::string::npos &&
              printed.find("10") != std::string::npos &&
              printed.find("7") != std::string::npos,
          "print() is const and shows name, skill, fatigue and missions");
    check(!printed.empty() && printed.back() == '\n', "print() ends with a newline");

    return finish("Checkpoint 1");
}
