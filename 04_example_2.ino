
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while(!Serial){
    ; // wait for serial port to connect. Needed for native USB.
  }
}

void loop() {
  Serial.println("Hello World!");
  delay(1000); // wait for 1,000 milliseconds
}