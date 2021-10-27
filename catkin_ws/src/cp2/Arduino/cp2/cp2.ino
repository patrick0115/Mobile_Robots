#include <ros.h>
#include <std_msgs/Int16.h>

#define in1 4
#define in2 5
#define in3 6
#define in4 7
#define ENB 10
#define ENA 11

ros::NodeHandle nh;  //manages an internal reference count

int pwm_r=0;
int pwm_l=0;

void cb_r(const std_msgs::Int16& msg){
  input_value_R = msg.data;
}
void cb_l(const std_msgs::Int16& msg){
  input_value_L = msg.data;
}

ros::Subscriber<std_msgs::Int16> sub_R("pwm_value_R", &cb_r);
ros::Subscriber<std_msgs::Int16> sub_L("pwm_value_L", &cb_l);


void setup() {
  nh.initNode();
  nh.subscribe(sub_R);
  nh.subscribe(sub_L;
  pinMode(OUTPUT, in1);
  pinMode(OUTPUT, in2);
  pinMode(OUTPUT, in3);
  pinMode(OUTPUT, in4);
  pinMode(OUTPUT, ENA);
  pinMode(OUTPUT, ENB);

}

void loop() {
  if(pwm_r >=0 and pwm_l >= 0){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(ENA,pwm_l);
    analogWrite(ENB,pwm_r);
  }
  else if(pwm_r >=0 and pwm_l <= 0){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    analogWrite(ENA,pwm_l);
    analogWrite(ENB,abs(pwm_r));
  }
  else if(pwm_r <=0 and pwm_l >= 0){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(ENA,abs(pwm_l));
    analogWrite(ENB,pwm_r );
  }
  else if(pwm_r ==0 and pwm_l == 0){
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    analogWrite(ENA,pwm_r);
    analogWrite(ENB,pwm_l );
  }
  else {
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    analogWrite(ENA,pwm_l);
    analogWrite(ENB,pwm_r);
  }  
  nh.spinOnce();
}
