#include <stdio.h>
#include "constants.h"
#include "klefkiAscii.h"

extern KeyCodes keyCodes[2];

long long* mask(long long mask[MASK_SIZE], int code) {
    int section = code / (sizeof(long long) * 8);
    int position = code % (sizeof(long long) * 8);
    mask[section] = mask[section] | (1 << position);
    return mask;
}

long long* unmask(long long mask[MASK_SIZE], int code) {
    int section = code / (sizeof(long long) * 8);
    int position = code % (sizeof(long long) * 8);
    mask[section] = mask[section] & ~(1 << position);
    return mask;
}

int comp(const void *a, const void *b) {
    return (*(int *)a) - (*(int *)b);
}

bool maskMatch(long long keyMask[MASK_SIZE], long long codeMask[MASK_SIZE]) {
   for(size_t i = 0; i < MASK_SIZE; i++) {
       if ((codeMask[i] & keyMask[i]) != codeMask[i]) {
           return false;
       }
   }
    return true;
}

void checkHotkeys(KeyRing *keyRing) {
    // Go through each hotkey
    for (size_t i = 0; i < sizeof(keyCodes) / sizeof(keyCodes[0]); i++) {
        // If the flag mask contains all the necessary keys
        if ((keyRing->flags & keyCodes[i].flags) != keyCodes[i].flags) continue;
        if (maskMatch(keyRing->keyMask, keyCodes[i].codeMask)) {
            keyCodes[i].func();
            // Only execute 1 hotkey at a time
            return;
        }
    }
    return;
}

CGEventRef eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* refcon) {
    KeyRing *keyRing = (KeyRing*)refcon;
    if (type == kCGEventKeyDown) {
        CGKeyCode keyCode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
        // set the bit
        mask(keyRing->keyMask, (int)keyCode);
        checkHotkeys(keyRing);
    } else if (type == kCGEventKeyUp) {
        CGKeyCode keyCode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
        // unset the bit
        unmask(keyRing->keyMask, (int)keyCode);
    } else if (type == kCGEventFlagsChanged) {
        keyRing->flags = CGEventGetFlags(event);
        checkHotkeys(keyRing);
    }
    return event;
}

int main(void) {
    KeyRing keyRing = {0, 0, 0};
    CGEventMask eventMask = (1 << kCGEventKeyDown | 1 << kCGEventKeyUp | 1 << kCGEventFlagsChanged);
    CFMachPortRef eventTap = CGEventTapCreate(
        kCGSessionEventTap,
        kCGHeadInsertEventTap,
        kCGEventTapOptionDefault,
        eventMask,
        eventCallback,
        &keyRing
        );

    if (!eventTap) {
        fprintf(stderr, "Failed to create event tap");
        return 1;
    }

    printf("%s", klefkiAscii);
    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(eventTap, true);
    CFRunLoopRun();

    return 0;
}