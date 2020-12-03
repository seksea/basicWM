#include "config.hpp"
#include "basicWM.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>

char* nameString = "basicWM v0.0.3";

void handleEvent() {
    XNextEvent(display, &event);
    if(event.type == KeyPress) {
        for (cKeybind bind : keybinds) {
            bind.processKeyPress(event);
        }
    }
    else if (event.type == MapRequest) {
        windowList.push_back(event.xmaprequest.window);
        XMapWindow(display, event.xmaprequest.window);
    }
}

void handleFocus() {
    int x, y;
    Window r, c;
    int rx, ry;
    unsigned int m;
    if (XQueryPointer(display, root, &r, &c, &rx, &ry, &x, &y, &m)) {
        focusedWindow = c;
    }
    XRaiseWindow(display, focusedWindow);
}

std::string generateBarString() {
    /* Get name of currently focused window */
    char* winName;
    XFetchName(display, focusedWindow, &winName);
    if (!winName) {
        winName = "";
    }

    /* Replace things in barConfig string with what they should be replaced with */
    std::string barString = std::regex_replace(barConfig, std::regex("WMNAME"), nameString);
    barString = std::regex_replace(barString, std::regex("CURFOCUS"), winName);

    return barString;
}

void loop() {
    /* Event loop */
    while (true) {
        /* Draw bar */
        std::string barString = generateBarString();
        XClearWindow(display, root);
        XSetForeground(display, gc, barBackground);
        XFillRectangle(display, root, gc, 0,0, XDefaultScreenOfDisplay(display)->width, 16);
        XSetForeground(display, gc, barText);
        XDrawString(display, root, gc, 4, 12, barString.c_str(), barString.length());

        handleFocus();
        
        /* If there are X events to handle, handle them and dont delay */
        if (XPending(display) > 0) {
            handleEvent();
        } else {
            /* No current event, sleep */
            usleep(10000);
        }
    }
}
 
/*Make an error handler that doesn't do anything,
  This is done to stop the program exiting when you
  attempt to kill a window when you have no focus*/
int errHandler(Display* disp, XErrorEvent* err) {return 0;}

int main() {
    display = XOpenDisplay(NULL);
    curScreen = DefaultScreen(display);
    root = RootWindow(display, curScreen);
    gc = XDefaultGC(display, curScreen);
    XSetErrorHandler(&errHandler);

    XSelectInput(display, root, SubstructureRedirectMask | SubstructureNotifyMask);

    /* Register all keys with X */
    for (cKeybind bind : keybinds) {
        bind.registerKey();
    }

    /* Event loop */
    loop();

    return 0;
}