#include <stdio.h>
#include "constants.h"
#include "klefkiAscii.h"

extern KeyCodes keyCodes[2];

int comp(const void *a, const void *b) {
    return (*(int *)a) - (*(int *)b);
}

// This algorithm sucks.
bool scanKeys(int code[RING_SIZE], int buf[RING_SIZE], int bufSize) {
    int codePos = 0;
    int bufPos = 0;
    while(bufPos + codePos < bufSize) {
        // We are at the end of the code
        if (code[codePos] == NULL_KEY) return true;
        // Match. Move code up by 1.
        if (code[codePos] == buf[bufPos + codePos]) {
            codePos++;
        // Don't match. reset the code and move the buffer up 1.
        } else {
            codePos = 0;
            bufPos++;
        }
    }
    // If the code isn't finished, then we have run out of buffered keys.
    return (code[codePos] == NULL_KEY);
}

void checkHotkeys(KeyRing *keyRing) {
    // copy the buffer, then sort
    int sBuf[RING_SIZE];
    memcpy(sBuf, keyRing->keyBuf, sizeof(keyRing->keyBuf));
    qsort(sBuf, sizeof(sBuf)/sizeof(sBuf[0]), sizeof(int), comp);
    // Go through each hotkey
    for (size_t i = 0; i < sizeof(keyCodes) / sizeof(keyCodes[0]); i++) {
        // If the flag mask contains all the necessary keys
        if (keyRing->flags & keyCodes[i].flags == keyCodes[i].flags) continue;
        // TODO massive bitmask. It will be sick as hell.
        if (scanKeys(keyCodes[i].code, sBuf, keyRing->count)) {
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
        for(int i = 0; i < RING_SIZE; i++) {
            if (keyRing->keyBuf[i] == keyCode) {
                return event;
            }
        }
        if (keyRing->count >= RING_SIZE) {
            keyRing->keyBuf[0] = keyCode;
            return event;
        }
        for(size_t i = 0; i < RING_SIZE; i++) {
            if (keyRing->keyBuf[i] == NULL_KEY) {
                keyRing->keyBuf[i] = keyCode;
                keyRing->count++;
                break;
            }
        }
        checkHotkeys(keyRing);
    } else if (type == kCGEventKeyUp) {
        CGKeyCode keyCode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
        for(size_t i = 0; i < RING_SIZE; i++) {
            if (keyRing->keyBuf[i] == keyCode) {
                keyRing->keyBuf[i] = NULL_KEY;
                keyRing->count--;
                break;
            }
        }
    } else if (type == kCGEventFlagsChanged) {
        keyRing->flags = CGEventGetFlags(event);
        checkHotkeys(keyRing);
    }
    return event;
}

int main(void) {
    KeyRing keyRing = {{}, 0, 0};
    for(size_t i=0; i < RING_SIZE; i++) keyRing.keyBuf[i] = NULL_KEY;
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