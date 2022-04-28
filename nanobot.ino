
/* include library */
#include <SoftwareSerial.h> // libreria que permite establecer pines digitales


SoftwareSerial miBT (10, 11);  //pin RX, pin TX

// ----------- Puenteh

int ENA = 13;
//derecho
int IN1 = 12;
int IN2 = 7;
//izquierdo
int IN3 = 6;
int IN4 = 5;
int ENB = 4;

int speedCar = 255;   // variable para almacenar valor de velocidad
int speedMAX = 255;  // variable para almacenar valor de velocidad
int speedMED = 200;     // variable para almacenar valor de velocidad
int speedMIN = 130;      // variable para almacenar valor de velocidad
int speedOff = 0 ;
char dato = 0;      // variable para almacenar caracter recibido



void setup(){
  
  miBT.begin(38400);
  Serial.begin(38400);

  // l298n
/*   pinMode(ENA, OUTPUT);   // ENA como salida
  pinMode(ENB, OUTPUT);   // ENB como salida
  pinMode(IN1, OUTPUT);   // IN1 como salida  
  pinMode(IN2, OUTPUT);   // IN2 como salida
  pinMode(IN3, OUTPUT);   // IN3 como salida
  pinMode(IN4, OUTPUT);   // IN4 como salida
 */  
  for (int i = 4; i <= 9; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop(){

    //------------Bluetooth
  if (miBT.available()){     // si hay informacion disponible desde modulo
    dato = miBT.read();   // almacena en dato el caracter recibido desde modulo
    Serial.println("dato");
    Serial.println(dato);
    Serial.write(dato);                       //Sacarlo a la terminal   
      
      if(dato == '4') { MotorForward();}
      else if(dato == '2') {MotorBackward();}
      else if(dato == '1') {TurnLeft();}
      else if(dato == '3') {TurnRight();}
      else if(dato == '0') {MotorStop(); }  //motor stop
      
      else if(dato == 'a') { SetSpeedCarMax(); }
      else if(dato == 'b') { SetSpeedCarUp();  }
      else if(dato == 'c') { SetSpeedCarDown(); }      

  }
  
     delay(500);
}


// Funciones de motores
/* FORWARD */
void MotorForward(){
  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB
  
  digitalWrite(IN1,HIGH);  
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

/* BACKWARD */
void MotorBackward(){
  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB
  
  digitalWrite(IN1,LOW);  
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
/* TURN RIGHT */
void TurnRight(){
  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB

  digitalWrite(IN1,HIGH);  
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);  
}

/* TURN LEFT */
void TurnLeft(){
  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB

  digitalWrite(IN1,LOW);  
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);  
}

void MotorStop(){
  analogWrite(ENA, speedOff);    // deshabilita motor A
  analogWrite(ENB, speedOff);    // deshabilita motor B
}

//  -----------------------  SPEED  -----------------------
void SetSpeedCarMax(){
  speedCar = speedMAX;
    Serial.print("speedCar "+ speedCar);
  delay(90);  
}



void SetSpeedCarUp(){
  speedCar = speedMED;
    Serial.print("speedCar s"+ speedCar);
  delay(90);  
}


void SetSpeedCarDown(){
  speedCar = speedMIN;
  delay(90);  
}
