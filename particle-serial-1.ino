// Super-hacky first Particle program to test serial communication
// Load this to your Particle, then
// Connect TX pin to RX pin, turn on the Particle console, and watch it talk to itself!

int state;
char c;

void setup() {
	Serial.begin(9600);             // init Serial for logging output to the console
	Serial1.begin(9600);            // init Serial1 for communicationover rx/tx pins
	Serial.write("begin");
	t = 0;
}


void loop() {
  if (state == 0) {
	  Serial1.write("pingx");       // write data over tx
	  state = 1;
	} else if (state == 1) {
	  if (Serial1.available()) {
	    c = Serial1.read();         // read data from rx
	    Serial.write(c);            // output read char to console
	    if (c == 'x')
	      state = 2;
	  }
	} else {                        // reset state and wait
	    state = 0;
	    delay(1000);
	}
}
