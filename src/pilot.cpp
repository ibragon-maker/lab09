#include "pilot.h"
#include <iostream>
#include <algorithm>

Pilot::Pilot(std::string name, int skill)
    : name_(name.empty() ? "Unnamed" : std::move(name)),
      skill_(std::clamp(skill, 1, 100)),
      fatigue_(0),
      missions_(0) {}

void Pilot::rest() {
    fatigue_ -= 30;
    fatigue_ = std::clamp(fatigue_, 0, 100);
}

bool Pilot::fly_mission() {
    if (fatigue_ > 80) {
        return false;
    }
    fatigue_ += 20;
    fatigue_ = std::clamp(fatigue_, 0, 100);
    missions_ += 1;
    return true;
}

void Pilot::print() const {
    std::cout << name_ << " | skill " << skill_ << " | fatigue "
              << fatigue_ << " | missions " << missions_ << '\n';
}

std::string Pilot::name() const {
    return name_;
}

bool Pilot::set_name(const std::string& name) {
    if (name.empty()) {
        return false;
    }
    name_ = name;
    return true;
}

int Pilot::skill() const {
    return skill_;
}

void Pilot::change_skill(int change) {
    skill_ += change;
    skill_ = std::clamp(skill_, 1, 100);
}

int Pilot::fatigue() const {
    return fatigue_;
}

int Pilot::missions() const {
    return missions_;
}
