#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <CoreGraphics/CoreGraphics.h>
#include <CoreFoundation/CoreFoundation.h>

#define RING_SIZE 5
#define NULL_KEY 127


typedef struct {
    int keyBuf[RING_SIZE];
    CGEventFlags flags;
    int count;
} KeyRing;

typedef struct {
    void (*func)(void);
    int code[RING_SIZE];
    CGEventFlags flags;
} KeyCodes;

// Keycode definitions
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_F 3
#define KEY_H 4
#define KEY_G 5
#define KEY_Z 6
#define KEY_X 7
#define KEY_C 8
#define KEY_V 9
#define KEY_B 11
#define KEY_Q 12
#define KEY_W 13
#define KEY_E 14
#define KEY_R 15
#define KEY_Y 16
#define KEY_T 17
#define KEY_1 18
#define KEY_2 19
#define KEY_3 20
#define KEY_4 21
#define KEY_6 22
#define KEY_5 23
#define KEY_EQUAL 24
#define KEY_9 25
#define KEY_7 26
#define KEY_MINUS 27
#define KEY_8 28
#define KEY_0 29
#define KEY_RIGHT_BRACKET 30
#define KEY_O 31
#define KEY_U 32
#define KEY_LEFT_BRACKET 33
#define KEY_I 34
#define KEY_P 35
#define KEY_RETURN 36
#define KEY_L 37
#define KEY_J 38
#define KEY_QUOTE 39
#define KEY_K 40
#define KEY_SEMICOLON 41
#define KEY_BACKSLASH 42
#define KEY_COMMA 43
#define KEY_SLASH 44
#define KEY_N 45
#define KEY_M 46
#define KEY_PERIOD 47
#define KEY_TAB 48
#define KEY_SPACE 49
#define KEY_GRAVE 50
#define KEY_DELETE 51
#define KEY_ESCAPE 53
#define KEY_RIGHT_COMMAND 54
#define KEY_LEFT_COMMAND 55
#define KEY_LEFT_SHIFT 56
#define KEY_CAPS_LOCK 57
#define KEY_LEFT_OPTION 58
#define KEY_LEFT_CONTROL 59
#define KEY_RIGHT_SHIFT 60
#define KEY_RIGHT_OPTION 61
#define KEY_RIGHT_CONTROL 62
#define KEY_FUNCTION 63
#define KEY_F17 64
#define KEY_KEYPAD_PERIOD 65
#define KEY_KEYPAD_MULTIPLY 67
#define KEY_KEYPAD_PLUS 69
#define KEY_KEYPAD_CLEAR 71
#define KEY_KEYPAD_DIVIDE 75
#define KEY_KEYPAD_ENTER 76
#define KEY_KEYPAD_MINUS 78
#define KEY_KEYPAD_EQUAL 81
#define KEY_KEYPAD_0 82
#define KEY_KEYPAD_1 83
#define KEY_KEYPAD_2 84
#define KEY_KEYPAD_3 85
#define KEY_KEYPAD_4 86
#define KEY_KEYPAD_5 87
#define KEY_KEYPAD_6 88
#define KEY_KEYPAD_7 89
#define KEY_KEYPAD_8 91
#define KEY_KEYPAD_9 92
#define KEY_F5 96
#define KEY_F6 97
#define KEY_F7 98
#define KEY_F3 99
#define KEY_F8 100
#define KEY_F9 101
#define KEY_F11 103
#define KEY_F13 105
#define KEY_F16 106
#define KEY_F14 107
#define KEY_F10 109
#define KEY_F12 111
#define KEY_F15 113
#define KEY_HELP 114
#define KEY_HOME 115
#define KEY_PAGE_UP 116
#define KEY_FORWARD_DELETE 117
#define KEY_F4 118
#define KEY_END 119
#define KEY_F2 120
#define KEY_PAGE_DOWN 121
#define KEY_F1 122
#define KEY_LEFT_ARROW 123
#define KEY_RIGHT_ARROW 124
#define KEY_DOWN_ARROW 125
#define KEY_UP_ARROW 126
#endif //CONSTANTS_H
