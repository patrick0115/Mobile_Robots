#include <ros.h>
#include <std_msgs/Int16.h>

const int r = A0; 
#define in1 4
#define in2 5
#define in3 6
#define in4 7
#define ENA 10
#define ENB 11
int r_value=0;

ros::NodeHandle nh;  //manages an internal reference count

int input_value_R=0;
int input_value_L=0;

void cb_r(const std_msgs::Int16& msg){
  input_value_R = msg.data;
}
void cb_l(const std_msgs::Int16& msg){
  input_value_L = msg.data;
}

ros::Subscriber<std_msgs::Int16> sub_R("pwm_value_R", &cb_r);
ros::Subscriber<std_msgs::Int16> sub_L("pwm_value_L", &cb_l);


void setup() {
  Serial.begin(9600);
  //nh.initNode();
  nh.subscribe(sub_R);
  nh.subscribe(sub_L);
  pinMode(r, INPUT);
  pinMode(OUTPUT, in1);
  pinMode(OUTPUT, in2);
  pinMode(OUTPUT, in3);
  pinMode(OUTPUT, in4);
  pinMode(OUTPUT, ENA);
  pinMode(OUTPUT, ENB);

}

void loop() {
  r_value= analogRead(r);
  Serial.println(r_value,DEC);
  if(r_value<100){
    motor(150,150);
  }
  else if(r_value>100){
    motor(0,0);
  }
  delay(500);
}

int motor(int input_value_R,int input_value_L){
if(input_value_R >=0 and input_value_L >= 0){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(ENA,input_value_L );
    analogWrite(ENB,input_value_R);
  }
  else if(input_value_R >=0 and input_value_L <= 0){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    analogWrite(ENA,input_value_L);
    analogWrite(ENB,abs(input_value_R));
  }
  else if(input_value_R <=0 and input_value_L >= 0){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(ENA,abs(input_value_L));
    analogWrite(ENB,input_value_R );
  }
  else if(input_value_R ==0 and input_value_L == 0){
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    analogWrite(ENA,input_value_R);
    analogWrite(ENB,input_value_L );
  }
  else {
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    analogWrite(ENA,input_value_L);
    analogWrite(ENB,input_value_R);
  }  
  nh.spinOnce();
}
