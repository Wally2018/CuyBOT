
/*===============================================================================
    
    PROYECTO: PLATAFORMA EDUCATIVA ROBOTICA
    Robot CuyBOT V1.0-2020
    by Julio Wallingre           
                   
                    O   O  
             |----|___^___|----|
             |----|       |----|
 _____________________________________________________________________________________       
 Variables a configurar CuyBOT V1.0-2020
 _____________________________________________________________________________________
 Nombre     |        Descripción                    |  Ejemplo
 -----------+---------------------------------------+---------------------------------
 velocidad  | velocidad del robot, puede ser:       |  velocidad = 3;
            |  1=lento, 2=medio o 3=rapido          |  
  ----------+---------------------------------------+---------------------------------
 dis_stop   | distancia (cm) a la que se detiene el | dis_stop = 10;
            | robot al detectar un objeto  (20)     |
 =====================================================================================

SERVOS
    90º 
0º   |   180º
|____|____|

//-----------------------------------------------------------------------------
HC-SR04
                    ____
trigPIN      ______|    |________   10 Micro seg
                         _   _   _   _   _   _   _   _
Pulso        ___________| |_| |_| |_| |_| |_| |_| |_| |___   envia 8 pulsos a 40KHZ 
                                                        ___________________
echoPin     ___________________________________________|                   |______  inicia el conteo hasta que recibe la señal o pasan 38 miliseg

la distancia al objeto es d=v*(t/2)  donde v = velocidad del sonido (0,034cm/us) por el tiempo dividido 2 (ida y vuelta)
*/

#include <Servo.h>       //cargamos los comando para crear el objeto Servo que genera una señal PWM
//No usamos librería para sensor ultrasónico HC-SR04

Servo leftDrive;         // crear objeto servo para controlar el servo izquierdo
Servo rightDrive;        //crear objeto servo para controlar el servo derecho


#define echoPin 2        // seleccionamos pin D2 Arduino para el pin Echo del HC-SR04
#define trigPin 3        //seleccionamos pin D3 Arduino para el pin Trig del HC-SR04

int pos = 0;                   // variable posicion del servo
long duracion;                 // variable para la duracion del sonido de la onda emitida por el HC-SR04
long randomNumber;             //variable donde almacenaremos el numero aleatorio que decide izquierda o derecha
int dis_stop=20;               // variable distancia stop a 20cm
int distancia;                 // variable de distancia medida por el sensor  
int velocidad = 2;             //variable que selecciona la velocidad del robot

void setup()
{
  Serial.begin(9600);         // Initializamos conexion serial para poder imprimir los valores.
  leftDrive.attach(8);        // seleccionamos el pin 8 para conexion del servo 1
  rightDrive.attach(9);       // seleccionamos el pin 9 para conexion del servo 2
  pinMode(trigPin, OUTPUT);   // Seteamos el trigPin como OUTPUT
  pinMode(echoPin, INPUT);    // Seteamos el echoPin como INPUT
  delay(3000);                //espera 3 seg antes de empezar
}

void loop()
{
   
  digitalWrite(trigPin, LOW);  //ponemos el trigPin en bajo y esperamos 2 milisegundos por cuestión de estabilización del sensor
  delayMicroseconds(2);

 
  digitalWrite(trigPin, HIGH);   //ponemos el trigPin en alto por 10 microsegundos
  delayMicroseconds(10);
 
  digitalWrite(trigPin, LOW);     //ponemos el trigPin en bajo, con esto pudimos generar una señal cuadrada de 10mseg
                                 //luego el Trig envia automaticamente 8 ondas sucesivas de 40KHZ
  duracion = pulseIn(echoPin, HIGH);   //leemos del echoPin el retorno de la señal enviada de 40KHZ
  // Calculamos la distancia
  distancia = duracion * 0.034 / 2; // La velocidad de la onda de sonido se divide por 2 (ida y vuelta)
  // Mostramos la distancia en el monitor serial
  Serial.print("Distance: ");
  Serial.print(distancia);
  Serial.println(" cm");

if(distancia>=dis_stop)
  {
    robotAdelante();  //todo adelante  
    Serial.println("Adelante");
    
  }else {
    randomNumber = random(1,10);    //genera num aleatorio entre 1 y 10
    robotStop();    //parar robot
    delay(2000);
    robotAtras();   //robot para atras
    delay(300);
    robotStop();    //parar robot
    delay(1000);
    if (randomNumber % 2 == 0)      // si el numero random div 2 da resultado cero entonces ir a la derecha (par = derecha impar = izquierda)
      {
         robotDerecha();  //a la derecha
         Serial.println("Derecha");
         delay(350);
         robotStop();    //parar
         delay(1000);
        
      }else {
         
         robotIzquierda();  //a la izquierda
         Serial.println("Izquierda");
         delay(350);
         robotStop();    //parar
         delay(1000);       
      }  
  }

} //end loop



//   0 para adelante, 90 es stop y 180 es para atras. 


void robotStop()
{
  leftDrive.write(90);
  rightDrive.write(90);
  delay(450);
}

void robotDerecha()
{
  leftDrive.write(50);
  rightDrive.write(50);
  delay(450);
}


void robotIzquierda()
{
  leftDrive.write(130);
  rightDrive.write(130);
  delay(450);
}


void robotAtras()
{
  leftDrive.write(50);
  rightDrive.write(130);
  delay(1000);
}


void robotAdelante()
{ 
  
  switch (velocidad) {
  case 1:
    leftDrive.write(100);
    rightDrive.write(80);
    delay(1000);
    break;
  case 2:
    leftDrive.write(130);
    rightDrive.write(50);
    delay(1000);
    break;
  case 3:
    leftDrive.write(180);
    rightDrive.write(0);
    delay(1000);
    break;
  default:
    // algo
    break;
  } 
}

//fin del codigo ----------------------------------
