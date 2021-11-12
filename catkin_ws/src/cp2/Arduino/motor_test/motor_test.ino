#define in1 4
#define in2 5
#define in3 6
#define in4 7
#define ENA 10
#define ENB 11

void setup() {
  pinMode(OUTPUT, in1);
  pinMode(OUTPUT, in2);
  pinMode(OUTPUT, in3);
  pinMode(OUTPUT, in4);
  pinMode(OUTPUT, ENA);
  pinMode(OUTPUT, ENB);

}

void loop() {
  f();
  delay(10); 

}
void f(){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(ENA,70);
    analogWrite(ENB,200);    
}
