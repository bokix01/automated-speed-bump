#include <Servo.h>

const int led_r = 3;
const int led_g = 4;
const int led_b = 5;

const int trig_pin_1 = 9;
const int echo_pin_1 = 10;
const int trig_pin_2 = 11;
const int echo_pin_2 = 12;

const int motor = 7;

Servo MG995_Servo;

const int motor_rotation_speed = 15;
const int motor_attach_delay = 3000;

const float space_between = 14;
const float speed_limit = 0.7;

const float min_distance = 2;
const float max_distance = 8;
const int default_angle = 0;
const int max_angle = 180;

void setup() {
  Serial.begin(9600);
  pinMode(led_r, OUTPUT);
  pinMode(led_g, OUTPUT);
  pinMode(led_b, OUTPUT);

  pinMode(trig_pin_1, OUTPUT);
  pinMode(echo_pin_1, INPUT);
  pinMode(trig_pin_2, OUTPUT);
  pinMode(echo_pin_2, INPUT);

  MG995_Servo.attach(motor);
  MG995_Servo.write(default_angle);
}

float get_distance(int trig_pin, int echo_pin, int sensor_num) {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  float duration, distance;
  duration = pulseIn(echo_pin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance ");
  Serial.print(sensor_num);
  Serial.print(": ");
  Serial.println(distance);

  return distance;
}

int start_timer() {
  float start_ms = millis();
  while (true) {
    float distance_2 = get_distance(trig_pin_2, echo_pin_2, 2);
    if (min_distance < distance_2 && distance_2 < max_distance) {
      float end_ms = millis();
      return end_ms - start_ms;
    }
  }
}

void speed_bump() {
  for (int angle = 0; angle < max_angle; angle++) {
    MG995_Servo.write(angle);
    delay(motor_rotation_speed);
  }

  MG995_Servo.detach();
  delay(motor_attach_delay);
  MG995_Servo.attach(motor);
  
  MG995_Servo.write(default_angle);
  delay(max_angle * motor_rotation_speed);
  MG995_Servo.detach();
  delay(motor_attach_delay);
  MG995_Servo.attach(motor);
}

void loop() {
  float distance_1 = get_distance(trig_pin_1, echo_pin_1, 1);
  if (min_distance < distance_1 && distance_1 < max_distance) {
    digitalWrite(led_b, HIGH);
    int time_ms = start_timer();
    digitalWrite(led_b, LOW);

    double speed = ((space_between/100.0) / (time_ms/1000.0)) * 3.6;
    Serial.print("Speed: ");
    Serial.print(speed, 2);
    Serial.println(" kmh");
    
    if (speed > speed_limit) {
      digitalWrite(led_r, HIGH);
      speed_bump();
      digitalWrite(led_r, LOW);
    } else {
      digitalWrite(led_g, HIGH);
      delay(max_angle*motor_rotation_speed + 2*motor_attach_delay);
      digitalWrite(led_g, LOW);
    }
  }
}
