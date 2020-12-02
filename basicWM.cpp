#include "config.hpp"
#include "basicWM.hpp"

std::string nameString = "basicWM v0.0.2";

void handleEvent() {
    XNextEvent(display, &event);
    if(event.type == KeyPress) {
        for (cKeybind bind : keybinds) {
            bind.checkKeyPressed(event);
        }
    }
}

int main() {
    display = XOpenDisplay(NULL);
    curScreen = DefaultScreen(display);
    root = RootWindow(display, curScreen);
    gc = XDefaultGC(display, curScreen);
    XSetForeground(display, gc, 0xffffff);

    for (cKeybind bind : keybinds) {
        bind.registerKey();
    }
    while (true) {
        XDrawString(display, root, gc, 4, 12, nameString.c_str(), nameString.length());
        
        if (XPending(display) > 0) {
            handleEvent();
        }
        else {
            /* No current event, sleep */
            usleep(20);
        }

        XFlush(display);
    }
    return 0;
}