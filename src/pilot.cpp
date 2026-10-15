#include "pilot.h"
#include <iostream>

void Pilot::rest() {
    fatigue -= 30;
    if (fatigue < 0) {
        fatigue = 0;
    }
}

bool Pilot::fly_mission() {
    if (fatigue > 80) {
        return false;
    }
    fatigue += 20;
    missions += 1;
    return true;
}

void Pilot::print() const {
    std::cout << name << " | skill " << skill << " | fatigue "
              << fatigue << " | missions " << missions << '\n';
}
