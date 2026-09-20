#include <stdint.h>

const char *szitbl[] = {
    "NOP",          // 00
    "RET",          // 01
    "",             // 02
    "",             // 03
    "",             // 04
    "",             // 05
    "",             // 06
    "",             // 07
    "CLR      RA",       // 08
    "SET      RA",       // 09
    "TMP      RA",       // 0A
    "",             // 0B
    "INC      RA",       // 0C
    "DEC      RA",       // 0D
    "",  // 0E
    "",  // 0F

    "PUSH     RA",  // 10
    "POP      RA",  // 11
    "MOV      RA",  // 12
    "",             // 13
    "AND      RA",  // 14
    "OR       RA",  // 15
    "XOR      RA",  // 16
    "CMP0     RA",  // 17
    "CMP1     RA",  // 18
    "",             // 19
    "SHR     RA",   // 1A
    "SHL     RA",   // 1B
    "",             // 1C
    "ADD      RA",  // 1D
    "",             // 1E
    "",             // 1F

    "INIT     RA, M8",  // 20
    "IN       RA, M8",  // 21
    "OUT      M8, RA",  // 22
    "",  // 23
    "",  // 24
    "",  // 25
    "",  // 26
    "",  // 27
    "",  // 28
    "",  // 29
    "RMEMA    RA, &M8",  // 2A
    "WMEMA    RA, &M8",  // 2B
    "",  // 2C
    "ADD	RA, M8",  // 2D
    "SUB	RA, M8",  // 2E
    "CMP    RA, M8",  // 2F

    "JE     ",  // 30
    "JNE    ",  // 31
    "JL     ",  // 32
    "JNL    ",  // 33
    "JB     ",  // 34
    "JNB    ",  // 35
    "JZ     ",  // 36
    "JNZ    ",  // 37
    "JSS0   ",  // 38
    "JSS1   ",  // 39
    "JOVER  ",  // 3A
    "JNOVER ",  // 3B
    "JPOS   ",  // 3C
    "JNEG   ",  // 3D
    "RJMP     L8",  // 3E
    "RCALL    L8",  // 3F

    "",                 // 40
    "",                 // 41
    "",                 // 42
    "",                 // 43
    "",                 // 44
    "",                 // 45
    "",                 // 46
    "",                 // 47
    "CLR      RB",      // 48
    "SET      RB",      // 49
    "TMP      RB",      // 4A
    "",                 // 4B
    "INC      RB",      // 4C
    "DEC      RB",      // 4D
    "",                 // 4E
    "",                 // 4F

    "PUSH     RB",      // 50
    "POP      RB",      // 51
    "MOV      RB",      // 52
    "",                 // 53
    "AND      RB",      // 54
    "OR       RB",      // 55
    "XOR      RB",      // 56
    "CMP0     RB",      // 57
    "CMP1     RB",      // 58
    "",                 // 59
    "SHR      RB",      // 5A
    "SHL      RB",      // 5B
    "",                 // 5C
    "ADD      RB",      // 5D
    "SUB      RB",      // 5E
    "CMP      RB",      // 5F


    "INIT     RB, M8",      // 60
    "IN       RB, M8",      // 61
    "OUT      M8, RB",      // 62
    "",                     // 63
    "",                     // 64
    "",                     // 65
    "",                     // 66
    "",                     // 67
    "",                     // 68
    "",                     // 69
    "RMEMA    RB, &M8",     // 6A
    "WMEMA    RB, &M8",     // 6B
    "",                     // 6C
    "ADD	RB, M8",        // 6D
    "SUB	RB, M8",        // 6E
    "CMP	RB, M8",        // 6F

    "",  // 70
    "",  // 71
    "",  // 72
    "",  // 73
    "",  // 74
    "",  // 75
    "",  // 76
    "",  // 77
    "",  // 78
    "",  // 79
    "",  // 7A
    "",  // 7B
    "",  // 7C
    "",  // 7D
    "",  // 7E
    "",  // 7F

    "",             // 80
    "",             // 81
    "",             // 82
    "",             // 83
    "",             // 84
    "",             // 85
    "",             // 86
    "",             // 87
    "CLR      RC",  // 88
    "SET      RC",  // 89
    "TMP      RC",  // 8A
    "",             // 8B
    "INC      RC",  // 8C
    "DEC      RC",  // 8D
    "",             // 8E
    "",             // 8F

    "PUSH     RC",  // 90
    "POP      RC",  // 91
    "MOV      RC",  // 92
    "",             // 93
    "AND      RC",  // 94
    "OR       RC",  // 95
    "XOR      RC",  // 96
    "CMP0     RC",  // 97
    "CMP1     RC",  // 98
    "",             // 99
    "SHR      RC",  // 9A
    "SHL      RC",  // 9B
    "",             // 9C
    "ADD      RC",  // 9D
    "SUB      RC",  // 9E
    "",             // 9F

    "INIT     RC, M8",  // A0
    "IN       RC, M8",  // A1
    "OUT      M8, RC",  // A2
    "",                 // A3
    "",                 // A4
    "",                 // A5
    "",                 // A6
    "",                 // A7
    "",                 // A8
    "",                 // A9
    "RMEMA    RC, &M8",   // AA
    "WMEMA    RC, &M8",   // AB
    "",                 // AC
    "ADD      RC, M8",    // AD
    "SUB      RC, M8",    // AE
    "CMP      RC, M8",    // AF

    "",  // B0
    "",  // B1
    "",  // B2
    "",  // B3
    "",  // B4
    "",  // B5
    "",  // B6
    "",  // B7
    "",  // B8
    "",  // B9
    "",  // BA
    "",  // BB
    "",  // BC
    "",  // BD
    "",  // BE
    "",  // BF

    "",             // C0
    "",             // C1
    "",             // C2
    "",             // C3
    "",             // C4
    "",             // C5
    "",             // C6
    "",             // C7
    "CLR      RD",  // C8
    "SET      RD",  // C9
    "TMP      RD",  // CA
    "",             // CB
    "INC      RD",  // CC
    "DEC      RD",  // CD
    "",             // CE
    "",             // CF

    "PUSH     RD",   // D0
    "POP      RD",   // D1
    "MOV      RD",   // D2
    "",              // D3
    "",              // D4
    "",              // D5
    "",              // D6
    "CMP0     RD",   // D7
    "CMP1     RD",   // D8
    "",              // D9
    "SHR      RD",   // DA
    "SHL      RD",   // DB
    "",              // DC
    "ADD      RD",   // DD
    "",              // DE
    "",              // DF

    "INIT     RD, M8",  // E0
    "IN       RD, M8",  // E1
    "OUT      M8, RD",  // E2
    "",  // E3
    "",  // E4
    "",  // E5
    "",  // E6
    "",  // E7
    "",  // E8
    "",  // E9
    "RMEMA   RD, &M8",  // EA
    "WMEMA   RD, &M8",  // EB
    "",                 // EC
    "ADD	 RD, M8",   // ED
    "SUB	 RD, M8",   // EE
    "CMP	 RD, M8",   // EF

    "",  // F0
    "",  // F1
    "",  // F2
    "",  // F3
    "",  // F4
    "",  // F5
    "",  // F6
    "",  // F7
    "",  // F8
    "",  // F9
    "",  // FA
    "",  // FB
    "",  // FC
    "",  // FD
    "LJMP     LBL",  // FE
    "LCALL    LBL"   // FF

};

