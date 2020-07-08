#include <Servo.h>
#include <Ultrasonic.h>

// Pino do servo motor:
int pinoServo = 5;
// Sensor de distancia ultrassônico
int trig = 7;
int echo = 6;
// Saidas da ponte H :
int B1A = 10;
int B1B = 11;
int A1A = 8;
int A1B = 9;
// Pino do buzzer:
int pinBuzzer = 12;

float distMaxima = 28; // Distancia em cm

Ultrasonic sensor(trig, echo);
Servo servo;

// Funções necessárias:
void somBuzzer(){
      tone(pinBuzzer,1500);
      delay(500);
      tone(pinBuzzer,500);
      delay(500);
      tone(pinBuzzer,700);
      delay(500);
      noTone(pinBuzzer);
}

void movimentar(int mov) {
  if (mov == 1) { // movimenta para frente
    digitalWrite(B1A, HIGH);
    digitalWrite(B1B, LOW);
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, HIGH);
  }else if (mov == 2) { // movimenta para trás
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, HIGH);
    digitalWrite(A1A, HIGH);
    digitalWrite(A1B, LOW);
  }else if (mov == 3) { // realiza uma curva pra direita
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, LOW);
    digitalWrite(A1A, HIGH);
    digitalWrite(A1B, LOW);
  }else if (mov == 4) { // realiza uma curva pra esquerda
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, HIGH);
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, LOW);
  }else { // freia o robô
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, LOW);
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, LOW);
    somBuzzer();
  }
}

int localizar() {
  float distDireita=0;
  float distEsquerda=0;
  
  delay(500);
  servo.write(2);
  delay(500);
  distDireita = sensor.Ranging(CM); // Verifica a distancia no lado direito.

  delay(500);
  servo.write(178);
  delay(500);
  distEsquerda = sensor.Ranging(CM); // Verifica a distancia no lado esquerdo

  delay(300);
  servo.write(90);

  if (distDireita > distEsquerda) {
    return 1; 
  }else if (distDireita < distEsquerda) {
    return -1;
  }else {
    return 0;
  }
} 

int deslocarRobo(int r){
  // Verifica o valor do parâmetro r
  if (r == 1) {
    movimentar(2);
    delay(400);
    movimentar(3);
    delay(200);
    movimentar(10);
  } else if (r == -1){
    movimentar(2);
    delay(400);
    movimentar(4);
    delay(200);
    movimentar(10);
  } else{
    movimentar(2);
    delay(400);
    movimentar(4);
    delay(200);
    movimentar(10);
  }

  delay(700);
}

//----------------------------------------------------------
// Programa principal:

void setup() {

  servo.attach(pinoServo); // Inicializa o pino 7
  servo.write(90); // ângulo de rotação do servo motor , no caso 90 graus. Ele começa olhando para frente.
  
  //pinos da ponte H
  pinMode(B1A,OUTPUT);
  pinMode(B1B,OUTPUT);
  pinMode(A1A,OUTPUT);
  pinMode(A1B,OUTPUT);
  pinMode(pinBuzzer,OUTPUT); 
 
  localizar();
}

void loop() {
  
  if (sensor.Ranging(CM) <= distMaxima) {
      movimentar(10); // vai frear o robô
      int retorno = localizar(); // Verificando se vai para direita ou para a esquerda.
      delay(400);
      deslocarRobo(retorno);
    }
  else {
      movimentar(1);
  }
}

   
