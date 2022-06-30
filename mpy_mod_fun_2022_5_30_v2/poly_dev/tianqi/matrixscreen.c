#include "matrixscreen.h"
#include "hi_io.h"
hi_u8  Din_num = 3;
hi_u8  Cs_num  = 1;
hi_u8  Clk_num = 4;

hi_bool enable = HI_FALSE;
/************************************6*8的点阵************************************/
static unsigned char FM6x8[][6] =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // sp  0
    { 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 }, // !   1
    { 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 }, // "   2
    { 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 }, // #   3
    { 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 }, // $   4
    { 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 }, // %  
    { 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 }, // &
    { 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 }, // '
    { 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 }, // (
    { 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 }, // )
    { 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 }, // *
    { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 }, // +
    { 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 }, // ,
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 }, // -
    { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 }, // .
    { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 }, // /
    { 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E }, // 0
    { 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 }, // 1
    { 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 }, // 2
    { 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 }, // 3
    { 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 }, // 4
    { 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 }, // 5
    { 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 }, // 6
    { 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 }, // 7
    { 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 }, // 8
    { 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E }, // 9
    { 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 }, // :
    { 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 }, // ;
    { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 }, // <
    { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 }, // =
    { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 }, // >
    { 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 }, // ?
    { 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E }, // @
    { 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C }, // A
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 }, // B
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 }, // C
    { 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C }, // D
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 }, // E
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 }, // F
    { 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A }, // G
    { 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F }, // H
    { 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 }, // I
    { 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 }, // J
    { 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 }, // K
    { 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 }, // L
    { 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F }, // M
    { 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F }, // N
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E }, // O
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 }, // P
    { 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E }, // Q
    { 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 }, // R
    { 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 }, // S
    { 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 }, // T
    { 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F }, // U
    { 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F }, // V
    { 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F }, // W
    { 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 }, // X
    { 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 }, // Y
    { 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 }, // Z
    { 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 }, // [
    { 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 }, // 55
    { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 }, // ]
    { 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 }, // ^
    { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 }, // _
    { 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 }, // '
    { 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 }, // a
    { 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 }, // b
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 }, // c
    { 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F }, // d
    { 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 }, // e
    { 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 }, // f
    { 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C }, // g
    { 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 }, // h
    { 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 }, // i
    { 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 }, // j
    { 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 }, // k
    { 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 }, // l
    { 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 }, // m
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 }, // n
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 }, // o
    { 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 }, // p
    { 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC }, // q
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 }, // r
    { 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 }, // s
    { 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 }, // t
    { 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C }, // u
    { 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C }, // v
    { 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C }, // w
    { 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 }, // x
    { 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C }, // y
    { 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 }, // z
    { 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }, // horiz lines
    
};

hi_u8  disp1[38][8]={
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//0
{0x10,0x18,0x14,0x10,0x10,0x10,0x10,0x10},//1
{0x7E,0x2,0x2,0x7E,0x40,0x40,0x40,0x7E},//2
{0x3E,0x2,0x2,0x3E,0x2,0x2,0x3E,0x0},//3
{0x8,0x18,0x28,0x48,0xFE,0x8,0x8,0x8},//4
{0x3C,0x20,0x20,0x3C,0x4,0x4,0x3C,0x0},//5
{0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x0},//6
{0x3E,0x22,0x4,0x8,0x8,0x8,0x8,0x8},//7
{0x0,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},//8
{0x3E,0x22,0x22,0x3E,0x2,0x2,0x2,0x3E},//9
{0x8,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},//A
{0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x0},//B
{0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x0},//C
{0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x0},//D
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},//F
{0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//G
{0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},//H
{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
{0x3C,0x8,0x8,0x8,0x8,0x8,0x48,0x30},//J
{0x0,0x24,0x28,0x30,0x20,0x30,0x28,0x24},//K
{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},//L
{0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},//M
{0x0,0x42,0x62,0x52,0x4A,0x46,0x42,0x0},//N
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
{0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},//P
{0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},//Q
{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
{0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},//S
{0x0,0x3E,0x8,0x8,0x8,0x8,0x8,0x8},//T
{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
{0x0,0x49,0x49,0x49,0x49,0x2A,0x1C,0x0},//W
{0x0,0x41,0x22,0x14,0x8,0x14,0x22,0x41},//X
{0x41,0x22,0x14,0x8,0x8,0x8,0x8,0x8},//Y
{0x0,0x7F,0x2,0x4,0x8,0x10,0x20,0x7F},//Z 
{0x8,0x7F,0x49,0x49,0x7F,0x8,0x8,0x8},//ÖÐ
{0xFE,0xBA,0x92,0xBA,0x92,0x9A,0xBA,0xFE},//¹ú
};

hi_u8 screen_array_state[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};



static hi_u8 pic[][7] = {
   {0x36,0x49,0x41,0x41,0x22,0x1C,0x08},//{0x00,0x12,0x2D,0x21,0x1E,0x0C,0x00};
   {0x00,0x14,0x2A,0x22,0x14,0x08,0x00},
};



static hi_u8 matrix_state[6] = {
   {0x00,0x00,0x00,0x00,0x00,0x00,0x00},//{0x00,0x12,0x2D,0x21,0x1E,0x0C,0x00};
};




unsigned short const font2[96][9] = { 
		{ 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // 0x20, Space
        { 0x07, 0,16,16,16,0,16 },   // 0x21, !
        { 0x07, 20,20,0,0,0,0 },   // 0x22, "
        { 0x07, 0,20,62,20,62,20 },   // 0x23, #
        { 0x07, 0,28,50,28,38,28 },   // 0x24, $
        { 0x07, 0,50,36,8,18,38 },   // 0x25, %
        { 0x07, 0,48,72,48,72,52 },   // 0x26, &
        { 0x07, 16,16,0,0,0,0 },   // 0x27, '
        { 0x07, 0,8,16,16,16,8 },   // 0x28, (
        { 0x07, 0,8,4,4,4,8 },   // 0x29, )
        { 0x07, 0,0,36,24,24,36 },   // 0x2a, *
        { 0x07, 0,16,16,124,16,16 },   // 0x2b, +
        { 0x04, 0,0,0,16,16,32 },   // 0x2c, ,
        { 0x07, 0,0,0,60,0,0 },   // 0x2d, -
        { 0x04, 0,0,0,48,16,0 },   // 0x2e, .
        { 0x07, 2,4,8,16,32,64 },   // 0x2f, /
        { 0x07, 28,34,34,34,34,28 },   // 0x30, 0
        { 0x07, 8,24,8,8,8,28 },   // 0x31, 1
        { 0x07, 28,34,2,12,16,62 },   // 0x32, 2
        { 0x07, 60,4,8,4,36,24 },   // 0x33, 3
        { 0x07, 0x08,0x18,0x28,0x48,0xFE,0x08,0x08 },   // 0x34, 4
        { 0x07, 0x00,0xE4,0x22,0x22,0x22,0x1C,0x00 },   // 0x35, 5
        { 0x07, 0x00,0xFC,0x22,0x22,0x22,0x9C,0x00 },   // 0x36, 6
        { 0x07, 0x00,0x80,0x00,0x1E,0x60,0x80,0x00 },   // 0x37, 7
        { 0x07, 0x00,0xDC,0x22,0x12,0x32,0xCC,0x00 },   // 0x38, 8
        { 0x07, 0x00,0xF6,0x12,0x12,0x12,0xFC,0x00 },   // 0x39, 9
        { 0x04, 0x00,0x00,0x00,0x22,0x00,0x00,0x00 },   // 0x3a, :
        { 0x07, 0x00,0x00,0x00,0x23,0x00,0x00,0x00 },   // 0x3b, ;
        { 0x07, 0x00,0x30,0x28,0x48,0x84,0x02,0x00 },   // 0x3c, <
        { 0x04, 0x00,0x30,0x30,0x30,0x30,0x30,0x00 },   // 0x3d, =
        { 0x07, 0x00,0x02,0x84,0x48,0x28,0x30,0x00 },   // 0x3e, >
        { 0x07, 0x00,0xC0,0x00,0x1A,0x20,0xE0,0x00 },   // 0x3f, ?
        { 0x07, 0x00,0xFC,0x3A,0x4A,0x7A,0x8A,0x74 },   // 0x40, @
        { 0x07, 0x00,0x1E,0x70,0x90,0x78,0x06,0x00 },   // 0x41, A
        { 0x07, 0x00,0xFE,0x22,0x22,0x22,0xDC,0x00 },   // 0x42, B
        { 0x07, 0x30,0xEC,0x02,0x02,0x02,0x82,0x04 },   // 0x43, C
        { 0x07, 0x00,0xFE,0x02,0x02,0x82,0xFC,0x00 },   // 0x44, D
        { 0x07, 0x00,0xFE,0x22,0x22,0x22,0x02,0x04 },   // 0x45, E
        { 0x07, 0x00,0xFE,0x20,0x20,0x20,0x00,0x80 },   // 0x46, F
        { 0x07, 0x30,0xCC,0x02,0x02,0x02,0x8C,0x00 },   // 0x37, G
        { 0x07, 0x00,0xFE,0x20,0x20,0x20,0xFE,0x00 },   // 0x48, H
        { 0x07, 0x00,0x00,0x02,0xFE,0x02,0x00,0x00 },   // 0x49, I
        { 0x07, 0x00,0x01,0x01,0x01,0xFE,0x00,0x00 },   // 0x4a, J
        { 0x07, 0x00,0xFE,0x20,0x70,0x8C,0x02,0x00 },   // 0x4b, K
        { 0x07, 0x00,0xFE,0x02,0x02,0x02,0x02,0x04 },   // 0x4c, L
        { 0x07, 0x3C,0xC2,0x38,0x0C,0x70,0xFE,0x00 },   // 0x4d, M
        { 0x07, 0x00,0xFE,0x40,0x30,0x08,0xFE,0x00 },   // 0x4e, N
        { 0x07, 0x00,0xFC,0x02,0x02,0x02,0xCC,0x30 },   // 0x4f, O
        { 0x07, 0x00,0xFE,0x10,0x10,0x10,0xE0,0x00 },   // 0x50, P
        { 0x07, 0x30,0xEC,0x0A,0x0A,0x06,0xCD,0x30 },   // 0x51, Q
        { 0x07, 0x00,0xFE,0x10,0x10,0x28,0xE6,0x00 },   // 0x52, R
        { 0x07, 0x00,0xE2,0x22,0x12,0x12,0x8C,0x00 },   // 0x53, S
        { 0x07, 0x80,0x00,0x00,0xFE,0x00,0x00,0x80 },   // 0x54, T
        { 0x07, 0x00,0xFC,0x02,0x02,0x02,0xFC,0x00 },   // 0x55, U
        { 0x07, 0x00,0xC0,0x38,0x06,0x38,0xC0,0x00 },   // 0x56, V
        { 0x07, 0x00,0xF0,0x1C,0xE0,0x1E,0xE0,0x00 },   // 0x57, W
        { 0x07, 0x00,0x02,0xCC,0x30,0x4C,0x82,0x00 },   // 0x58, X
        { 0x07, 0x00,0x80,0x60,0x1E,0x60,0x80,0x00 },   // 0x59, Y
        { 0x07, 0x00,0x86,0x0A,0x32,0x42,0x82,0x00 },   // 0x5a, Z
        { 0x07, 0x00,0x00,0x00,0xFF,0x01,0x01,0x00 },   // 0x5b, [
        { 0x07, 0x00,0x00,0xC0,0x30,0x0C,0x03,0x00 },   // 0x5c, '\'
        { 0x07, 0x00,0x01,0x01,0xFF,0x00,0x00,0x00 },   // 0x5d, ]
        { 0x07, 0x00,0x00,0x00,0x00,0x00,0x00,0x00 },   // 0x5e, ^
        { 0x07, 0x00,0x00,0x00,0x00,0x00,0x00,0x00 },   // 0x5f, _
        { 0x07, 0x00,0x00,0x00,0x00,0x00,0x00,0x00 },   // 0x60, `
        { 0x07, 0,0,56,72,72,60 },   // 0x61, a
        { 0x07, 0x00,0xFE,0x22,0x22,0x22,0x3C,0x00 },   // 0x62, b
        { 0x07, 0x00,0x1C,0x22,0x22,0x22,0x32,0x00 },   // 0x63, c
        { 0x07, 0x00,0x1C,0x22,0x22,0x22,0xFE,0x02 },   // 0x64, d
        { 0x07, 0x00,0x1C,0x2A,0x2A,0x2A,0x12,0x00 },   // 0x65, e
        { 0x07, 0x00,0x00,0xFE,0x22,0x20,0x00,0x80 },   // 0x66, f
        { 0x07, 0x00,0x1F,0x2B,0x2B,0x2B,0x33,0x20 },   // 0x67, g
        { 0x07, 0x00,0xFE,0x20,0x20,0x20,0x3E,0x00 },   // 0x68, h
        { 0x05, 0x00,0x00,0x22,0x3E,0x02,0x00,0x00 },   // 0x69, i
        { 0x07, 0x00,0x01,0x01,0x01,0x21,0x3E,0x00 },   // 0x6a, j
        { 0x07, 0x00,0xFE,0x08,0x18,0x24,0x02,0x00 },   // 0x6b, k
        { 0x05, 0x00,0x00,0x02,0xFE,0x02,0x00,0x00 },   // 0x6c, l
        { 0x07, 0x00,0x3E,0x20,0x3E,0x20,0x20,0x1E },   // 0x6d, m
        { 0x07, 0x00,0x3E,0x20,0x20,0x20,0x3E,0x00 },   // 0x6e, n
        { 0x07, 0x00,0x1C,0x22,0x22,0x22,0x1C,0x00 },   // 0x6f, o
        { 0x07, 0x00,0x3F,0x22,0x22,0x22,0x3C,0x00 },   // 0x70, p
        { 0x07, 0x00,0x1C,0x22,0x22,0x22,0x3F,0x00 },   // 0x71, q
        { 0x07, 0x00,0x22,0x3E,0x20,0x20,0x20,0x00 },   // 0x72, r
        { 0x07, 0x00,0x36,0x2A,0x2A,0x2A,0x26,0x00 },   // 0x73, s
        { 0x07, 0x00,0x00,0x7C,0x22,0x02,0x02,0x00 },   // 0x74, t
        { 0x07, 0x00,0x3C,0x02,0x02,0x02,0x3E,0x02 },   // 0x75, u
        { 0x07, 0x00,0x20,0x18,0x06,0x18,0x20,0x00 },   // 0x76, v
        { 0x07, 0x00,0x3C,0x0E,0x30,0x0E,0x18,0x20 },   // 0x77, w
        { 0x07, 0x00,0x02,0x34,0x08,0x14,0x22,0x00 },   // 0x78, x
        { 0x07, 0x00,0x20,0x19,0x07,0x18,0x20,0x00 },   // 0x79, y
        { 0x07, 0x00,0x22,0x26,0x2A,0x32,0x02,0x00 },   // 0x7a, z
        { 0x07, 0x00,0x00,0x00,0x00,0xFF,0x00,0x00 },   // 0x7b, {
        { 0x07, 0x00,0x00,0x00,0xFF,0x00,0x00,0x00 },   // 0x7c, |
        { 0x07, 0x00,0x00,0xFF,0x00,0x00,0x00,0x00 },   // 0x7d, }
        { 0x07, 0x00,0x00,0x00,0x00,0x00,0x00,0x00 },   // 0x7e, ~
};



#define anzMAX     1 

unsigned short maxPosX = anzMAX * 8 - 1; 

unsigned short LEDarr[anzMAX][8];                   
unsigned short helpArrMAX[anzMAX * 8];              
unsigned short helpArrPos[anzMAX * 8];    


void helpArr_init(void)  //helperarray init
{
    unsigned short i, j, k;
    j = 0;
    k = 0;
    for (i = 0; i < anzMAX * 8; i++) {
        helpArrPos[i] = (1 << j);   //bitmask
        helpArrMAX[i] = k;
        j++;
        if (j > 7) {
            j = 0;
            k++;
        }
    }
}

#if 0
void char2Arr(unsigned short ch, int PosX, short PosY) { //characters into arr
    int i, j, k, l, m, o1, o2, o3, o4;  //in LEDarr
    PosX++;
    k = ch - ' ';                        //ASCII position in font
    if ((k >= 0) && (k < 96))           //character found in font?
    {
    	
        o4 = font1[k][0];                 //character width
        printf("k = %d, c = %c,o4 = %d\r\n",k,ch,o4);
        o3 = 1 << (o4 - 2);
        for (i = 0; i < o4; i++) {
            if (((PosX - i <= maxPosX) && (PosX - i >= 0))
                    && ((PosY > -8) && (PosY < 8))) //within matrix?
            {
                o1 = helpArrPos[PosX - i];
                o2 = helpArrMAX[PosX - i];
                for (j = 0; j < 8; j++) {
                    if (((PosY >= 0) && (PosY <= j)) || ((PosY < 0) && (j < PosY + 8))) //scroll vertical
                    {
                        l = font1[k][j + 1];
                        m = (l & (o3 >> i));  //e.g. o4=7  0zzzzz0, o4=4  0zz0
                        if (m > 0)
                            LEDarr[o2][j - PosY] = LEDarr[o2][j - PosY] | (o1);  //set point
                        else
                            LEDarr[o2][j - PosY] = LEDarr[o2][j - PosY] & (~o1); //clear point
                    }
                }
            }
        }
    }
}
#endif
void char22Arr(unsigned short ch, int PosX, short PosY) { //characters into arr
    int i, j, k, l, m, o1, o2, o3, o4;  //in LEDarr
    PosX++;
    k = ch - 32;                        //ASCII position in font
    if ((k >= 0) && (k < 96))           //character found in font?
    {
        o4 = font2[k][0];                 //character width
        o3 = 1 << (o4 - 2);
        for (i = 0; i < o4; i++) {
            if (((PosX - i <= maxPosX) && (PosX - i >= 0))
                    && ((PosY > -8) && (PosY < 8))) //within matrix?
            {
                o1 = helpArrPos[PosX - i];
                o2 = helpArrMAX[PosX - i];
                for (j = 0; j < 8; j++) {
                    if (((PosY >= 0) && (PosY <= j)) || ((PosY < 0) && (j < PosY + 8))) //scroll vertical
                    {
                        l = font2[k][j + 1];
                        m = (l & (o3 >> i));  //e.g. o4=7  0zzzzz0, o4=4  0zz0
                        if (m > 0)
                            LEDarr[o2][j - PosY] = LEDarr[o2][j - PosY] | (o1);  //set point
                        else
                            LEDarr[o2][j - PosY] = LEDarr[o2][j - PosY] & (~o1); //clear point
                    }
                }
            }
        }
    }
}


void rotate_90() // for Generic displays
{
    for (uint8_t k = anzMAX; k > 0; k--) {

        uint8_t i, j, m, imask, jmask;
        uint8_t tmp[8]={0,0,0,0,0,0,0,0};
        for (  i = 0, imask = 0x01; i < 8; i++, imask <<= 1) {
          for (j = 0, jmask = 0x01; j < 8; j++, jmask <<= 1) {
            if (LEDarr[k-1][i] & jmask) {
              tmp[j] |= imask;
            }
          }
        }
        for(m=0; m<8; m++){
            LEDarr[k-1][m]=tmp[m];
        }
    }
}





hi_void Write_Max7219_byte(hi_u8 DATA)         
{
    hi_u8 i; 
    IoTGpioSetOutputVal(Cs_num, 0);	
    for(i=8;i>=1;i--){	
        IoTGpioSetOutputVal(Clk_num, 0);
        if(DATA&0x80)
          IoTGpioSetOutputVal(Din_num, 1);
        else
          IoTGpioSetOutputVal(Din_num, 0); 
        DATA=DATA<<1;
        IoTGpioSetOutputVal(Clk_num, 1);    
    }    
}



void max7219_write_data_lsbfirst(hi_u8 DATA){
	hi_u8 i; 
    IoTGpioSetOutputVal(Cs_num, 0);	
    for(i=8;i>=1;i--){	
        IoTGpioSetOutputVal(Clk_num, 0);
        if(DATA&0x01)
          IoTGpioSetOutputVal(Din_num, 1);
        else
          IoTGpioSetOutputVal(Din_num, 0); 
        DATA=DATA>>1;
        IoTGpioSetOutputVal(Clk_num, 1);    
    }  
}





void max7219_write_data_msbfirst(hi_u8 DATA){
	hi_u8 i; 
    for(i=8;i>=1;i--){	
        IoTGpioSetOutputVal(Clk_num, 0);
        if(DATA&0x80)
          IoTGpioSetOutputVal(Din_num, 1);
        else
          IoTGpioSetOutputVal(Din_num, 0); 
        DATA=DATA<<1;
        IoTGpioSetOutputVal(Clk_num, 1);    
    }  
}






hi_void Write_Max7219(hi_u8 address,hi_u8 dat)
{
	IoTGpioSetOutputVal(Cs_num, 0);
	Write_Max7219_byte(address);
	Write_Max7219_byte(dat);
	if(address>0 && address<7)
		matrix_state[address-1] = dat;
	IoTGpioSetOutputVal(Cs_num, 1);
                       
}


void refresh_display() //take info into LEDarr
{
    unsigned short i, j;
	
#ifdef ROTATE_90
    rotate_90();
#endif
	
    for (i = 0; i < 8; i++)     //8 rows
    {
        IoTGpioSetOutputVal(Cs_num, 0);	
        //delayMicroseconds(1);
        for (j = 1; j <= anzMAX; j++) {
            max7219_write_data_msbfirst(i + 1);  //current row
#if 0 
#ifdef REVERSE_VERTICAL
#ifdef REVERSE_HORIZONTAL
            max7219_write_data_lsbfirst(LEDarr[j - 1][7-i]);
#else
			max7219_write_data_msbfirst(LEDarr[j - 1][7-i]);
#endif

#else
#ifdef REVERSE_HORIZONTAL
            max7219_write_data_lsbfirst(LEDarr[j - 1][i]);
#else
			max7219_write_data_msbfirst(LEDarr[j - 1][i]);
#endif
#endif
#endif
			max7219_write_data_msbfirst(LEDarr[j - 1][i]);
			printf("0x%02x,",LEDarr[j - 1][i]);
        }
		
        IoTGpioSetOutputVal(Cs_num, 1);	
    }
	printf("\r\n");
}


hi_void matribrightness(hi_u8 brightness){
  Write_Max7219(0x0a, brightness * 2); 
}









hi_void Init_MAX7219(hi_u8 din_num,hi_u8 cs_num,hi_u8 clk_num)
{
  Din_num = din_num;
  Cs_num  = cs_num;
  Clk_num = clk_num;
  helpArr_init();
  IoTGpioInit(Din_num);
  IoTGpioInit(Cs_num);
  IoTGpioInit(Clk_num);
  IoTGpioSetDir(Din_num,IOT_GPIO_DIR_OUT);
  IoTGpioSetDir(Cs_num,IOT_GPIO_DIR_OUT);
  IoTGpioSetDir(Clk_num,IOT_GPIO_DIR_OUT);
  hi_io_set_func(Din_num,HI_IO_FUNC_GPIO_14_GPIO);
  hi_io_set_func(Cs_num,HI_IO_FUNC_GPIO_9_GPIO);
  hi_io_set_func(Clk_num,HI_IO_FUNC_GPIO_10_GPIO);
  Write_Max7219(0x09, 0x00);      
  Write_Max7219(0x0a, 0x03);  //亮度 级别
  Write_Max7219(0x0b, 0x07);
  Write_Max7219(0x0c, 0x01);
  Write_Max7219(0x0f, 0x00);
}








hi_void matritest(hi_void)
{
 hi_u8 i,j;
 hi_sleep(50);
 Init_MAX7219(14,9,10);  
 i = 1;
 while(1)
 {                                                                             
  for(j=0;j<38;j++){
   for(i=1;i<9;i++)
     Write_Max7219(i,disp1[j][i-1]);
     hi_sleep(1000);
     //printf("hello world\r\n");
  }  
 }    
}











hi_void matridisplay(hi_u8 *array_date){
  hi_u8 i = 0;
  if(enable){
    return;
  }
  Init_MAX7219(1,4,6);   
  for(i=1;i<9;i++)
     Write_Max7219(i,array_date[i-1]);

}


hi_void matriOffall(){
  hi_u8 screen_array_temp[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  hi_u8 i = 0;
  if(enable){
    return;
  }
//   Init_MAX7219(1,4,6);   
//   for(i=1;i<9;i++)
//      Write_Max7219(i,screen_array_temp[i-1]);
  for(i=1;i<7;i++)
       Write_Max7219(i,0);

}


hi_void matriEnable(hi_bool flag){
    enable = flag;  
}


hi_void matriWriteString(hi_u8 *str_date){
#if 1
	hi_u8 i,j;
	hi_sleep(50);
	if(enable){
		return;
	}
	Init_MAX7219(14,9,10);  
	i = 1;
	j = 0;
	while(str_date[j])
	{  
		for(i=1;i<7;i++)
		   Write_Max7219(i,FM6x8[str_date[j] - ' '][i-1]);
		hi_sleep(1000);  
		j++;
	}    
#else
	int pos_x = -8;
	Init_MAX7219(14,9,10);
	//char2Arr(str_date[0],4,4);
	int j = 0;
	
	while(str_date[j]){
		while(1){
			char22Arr(str_date[j],pos_x-(j*6),0);
			if((str_date+j+1)!=NULL && str_date[j]!=0)
				char22Arr(str_date[j+1],pos_x-(j+1)*6,0);
			
			refresh_display();
			pos_x++;
			if(pos_x>(j+2)*6){
				break;
				
			}
			usleep(100000);
		}
		j++;
		
	}
#endif
}


hi_void matriWriteChar(hi_u8 c){
	hi_u8 i;
	for(i=1;i<7;i++)
       Write_Max7219(i,FM6x8[c- ' '][i-1]);
       //Write_Max7219(i,test_pic[i-1]);
}



hi_void matriShowPic(hi_u8 index){
	hi_u8 i;
	for(i=1;i<7;i++)
       Write_Max7219(i,pic[index][i-1]);
}



hi_u8* getMatrixDate(void){
	return matrix_state;
	
}


hi_void matriShowdotMatrix(hi_u8 matrix[6]){
	hi_u8 i;
	for(i=1;i<7;i++){
       Write_Max7219(i,matrix[i-1]);
	}
}



hi_void matriFilldisplay(hi_u32 array_date0,hi_u32 array_date1){
    hi_u8 i,j;
    hi_sleep(50);
    if(enable){
      return;
    }
    hi_u64 array_date = 0;
    array_date = array_date0;
    array_date = array_date << 21;
    array_date = array_date + array_date1;
    hi_u64 temp_date = 0;
    hi_u8 screen_array_temp[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    for(int i = 5; i >= 0; i--){
      temp_date = array_date;
      screen_array_temp[i] = (temp_date >> ( 7 * (5 - i))) & 0x7F; 
    }
    matridisplay(screen_array_temp);
}





#if 0
/* 矩阵管理结构体 */
Led_Matrix_t g_led_matrix;





void Led_Matrix_Init(){
	Led_Matrix_t *led_matrix = &g_led_matrix;
	if(led_matrix == NULL){
		return 0;
	}
	if(led_matrix->led_mux_buf!= NULL){
		free(led_matrix->led_mux_buf);
	}
	led_matrix->led_mux_buf = NULL;
	for(int i=0; i<8; i++){
		led_matrix->led_row[i] = 0;
		led_matrix->character[i] = 0;
	}
	led_matrix->led_mux_buf_len = 0;
	led_matrix->roll_character_cnt = 0;
	led_matrix->roll_cnt = 0;
	led_matrix->roll_flag = 0;
	return;
}








/* 滑动任务 */
void led_roll_task(void* arg){
	Led_Matrix_t *led_matrix = (Led_Matrix_t*)g_led_matrix;
	while (1){
		/* 获取互斥体 */
		//xSemaphoreTake(led_matrix->led_matrix_mutex,portMAX_DELAY);
		if(led_matrix->led_mux_buf_len > 0 && led_matrix->led_mux_buf != NULL){
			for(int i = 0; i<8 ;i++){
				Write_Max7219(i+1,(led_matrix->led_row[i]>>8)&0xff);
			}
			for(int i =0; i<8; i++){
				led_matrix->led_row[i] <<= 1;
				led_matrix->led_row[i] |= ((led_matrix->character[i]>>7)&0x0001);
				led_matrix->character[i] <<= 1;
			}
			led_matrix->roll_cnt ++; 
			if(led_matrix->roll_cnt >= 8){
				led_matrix->roll_cnt = 0;
				if(led_matrix->roll_character_cnt<led_matrix->led_mux_buf_len){
					for(int i =0; i<8; i++, led_matrix->roll_character_cnt++){
						if(led_matrix->led_mux_buf){
							led_matrix->character[i] = led_matrix->led_mux_buf[led_matrix->roll_character_cnt];
						}
					}
				}else{
					led_matrix->roll_character_cnt = 0;
					for(int i =0; i<8; i++,led_matrix->roll_character_cnt++){
						if(led_matrix->led_mux_buf){
							led_matrix->character[i] = led_matrix->led_mux_buf[led_matrix->roll_character_cnt];
						}
					}
				}
			}
			/* 释放互斥体 */
		}
	}	
}





int  left_roll_display(uint8_t *buf, int buf_len){
	Led_Matrix_t *led_matrix = &g_led_matrix;
	//xSemaphoreTake(led_matrix->led_matrix_mutex,portMAX_DELAY);
	/* 释放先前的 */
	Led_Matrix_Init();
	if(led_matrix->led_mux_buf!=NULL){
		free(led_matrix->led_mux_buf);
		led_matrix->led_mux_buf = NULL;
	}
	led_matrix->led_mux_buf_len = buf_len *8;
	led_matrix->led_mux_buf = (uint8_t *)malloc(led_matrix->led_mux_buf_len);
	/* 申请内存失败 */
	if(led_matrix->led_mux_buf == NULL){
		led_matrix->led_mux_buf_len = 0;
		return -1;
	}
	/* 获取点阵 */
	if(buf_len > 0){
		for(int i =0; i<buf_len; i++){
			for(int j=0; j<8; j++){
				led_matrix->led_mux_buf[i*8+j] = disp1[buf[i]-32][j];
			}
		}
	}else{
		return -2;
	}
	/* 初始化点阵 */
	/* 只有一个字符需要显示 */
	if(buf_len == 1){
		for(int i =0; i<8 ;i++,led_matrix->roll_character_cnt++){
			led_matrix->led_row[i] = led_matrix->led_mux_buf[led_matrix->roll_character_cnt];
		}
		
	}
	else if(buf_len >= 2){
		
		for(int i =0; i<8 ;i++,led_matrix->roll_character_cnt++){
			led_matrix->led_row[i] = led_matrix->led_mux_buf[led_matrix->roll_character_cnt];
		}

		for(int i =0; i<8 ;i++,led_matrix->roll_character_cnt++){
			led_matrix->character[i] = led_matrix->led_mux_buf[led_matrix->roll_character_cnt];
		}
		
	}
	//xSemaphoreGive(led_matrix->led_matrix_mutex);
	return 0;
}








void start_roll_display(void){
	Led_Matrix_t *led_matrix = &g_led_matrix;
	#if 0
	if(led_matrix->led_matrix_handle != NULL){
		vTaskResume(led_matrix->led_matrix_handle);
		xSemaphoreGive(led_matrix->led_matrix_mutex);
	}
	#endif
	return ;
}





void stop_roll_display(void){
	Led_Matrix_t *led_matrix = &g_led_matrix;
#if 0
	if(led_matrix->led_matrix_handle != NULL){
		vTaskSuspend(led_matrix->led_matrix_handle);
		/* 释放锁 */
		xSemaphoreGive(led_matrix->led_matrix_mutex);
	}
#endif;
	return ;
}





/* 清除，滚动显示 */
void clean_roll_display(void){
	/* 停止滚动显示 */
	stop_roll_display();
	/* 初始化显示矩阵 */
	Led_Matrix_Init();
	
}

#endif

