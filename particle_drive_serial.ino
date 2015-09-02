// Send RC car commands to Arduino


const int
//serial commands
MOVE_FORWARD = 1,
MOVE_BACKWARD = 2,
TURN_LEFT = 3,
TURN_RIGHT = 4,
BRAKE = 5;

int t;
int value;
char c;
char printBuff[64];
String altSerialBuffer;

void setup() {
  Serial.begin(9600);             // init Serial for logging output to the console
  Serial1.begin(9600);            // init Serial1 for communicationover rx/tx pins
  Serial.write("begin");
  t = MOVE_FORWARD;
  value = 0;
}


void loop() {
  char inChar;

  if (Serial1.available()) {
    inChar = Serial1.read();
    altSerialBuffer += inChar;
    if (inChar == '\n') {
      processCommand(altSerialBuffer);
      altSerialBuffer = "";
    }
  }
  
  sendCommand(t, value);
  value += 20;
  if (value > 255) {
      value = 0;
      sendCommand(t, value);
      t++;
      if (t > TURN_RIGHT) {
          sendCommand(BRAKE, 0);
          t = MOVE_FORWARD;
      }
  }
  delay(100);
}

void sendCommand(int action, int value) {
    char command[8];
    sprintf(command, "%d %d\n", action, value);
    sprintf(printBuff, "Send command: %s\n", command);
    Serial.write(printBuff);
    Serial1.write(command);
}

void processCommand(String command) {
  int action = 0;
  int val = 0;
  int tokenIndex = command.indexOf(' ');
  if (tokenIndex > -1) {
    action = command.substring(0, tokenIndex - 1).toInt();
    val = command.substring(tokenIndex + 1).toInt();
  } else {
    action = command.toInt();
  }
  sprintf(printBuff, "got command: %d %d\n", action, val);
  Serial.write(printBuff);
}
