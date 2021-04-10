/*
    START(8) | TYPE(8) | LENGTH(8) | DATA ~
    LED On  : 0x01110101
    LED Off : 0x01110100
    LED Dim : 0x011201xx ex) 50%(0x80) brightness -> 0x01_12_01_80
    LED Blink : 0x011303xxyyyy ex) 5 times(0x05) with 500ms(0x01C0) interval -> 0x01_13_03_05_01C0
*/

#define CMD_START 0x1

#define BIT_START  0
#define BIT_TYPE   1
#define BIT_LENGTH 2
#define BIT_DATA   3

#define TYPE_LED_SW       0x11
#define TYPE_LED_DIM      0x12
#define TYPE_LED_BLINK    0x13
#define TYPE_MOVE_DIR     0x21
#define TYPE_MOVE_SPEED   0x22
#define TYPE_ROTATE_DIR   0x23
#define TYPE_ROTATE_SPEED 0x24