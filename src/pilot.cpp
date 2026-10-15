#include "pilot.h"

#include <iostream>

void rest(Pilot& pilot) {
    pilot.fatigue -= 30;
    if (pilot.fatigue < 0) {
        pilot.fatigue = 0;
    }
}

bool fly_mission(Pilot& pilot) {
    if (pilot.fatigue > 80) {
        return false;
    }
    pilot.fatigue += 20;
    pilot.missions += 1;
    return true;
}

void print_pilot(const Pilot& pilot) {
    std::cout << pilot.name << " | skill " << pilot.skill << " | fatigue "
              << pilot.fatigue << " | missions " << pilot.missions << '\n';
}
