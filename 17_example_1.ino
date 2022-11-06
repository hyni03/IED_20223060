#include <Servo.h>

// Arduino pin assignment
#define PIN_LED  9

#define PIN_POTENTIOMETER 3 // Potentiometer at Pin A3

// Add IR Sensor Definition Here !!!
#define IR 0

#define PIN_SERVO 10
#define _SERVO_SPEED 50 // servo speed limit (unit: degree/second)
#define INTERVAL 20     // servo update interval (unit: msec)

#define _DUTY_MIN 550  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1480 // servo neutral position (90 degree)
#define _DUTY_MAX 2410 // servo full counter-clockwise position (180 degree)

#define _DIST_MAX 250.0
#define _DIST_MIN 100.0

#define LOOP_INTERVAL 20   // Loop Interval (unit: msec)
#define _EMA_ALPHA 0.5    //// EMA weight of new sample (range: 0 to 1)

Servo myservo;
unsigned long last_loop_time;   // unit: msec

float dist_prev;
float dist_ema;

void setup()
{
  pinMode(PIN_LED, OUTPUT);
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  
  Serial.begin(2000000);
}

void loop()
{
  int dist_raw;
  unsigned long time_curr = millis();
  int a_value, duty;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;

  last_loop_time += LOOP_INTERVAL;

  // Remove Next line !!!
  // Read IR Sensor value !!!
  a_value = analogRead(IR);

  // Convert IR sensor value into distance !!!
  dist_raw = (6762.0/(a_value-9)-4.0)*10.0 - 60.0;
  
  // we need distance range filter here !!!
  if (dist_raw < _DIST_MIN) {
    dist_raw = dist_prev;           // cut lower than minimum
    digitalWrite(PIN_LED, 1);       // LED OFF
  } else if (dist_raw > _DIST_MAX) {
    dist_raw = dist_prev;           // Cut higher than maximum
    digitalWrite(PIN_LED, 1);       // LED OFF
  } else {    // In desired Range     
    dist_prev = dist_raw;
    digitalWrite(PIN_LED, 0);       // LED ON 
  }

  // we need EMA filter here !!!
  dist_ema = _EMA_ALPHA * dist_raw + (1 - _EMA_ALPHA) * dist_ema;

  // Modify the below line to implement the EMA equation 
  duty = (float)(dist_ema - _DIST_MIN) * (_DUTY_MAX - _DUTY_MIN)/(_DIST_MAX - _DIST_MIN) + _DIST_MIN;
  myservo.writeMicroseconds(duty);

  // print IR sensor value, distnace, duty !!!
  Serial.print("MIN:"); Serial.print(_DIST_MIN);
  Serial.print(",IR:"); Serial.print(a_value);
  Serial.print(",dist:"); Serial.print(dist_raw);
  Serial.print(",ema:"); Serial.print(dist_ema);
  Serial.print(",servo: "); Serial.print(duty);
  Serial.print(",MAX:"); Serial.print(_DIST_MAX);
  Serial.println("");
}


