//#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

// interupts for mega: 2, 3, 18, 19, 20, 21
#define encoder1I   2   // 1 - wrist L
#define encoder1R   4
#define encoder2I   3   // 2 - wrist R
#define encoder2R   5
#define encoder3I   18  // 3 - wrist yaw
#define encoder3R   22
#define encoder4I   19  // 4 - shoulder
#define encoder4R   23
#define encoder5I   20  // 5 - elbow ##################
#define encoder5R   24
#define encoder6I   21  // 6 - gripper
#define encoder6R   25

#define buttonB     6
#define buttonF     7

#define buttonEN    10
#define getEN()     (!digitalRead(buttonEN))
#define buttonEN_D  3
#define getEN_D()   (!digitalRead(buttonEN_D))

#define motor1F     8 // ##############################
#define motor1B     9

//  Encoder en1(encoder1I, encoder1R); // 1
//  Encoder en2(encoder2I, encoder2R); // 2
//  Encoder en3(encoder3I, encoder3R); // 3
//  Encoder en4(encoder4I, encoder4R); // 4
Encoder en5(encoder5I, encoder5R); // 5
//  Encoder en6(encoder6I, encoder6R); // 6

void setup() {
  //  int forward = 0;
  //  int backward = 0;
  // put your setup code here, to run once:
  Serial.begin(250000);
  Serial.println("\n\nProgram Start");
  delay(100);
  Serial.print("Initializing Pins");
  pinMode(buttonEN, INPUT_PULLUP);
  Serial.write('.');
  pinMode(buttonEN_D, INPUT_PULLUP);
  Serial.write('.');
  Serial.println(".");
  delay(400);
  Serial.println("done\n");
}

const double conv = 14.6113;
unsigned long count = 0;
bool motorOn;
bool dState;

void loop() {
  // put your main code here, to run repeatedly:
  motorOn = getEN();
  dState = getEN_D();
  if (motorOn) {
    Serial.println(en5.read());
    long enc = en5.read();
    Serial.println(enc);
    double deg = enc / conv;
    Serial.println(String(count) + " seconds");
    Serial.println("Encoder at " + String(deg, 5) + " degrees\n");
  } else {
    //
  }
  for (int i = 0; i < 100; i++) {
    bool buttonState = getEN();
    bool dB_State = getEN_D();
    if (buttonState != motorOn || dB_State != dState) {
      Serial.println("==================================================\n\nMotor turned " + getWord(buttonState, dState) + "\n"); // \n\n==================================================
      motorOn = buttonState;
      dState = dB_State;
      runMotor();
    }
    delay(10);
  }
  count++;
}

void runMotor() {
  if (motorOn) {
    if (dState) {
      analogWrite(motor1F, 60);
      analogWrite(motor1B, 0);
    } else {
      analogWrite(motor1F, 0);
      analogWrite(motor1B, 60);
    }
  } else {
    analogWrite(motor1F, 0);
    analogWrite(motor1B, 0);
  }
}

String getWord(bool b, bool d) {
  if (b) {
    if (d) return "forward";
    else return "backward";
  } else return "off";
}

