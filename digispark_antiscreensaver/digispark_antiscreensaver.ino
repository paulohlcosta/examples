// esse programa fica movendo o mouse para nao entrar screensaver

#include <DigiMouse.h>

void setup() {
  DigiMouse.begin(); //start or reenumerate USB - BREAKING CHANGE from old versions that didn't require this
  pinMode(1, OUTPUT);
  digitalWrite(1, LOW);
}

void loop() {

  DigiMouse.moveY(1);
  digitalWrite(1, HIGH);
  DigiMouse.delay(80);
  digitalWrite(1, LOW);
  DigiMouse.delay(55000);

}
