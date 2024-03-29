#include "defines.h"

#define STAR_IX 0xD0
#define STAR_SZ 0x10

const uint16_t sprite_ix[] = {
  0, 0x20, 0x30, 0xB0, 0x10, 0x08, 0x18, 0};

const uint8_t sprites[] PROGMEM = {
// Floor  width: 8 height: 8
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// BoxOnTarget.png  width: 8 height: 8
0xff,0x81,0xa5,0x99,0x99,0xa5,0x81,0xff,
// Box.png  width: 8 height: 8
0xff,0x81,0x81,0x81,0x81,0x81,0x81,0xff,
// Target.png  width: 8 height: 8
0x00,0x00,0x24,0x18,0x18,0x24,0x00,0x00,
// WallH.png  width: 8 height: 8
0xe5,0xa5,0xbd,0xa7,0xe5,0xa5,0xbd,0xa7,
// WallV.png  width: 8 height: 8
0xff,0x11,0xff,0x44,0x44,0xff,0x88,0xff,

// Index 0x30;
// WorkerDown0.png  width: 8 height: 8
0x00,0x10,0x20,0x37,0xfc,0x37,0x20,0x10,
// WorkerDown1.png  width: 8 height: 8
0x00,0x10,0x20,0x36,0xfc,0x37,0x20,0x10,
// WorkerDown2.png  width: 8 height: 8
0x00,0x10,0x20,0x37,0xfc,0x37,0x20,0x10,
// WorkerDown3.png  width: 8 height: 8
0x00,0x10,0x20,0x37,0xfc,0x36,0x20,0x10,
// WorkerLeft0.png  width: 8 height: 8
0x10,0x10,0x7c,0xba,0x10,0x38,0x28,0x28,
// WorkerLeft1.png  width: 8 height: 8
0x10,0x10,0x7c,0xba,0x10,0x38,0x28,0x20,
// WorkerLeft2.png  width: 8 height: 8
0x10,0x10,0x7c,0xba,0x10,0x38,0x28,0x28,
// WorkerLeft3.png  width: 8 height: 8
0x10,0x10,0x7c,0xba,0x10,0x38,0x28,0x08,
// WorkerRight0.png  width: 8 height: 8
0x14,0x14,0x1c,0x08,0x5d,0x3e,0x08,0x08,
// WorkerRight1.png  width: 8 height: 8
0x04,0x14,0x1c,0x08,0x5d,0x3e,0x08,0x08,
// WorkerRight2.png  width: 8 height: 8
0x14,0x14,0x1c,0x08,0x5d,0x3e,0x08,0x08,
// WorkerRight3.png  width: 8 height: 8
0x10,0x14,0x1c,0x08,0x5d,0x3e,0x08,0x08,
// WorkerUp0.png  width: 8 height: 8
0x08,0x04,0xec,0x3f,0xec,0x04,0x08,0x00,
// WorkerUp1.png  width: 8 height: 8
0x08,0x04,0xec,0x3f,0x6c,0x04,0x08,0x00,
// WorkerUp2.png  width: 8 height: 8
0x08,0x04,0xec,0x3f,0xec,0x04,0x08,0x00,
// WorkerUp3.png  width: 8 height: 8
0x08,0x04,0x6c,0x3f,0xec,0x04,0x08,0x00,

// Index 0xB0
// WorkerDownOnTarget.png  width: 8 height: 8
0x00,0x00,0x10,0x27,0xdc,0x27,0x10,0x00,
// WorkerLeftOnTarget.png  width: 8 height: 8
0x10,0x10,0x28,0x54,0x10,0x38,0x28,0x28,
// WorkerRightOnTarget.png  width: 8 height: 8
0x14,0x14,0x1c,0x08,0x2a,0x14,0x08,0x08,
// WorkerUpOnTarget.png  width: 8 height: 8
0x00,0x08,0xe4,0x3b,0xe4,0x08,0x00,0x00,

// Index 0xD0
// StarEmpty.png  width: 16 height: 16
0x40,0xc0,0xc0,0x40,0x40,0x20,0x3c,0x07,
0x3c,0x20,0x40,0x40,0xc0,0xc0,0x40,0x00,
0x00,0x00,0x00,0x61,0x39,0x16,0x08,0x04,
0x08,0x16,0x39,0x61,0x00,0x00,0x00,0x00,
// StarFull.png  width: 16 height: 16
0x40,0xc0,0xc0,0xc0,0xc0,0xe0,0xfc,0xff,
0xfc,0xe0,0xc0,0xc0,0xc0,0xc0,0x40,0x00,
0x00,0x00,0x00,0x61,0x39,0x1f,0x0f,0x07,
0x0f,0x1f,0x39,0x61,0x00,0x00,0x00,0x00
};
