#pragma once

#include <X11/X.h>
#include <X11/Xlib.h>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>


inline Display* display;
inline int curScreen;
inline Window root;
inline GC gc;
inline XEvent event;

enum KeybindType {
    RUN, /* Run with popen, e.g open term/browser/rofi/dmenu */
    INTERNAL /* Run an internal command, coming later, (e.g move a window, kill a window, change workspace, etc) */
};
class cKeybind {
public:
    cKeybind(std::string _keyName, int _modMask, KeybindType _type, std::string _command) {
        keyName = _keyName;
        modMask = _modMask;
        type = _type;
        command = _command;
    }

    void registerKey() {
        /* Register key with X so it is caught by X events */
        XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym(keyName.c_str())), modMask, root, True, GrabModeAsync, GrabModeAsync);
    }

    void processKeyPress(XEvent event) {
        /* Check if key is being pressed */
        if(event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym(keyName.c_str()))) {
            /* Check if the correct mod key is being pressed */
            if (event.xkey.state & modMask) {
                if (type == RUN) {
                    /* Run with popen, e.g open term/browser/rofi/dmenu */
                    popen(command.c_str(), "r");
                }
                if (type == INTERNAL) {
                    /* Run an internal command, coming later, (e.g move a window, kill a window, change workspace, etc) */
                }
            }
        }
    }
    std::string keyName;
    int modMask;
    KeybindType type;
    std::string command;
};
