#include <stdio.h>
#include "constants.h"

void hotkey1() {
    printf("Hotkey 1 triggered\n");
}
void hotkey2() {
    printf("Hotkey 2 triggered\n");
}

KeyCodes keyCodes[2] = {
    {
        hotkey1,
        {(1 << KEY_A) | (1 << KEY_S), 0},
   (kCGEventFlagMaskShift)
    },
    {
        hotkey2,
        {(1 << KEY_A) | (1 << KEY_D), 0},
   (kCGEventFlagMaskShift)
    }
};