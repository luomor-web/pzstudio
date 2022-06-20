#if 0
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "py/obj.h"
#include "py/runtime.h"
#if BUILD_BOARD == DASHIXIONG_BOARD
#include "iot_gpio.h" 
#include <unistd.h>
#include "los_mux.h"
UINT32 ledMux;
mp_obj_t mp_led_init(mp_obj_t index) {
    
    if (ledMux == NULL){
        LOS_MuxCreate(&ledMux);
    }
    int i = mp_obj_get_int(index);
    LOS_MuxPend(ledMux, LOS_WAIT_FOREVER);
    IoTGpioInit(i);
    IoTGpioSetDir(i, IOT_GPIO_DIR_OUT);
    LOS_MuxPost(ledMux);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_led_init_obj, mp_led_init);

mp_obj_t mp_led_on(mp_obj_t index) {
    if (ledMux == NULL){
        LOS_MuxCreate(&ledMux);
    }
    int i = mp_obj_get_int(index);
    LOS_MuxPend(ledMux, LOS_WAIT_FOREVER);
    IoTGpioSetOutputVal(i, 1);
    LOS_MuxPost(ledMux);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_led_on_obj, mp_led_on);

mp_obj_t mp_led_off(mp_obj_t index) {
    if (ledMux == NULL){
        LOS_MuxCreate(&ledMux);
    }
    int i = mp_obj_get_int(index);
    LOS_MuxPend(ledMux, LOS_WAIT_FOREVER);
    IoTGpioSetOutputVal(i, 0);
    LOS_MuxPost(ledMux);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_led_off_obj, mp_led_off);

MP_STATIC const mp_rom_map_elem_t led_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_led) },
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mp_led_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_on), MP_ROM_PTR(&mp_led_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_off), MP_ROM_PTR(&mp_led_off_obj) },
};

MP_STATIC MP_DEFINE_CONST_DICT(led_module_globals, led_module_globals_table);

const mp_obj_module_t mp_module_led = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&led_module_globals,
};
#else
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "py/obj.h"
#include "py/runtime.h"
#include "matrixscreen.h"
// static unsigned char FM6x8[][6] =
// {
//     { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // sp  0
//     { 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 }, // !   1
//     { 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 }, // "   2
//     { 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 }, // #   3
//     { 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 }, // $   4
//     { 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 }, // %  
//     { 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 }, // &
//     { 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 }, // '
//     { 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 }, // (
//     { 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 }, // )
//     { 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 }, // *
//     { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 }, // +
//     { 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 }, // ,
//     { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 }, // -
//     { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 }, // .
//     { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 }, // /
//     { 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E }, // 0
//     { 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 }, // 1
//     { 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 }, // 2
//     { 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 }, // 3
//     { 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 }, // 4
//     { 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 }, // 5
//     { 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 }, // 6
//     { 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 }, // 7
//     { 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 }, // 8
//     { 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E }, // 9
//     { 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 }, // :
//     { 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 }, // ;
//     { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 }, // <
//     { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 }, // =
//     { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 }, // >
//     { 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 }, // ?
//     { 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E }, // @
//     { 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C }, // A
//     { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 }, // B
//     { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 }, // C
//     { 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C }, // D
//     { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 }, // E
//     { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 }, // F
//     { 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A }, // G
//     { 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F }, // H
//     { 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 }, // I
//     { 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 }, // J
//     { 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 }, // K
//     { 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 }, // L
//     { 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F }, // M
//     { 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F }, // N
//     { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E }, // O
//     { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 }, // P
//     { 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E }, // Q
//     { 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 }, // R
//     { 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 }, // S
//     { 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 }, // T
//     { 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F }, // U
//     { 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F }, // V
//     { 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F }, // W
//     { 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 }, // X
//     { 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 }, // Y
//     { 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 }, // Z
//     { 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 }, // [
//     { 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 }, // 55
//     { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 }, // ]
//     { 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 }, // ^
//     { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 }, // _
//     { 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 }, // '
//     { 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 }, // a
//     { 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 }, // b
//     { 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 }, // c
//     { 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F }, // d
//     { 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 }, // e
//     { 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 }, // f
//     { 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C }, // g
//     { 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 }, // h
//     { 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 }, // i
//     { 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 }, // j
//     { 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 }, // k
//     { 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 }, // l
//     { 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 }, // m
//     { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 }, // n
//     { 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 }, // o
//     { 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 }, // p
//     { 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC }, // q
//     { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 }, // r
//     { 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 }, // s
//     { 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 }, // t
//     { 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C }, // u
//     { 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C }, // v
//     { 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C }, // w
//     { 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 }, // x
//     { 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C }, // y
//     { 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 }, // z
//     { 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }, // horiz lines
// };

// hi_u8  disp1[38][8]={
// {0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//0
// {0x10,0x18,0x14,0x10,0x10,0x10,0x10,0x10},//1
// {0x7E,0x2,0x2,0x7E,0x40,0x40,0x40,0x7E},//2
// {0x3E,0x2,0x2,0x3E,0x2,0x2,0x3E,0x0},//3
// {0x8,0x18,0x28,0x48,0xFE,0x8,0x8,0x8},//4
// {0x3C,0x20,0x20,0x3C,0x4,0x4,0x3C,0x0},//5
// {0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x0},//6
// {0x3E,0x22,0x4,0x8,0x8,0x8,0x8,0x8},//7
// {0x0,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},//8
// {0x3E,0x22,0x22,0x3E,0x2,0x2,0x2,0x3E},//9
// {0x8,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},//A
// {0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x0},//B
// {0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x0},//C
// {0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x0},//D
// {0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E
// {0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},//F
// {0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//G
// {0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},//H
// {0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
// {0x3C,0x8,0x8,0x8,0x8,0x8,0x48,0x30},//J
// {0x0,0x24,0x28,0x30,0x20,0x30,0x28,0x24},//K
// {0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},//L
// {0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},//M
// {0x0,0x42,0x62,0x52,0x4A,0x46,0x42,0x0},//N
// {0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
// {0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},//P
// {0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},//Q
// {0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
// {0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},//S
// {0x0,0x3E,0x8,0x8,0x8,0x8,0x8,0x8},//T
// {0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
// {0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
// {0x0,0x49,0x49,0x49,0x49,0x2A,0x1C,0x0},//W
// {0x0,0x41,0x22,0x14,0x8,0x14,0x22,0x41},//X
// {0x41,0x22,0x14,0x8,0x8,0x8,0x8,0x8},//Y
// {0x0,0x7F,0x2,0x4,0x8,0x10,0x20,0x7F},//Z 
// {0x8,0x7F,0x49,0x49,0x7F,0x8,0x8,0x8},//ÖÐ
// {0xFE,0xBA,0x92,0xBA,0x92,0x9A,0xBA,0xFE},//¹ú
// };

// hi_u8 screen_array_state[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
// hi_bool enable = 0;
mp_obj_t mp_led_init() {
    Init_MAX7219(14,9,10);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_0(mp_led_init_obj, mp_led_init);

mp_obj_t mp_led_clear() {
    matriOffall();
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_0(mp_led_clear_obj, mp_led_clear);

mp_obj_t mp_led_showChar(mp_obj_t c) {
    char *i = mp_obj_str_get_str(c);
    matriWriteString(i);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_led_showChar_obj, mp_led_showChar);


mp_obj_t mp_led_showString(mp_obj_t c) {
    char *str_date = mp_obj_str_get_str(c);
    matriWriteString(str_date);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_led_showString_obj, mp_led_showString);


mp_obj_t mp_led_showMatrix(mp_obj_t wr_buf){
	mp_buffer_info_t matrix;
	
    mp_get_buffer_raise(wr_buf, &matrix, MP_BUFFER_READ);
	if(matrix.len>0 && matrix.buf != NULL){
		matriShowdotMatrix(matrix.buf);
	}
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_led_showMatrix_obj, mp_led_showMatrix);




mp_obj_t mp_led_showDot(mp_obj_t obj_x,mp_obj_t obj_y,mp_obj_t obj_on_off){
	unsigned char* matrix_state =  getMatrixDate();
	int x = mp_obj_get_int(obj_x);
	int y = mp_obj_get_int(obj_y);
	int on_off = mp_obj_get_int(obj_on_off);
	if(x<=0 ){
		x = 1;
	}
	if(y <= 0){
		y = 1;
	}
	y = y-1;
	x = x-1;
	x=x%7;
	y=y%6;
	if(on_off==0){
		matrix_state[y] &= ((~(1<<(7-x-1)))&0x7f);
	}else{
		matrix_state[y] |= ((1<<(7-x-1))&0x7f);
	}	
	matriShowdotMatrix(matrix_state);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_3(mp_led_showDot_obj, mp_led_showDot);



MP_STATIC const mp_rom_map_elem_t led_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_led) },
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mp_led_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_showChar), MP_ROM_PTR(&mp_led_showChar_obj) },
    { MP_ROM_QSTR(MP_QSTR_showString), MP_ROM_PTR(&mp_led_showString_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear), MP_ROM_PTR(&mp_led_clear_obj) },
    { MP_ROM_QSTR(MP_QSTR_showMatrix), MP_ROM_PTR(&mp_led_showMatrix_obj) },
    { MP_ROM_QSTR(MP_QSTR_dot), MP_ROM_PTR(&mp_led_showDot_obj) },
};

MP_STATIC MP_DEFINE_CONST_DICT(led_module_globals, led_module_globals_table);

const mp_obj_module_t mp_module_led = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&led_module_globals,
};

#endif
#endif