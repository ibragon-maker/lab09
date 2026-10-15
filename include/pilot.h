#ifndef HANGAR_PILOT_H
#define HANGAR_PILOT_H

#include <string>

/// A mech pilot.
class Pilot {
public:
    Pilot(std::string name, int skill);

    void rest();
    bool fly_mission();
    void print() const;

    std::string name() const;
    bool set_name(const std::string&name); 
    int skill() const;    ///< 1 (rookie) to 100 (ace)
    void change_skill(int change);
    int fatigue() const;  ///< 0 (rested) to 100 (exhausted)
    int missions() const; ///< missions flown, 0 or more

private:
    std::string name_;
    int skill_;
    int fatigue_;
    int missions_;
};

#endif
