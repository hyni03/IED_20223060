#define PIN_LED 7
unsigned int toggle, i;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN_LED, toggle);
  delay(1000);  

  for(i=1;i<=10;i++){
    toggle = toggle_state(toggle);
    digitalWrite(PIN_LED, toggle);
    delay(100);
  }

  while(1){
    digitalWrite(PIN_LED, 1);
  }
}

int toggle_state(int toggle){
  return !toggle;
}