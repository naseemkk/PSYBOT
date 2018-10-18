#define ir 2;

#define trigPin1 3;
#define echoPin1 4;

#define en1 5;
#define en2 6;

#define trigPin2 7;
#define echoPin2 8;

#define switch1 9;
#define switch2 10;
#define buzzer 13;

#define in1 14;
#define in2 15;
#define in3 16;
#define in4 17;

int count;
float distance;
int tmpcount;

void setup() {
  // put your setup code here, to run once:

  //IR sensor
  pinMode(ir, INPUT);

  //UltraSonic sensor front
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  //Motor driver enable pins
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);

  //UltraSonic sensor side
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  //Switch1
  pinMode(switch1, INPUT);

  //switch2
  pinMode(switch2, INPUT);

  //Right set of wheels
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //Left set of wheels
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //Buzzer
  pinMode(buzzer, OUTPUT);

  analogWrite(en1, 70);
  analogWrite(en2, 70);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(switch1) == 0) {
    count = 75;
    forward();
  
    rightTurn();
  
    count = 200 - tmpcount;
    forward();
  
    leftTurn();
  
    count = 25 - tmpcount;
    forward();

    digitalWrite(buzzer, HIGH);
    delay(5000);
    digitalWrite(buzzer, LOW);
    
    rightTurn();
    rightTurn();
  
    count = 25;
    forward();
  
    rightTurn();
  
    count =  200 - tmpcount;
    forward();
  
    leftTurn();
    
    count = 75 + tmpcount;
    forward();
  
    rightTurn();
    rightTurn();
  
  } else if (digitalRead(switch2) == 0) {
    count = 50;
    forward();
  
    rightTurn();
  
    count = 125 - tmpcount;
    forward();
  
    digitalWrite(buzzer, HIGH);
    delay(5000);
    digitalWrite(buzzer, LOW);
    
    rightTurn();
    rightTurn();
  
    count = 125;
    forward();
  
    leftTurn();
  
    count =  50 + tmpcount;
    forward();
  
    rightTurn();
    rightTurn();
  }
}

void forward() {
  while(count > 0) {
    distance = ultrasonic(trigPin1, echoPin1);
    
    if(distance > 2 && distance <= 40) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      
      // Rerouting codes
      reroute();
    } else {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);

      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      
      // Check the sensor output
      if(digitalRead(ir) == HIGH) {
        while(digitalRead(ir) == HIGH) {
          // To count a division only once
        }
        count--;
      }
    }
  } //While loop
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

float ultrasonic(int id1,int id2) {
  float cm, duration;
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(id1, LOW);
  delayMicroseconds(2);
  digitalWrite(id1, HIGH);
  delayMicroseconds(10);
  digitalWrite(id1, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(id2, HIGH);

  // convert the time into a distance
  cm = (duration / 2) * 0.0344;    // As half duration is required to find the distance

  return cm;
}

void rightTurn() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(500);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void leftTurn() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(500);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

long reroute() {
  tmpcount = 0;
  int c;
  
  rightTurn();
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  distance = ultrasonic(trigPin2, echoPin2);

  while(distance > 2 && distance <= 40) { //distance calculated from the left ultrasonic sensor
    if(digitalRead(ir) == HIGH) { //input from ir sensor to measure the number of rotations
      while(digitalRead(ir) == HIGH) {
        //To count a division only once
      }
      tmpcount++;
    }
    distance = ultrasonic(trigPin2, echoPin2);
  }
  
  c = 10;
  while(c > 0) {
    if(digitalRead(ir) == HIGH) { //input from ir sensor to measure the number of rotations
      while(digitalRead(ir) == HIGH) {
        //To count a division only once
      }
      c--;
      tmpcount++;
    }
  }
    
  leftTurn();

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  distance = ultrasonic(trigPin2, echoPin2);
  
  while(distance > 2 && distance <= 40) { //distance calculated from the left ultrasonic sensor
    if(count == 0) {
      return 0;
    } else {
      if(digitalRead(ir) == HIGH) { //input from ir sensor to measure the number of rotations
        while(digitalRead(ir) == HIGH) {
          //To count a division only once
        }
        count--;
      }
    }
    distance = ultrasonic(trigPin2, echoPin2);
  }
  
  c = 10;
  while(c > 0) {
    if(digitalRead(ir) == HIGH) { //input from ir sensor to measure the number of rotations
      while(digitalRead(ir) == HIGH) {
        //To count a division only once
      }
      c--;
      count--;
    }
  }
  
  leftTurn();
  
  while(tmpcount != 0) {
    if(digitalRead(ir) == HIGH) { //input from ir sensor to measure the number of rotations
      while(digitalRead(ir) == HIGH) {
        //To count a division only once
      }
      tmpcount--;
    }
  }
  
  rightTurn();
}