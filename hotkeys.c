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
        {KEY_A, KEY_S, NULL_KEY, NULL_KEY, NULL_KEY},
   (kCGEventFlagMaskShift)
    },
    {
        hotkey2,
    {KEY_A, KEY_D, NULL_KEY, NULL_KEY, NULL_KEY},
   (kCGEventFlagMaskShift)
    }

};