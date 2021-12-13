#include <ros.h>
#include <std_msgs/Int16.h>

const int light = A0;
#define in1 4
#define in2 5
#define in3 6
#define in4 7
#define ENA 10
#define ENB 11
int light_value = 800;
ros::NodeHandle nh;
int touch = 0;
int state = 0;
int light_storage[7];
int MinNum;



void cb_r(const std_msgs::Int16& msg) {
  touch = msg.data;
}

ros::Subscriber<std_msgs::Int16> sub("touch", &cb_r);

std_msgs::Int16 light_msg;
ros::Publisher pub_light("light_value", &light_msg);


void setup() {
  Serial.begin(57600);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub_light);
  pinMode(light, INPUT);
  pinMode(OUTPUT, in1);
  pinMode(OUTPUT, in2);
  pinMode(OUTPUT, in3);
  pinMode(OUTPUT, in4);
  pinMode(OUTPUT, ENA);
  pinMode(OUTPUT, ENB);

}

void loop() {
  if (state == 0) {
    motor(130, 160);
    if (touch == 1 || touch == 2 || touch == 3 ) {
      state = 1;
      touch_wall();
    }
  }
  else if (state == 1) {
    findlight();
    if (touch == 0 ) {
      state = 2;
      touch_wall();
    }
  }
  else if (state == 2) {
    findlir();
  }
  nh.spinOnce();
}
int findlir() {

}
int findlight() {
  for (int i = 0; i < 7; i++) {
    motor(180, -180);
    delay(500);
    motor(0, 0);
    delay(100);
    light_value = analogRead(light);
    Serial.println(light_value, DEC);
    light_storage[i] = light_value;
  }
  Minlight(light_storage[7]);
  /*
    light_msg.data = analogRead(light);
    pub_light.publish( &light_msg );
  */
}
int touch_wall() {
  motor(0, 0);
  delay(200);
  motor(-180, -160);
  delay(1000);
}
int Minlight(int light_storage[7])
{
  int num=0;
  MinNum = light_storage[0];
  for (int i = 1; i < 7; i++)
  {
    if (light_storage[i] < MinNum)
      MinNum = light_storage[i];
  }
  return MinNum;
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
