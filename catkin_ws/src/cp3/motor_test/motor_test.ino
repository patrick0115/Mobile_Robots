#include <ros.h>
#include <std_msgs/Int16.h>

const int light = A0;
#define in1 4
#define in2 5
#define in3 6
#define in4 7
#define ENA 10
#define ENB 11
int light_value = 0;

ros::NodeHandle nh;  //manages an internal reference count

int state = 0;


void cb_r(const std_msgs::Int16& msg) {
  state= msg.data;
}

ros::Subscriber<std_msgs::Int16> sub_R("touch", &cb_r);

void setup() {
  Serial.begin(9600);
  //nh.initNode();
  nh.subscribe(sub_R);
  nh.subscribe(sub_L);
  pinMode(light, INPUT);
  pinMode(OUTPUT, in1);
  pinMode(OUTPUT, in2);
  pinMode(OUTPUT, in3);
  pinMode(OUTPUT, in4);
  pinMode(OUTPUT, ENA);
  pinMode(OUTPUT, ENB);

}

void loop() {
  light_value = analogRead(light);
  Serial.println(light_value, DEC);
  if (light_value < 100) {
    if (state==1) {
      motor(60, 130);
    }
    else if (state==2) {
      motor(130, 60);
    }
    else if (state==3) {
      motor(-130, -130);
    }
    else {
      motor(64, 64);
    }
  }
  else if (light_value > 100) {
    motor(64, 64);
    if (light_value > 500) {
      motor(0, 0);
    }
  }
  delay(500);
}

int motor(int input_value_R, int input_value_L) {
  if (input_value_R >= 0 and input_value_L >= 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(ENA, input_value_L );
    analogWrite(ENB, input_value_R);
  }
  else if (input_value_R >= 0 and input_value_L <= 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(ENA, input_value_L);
    analogWrite(ENB, abs(input_value_R));
  }
  else if (input_value_R <= 0 and input_value_L >= 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(ENA, abs(input_value_L));
    analogWrite(ENB, input_value_R );
  }
  else if (input_value_R == 0 and input_value_L == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(ENA, input_value_R);
    analogWrite(ENB, input_value_L );
  }
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(ENA, input_value_L);
    analogWrite(ENB, input_value_R);
  }
  nh.spinOnce();
}
