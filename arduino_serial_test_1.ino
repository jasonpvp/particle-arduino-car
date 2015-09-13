#include <AltSoftSerial.h>

AltSoftSerial altSerial;
int t;
char c;

void setup() {
  Serial.begin(9600);
  Serial.println("AltSoftSerial Test Begin");
  altSerial.begin(9600);
  altSerial.println("Hello World");
  t = 0;
}

void loop() {
  if (t == 0) {
    altSerial.println("pongx");
    t = 1;
  } else if (t == 1) {
    if (altSerial.available()) {
      c = altSerial.read();
      Serial.write(c);
      if (c == 'x')
        t = 2;
    }
  } else {
      t = 0;
      delay(1000);
  }
}


