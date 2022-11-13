//
// Created by robin on 28.10.22.
//

#ifndef GAME_DEV_TEMPLATE_KEYBOARDKEY_H
#define GAME_DEV_TEMPLATE_KEYBOARDKEY_H

#include <cstdint>

namespace ggj
{
    // Based on the RayLib Keyboard keys (US keyboard layout)
    // NOTE: Use GetKeyPressed() to allow redefining
    // required keys for alternative layouts
    enum class KeyboardKey : int16_t
    {
        Null           = 0,        // Key: NULL, used for no key pressed
        // Alphanumeric keys
        Apostrophe     = 39,       // Key: '
        NoedicAe       = 39,       // Key: Æ | æ
        Comma          = 44,       // Key: ,
        Minus          = 45,       // Key: - | Nordic: +
        Period         = 46,       // Key: .
        Slash          = 47,       // Key: / | Nordic: -
        Zero           = 48,       // Key: 0
        One            = 49,       // Key: 1
        Two            = 50,       // Key: 2
        Three          = 51,       // Key: 3
        Four           = 52,       // Key: 4
        Five           = 53,       // Key: 5
        Six            = 54,       // Key: 6
        Seven          = 55,       // Key: 7
        Eight          = 56,       // Key: 8
        Nine           = 57,       // Key: 9
        Semicolon      = 59,       // Key: ;
        NordicOe       = 59,       // Key: Ø | ø
        Equal          = 61,       // Key: = | Nordic: '\'
        A              = 65,       // Key: A | a
        B              = 66,       // Key: B | b
        C              = 67,       // Key: C | c
        D              = 68,       // Key: D | d
        E              = 69,       // Key: E | e
        F              = 70,       // Key: F | f
        G              = 71,       // Key: G | g
        H              = 72,       // Key: H | h
        I              = 73,       // Key: I | i
        J              = 74,       // Key: J | j
        K              = 75,       // Key: K | k
        L              = 76,       // Key: L | l
        M              = 77,       // Key: M | m
        N              = 78,       // Key: N | n
        O              = 79,       // Key: O | o
        P              = 80,       // Key: P | p
        Q              = 81,       // Key: Q | q
        R              = 82,       // Key: R | r
        S              = 83,       // Key: S | s
        T              = 84,       // Key: T | t
        U              = 85,       // Key: U | u
        V              = 86,       // Key: V | v
        W              = 87,       // Key: W | w
        X              = 88,       // Key: X | x
        Y              = 89,       // Key: Y | y
        Z              = 90,       // Key: Z | z
        LeftBracket    = 91,       // Key: [
        NordicAa       = 91,       // Key: Å | å
        Backslash      = 92,       // Key: '\' | Nordic: '
        RightBracket   = 93,       // Key: ] | Modifier to produce signs like Ö | Ä | Ü on nordic keyboards
        Grave          = 96,       // Key: ` | Nordic: | (A.k.a pipe)
        NordicCrocodile= 161,      // Key - Nordic: <
        // Function keys
        Space          = 32,       // Key: Space
        Escape         = 256,      // Key: Esc
        Enter          = 257,      // Key: Enter
        Tab            = 258,      // Key: Tab
        Backspace      = 259,      // Key: Backspace
        Insert         = 260,      // Key: Ins
        Delete         = 261,      // Key: Del
        Right          = 262,      // Key: Cursor right
        Left           = 263,      // Key: Cursor left
        Down           = 264,      // Key: Cursor down
        Up             = 265,      // Key: Cursor up
        PageUp         = 266,      // Key: Page up
        PageDown       = 267,      // Key: Page down
        Home           = 268,      // Key: Home
        End            = 269,      // Key: End
        CapsLock       = 280,      // Key: Caps lock
        ScrollLock     = 281,      // Key: Scroll down
        NumLock        = 282,      // Key: Num lock
        PrintScreen    = 283,      // Key: Print screen
        Pause          = 284,      // Key: Pause
        F1             = 290,      // Key: F1
        F2             = 291,      // Key: F2
        F3             = 292,      // Key: F3
        F4             = 293,      // Key: F4
        F5             = 294,      // Key: F5
        F6             = 295,      // Key: F6
        F7             = 296,      // Key: F7
        F8             = 297,      // Key: F8
        F9             = 298,      // Key: F9
        F10            = 299,      // Key: F10
        F11            = 300,      // Key: F11
        F12            = 301,      // Key: F12
        LeftShift      = 340,      // Key: Shift left
        LeftControl    = 341,      // Key: Control left
        LeftAlt        = 342,      // Key: Alt left
        LeftSuper      = 343,      // Key: Super left
        RightShift     = 344,      // Key: Shift right
        RightControl   = 345,      // Key: Control right
        RightAlt       = 346,      // Key: Alt right
        RightSuper     = 347,      // Key: Super right
        KbMenu         = 348,      // Key: KB menu
        // Keypad keys
        Kp0            = 320,      // Key: Keypad 0
        Kp1            = 321,      // Key: Keypad 1
        Kp2            = 322,      // Key: Keypad 2
        Kp3            = 323,      // Key: Keypad 3
        Kp4            = 324,      // Key: Keypad 4
        Kp5            = 325,      // Key: Keypad 5
        Kp6            = 326,      // Key: Keypad 6
        Kp7            = 327,      // Key: Keypad 7
        Kp8            = 328,      // Key: Keypad 8
        Kp9            = 329,      // Key: Keypad 9
        KpDecimal      = 330,      // Key: Keypad .
        KpDivide       = 331,      // Key: Keypad /
        KpMultiply     = 332,      // Key: Keypad *
        KpSubtract     = 333,      // Key: Keypad -
        KpAdd          = 334,      // Key: Keypad +
        KpEnter        = 335,      // Key: Keypad Enter
        KpEqual        = 336,      // Key: Keypad =

        // Android key buttons
        Back           = 4,        // Key: Android back button
        Menu           = 82,       // Key: Android menu button
        VolumeUp       = 24,       // Key: Android volume up button
        VolumeDown     = 25        // Key: Android volume down button
    };
}

#endif //GAME_DEV_TEMPLATE_KEYBOARDKEY_H
