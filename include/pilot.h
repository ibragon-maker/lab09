#ifndef HANGAR_PILOT_H
#define HANGAR_PILOT_H

#include <string>

/// A mech pilot. This is the STARTER version: every field is public, so any code
/// anywhere can set a pilot's skill to -40 or give them an empty name.
/// Your job is to fix that. See README.md for the checkpoints.
struct Pilot {
    std::string name;
    int skill;      ///< 1 (rookie) to 100 (ace)
    int fatigue;    ///< 0 (rested) to 100 (exhausted)
    int missions;   ///< missions flown, 0 or more
};

/// Lowers fatigue by 30. Fatigue never drops below 0.
void rest(Pilot& pilot);

/// A pilot with fatigue above 80 is too tired to fly: return false and change nothing.
/// Otherwise add 20 fatigue, add 1 mission, and return true.
bool fly_mission(Pilot& pilot);

/// Prints one line:  name | skill N | fatigue N | missions N
void print_pilot(const Pilot& pilot);

#endif
