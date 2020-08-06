#include"APQuad.h"
#include"IRremote.h"
// Meccano Remote Control
#define ever (;;)
#define turbo (cmd.value == 0xFF10EF || cmd.value == 0x8C22657B)
#define volumeUp (cmd.value == 0xFF08F7 || cmd.value == 0x45473C1B)
#define reWind (cmd.value == 0xFF18E7 || cmd.value == 0x3D9AE3F7)
#define playStop (cmd.value == 0xFF30CF || cmd.value == 0x9716BE3F)
#define fastForward (cmd.value == 0xFF38C7 || cmd.value == 0x488F3CBB)
#define backwards (cmd.value == 0xFF00FF || cmd.value == 0xFA3F159F)
#define left (cmd.value == 0xFF20DF || cmd.value == 0x51E43D1B)
#define right (cmd.value == 0xFFA05F || cmd.value == 0xAB91951F)
#define volumeDown (cmd.value == 0xFF28D7 || cmd.value == 0x13549BDF)
#define forwards (cmd.value == 0xFF807F || cmd.value == 0x8AB3679B)
#define zzz (cmd.value == 0xFFB04F || cmd.value == 0xF0C41643)
#define skeleton (cmd.value == 0xFF906F || cmd.value == 0xE5CFBD7F)
#define noSignal (IR.decode(&cmd)==0)
bool trotGait = false;
IRrecv IR(9);
decode_results cmd;
void setup() {
  // put your setup code here, to run once:
  setServos();
  Serial.begin(57600);
  IR.enableIRIn();
}
byte getNum(void) {
  delay(500);
  bool trig = false;
  IR.resume();
  byte num;
  for ever {
  long stopTime = millis();
    while noSignal {
    long currentTime = millis();
      if (currentTime - stopTime > 2000) {
        trig = true;
        break;
      }
    }
    if (trig == true) {
      break;
    }
    if playStop {
    num++;
  }
  IR.resume();
  }
  return num;
}

void loop() {
  // put your main code here, to run repeatedly:

  while noSignal {
  // Do nothing
}
if zzz {
  if sleeping {
    initialiseServos(15);
    }
    else {
      goSleep(15);
    }
  }

  if volumeDown {
  raiseBody(-10, 5);
  }
  if volumeUp {
  raiseBody(10, 5);
  }
  if (skeleton and (trotGait == true)) {
    byte num = getNum();
    squat(num);
  }
  if (skeleton and (trotGait == false)) {
    byte num = getNum();
    pressUp(num);
  }
  if forwards {
  byte num = getNum();
    if (trotGait == true) {
      stepForwardsTrotGait(num, 80);
    }
    else {
      stepForwardsCreepGait(num, 80);
    }

  }
  if backwards {
  byte num = getNum();
    if (trotGait == true) {
      stepBackwardsTrotGait(num, 80);
    }
    else {
      stepBackwardsCreepGait(num, 80);
    }

  }
  if left {
  byte num = getNum();
    if (trotGait == true) {
      stepLeftTrotGait(num, 80);
    }
    else {
      stepLeftCreepGait(num, 80);
    }

  }
  if right {
  byte num = getNum();
    if (trotGait == true) {
      stepRightTrotGait(num, 80);
    }
    else {
      stepRightCreepGait(num, 80);
    }

  }
  if fastForward {
  byte num = getNum();
    turnRight(num, 80);
  }
  if reWind {
  byte num = getNum();
    turnLeft(num, 80);
  }
  if turbo {
  trotGait = not trotGait;
}
delay(100);
  IR.resume();

}
