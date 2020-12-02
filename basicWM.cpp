#include "config.hpp"
#include "basicWM.hpp"
#include <X11/Xlib.h>

std::string nameString = "basicWM v0.0.2";

void handleEvent() {
    XNextEvent(display, &event);
    if(event.type == KeyPress) {
        for (cKeybind bind : keybinds) {
            bind.processKeyPress(event);
        }
    }
}

void loop() {
    /* Event loop */
    while (true) {
        /* Draw nameString */
        XDrawString(display, root, gc, 4, 10, nameString.c_str(), nameString.length());
        
        /* If there are X events to handle, handle them and dont delay */
        if (XPending(display) > 0) {
            handleEvent();
        } else {
            /* No current event, sleep */
            usleep(20);
        }

        /* Flush screen (draw everything)*/
        XFlush(display);
    }

}

int main() {
    display = XOpenDisplay(NULL);
    curScreen = DefaultScreen(display);
    root = RootWindow(display, curScreen);
    gc = XDefaultGC(display, curScreen);
    XSetForeground(display, gc, 0xffffff);

    /* Register all keys with X */
    for (cKeybind bind : keybinds) {
        bind.registerKey();
    }

    /* Event loop */
    loop();
    return 0;
}