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

ros::NodeHandle nh;  //manages an internal reference count

int state = 0;


void cb_r(const std_msgs::Int16& msg) {
  state = msg.data;
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
  motor(0, 0);
/*
  light_value = analogRead(light);
  Serial.println(light_value, DEC);
  light_msg.data = analogRead(light);
  pub_light.publish( &light_msg );
*/
  if (state != 4) {
    if (state == 2) {
      motor(130, 80);
      delay(500);
    }
    else if (state == 1) {
      motor(80, 130);
      delay(500);
    }
    else if (state == 3) {
      motor(-130, -130);
      delay(500);
    }
    else {
      motor(64, 64);
      delay(500);
    }

  }
  else if (state == 4) {
    motor(0, 0);
    delay(5000);
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
