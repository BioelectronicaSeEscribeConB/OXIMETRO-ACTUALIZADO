int buzzer=A2;
///// FRECUENCIOMETRO ///
long rango=5; // este es el rongo por el que se disparará la salida 2 y pasa a estado lógico 1
long ultimamedicion; // contiene el valor de la última medición que disparó a lógico 1, la salida 2
int ciclo=0; // 1=alto 0=bajo
int cambiodeciclo=0;
int picodetension;
int valledetension=1023;
long contadorciclo;
///////********************/////////

boolean estadoBPM = true;  //guarda el estado del led (encendido o apagado)
boolean estadoLed = true;  //guarda el estado del led (encendido o apagado)
int intervaloEncendido =200;  // tiempo que esta encendido el led
int IntervaloApagado = 50;  // tiempo que esta apagado el led

int IntervaloBPM = 15000;  // tiempo que esta apagado el led
int IntervaloBPM2 = 1;  // tiempo que esta apagado el led

unsigned long tiempoAnteriorEncendido = 0;  //guarda tiempo de referencia para comparar
unsigned long tiempoAnteriorApagado = 0;  //guarda tiempo de referencia para comparar
unsigned long tiempoAnteriorBPM = 0;  //guarda tiempo de referencia para comparar
unsigned long tiempoAnteriorBPM2 = 0;  //guarda tiempo de referencia para comparar
/////////////////////////////
int lectura=A0; //pin de conexion de señal del oximetro
int senal=0; //variable donde guardamos el valor de la señal
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6, 5, 4, 3, 2);
///////////////////////
int pulsos=0;
int pulsos2=0;
//***********************************************************
byte COR1[8] = 
{
  B00000,
  B00011,
  B01111,
  B11111,
  B11111,
  B01111,
  B01111,
  B00011
};
byte COR2[8] = 
{
  B00000,
  B11011,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte COR3[8] = 
{
  B00000,
  B11000,
  B11110,
  B11111,
  B11111,
  B11110,
  B11110,
  B11000
};
byte COR4[8] = 
{
  B11111,
  B01110,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
//***********************************************************
byte KOR1[8] = 
{
  B00000,
  B00000,
  B00011,
  B00111,
  B00111,
  B00011,
  B00011,
  B00000
};
byte KOR2[8] = 
{
  B00000,
  B00000,
  B11011,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};
byte KOR3[8] = 
{
  B00000,
  B00000,
  B11000,
  B11100,
  B11100,
  B11000,
  B11000,
  B00000
};
byte KOR4[8] = 
{
  B00100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
void setup() 
{
    Serial.begin(9600); //comunicacion serial
    pinMode(12,OUTPUT);  //configura el pin como salida
    digitalWrite(12,estadoLed);  //enciende el led
     lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(buzzer,OUTPUT);
  lcd.print("PULSOMETRO !");
// delay(2000);
    lcd.clear();
}


void loop() 
{
     senal=analogRead(lectura); //guardamos el valor en la variable senal
  /////////***********************************************************//////////////////
   if (senal >= ( ultimamedicion+200) ) // La salida 2 pasa a 1 logico si la tensión medida en la entrada analógica 0 es mayor que la anterior lectura + latensión de RANGO
   {
     ultimamedicion = senal;  // SE ASIGANA A LA VARIABLE ULTIMAMEDICION EL VALOR LEIDO POR LA ENTRADA ANALÓGICA CERO 
     ciclo=1;
     if (senal>picodetension) // SI LA TENSIÓN MEDIDA POR LA ENTRADA CERO, ES LA MAYOR DETECTADA, SE ASIGNA A LA VARIABLE PICODETENSIÓN EL VALOR LEYDO POR AL ENTRADA CERO ANALÓGICA 
     {
     picodetension=senal; // SE ASIGNA EL VALOR LEYDO POR LA ENTRADA CERO ANALÓGICA A LA VARIABLE PICODETENSIÓN.
     }
   }
     
   if (senal <= ( ultimamedicion-200))  // La salida 2 pasa a 1 lógico si la tensión medida en la entrada analógica 0 es menor que la anterior lectura - la tensión de RANGO
   {
     ultimamedicion = senal; // SE ASIGNA A LA VARIABLE ULTIMAMEDICIÓN LA LECTURA MEDIDA POR EL PUERTO ANALÓGICO CERO
     ciclo=0; // EL CICLO SE PONE A CERO, ES DECIR, QUE EL VOLTAJE EMPIEZA A BAJAR DESDE EL PICO DE TENSIÓN MÁS ALTA
     if (senal<valledetension) // SE CUMPLE LA CONDICIÓN SI LA TENSIÓN DETECTADA POR EL PUERTO ANALÓGICO CERO ES MENOR QUE LA CONTENIDA EN LA VARIABLE VALLEDETENSIÓN
     {
     valledetension=senal; //Se asigna a la variable valledetensión el valor medido por la entrada analógica cero
     }
   }

  ////////***********************************************************///////////////////
  
  
  //////////////////// 1 minuto ////////////
   if(millis()-tiempoAnteriorBPM>=IntervaloBPM){  //si ha transcurrido el periodo programado
    estadoBPM=false;
    pulsos2=pulsos;
//    Serial.print("  BPM: ");
//    Serial.print(pulsos2);
     tiempoAnteriorBPM=millis();  //guarda el tiempo actual para comenzar a contar el tiempo apagad
    pulsos=0;
   
  }
  if(millis()-tiempoAnteriorBPM2>=IntervaloBPM2){  //si ha transcurrido el periodo programado
    estadoBPM=true;
    Serial.print("BPM: ");
    pulsos2=(pulsos2+pulsos2)/2;
    Serial.print(pulsos2*4);
   lcd.setCursor(0,0); 
   lcd.write("Frecuencia");
   lcd.setCursor(0,1); 
   lcd.write("Cardiaca:");
   lcd.setCursor(10,1); 
    lcd.print(pulsos2*4);  // print the number of seconds since reset:
    tiempoAnteriorBPM2=millis();  //guarda el tiempo actual para comenzar a contar el tiempo apagado
  }
    ///////////////////////////////////////
  if((millis()-tiempoAnteriorEncendido>=intervaloEncendido)&&estadoLed==true && ciclo==0){  //si ha transcurrido el periodo programado
    estadoLed=false;  //actualizo la variable para apagar el led
    picodetension=senal;//SE ASIGNA A LA VARIABLE PICODETENSIÓN EL VALOR DE LA TENSIÒN LEIDA POR EL PUERTO ANALÓGICO CERO
    valledetension=senal;//SE ASIGNA A LA VALLEDETENSION EL VALOR DE LA TENSIÒN LEIDA POR EL PUERTO ANALÓGICO CERO  
    digitalWrite(12,estadoLed);  //apago el led
     digitalWrite(buzzer,LOW);
      lcd.createChar(1,KOR1);
      lcd.setCursor(13,0); 
      lcd.write(1); 
      lcd.createChar(2,KOR2);
      lcd.setCursor(14,0); 
      lcd.write(2); 
      lcd.createChar(3,KOR3);
      lcd.setCursor(15,0); 
      lcd.write(3); 
      lcd.createChar(4,KOR4);
      lcd.setCursor(14,1); 
      lcd.write(4); 
    tiempoAnteriorApagado=millis();  //guarda el tiempo actual para comenzar a contar el tiempo apagado
  }
  if((millis()-tiempoAnteriorApagado>=IntervaloApagado)&&estadoLed==false && ciclo==1) //PULSO
  {  //si ha transcurrido el periodo programado
    pulsos++;
    picodetension=senal;//SE ASIGNA A LA VARIABLE PICODETENSIÓN EL VALOR DE LA TENSIÒN LEIDA POR EL PUERTO ANALÓGICO CERO
    valledetension=senal;//SE ASIGNA A LA VALLEDETENSION EL VALOR DE LA TENSIÒN LEIDA POR EL PUERTO ANALÓGICO CERO
    estadoLed=true;  //actualizo la variable para encender el led 
    digitalWrite(buzzer,HIGH);
    digitalWrite(12,estadoLed);  //enciendo el led
    /////////////////////////////// 
      lcd.createChar(1,COR1);
      lcd.setCursor(13,0); 
      lcd.write(1); 
      lcd.createChar(2,COR2);
      lcd.setCursor(14,0); 
      lcd.write(2); 
      lcd.createChar(3,COR3);
      lcd.setCursor(15,0); 
      lcd.write(3); 
      lcd.createChar(4,COR4);
      lcd.setCursor(14,1); 
      lcd.write(4); 
    tiempoAnteriorEncendido=millis();  //guarda el tiempo actual para comenzar a contar el tiempo encendido
  }
 
  Serial.print("     Senal: ");
   Serial.println(senal); //imprimimos en monitor serial la señal

}
