#pragma once
#include <stdint.h>

/* Insert 24 random results here (1..24)
 * uint16_t: deciseconds to succeed level (can deduce stars from that).
 */
const uint16_t Results[] = {
0X0019,0X003B,0X0050,0X0065,0X0A8D,0X0E0F,0X1000,0X176F,
0X30D2,0X27A2,0X1463,0X09D9,0X2738,0X3142,0X077E,0X241E,
0X353E,0X3205,0X37C1,0X0215,0X18A7,0X1245,0X1365,0X3E89,
0X1763,0X1719,0X1D4F,0X1DA2,0X1288,0X244A,0X21FB,0X06DC,
0X12B1,0X21AE,0X0DE0,0X2D9C,0X23FD,0X096D,0X2491,0X07DC,
0X2536,0X270D,0X0E42,0X1505,0X2A37,0X0C6D,0X26DE,0X1D96,
0X11B8,0X0990,0X1C51,0X0F27,0X20B4,0X1FFC,0X2074,0X2F37,
0X26D6,0X1F5C,0X26E3,0X012C,0X2A9B,0X221B,0X1ECD,0X256A,
0X0860,0X025D,0X1020,0X09E3,0X2F18,0X1402,0X2C8A,0X125F,
0X279C,0X0F58,0X2DE1,0X03B6,0X25C0,0X2649,0X208B,0X15C8,
0X104A,0X1067,0X1723,0X0F3A,0X003B,0X1593,0X1618,0X2687,
0X05A1,0X17A1,0X25DC,0X0FC0,0X0866,0X2CB8,0X103C,0X2713,
0X04FA,0X165A,0X0095,0X2955,0X2645,0X03C3,0X1057,0X1250,
0X0264,0X1860,0X1363,0X2033,0X1EAD,0X108B,0X079A,0X0960,
0X1B09,0X09F1,0X0782,0X09DE,0X259E,0X0726,0X2B11,0X1A28,
0X1CE6,0X0DB6,0X1BD8,0X181E,0X2D1F,0X0587,0X1116,0X1520,
0X1C27,0X1B14,0X2E31,0X10A2,0X2C1D,0X0F5B,0X2DCD,0X2752,
0X0E61,0X1E94,0X0E44,0X1D7E,0X2A93,0X0FE8,0X1393,0X260D,
0X24A9,0X1046,0X096D,0X0431,0X17AE,0X2851,0X0A06,0X23D1,
0X24E6,0X18BE,0X11B6,0X21B4,0X2022,0X0970,0X0CC5,0X1FB0,
0X07CB,0X29D4,0X0702,0X2FE7,0X1C1F,0X0BAA,0X27A6,0X27EB,
0X16A2,0X2279,0X2528,0X0EB6,0X020B,0X1184,0X2CBB,0X0009,
0X01BE,0X2AD9,0X15F7,0X200A,0X1A5D,0X214F,0X12F0,0X1808,
0X2A9A,0X0B46,0X17E4,0X1593,0X05DD,0X0BF8,0X0D54,0X299B,
0X2365,0X04BD,0X2545,0X1667,0X1F70,0X1612,0X12A3,0X2B6D,
0X0873,0X1484,0X2C6B,0X1781,0X1711,0X17D8,0X1F4F,0X2B53,
0X0D25,0X1044,0X1106,0X08A4,0X04EE,0X0179,0X28BA,0X2A9F,
0X0967,0X0970,0X211A,0X2B67,0X1C96,0X0DE7,0X22DB,0X270B,
0X2A0D,0X11A4,0X17DB,0X1ACD,0X18BB,0X1572,0X09D5,0X0533,
0X05E6,0X16EF,0X007C,0X0EDC,0X0BC3,0X0E88,0X0AAC,0X2143,
0X1413,0X07E4,0X1CB2,0X082A,0X0774,0X05FB,0X01E5,0X2EC1,
0X2D3F,0X17FE,0X1197,0X0124,0X1E27,0X1249,0X1FC7,0X0D3D,
0X2200,0X0817,0X12CF,0X2BB9,0X1AED,0X0BFF,0X0E3E,0X0CB9,
0X13ED,0X16F2,0X27A8,0X1ACB,0X172E,0X2691,0X1BAD,0X1532,
0X15BB,0X1662,0X0B33,0X10CE,0X24DB,0X1B6D,0X200F,0X02DD,
0X148A,0X2C4A,0X0204,0X06B9,0X2FD7,0X0E03,0X1D03,0X091A,
0X2A31,0X1462,0X266D,0X2BFC,0X0F1F,0X21D2,0X1FF3,0X1584,
0X0A0B,0X10B8,0X178F,0X0497,0X1A60,0X24D2,0X0CCF,0X1C89,
0X27CD,0X23B6,0X2314,0X2487,0X0F1C,0X0C60,0X06CE,0X082F,
0X167F,0X02BF,0X1409,0X2B9E,0X24D1,0X22C5,0X244B,0X25A8,
0X042B,0X14C5,0X2C45,0X29AE,0X2441,0X2901,0X2878,0X14D3,
0X169B,0X2705,0X18FC,0X02E1,0X07F9,0X1E8B,0X0E93,0X2843,
0X0F28,0X0899,0X1DAD,0X1ABC,0X0A96,0X15E1,0X04B1,0X2AAF,
0X1B0E,0X132F,0X2AFC,0X0BE1,0X28B5,0X054F,0X0B77,0X1780,
0X2FD9,0X1482,0X0A65,0X1D03,0X1D4C,0X0563,0X1E54,0X085B,
0X116E,0X2A12,0X2021,0X0525,0X094B,0X2773,0X2AFA,0X092B,
0X1F4C,0X0EBE,0X171D,0X1B75,0X19E5,0X294A,0X1B30,0X0E7E,
0X1E96,0X1B9F,0X0B6A,0X1181,0X0025,0X2E90,0X2D56,0X28F0,
0X104B,0X0FF8,0X2D95,0X238F,0X193A,0X29AD,0X2108,0X2F3C,
0X17CA,0X2074,0X1331,0X1265,0X0D13,0X1984,0X297A,0X011E,
0X02F9,0X2413,0X2AA2,0X1A1C,0X234E,0X0CAF,0X0E87,0X20D1,
0X2314,0X05D1,0X16F1,0X2A44,0X1B8E,0X246B,0X0719,0X265E,
0X2167,0X22AF,0X2A49,0X2CA7,0X1B6B,0X0919,0X014E,0X07FE,
0X2D0E,0X2905,0X21B1,0X1143,0X17D5,0X1628,0X1422,0X1E34,
0X139A,0X1587,0X2264,0X2722,0X187D,0X1798,0X1E42,0X1B46,
0X220E,0X0330,0X2E1B,0X166E,0X0B65,0X27DF,0X273B,0X15D8,
0X01FA,0X20AD,0X11FA,0X2C2C,0X1325,0X2C3F,0X068F,0X28B8,
0X2CE3,0X215E,0X2998,0X2F90,0X0CDC,0X20A3,0X13BF,0X03D8,
0X2467,0X2530,0X16CE,0X1D20,0X092D,0X1A59,0X2B91,0X1A83,
0X2B13,0X2640,0X1038,0X2F52,0X1209,0X2F73,0X2C1E,0X2EFD,
0X2897,0X21AB,0X07D4,0X1426,0X1288,0X20DE,0X27F8,0X1F0C,
0X2D49,0X1A44,0X0C61,0X1B5E,0X0BCD,0X2812,0X057C,0X047D,
0X0F15,0X1829,0X2701,0X0F45,0X2F64,0X28F9,0X0B3B,0X1675,
0X0631,0X2663,0X267E,0X1EF6,0X246E,0X2C17,0X03B6,0X01C7,
};

// vim:ft=cpp