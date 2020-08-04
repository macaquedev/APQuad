#include"iarduino_MultiServo.h"
#include"IRremote.h"
#include "config.h"
byte neutralKnees = 110;
byte neutralAnkles = 110;
bool sl = true;
bool trotGait = false;
#define neutralHips 90
#define sleeping (sl)
#define sleepHips 45
#define sleepKnees 0
#define sleepAnkles 0
const int kneeUp = -44;
#define fla 0
#define flk 1
#define flh 2
#define fra 3
#define frk 4
#define frh 5
#define bla 6
#define blk 7
#define blh 8
#define bra 9
#define brk 10
#define brh 11
// Elegoo Remote Control
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
const byte offsets[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
iarduino_MultiServo s;
IRrecv IR(9);
decode_results cmd;


void moveServo(byte servoPin, int pos) {
  pos += offsets[servoPin];
  if (pos > 180) {
    pos = 180;
  }
  else if (pos < 0) {
    pos = 0;
  }
  s.servoWrite(servoPin, pos);
}

void setServos(void) {
  s.servoSet(SERVO_ALL, SERVO_SG90);
  s.begin(I2C_ADDR);
}

void initialiseServos(byte servoSpeed) {

  for (byte i = sleepHips; i <= neutralHips; i++) {
    moveServo(brh, i);
    moveServo(blh, 180 - i);
    moveServo(frh, 180 - i);
    moveServo(flh, i);
    delay(servoSpeed);
  }

  delay(servoSpeed * 35);
  for (byte i = sleepKnees; i <= neutralKnees; i++) {
    moveServo(brk, 180 - i);
    moveServo(blk, i);
    moveServo(frk, i);
    moveServo(flk, 180 - i);
    delay(servoSpeed);
  }
  delay(servoSpeed * 35);
  for (byte i = sleepAnkles; i <= neutralAnkles; i++) {
    moveServo(bra, 180 - i);
    moveServo(bla, i);
    moveServo(fra, i);
    moveServo(fla, 180 - i);
    delay(servoSpeed);
  }
  sl = false;
}

void goSleep(byte servoSpeed) {

  for (byte i = neutralAnkles; i >= sleepAnkles + 1; i--) {
    moveServo(bra, 180 - i);
    moveServo(bla, i);
    moveServo(fra, i);
    moveServo(fla, 180 - i);
    delay(servoSpeed);
  }
  delay(servoSpeed * 35);
  for (byte i = neutralKnees; i >= sleepKnees + 1; i--) {
    moveServo(brk, 180 - i);
    moveServo(blk, i);
    moveServo(frk, i);
    moveServo(flk, 180 - i);
    delay(servoSpeed);
  }
  delay(servoSpeed * 35);
  for (byte i = neutralHips; i >= sleepHips + 1; i--) {
    moveServo(brh, i);
    moveServo(blh, 180 - i);
    moveServo(frh, 180 - i);
    moveServo(flh, i);
    delay(servoSpeed);
  }

  delay(servoSpeed * 35);
  sl = true;
}

void stepForwardsCreepGait(byte x, int y) {
  // Set delays
  // INIT FOR CREEP GAIT
  moveServo(frk, neutralKnees + kneeUp);
  moveServo(fra, neutralKnees + kneeUp);
  delay(y);
  moveServo(frh, 35);
  delay(y * 2);
  moveServo(frk, neutralKnees);
  moveServo(fra, neutralKnees);
  delay(y);
  moveServo(brk, 180 - (neutralKnees + kneeUp));
  moveServo(bra, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(brh, 145);
  delay(y * 2);
  moveServo(brk, 180 - neutralKnees);
  moveServo(bra, 180 - neutralKnees);
  delay(y);

  // Start Repeating
  for (byte i = 1; i <= x; i++) {
    // STEP 1
    moveServo(frk, neutralKnees + kneeUp);
    moveServo(fra, neutralKnees + kneeUp);
    delay(y);
    moveServo(frh, 125);
    delay(y * 2);
    moveServo(frk, neutralKnees);
    moveServo(fra, neutralKnees);
    delay(y);

    // STEP 2
    moveServo(frh, 90);
    moveServo(brh, 90);
    moveServo(flh, 145);
    moveServo(blh, 125);
    delay(y * 2);

    // STEP 3
    moveServo(blk, neutralKnees + kneeUp);
    moveServo(bla, neutralKnees + kneeUp);
    delay(y);
    moveServo(blh, 35);
    delay(y * 2);
    moveServo(blk, neutralKnees);
    moveServo(bla, neutralKnees);
    delay(y);
    // STEP 4
    moveServo(flk, 180 - (neutralKnees + kneeUp));
    moveServo(fla, 180 - (neutralKnees + kneeUp));
    delay(y);
    moveServo(flh, 55);
    delay(y * 2);
    moveServo(flk, 180 - neutralKnees);
    moveServo(fla, 180 - neutralKnees);
    delay(y);

    // STEP 5
    moveServo(flh, 90);
    moveServo(blh, 90);
    moveServo(frh, 35);
    moveServo(brh, 55);
    delay(y * 2);
    // STEP 6
    if (i != x) {
      moveServo(brk, 180 - (neutralKnees + kneeUp));
      moveServo(bra, 180 - (neutralKnees + kneeUp));
      delay(y);
      moveServo(brh, 145);
      delay(y * 2);
      moveServo(brk, 180 - neutralKnees);
      moveServo(bra, 180 - neutralKnees);
      delay(y);
    }


  }
  moveServo(brk, 180 - (neutralKnees + kneeUp));
  moveServo(bra, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(brh, 180 - neutralHips);
  delay(y * 2);
  moveServo(brk, 180 - neutralKnees);
  moveServo(bra, 180 - neutralKnees);
  delay(y);
  moveServo(frk, neutralKnees + kneeUp);
  moveServo(fra, neutralKnees + kneeUp);
  delay(y);
  moveServo(frh, neutralHips);
  delay(y * 2);
  moveServo(frk, neutralKnees);
  moveServo(fra, neutralKnees);
}

void stepBackwardsCreepGait(byte x, int y) {
  // Set delays
  // INIT FOR CREEP GAIT
  moveServo(blk, neutralKnees + kneeUp);
  moveServo(bla, neutralKnees + kneeUp);
  delay(y);
  moveServo(blh, 35);
  delay(y * 2);
  moveServo(blk, neutralKnees);
  moveServo(bla, neutralKnees);
  delay(y);
  moveServo(flk, 180 - (neutralKnees + kneeUp));
  moveServo(fla, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(flh, 145);
  delay(y * 2);
  moveServo(flk, 180 - neutralKnees);
  moveServo(fla, 180 - neutralKnees);
  delay(y);

  // Start Repeating
  for (byte i = 1; i <= x; i++) {
    // STEP 1
    moveServo(blk, neutralKnees + kneeUp);
    moveServo(bla, neutralKnees + kneeUp);
    delay(y);
    moveServo(blh, 125);
    delay(y * 2);
    moveServo(blk, neutralKnees);
    moveServo(bla, neutralKnees);
    delay(y);

    // STEP 2
    moveServo(blh, 90);
    moveServo(flh, 90);
    moveServo(brh, 145);
    moveServo(frh, 125);
    delay(y * 2);

    // STEP 3
    moveServo(frk, neutralKnees + kneeUp);
    moveServo(fra, neutralKnees + kneeUp);
    delay(y);
    moveServo(frh, 35);
    delay(y * 2);
    moveServo(frk, neutralKnees);
    moveServo(fra, neutralKnees);
    delay(y);
    // STEP 4
    moveServo(brk, 180 - (neutralKnees + kneeUp));
    moveServo(bra, 180 - (neutralKnees + kneeUp));
    delay(y);
    moveServo(brh, 55);
    delay(y * 2);
    moveServo(brk, 180 - neutralKnees);
    moveServo(bra, 180 - neutralKnees);
    delay(y);

    // STEP 5
    moveServo(brh, 90);
    moveServo(frh, 90);
    moveServo(blh, 35);
    moveServo(flh, 55);
    delay(y * 2);
    // STEP 6
    if (i != x) {
      moveServo(flk, 180 - (neutralKnees + kneeUp));
      moveServo(fla, 180 - (neutralKnees + kneeUp));
      delay(y);
      moveServo(flh, 145);
      delay(y * 2);
      moveServo(flk, 180 - neutralKnees);
      moveServo(fla, 180 - neutralKnees);
      delay(y);
    }


  }
  moveServo(flk, 180 - (neutralKnees + kneeUp));
  moveServo(fla, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(flh, 180 - neutralHips);
  delay(y * 2);
  moveServo(flk, 180 - neutralKnees);
  moveServo(fla, 180 - neutralKnees);
  delay(y);
  moveServo(blk, neutralKnees + kneeUp);
  moveServo(bla, neutralKnees + kneeUp);
  delay(y);
  moveServo(blh, neutralHips);
  delay(y * 2);
  moveServo(blk, neutralKnees);
  moveServo(bla, neutralKnees);
}

void stepRightCreepGait(byte x, int y) {
  // Set delays
  // INIT FOR CREEP GAIT
  moveServo(brk, 180 - (neutralKnees + kneeUp));
  moveServo(bra, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(brh, 35);
  delay(y * 2);
  moveServo(brk, 180 - neutralKnees);
  moveServo(bra, 180 - neutralKnees);
  delay(y);
  moveServo(blk, neutralKnees + kneeUp);
  moveServo(bla, neutralKnees + kneeUp);
  delay(y);
  moveServo(blh, 145);
  delay(y * 2);
  moveServo(blk, neutralKnees);
  moveServo(bla, neutralKnees);
  delay(y);

  // Start Repeating
  for (byte i = 1; i <= x; i++) {
    // STEP 1
    moveServo(brk, 180 - (neutralKnees + kneeUp));
    moveServo(bra, 180 - (neutralKnees + kneeUp));
    delay(y);
    moveServo(brh, 125);
    delay(y * 2);
    moveServo(brk, 180 - neutralKnees);
    moveServo(bra, 180 - neutralKnees);
    delay(y);

    // STEP 2
    moveServo(brh, 90);
    moveServo(blh, 90);
    moveServo(frh, 145);
    moveServo(flh, 125);
    delay(y * 2);

    // STEP 3
    moveServo(flk, 180 - (neutralKnees + kneeUp));
    moveServo(fla, 180 - (neutralKnees + kneeUp));
    delay(y);
    moveServo(flh, 35);
    delay(y * 2);
    moveServo(flk, 180 - neutralKnees);
    moveServo(fla, 180 - neutralKnees);
    delay(y);
    // STEP 4
    moveServo(frk, neutralKnees + kneeUp);
    moveServo(fra, neutralKnees + kneeUp);
    delay(y);
    moveServo(frh, 55);
    delay(y * 2);
    moveServo(frk, neutralKnees);
    moveServo(fra, neutralKnees);
    delay(y);

    // STEP 5
    moveServo(frh, 90);
    moveServo(flh, 90);
    moveServo(brh, 35);
    moveServo(blh, 55);
    delay(y * 2);
    // STEP 6
    if (i != x) {
      moveServo(blk, neutralKnees + kneeUp);
      moveServo(bla, neutralKnees + kneeUp);
      delay(y);
      moveServo(blh, 145);
      delay(y * 2);
      moveServo(blk, neutralKnees);
      moveServo(bla, neutralKnees);
      delay(y);
    }


  }
  moveServo(blk, neutralKnees + kneeUp);
  moveServo(bla, neutralKnees + kneeUp);
  delay(y);
  moveServo(blh, neutralHips);
  delay(y * 2);
  moveServo(blk, neutralKnees);
  moveServo(bla, neutralKnees);
  delay(y);
  moveServo(brk, 180 - (neutralKnees + kneeUp));
  moveServo(bra, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(brh, 180 - neutralHips);
  delay(y * 2);
  moveServo(brk, 180 - neutralKnees);
  moveServo(bra, 180 - neutralKnees);
}

void stepLeftCreepGait(byte x, int y) {
  // Set delays
  // INIT FOR CREEP GAIT
  moveServo(flk, 180 - (neutralKnees + kneeUp));
  moveServo(fla, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(flh, 35);
  delay(y * 2);
  moveServo(flk, 180 - neutralKnees);
  moveServo(fla, 180 - neutralKnees);
  delay(y);
  moveServo(frk, neutralKnees + kneeUp);
  moveServo(fra, neutralKnees + kneeUp);
  delay(y);
  moveServo(frh, 145);
  delay(y * 2);
  moveServo(frk, neutralKnees);
  moveServo(fra, neutralKnees);
  delay(y);

  // Start Repeating
  for (byte i = 1; i <= x; i++) {
    // STEP 1
    moveServo(flk, 180 - (neutralKnees + kneeUp));
    moveServo(fla, 180 - (neutralKnees + kneeUp));
    delay(y);
    moveServo(flh, 125);
    delay(y * 2);
    moveServo(flk, 180 - neutralKnees);
    moveServo(fla, 180 - neutralKnees);
    delay(y);

    // STEP 2
    moveServo(flh, 90);
    moveServo(frh, 90);
    moveServo(blh, 145);
    moveServo(brh, 125);
    delay(y * 2);

    // STEP 3
    moveServo(brk, 180 - (neutralKnees + kneeUp));
    moveServo(bra, 180 - (neutralKnees + kneeUp));
    delay(y);
    moveServo(brh, 35);
    delay(y * 2);
    moveServo(brk, 180 - neutralKnees);
    moveServo(bra, 180 - neutralKnees);
    delay(y);
    // STEP 4
    moveServo(blk, neutralKnees + kneeUp);
    moveServo(bla, neutralKnees + kneeUp);
    delay(y);
    moveServo(blh, 55);
    delay(y * 2);
    moveServo(blk, neutralKnees);
    moveServo(bla, neutralKnees);
    delay(y);

    // STEP 5
    moveServo(blh, 90);
    moveServo(brh, 90);
    moveServo(flh, 35);
    moveServo(frh, 55);
    delay(y * 2);
    // STEP 6
    if (i != x) {
      moveServo(frk, neutralKnees + kneeUp);
      moveServo(fra, neutralKnees + kneeUp);
      delay(y);
      moveServo(frh, 145);
      delay(y * 2);
      moveServo(frk, neutralKnees);
      moveServo(fra, neutralKnees);
      delay(y);
    }


  }
  moveServo(frk, neutralKnees + kneeUp);
  moveServo(fra, neutralKnees + kneeUp);
  delay(y);
  moveServo(frh, neutralHips);
  delay(y * 2);
  moveServo(frk, neutralKnees);
  moveServo(fra, neutralKnees);
  delay(y);
  moveServo(flk, 180 - (neutralKnees + kneeUp));
  moveServo(fla, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(flh, 180 - neutralHips);
  delay(y * 2);
  moveServo(flk, 180 - neutralKnees);
  moveServo(fla, 180 - neutralKnees);
}

void stepForwardsTrotGait(byte x, int y) {
  moveServo(frk, neutralKnees + kneeUp);
  moveServo(fra, neutralKnees + kneeUp);
  delay(y);
  moveServo(frh, 35);
  delay(y * 2);
  moveServo(frk, neutralKnees);
  moveServo(fra, neutralKnees);
  delay(y);
  moveServo(brk, 180 - (neutralKnees + kneeUp));
  moveServo(bra, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(brh, 145);
  delay(y * 2);
  moveServo(brk, 180 - neutralKnees);
  moveServo(bra, 180 - neutralKnees);
  delay(y);
  for (byte r = 1; r <= x; r++) {
    moveServo(frk, neutralKnees + (kneeUp >> 1));
    moveServo(fra, neutralKnees + (kneeUp >> 1));
    moveServo(bla, neutralKnees + (kneeUp >> 1));
    moveServo(blk, neutralKnees + (kneeUp >> 1));
    for (byte i = 90; i <= 145; i++) {
      moveServo(flh, i);
      moveServo(brh, map(i, 90, 145, 145, 90));
      moveServo(frh, 180 - (map(i, 90, 145, 145, 90)));
      moveServo(blh, 180 - i);
      delay(y / 20);
    }
    moveServo(frk, neutralKnees);
    moveServo(fra, neutralKnees);
    moveServo(bla, neutralKnees);
    moveServo(blk, neutralKnees);

    moveServo(flk, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(fla, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(bra, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(brk, 180 - (neutralKnees + (kneeUp >> 1)));
    for (byte i = 145; i >= 90; i--) {
      moveServo(flh, i);
      moveServo(brh, map(i, 145, 90, 90, 145));
      moveServo(frh, 180 - (map(i, 145, 90, 90, 145)));
      moveServo(blh, 180 - i);
      delay(y / 20);
    }
    moveServo(flk, 180 - neutralKnees);
    moveServo(fla, 180 - neutralKnees);
    moveServo(bra, 180 - neutralKnees);
    moveServo(brk, 180 - neutralKnees);
    if (r != x) {
      delay(y);
    }
  }
  moveServo(brk, 180 - (neutralKnees + kneeUp));
  moveServo(bra, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(brh, 180 - neutralHips);
  delay(y * 2);
  moveServo(brk, 180 - neutralKnees);
  moveServo(bra, 180 - neutralKnees);
  delay(y);
  moveServo(frk, neutralKnees + kneeUp);
  moveServo(fra, neutralKnees + kneeUp);
  delay(y);
  moveServo(frh, neutralHips);
  delay(y * 2);
  moveServo(frk, neutralKnees);
  moveServo(fra, neutralKnees);

}

void stepBackwardsTrotGait(byte x, int y) {
  moveServo(blk, neutralKnees + kneeUp);
  moveServo(bla, neutralKnees + kneeUp);
  delay(y);
  moveServo(blh, 35);
  delay(y * 2);
  moveServo(blk, neutralKnees);
  moveServo(bla, neutralKnees);
  delay(y);
  moveServo(flk, 180 - (neutralKnees + kneeUp));
  moveServo(fla, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(flh, 145);
  delay(y * 2);
  moveServo(flk, 180 - neutralKnees);
  moveServo(fla, 180 - neutralKnees);
  delay(y);
  for (byte r = 1; r <= x; r++) {
    moveServo(blk, neutralKnees + (kneeUp >> 1));
    moveServo(bla, neutralKnees + (kneeUp >> 1));
    moveServo(fra, neutralKnees + (kneeUp >> 1));
    moveServo(frk, neutralKnees + (kneeUp >> 1));
    for (byte i = 90; i <= 145; i++) {
      moveServo(brh, i);
      moveServo(flh, map(i, 90, 145, 145, 90));
      moveServo(blh, 180 - (map(i, 90, 145, 145, 90)));
      moveServo(frh, 180 - i);
      delay(y / 20);
    }
    moveServo(blk, neutralKnees);
    moveServo(bla, neutralKnees);
    moveServo(fra, neutralKnees);
    moveServo(frk, neutralKnees);

    moveServo(flk, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(fla, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(bra, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(brk, 180 - (neutralKnees + (kneeUp >> 1)));
    for (byte i = 145; i >= 90; i--) {
      moveServo(brh, i);
      moveServo(flh, map(i, 145, 90, 90, 145));
      moveServo(blh, 180 - (map(i, 145, 90, 90, 145)));
      moveServo(frh, 180 - i);
      delay(y / 20);
    }
    moveServo(flk, 180 - neutralKnees);
    moveServo(fla, 180 - neutralKnees);
    moveServo(bra, 180 - neutralKnees);
    moveServo(brk, 180 - neutralKnees);
    if (r != x) {
      delay(y);
    }
  }
  moveServo(flk, 180 - (neutralKnees + kneeUp));
  moveServo(fla, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(flh, 180 - neutralHips);
  delay(y * 2);
  moveServo(flk, 180 - neutralKnees);
  moveServo(fla, 180 - neutralKnees);
  delay(y);
  moveServo(blk, neutralKnees + kneeUp);
  moveServo(bla, neutralKnees + kneeUp);
  delay(y);
  moveServo(blh, neutralHips);
  delay(y * 2);
  moveServo(blk, neutralKnees);
  moveServo(bla, neutralKnees);

}

void stepRightTrotGait(byte x, int y) {
  moveServo(brk, 180 - (neutralKnees + kneeUp));
  moveServo(bra, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(brh, 35);
  delay(y * 2);
  moveServo(brk, 180 - neutralKnees);
  moveServo(bra, 180 - neutralKnees);
  delay(y);
  moveServo(blk, neutralKnees + kneeUp);
  moveServo(bla, neutralKnees + kneeUp);
  delay(y);
  moveServo(blh, 145);
  delay(y * 2);
  moveServo(blk, neutralKnees);
  moveServo(bla, neutralKnees);
  delay(y);
  for (byte r = 1; r <= x; r++) {
    moveServo(brk, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(bra, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(fla, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(flk, 180 - (neutralKnees + (kneeUp >> 1)));
    for (byte i = 90; i <= 145; i++) {
      moveServo(frh, i);
      moveServo(blh, map(i, 90, 145, 145, 90));
      moveServo(brh, 180 - (map(i, 90, 145, 145, 90)));
      moveServo(flh, 180 - i);
      delay(y / 20);
    }
    moveServo(brk, 180 - neutralKnees);
    moveServo(bra, 180 - neutralKnees);
    moveServo(fla, 180 - neutralKnees);
    moveServo(flk, 180 - neutralKnees);

    moveServo(frk, neutralKnees + (kneeUp >> 1));
    moveServo(fra, neutralKnees + (kneeUp >> 1));
    moveServo(bla, neutralKnees + (kneeUp >> 1));
    moveServo(blk, neutralKnees + (kneeUp >> 1));
    for (byte i = 145; i >= 90; i--) {
      moveServo(frh, i);
      moveServo(blh, map(i, 145, 90, 90, 145));
      moveServo(brh, 180 - (map(i, 145, 90, 90, 145)));
      moveServo(flh, 180 - i);
      delay(y / 20);
    }
    moveServo(frk, neutralKnees);
    moveServo(fra, neutralKnees);
    moveServo(bla, neutralKnees);
    moveServo(blk, neutralKnees);
    if (r != x) {
      delay(y);
    }
  }
  moveServo(blk, neutralKnees + kneeUp);
  moveServo(bla, neutralKnees + kneeUp);
  delay(y);
  moveServo(blh, 180 - neutralHips);
  delay(y * 2);
  moveServo(blk, neutralKnees);
  moveServo(bla, neutralKnees);
  delay(y);
  moveServo(brk, 180 - (neutralKnees + kneeUp));
  moveServo(bra, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(brh, neutralHips);
  delay(y * 2);
  moveServo(brk, 180 - neutralKnees);
  moveServo(bra, 180 - neutralKnees);

}

void stepLeftTrotGait(byte x, int y) {
  moveServo(flk, 180 - (neutralKnees + kneeUp));
  moveServo(fla, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(flh, 35);
  delay(y * 2);
  moveServo(flk, 180 - neutralKnees);
  moveServo(fla, 180 - neutralKnees);
  delay(y);
  moveServo(frk, neutralKnees + kneeUp);
  moveServo(fra, neutralKnees + kneeUp);
  delay(y);
  moveServo(frh, 145);
  delay(y * 2);
  moveServo(frk, neutralKnees);
  moveServo(fra, neutralKnees);
  delay(y);
  for (byte r = 1; r <= x; r++) {
    moveServo(brk, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(bra, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(fla, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(flk, 180 - (neutralKnees + (kneeUp >> 1)));
    for (byte i = 90; i <= 145; i++) {
      moveServo(blh, i);
      moveServo(frh, map(i, 90, 145, 145, 90));
      moveServo(flh, 180 - (map(i, 90, 145, 145, 90)));
      moveServo(brh, 180 - i);
      delay(y / 20);
    }
    moveServo(brk, 180 - neutralKnees);
    moveServo(bra, 180 - neutralKnees);
    moveServo(fla, 180 - neutralKnees);
    moveServo(flk, 180 - neutralKnees);

    moveServo(frk, neutralKnees + (kneeUp >> 1));
    moveServo(fra, neutralKnees + (kneeUp >> 1));
    moveServo(bla, neutralKnees + (kneeUp >> 1));
    moveServo(blk, neutralKnees + (kneeUp >> 1));
    for (byte i = 145; i >= 90; i--) {
      moveServo(blh, i);
      moveServo(frh, map(i, 145, 90, 90, 145));
      moveServo(flh, 180 - (map(i, 145, 90, 90, 145)));
      moveServo(brh, 180 - i);
      delay(y / 20);
    }
    moveServo(frk, neutralKnees);
    moveServo(fra, neutralKnees);
    moveServo(bla, neutralKnees);
    moveServo(blk, neutralKnees);
    if (r != x) {
      delay(y);
    }
  }
  moveServo(frk, neutralKnees + kneeUp);
  moveServo(fra, neutralKnees + kneeUp);
  delay(y);
  moveServo(frh, 180 - neutralHips);
  delay(y * 2);
  moveServo(frk, neutralKnees);
  moveServo(fra, neutralKnees);
  delay(y);
  moveServo(flk, 180 - (neutralKnees + kneeUp));
  moveServo(fla, 180 - (neutralKnees + kneeUp));
  delay(y);
  moveServo(flh, neutralHips);
  delay(y * 2);
  moveServo(flk, 180 - neutralKnees);
  moveServo(fla, 180 - neutralKnees);

}

void raiseBody(int x, int y) {
  if (neutralKnees + x > 180) {
    x = 180 - neutralKnees;
  }
  if (neutralKnees + x < 1) {
    x = 1 - neutralKnees;
  }
  if (x > 0) {
    for (byte i = neutralKnees; i <= neutralKnees + x; i++) {
      moveServo(blk, i);
      moveServo(brk, 180 - i);
      moveServo(frk, i);
      moveServo(flk, 180 - i);
      moveServo(bla, i);
      moveServo(bra, 180 - i);
      moveServo(fra, i);
      moveServo(fla, 180 - i);
      delay(y);
    }
    neutralKnees = neutralKnees + x;
    neutralAnkles = neutralAnkles + x;
  }
  else {
    for (byte i = neutralKnees; i >= neutralKnees + x; i--) {
      moveServo(blk, i);
      moveServo(brk, 180 - i);
      moveServo(frk, i);
      moveServo(flk, 180 - i);
      moveServo(bla, i);
      moveServo(bra, 180 - i);
      moveServo(fra, i);
      moveServo(fla, 180 - i);
      delay(y);
    }
    neutralKnees = neutralKnees + x;
    neutralAnkles = neutralAnkles + x;
  }
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


void squat(byte x) {
  byte cnn = neutralKnees;
  raiseBody(180 - neutralKnees, 5);
  delay(1000);
  for (byte i = 1; i <= x; i++) {
    raiseBody(-70, 5);
    delay(400);
    raiseBody(70, 5);
    delay(400);
  }
  delay(1000);
  raiseBody(110 - neutralKnees, 5);
}

void turnRight(byte x, int y) {
  for (byte i = 1; i <= x; i++) {
    moveServo(frk, neutralKnees + (kneeUp >> 1));
    moveServo(fra, neutralKnees + (kneeUp >> 1));
    moveServo(blk, neutralKnees + (kneeUp >> 1));
    moveServo(bla, neutralKnees + (kneeUp >> 1));
    delay(y);
    moveServo(blh, 45);
    moveServo(frh, 45);
    delay(y);
    moveServo(frk, neutralKnees);
    moveServo(fra, neutralKnees);
    moveServo(blk, neutralKnees);
    moveServo(bla, neutralKnees);
    delay(y);
    moveServo(flk, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(fla, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(brk, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(bra, 180 - (neutralKnees + (kneeUp >> 1)));
    delay(y);
    moveServo(flh, 45);
    moveServo(brh, 45);
    delay(y);
    moveServo(flk, 180 - neutralKnees);
    moveServo(fla, 180 - neutralKnees);
    moveServo(brk, 180 - neutralKnees);
    moveServo(bra, 180 - neutralKnees);

    delay(y);
    moveServo(blh, neutralHips);
    moveServo(brh, 180 - neutralHips);
    moveServo(flh, 180 - neutralHips);
    moveServo(frh, neutralHips);
    delay(y);
  }
}

void turnLeft(byte x, int y) {
  for (byte i = 1; i <= x; i++) {
    moveServo(frk, neutralKnees + (kneeUp >> 1));
    moveServo(fra, neutralKnees + (kneeUp >> 1));
    moveServo(blk, neutralKnees + (kneeUp >> 1));
    moveServo(bla, neutralKnees + (kneeUp >> 1));
    delay(y);
    moveServo(blh, 135);
    moveServo(frh, 135);
    delay(y);
    moveServo(frk, neutralKnees);
    moveServo(fra, neutralKnees);
    moveServo(blk, neutralKnees);
    moveServo(bla, neutralKnees);
    delay(y);
    moveServo(flk, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(fla, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(brk, 180 - (neutralKnees + (kneeUp >> 1)));
    moveServo(bra, 180 - (neutralKnees + (kneeUp >> 1)));
    delay(y);
    moveServo(flh, 135);
    moveServo(brh, 135);
    delay(y);
    moveServo(flk, 180 - neutralKnees);
    moveServo(fla, 180 - neutralKnees);
    moveServo(brk, 180 - neutralKnees);
    moveServo(bra, 180 - neutralKnees);

    delay(y);
    moveServo(blh, neutralHips);
    moveServo(brh, 180 - neutralHips);
    moveServo(flh, 180 - neutralHips);
    moveServo(frh, neutralHips);
    delay(y);
  }
}

void pressUp(byte x) {
  byte currentNeutralKnees = neutralKnees;
  raiseBody(90 - neutralKnees, 10);
  for (byte i = neutralAnkles; i >= sleepAnkles + 1; i--) {
    moveServo(bla, i);
    moveServo(bra, 180 - i);
    moveServo(fra, i);
    moveServo(fla, 180 - i);
    Serial.println(i);
    delay(10);
  }
  for (byte i = 90; i <= 145; i++) {
    moveServo(frh, 180 - i);
    moveServo(brh, 180 - i);
    moveServo(blh, i);
    moveServo(flh, i);
    delay(10);
  }
  for (byte i = sleepAnkles; i <= neutralAnkles; i++) {
    moveServo(bla, i);
    moveServo(bra, 180 - i);
    moveServo(fra, i);
    moveServo(fla, 180 - i);
    delay(10);
  }
  delay(1000);

  // Robot is in pressup position.

  for (byte i = 1; i <= x; i++) {
    // PRESS UP

    for (byte i = neutralKnees; i <= 170; i++) {
      moveServo(fra, i);
      moveServo(frk, i);
      moveServo(fla, 180 - i);
      moveServo(flk, 180 - i);
      delay(5);
    }

    // GO DOWN

    for (byte i = 170; i >= neutralKnees + 20; i--) {
      moveServo(fra, i);
      moveServo(frk, i);
      moveServo(fla, 180 - i);
      moveServo(flk, 180 - i);
      delay(5);
    }
  }

  for (byte i = neutralKnees + 20; i >= neutralKnees; i--) {
    moveServo(fra, i);
    moveServo(frk, i);
    moveServo(fla, 180 - i);
    moveServo(flk, 180 - i);
    delay(5);
  }
  // Robot has done pressups
  delay(1000);
  for (byte i = neutralAnkles; i >= sleepAnkles + 1; i--) {
    moveServo(bla, i);
    moveServo(bra, 180 - i);
    moveServo(fra, i);
    moveServo(fla, 180 - i);
    delay(10);
  }
  for (byte i = 145; i >= 90; i--) {
    moveServo(frh, 180 - i);
    moveServo(brh, 180 - i);
    moveServo(blh, i);
    moveServo(flh, i);
    delay(10);
  }
  for (byte i = sleepAnkles + 1; i <= neutralAnkles; i++) {
    moveServo(bla, i);
    moveServo(bra, 180 - i);
    moveServo(fra, i);
    moveServo(fla, 180 - i);
    delay(10);
  }
  raiseBody(currentNeutralKnees - neutralKnees, 10);

}

void setup() {
  // put your setup code here, to run once:
  setServos();
  Serial.begin(57600);
  IR.enableIRIn();
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
