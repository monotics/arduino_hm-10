#include "command.h"
#include "led.h"

void executeCommand(int cmd[]) {
  switch(cmd[BIT_TYPE]) {
    case TYPE_LED_SW:
      ledSwitch(cmd[BIT_DATA]);
      break;
    case TYPE_LED_DIM:
      ledDim(cmd[BIT_DATA]);
      break;
    case TYPE_LED_BLINK:
      ledBlink(cmd[BIT_DATA], cmd[BIT_DATA+1] << 8 | cmd[BIT_DATA+2]);
      break;
  }
}