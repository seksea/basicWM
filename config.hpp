#pragma once

#include "basicWM.hpp"

inline std::vector<cKeybind> keybinds {
    cKeybind("Return", Mod1Mask, RUN, "alacritty"),
    cKeybind("d", Mod1Mask, RUN, "rofi -show run"),
};