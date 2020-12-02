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
    RUN,
    INTERNAL
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
        XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym(keyName.c_str())), modMask, root, True, GrabModeAsync, GrabModeAsync);
    }

    void checkKeyPressed(XEvent event) {
        if(event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym(keyName.c_str()))) {
            if (event.xkey.state & modMask) {
                popen(command.c_str(), "r");
            }
        }
    }
    std::string keyName;
    int modMask;
    KeybindType type;
    std::string command;
};
