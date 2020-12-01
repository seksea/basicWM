import Xlib.display
import Xlib
from Xlib import X, XK
import subprocess
import time

display = Xlib.display.Display()
screen = display.screen()
root = screen.root
gc = root.create_gc(foreground = screen.white_pixel, background = screen.black_pixel)
focusedWindow = None

## CONFIG BEGINS HERE
wmVer = b"v0.0.1"
modMask = X.Mod1Mask

raiseOnFocus = True

keybinds = [
            [display.keysym_to_keycode(XK.string_to_keysym("Return")), modMask, "Popen", "alacritty"],
            [display.keysym_to_keycode(XK.string_to_keysym("d")), modMask, "Popen", "rofi -show run"],
            [display.keysym_to_keycode(XK.string_to_keysym("q")), modMask | X.ShiftMask, "Internal", "killFocusedWindow"],
            [display.keysym_to_keycode(XK.string_to_keysym("Left")), modMask | X.ShiftMask, "Internal", "windowMoveLeft"],
            [display.keysym_to_keycode(XK.string_to_keysym("Right")), modMask | X.ShiftMask, "Internal", "windowMoveRight"],
            [display.keysym_to_keycode(XK.string_to_keysym("Down")), modMask | X.ShiftMask, "Internal", "windowMoveDown"],
            [display.keysym_to_keycode(XK.string_to_keysym("Up")), modMask | X.ShiftMask, "Internal", "windowMoveUp"],
            ]


## CONFIG ENDS HERE

print("""
 _               _    __        ____  __
| |__   __ _ ___(_) __\ \      / /  \/  |
| '_ \ / _` / __| |/ __\ \ /\ / /| |\/| |
| |_) | (_| \__ \ | (__ \ V  V / | |  | |
|_.__/ \__,_|___/_|\___| \_/\_/  |_|  |_|
 -sekc """+wmVer.decode("utf-8"))


def createKeyBinds():
    for keybind in keybinds:
        root.grab_key(keybind[0], keybind[1], 1, X.GrabModeAsync, X.GrabModeAsync)

def handleEvent(event):
    global focusedWindow
    if event.type == X.KeyPress:
        for keybind in keybinds:
            if event.detail == keybind[0]:
                if keybind[2] == "Popen":
                    subprocess.Popen(keybind[3], shell=True)
                elif keybind[2] == "Internal":
                    if keybind[3] == "killFocusedWindow":
                        focusedWindow.destroy()
                        focusedWindow = None
                    if keybind[3] == "windowMoveLeft":
                        focusedWindow.configure(x=focusedWindow.get_geometry().x-5)
                    if keybind[3] == "windowMoveRight":
                        focusedWindow.configure(x=focusedWindow.get_geometry().x+5)
                    if keybind[3] == "windowMoveDown":
                        focusedWindow.configure(y=focusedWindow.get_geometry().y-5)
                    if keybind[3] == "windowMoveUp":
                        focusedWindow.configure(y=focusedWindow.get_geometry().y+5)
                    if keybind[3] == "raise":
                        focusedWindow.configure(stack_mode = X.Above)


def updateFocus():
    global focusedWindow
    win = root.query_pointer().child
    if (win != 0):
        focusedWindow = win

def main():
    createKeyBinds()
    while True:
        try:
            root.draw_text(gc, 5, 15, b"BasicWM ("+wmVer+b")")
            display.sync()
            updateFocus()
            if display.pending_events() > 0: 
                event = display.next_event()
                handleEvent(event)
            else:
                time.sleep(0.1) #Sleep to avoid 100% cpu usage, kinda jank but i dont know python well enough yet, submit a pr if u have a solution :(
        except:
            print("ERR")

if __name__ == "__main__":
        main()
