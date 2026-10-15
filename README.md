# Mech Hangar

A command-line garage for your combat mechs. This repo grows every week of COSC 1437.

## Week 9: Hangar Pilot Refactor

The hangar now hires pilots. The Pilot Office (main menu option 6) works, but `Pilot` is a
plain `struct` with public fields, so nothing stops a pilot from having a skill of -500 or an
empty name. Your job is to turn `Pilot` into a protected class.

The Week 8 roster code (`src/roster_io.cpp`, menu options 3 to 5) is already finished in this
starter so everyone begins level. `Mech` is untouched.

### Build and run

```
cmake -S . -B build
cmake --build build
./build/hangar
```

### Self-checks

Each checkpoint has its own check. Build and run only the one you are working on:

```
cmake --build build --target check_cp1 && ./build/check_cp1
cmake --build build --target check_cp2 && ./build/check_cp2
cmake --build build --target check_cp3 && ./build/check_cp3
```

A check that will not compile usually means a name or signature does not match the
checkpoint. Read the first error; it names what is missing. Passing every check is strong
evidence, but the Canvas rubric also grades your design, comments, and commits.

### Files you edit

| File | What to do |
|---|---|
| `src/pilot.h` | Declare the class and its members |
| `src/pilot.cpp` | Define the members with `Pilot::` |
| `src/pilot_menu.cpp` | Update every use of `Pilot` so it compiles |

### Files you do not edit

`src/mech.*`, `src/battle_sim.*`, `src/roster_io.*`, `src/input.*`, `src/main.cpp`,
`tests/`, `CMakeLists.txt`

### Checkpoints

| CP | What to do | Check |
|---|---|---|
| 1 | Turn `rest`, `fly_mission`, and `print_pilot` into member functions of `Pilot`. `print_pilot` becomes `print() const`. Data stays public. Behavior does not change. | `check_cp1` |
| 2 | Change `struct` to `class` with private data. Add a constructor `Pilot(std::string name, int skill)` (fatigue and missions start at 0) and `const` getters `name()`, `skill()`, `fatigue()`, `missions()`. Fix `pilot_menu.cpp`. | `check_cp2` |
| 3 | Enforce the invariants (below). Add `bool set_name(const std::string&)` and `void change_skill(int change)`. Use `change_skill` for menu option 5. | `check_cp3` |
| Stretch | Save and load pilots to `data/pilots.csv` using only the public interface. A missing file leaves the pilot list unchanged. | none |

### Invariants

- name is never empty (the constructor uses `"Unnamed"`; `set_name("")` returns `false` and changes nothing)
- skill is always 1 to 100 (clamp it)
- fatigue is always 0 to 100
- missions is never negative

### Behavior (do not change)

- `rest()` lowers fatigue by 30, never below 0.
- `fly_mission()` returns `false` and changes nothing if fatigue is above 80. Otherwise it adds 20 fatigue and 1 mission, and returns `true`.
- `print()` shows: `name | skill N | fatigue N | missions N`

### Commits

Conventional Commits, composed in your editor (no `-m`). At least one commit per checkpoint,
for example `refactor(pilot): move pilot functions into the Pilot class`.
