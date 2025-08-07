#include <stdio.h>
#include "constants.h"
#include <stdlib.h>

void hotkey1() {
    printf("Redirecting to CLion\n");
    system("open /Applications/CLion.app");
}
void hotkey2() {
    printf("Redirecting to LibreWolf\n");
    system("open /Applications/LibreWolf.app");
}

KeyCodes keyCodes[2] = {
    {
        hotkey1,
        {((long long)1 << KEY_L), 0},
   (kCGEventFlagMaskShift | kCGEventFlagMaskCommand)
    },
    {
        hotkey2,
        {(1 << KEY_B), 0},
   (kCGEventFlagMaskShift | kCGEventFlagMaskCommand)
    }
};