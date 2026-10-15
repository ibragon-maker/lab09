#ifndef HANGAR_PILOT_MENU_H
#define HANGAR_PILOT_MENU_H

#include <vector>

#include "pilot.h"

/// The "Pilot Office" sub-menu. Runs until the user chooses Back (or presses Ctrl-D).
void run_pilot_menu(std::vector<Pilot>& pilots);

#endif
