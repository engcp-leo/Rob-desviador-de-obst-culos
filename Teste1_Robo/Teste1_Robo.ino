void setup(){
  //motor_A
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  
  //motor_B
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}
 
void loop(){
  // Motor B ,roda girando para frente
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  // Motor A, roda girando para frente
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
}
