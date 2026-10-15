#ifndef HANGAR_PILOT_H
#define HANGAR_PILOT_H

#include <string>

/// A mech pilot.
struct Pilot {
    std::string name;
    int skill;    ///< 1 (rookie) to 100 (ace)
    int fatigue;  ///< 0 (rested) to 100 (exhausted)
    int missions; ///< missions flown, 0 or more

    /// Lowers fatigue by 30. Fatigue never drops below 0.
    void rest();

    /// A pilot with fatigue above 80 is too tired to fly: return false and changes nothing.
    /// Otherwise add 20 fatigue, add 1 mission, and return true.
    bool fly_mission();

    /// Prints one line: name | skill N | fatigue N | missions N
    void print() const;
};

#endif
