# Automated speed bump

The innovation is called "Automated speed bump" and can be used on any roads with speed limits. It measures the speed of cars and if they are speeding the speed bump will rise, otherwise it will be down and the road will be flat.

### Components
- Arduino Uno Rev3
- 2x HC-SR04 (Ultrasonic sensors)
- MG995 (Servo motor)

You can adjust the space between the two sensors and the speed limit in these variables:
```
const float space_between = 14; // <-- Value here (cm)
const float speed_limit = 0.8; // <-- Value here (kmh)
```

You can as well adjust accepted distances between a car and sensors in these variables:
```
const float min_distance = 2; // <-- Value here (cm)
const float max_distance = 8; // <-- Value here (cm)
```

You can as well adjust motor speed and motor delay in these variables:
```
const int motor_rotation_speed = 15; // <-- Value here (ms)
const int motor_attach_delay = 3000; // <-- Value here (ms)
```
