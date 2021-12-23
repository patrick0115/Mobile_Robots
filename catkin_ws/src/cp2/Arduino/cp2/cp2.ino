#include <ros.h>
#include <std_msgs/Int16.h>

#define in1 4
#define in2 5
#define in3 6
#define in4 7
#define ENA 10
#define ENB 11

ros::NodeHandle nh; 

int dir = 0;

void cb(const std_msgs::Int16& msg) {
  dir= msg.data;
}

ros::Subscriber<std_msgs::Int16> sub("dir_value", &cb);

void setup() {
  nh.initNode();
  nh.subscribe(sub);
  pinMode(OUTPUT, in1);
  pinMode(OUTPUT, in2);
  pinMode(OUTPUT, in3);
  pinMode(OUTPUT, in4);
  pinMode(OUTPUT, ENA);
  pinMode(OUTPUT, ENB);

}

void loop() {
  if (dir==2) {
    motor(150, 150);
  }
  else if (dir==1) {
    motor(150,100);
  }
  else if (dir==3) {
    motor(100,140);
  }
  else if (dir==4) {
    motor(0,0);
  }
  nh.spinOnce();
}

int motor(int input_value_L, int input_value_R) {
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
    analogWrite(ENA, input_value_L);
    analogWrite(ENB, input_value_R );
  }
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(ENA, input_value_L);
    analogWrite(ENB, input_value_R);
  }

}
