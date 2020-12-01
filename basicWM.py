import Xlib.display
import Xlib
from Xlib import X, XK
import keybind
import subprocess

## CONFIG BEGINS HERE
wmVer = b"v0.0.1"
modMask = X.Mod1Mask

def createKeyBinds():
    root.grab_key(display.keysym_to_keycode(XK.string_to_keysym("Return")), modMask, 1, X.GrabModeAsync, X.GrabModeAsync)

## CONFIG ENDS HERE

print("""
 _               _    __        ____  __
| |__   __ _ ___(_) __\ \      / /  \/  |
| '_ \ / _` / __| |/ __\ \ /\ / /| |\/| |
| |_) | (_| \__ \ | (__ \ V  V / | |  | |
|_.__/ \__,_|___/_|\___| \_/\_/  |_|  |_|
 -sekc """+wmVer.decode("utf-8"))

display = Xlib.display.Display()
screen = display.screen()
root = screen.root
gc = root.create_gc(foreground = screen.white_pixel, background = screen.black_pixel)

def handleEvent(event):
    if event.type == X.KeyPress:
        if (event.detail == 36):
            subprocess.Popen("alacritty")
def main():
    createKeyBinds()
    while True:
        root.draw_text(gc, 5, 15, b"BasicWM ("+wmVer+b")")
        display.sync()
        if display.pending_events() > 0:
            event = display.next_event()
            handleEvent(event)

if __name__ == "__main__":
        main()
