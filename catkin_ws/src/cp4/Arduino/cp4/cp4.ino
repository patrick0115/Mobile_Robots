#include <ros.h>
#include <std_msgs/Int16.h>

//L298N
//in1 in2 ENA is right
//in3 in4 ENB is right
#define in1 4
#define in2 5
#define in3 6
#define in4 7
#define ENA 10
#define ENB 11
//sensor
#define light  A0
#define ir  A1
ros::NodeHandle nh;

//state
int touch = 4;
int state = 0;

//light parameter
int light_value = 0;
int light_avg = 0;
int light_sum = 0;
int find_light = 800;
int light_min = 999999;
int light_count = 0;
int light_num = 0;

//ir parameter
int ir_value = 0;//detect=0 ; not detect = 1024
int ir_low = 26;
int ir_hight = 50;
int ir_num1 = 0;
int ir_num2 = 0;
int ir_temp = 0;

//ROS
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
  pinMode(ir, INPUT);
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
    motor(135, 160);
    if (touch == 1 || touch == 2 || touch == 3 ) {
      touch_wall();
      rotate_l(450);
      go_straight(2000);
      state = 1;
      touch = 4;
    }
  }
  else if (state == 1) {
    if (touch == 0 ) {
      state = 2;
      touch = 4;
    }
    else if (touch == 4) {
      if (light_num == 0) {
        light_min = 999999;
      }
      findlight();
      light_num++;
    }
    else if (touch == 1 || touch == 2 || touch == 3) {
      avoid(touch);
      touch = 4;
      light_num = 0;
    }
  }
  else if (state == 2) {
    if (touch == 4) {
      findlir();
    }
    else if (touch == 1 || touch == 2 || touch == 3) {
      avoid(touch);
      touch = 4;
    }
  }
  nh.spinOnce();
}
int findlir() {
  ir_value = analogRead(ir);
  ir_num1++;
  if (ir_value < 512) {
    ir_num2++;
  }
  if (ir_num1 > 100) {
    ir_temp = ir_num2;
    ir_num2 = 0;
    ir_num1 = 0;
    if (ir_temp > ir_low && ir_temp < ir_hight) {
      go_straight(500);
    }
    else {
      rotate_r(100);
      go_straight(200);
    }
  }
}
int avoid(int touch) {
  if (touch == 1) {
    touch_wall();
    rotate_l(400);
    go_straight(500);
  }
  else if (touch == 2) {
    touch_wall();
    rotate_r(400);
    go_straight(500);
  }
  else if (touch == 3) {
    touch_wall();
    rotate_l(400);
    go_straight(500);
  }
}
int findlight() {
  /*
    light_msg.data = analogRead(light);
    pub_light.publish( &light_msg );
  */
  if (light_num <= 7) {
    rotate_l(210);
    go_stop(200);
    light_value = analogRead(light);
    Serial.println(light_value, DEC);
    if (light_value < light_min) {
      light_min = light_value;
      light_count = light_num;
    }
  }
  if (light_num == 7) {
    go_stop(1000);
    for (int i = 0; i < light_count; i++) {
      rotate_l(210);
      go_stop(200);
    }
    go_straight(1000);
    light_num = 0;
  }


}

//move
int go_straight(int s_time) {
  motor(180, 180);
  if (s_time != 0) {
    delay(s_time);
  }
}
int go_stop(int s_time) {
  motor(0, 0);
  delay(s_time);
}


int rotate_l(int l_time) {
  motor(-150, 180);
  delay( l_time);
}

int rotate_r(int r_time) {
  motor(180, -150);
  delay( r_time);
}

int touch_wall() {
  motor(0, 0);
  delay(200);
  motor(-180, -160);
  delay(1000);
}

int motor(int input_value_L, int input_value_R) {
  if (input_value_R >= 0 and input_value_L >= 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(ENA, input_value_R );
    analogWrite(ENB, input_value_L);
  }
  else if (input_value_R >= 0 and input_value_L <= 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(ENA, input_value_R);
    analogWrite(ENB, abs(input_value_L));
  }
  else if (input_value_R <= 0 and input_value_L >= 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(ENA, abs(input_value_R));
    analogWrite(ENB, input_value_L );
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
    analogWrite(ENA, abs(input_value_R));
    analogWrite(ENB, abs(input_value_L));
  }

}
