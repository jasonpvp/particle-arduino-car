// Send RC car commands to Arduino

#include "HttpClient/HttpClient.h"

const int
//serial commands
MOVE_FORWARD = 1,
MOVE_BACKWARD = 2,
TURN_LEFT = 3,
TURN_RIGHT = 4,
BRAKE = 5;

const int updateInterval = 10;

int t;
int value;
char c;
char printBuff[64];
String altSerialBuffer;
int lastUpdateTime;

HttpClient http;
static const char* HOSTNAME   = "http://guarded-shore-3605.herokuapp.com/";
static const char* POST_URL   = "robot";
http_header_t headers[] = {
  { "Content-Type", "application/json" },
  { "Accept" , "application/json" },
  { "X-Access-Key" , "mykey" },
  { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;

void setup() {
  Serial.begin(9600);             // init Serial for logging output to the console
  Serial1.begin(9600);            // init Serial1 for communicationover rx/tx pins
  Serial.write("begin");
  t = MOVE_FORWARD;
  value = 0;
  request.hostname = HOSTNAME;
  request.port = 80;
  request.path = POST_URL;
  lastUpdateTime = 0;
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
  
  attemptUpdate();
  delay(100);
}

void attemptUpdate() {
    int t = Time.now();
    if (lastUpdateTime + updateInterval <= t) {
        statusUpdate();
        lastUpdateTime = t;
    }
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

void statusUpdate() {
    Serial.println("post status update");

    String body = "{\"status\":\"updated at";
    body.concat(String(lastUpdateTime));
    body.concat("\"}");
    request.body = body;
    
    http.post(request, response, headers);
    
    Serial.println(response.body);
}

