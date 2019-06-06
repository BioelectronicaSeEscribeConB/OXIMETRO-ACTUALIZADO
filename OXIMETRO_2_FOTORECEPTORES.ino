#include <LiquidCrystal.h>
//***** Conexion LCD 16x2 ***//
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
// *** Variables *** //
float spo2=0;   //%spo2
float spo2total=0; //sumatoria de ambas señales 
 //Sensores Fototransistores//

int sensor=A0;    //Fototransistor 790nm - 1050nm  IR (950nm)
int valorSensor;
int sensor2=A1;  //Fototransistor  400nm - 1100nm ROJO
int valorSensor2;


unsigned int   intensidad_infrarrojo;  // intensidad reflejada HbO2 (oxihemoglobina)
unsigned int   intensidad_rojo;        //intensidad refleada   Hb (hemoglobina)

////
const int numReadings = 100;  //numero de muestras para promedio

int readings[numReadings]; // Lecturas de la entrada analogica 
int index = 0; // El indice de la lectura actual 
int total = 0; // Total 
float average = 0; // Promedio 



void setup() 
{
Serial.begin(9600);
// Iniciamos todas las lecturas a la entrada 0 
for (int thisReading = 0; thisReading < numReadings; thisReading++) 
readings[thisReading] = 0; 
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("CALCULO DE SpO2");
  lcd.setCursor(0, 0);
  lcd.print("Oximetro Arduino");
  lcd.setCursor(0, 1);
  delay(500);
  lcd.clear();
}

void loop() 
{
 //lectura de Fototransistores
  valorSensor=analogRead(sensor);
  intensidad_infrarrojo=valorSensor;

  valorSensor2=analogRead(sensor2);
 intensidad_rojo=valorSensor2;

 lcd.setCursor(5,0); 
 lcd.write("OXIMETRO"); 

 // calculo de % de saturacion de Oxigeno basada en la Ley de Beer-Lambert
 spo2total=((float)intensidad_rojo+(float)intensidad_infrarrojo);
 spo2=((float)intensidad_infrarrojo/spo2total);
 spo2=100.0*spo2;
 spo2=spo2+47;
  Serial.print(valorSensor);
  Serial.print("\t");
  Serial.print(valorSensor2);
  Serial.print("\t");
// Restamos la ultima lectura: 
total= total - readings[index]; 
// Leemos del sensor: 
readings[index] = spo2; 
// Añadimos la lectura al total: 
total= total + readings[index]; 
// Avanzamos a la proxima posicion del array 
index = index + 1; 

// Si estamos en el final del array... 
if (index >= numReadings) 
// ...volvemos al inicio: 
index = 0; 

// Calculamos el promedio: 
average = total / numReadings; 
// Lo mandamos a la PC como un valor ASCII 
///*********** LCD 16X2 *********////
 lcd.setCursor(1,1); 
 lcd.print("%SpO2: "); 
 lcd.setCursor(8,1); 
 lcd.print(average);
//******* SERIAL PLOTTER *****/// 
Serial.print(spo2); 
Serial.print(","); 
Serial.println(average, DEC); 
delayMicroseconds(1000);  

}
