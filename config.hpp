/* 
 Config.hpp
============
Configure keybinds by changing/adding binds to 
the vector 'keybinds'.
*/

#pragma once
#include "basicWM.hpp"
#include <X11/X.h>

int modKey = Mod1Mask;

std::string barConfig = "WMNAME | CURFOCUS";

/* Colours */
unsigned long barBackground = 0x1b1b1c;
unsigned long barText = 0xeeeeee;

std::vector<cKeybind> keybinds {
    /* Default bindings */
    cKeybind("Return", modKey, RUN, "alacritty"),
    cKeybind("d", modKey, RUN, "rofi -show run"),
    cKeybind("q", modKey | ShiftMask, INTERNAL, "kill"),
};