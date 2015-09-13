int t;
char c;

void setup() {
  //Spark.function("sendData", sendData);

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.write("begin");
  t = 0;
}


void loop() {
    if (t == 0) {
    Serial1.write("pingx");
    t = 1;
  } else if (t == 1) {
    if (Serial1.available()) {
      c = Serial1.read();
      Serial.write(c);
      if (c == 'x')
        t = 2;
    }
  } else {
      t = 0;
      delay(1000);
  }
}

