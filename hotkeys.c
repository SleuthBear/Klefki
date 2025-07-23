#include <stdio.h>
#include "constants.h"

void hotkey1() {
    printf("Redirecting to CLion\n");
    system("open /Applications/CLion.app");
}
void hotkey2() {
    printf("Redirecting to LibreWolf\n");
    system("open /Application/LibreWolf.app");
}

KeyCodes keyCodes[2] = {
    {
        hotkey1,
        {(1 << KEY_C) | (1 << KEY_L), 0},
   (kCGEventFlagMaskShift)
    },
    {
        hotkey2,
        {(1 << KEY_B), 0},
   (kCGEventFlagMaskShift)
    }
};