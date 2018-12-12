// Link til DHT11 sensor tutorial:
// https://create.arduino.cc/projecthub/Arca_Ege/using-dht11-b0f365?ref=platform&ref_id=424_trending___&offset=3

// Importerer dht11 library
#include <dht11.h>

#include <ESP8266WiFi.h>

// Definerer at den første temp sensor skal køre på pin 5
#define DHT11PIN_1 5

// Definerer at den anden temp sensor skal køre på pin 4
#define DHT11PIN_2 4

int chk_1;
int chk_2;

// Deklarer en dht11 variabel til den første temp sensor
dht11 DHT11_1;

// Deklarer en dht11 variabel til den anden temp sensor
dht11 DHT11_2;

// Deklarer int datatyper til at gemme den første temp sensors - temperatur og humidity
int humidity_1;
int temperature_1;


// Deklarer int datatyper til at gemme den anden temp sensors - temperatur og humidity
int humidity_2;
int temperature_2;

// Deklarer pin variabler til vores LEDs
int ledRed = 14;
int ledYellow = 12;
int ledGreen = 13;


/*
  const int latchPin = 8; //Pin connected to ST_CP of 74HC595
  const int clockPin = 12; //Pin connected to SH_CP of 74HC595
  const int dataPin = 11; //Pin connected to DS of 74HC595
*/
// int data[] = {
//  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*" ",0*/
//  0xFF,0xC1,0xBE,0xBE,0xBE,0xC1,0xFF,0xFF,/*"0",1*/
//  0xFF,0xDF,0xDF,0x80,0xFF,0xFF,0xFF,0xFF,/*"1",2*/
//  0xFF,0xDC,0xBC,0xBA,0xB6,0xCE,0xFF,0xFF,/*"2",3*/
//  0xFF,0xDD,0xBE,0xB6,0xB6,0xC9,0xFF,0xFF,/*"3",4*/
//  0xFB,0xF3,0xEB,0xDB,0x80,0xFB,0xFF,0xFF,/*"4",5*/
//  0xFF,0x8D,0xAE,0xAE,0xAE,0xB1,0xFF,0xFF,/*"5",6*/
//  0xFF,0xC1,0x96,0xB6,0xB6,0xD9,0xFF,0xFF,/*"6",7*/
//  0xFF,0xBF,0xBC,0xB3,0xAF,0x9F,0xFF,0xFF,/*"7",8*/
//  0xFF,0xC9,0xB6,0xB6,0xB6,0xC9,0xFF,0xFF,/*"8",9*/
//  0xFF,0xCD,0xB6,0xB6,0xB4,0xC1,0xFF,0xFF,/*"9",10*/
//  0xFC,0xF3,0xCB,0x9B,0xEB,0xF3,0xFC,0xFF,/*"A",11*/
//  0xFF,0x80,0xB6,0xB6,0xB6,0xB6,0xC9,0xFF,/*"B",12*/
//  0xFF,0xE3,0xDD,0xBE,0xBE,0xBE,0xBE,0xDD,/*"C",13*/
//  0xFF,0x80,0xBE,0xBE,0xBE,0xBE,0xDD,0xE3,/*"D",14*/
//  0xFF,0x80,0xB6,0xB6,0xB6,0xB6,0xBE,0xFF,/*"E",15*/
//  0xFF,0x80,0xB7,0xB7,0xB7,0xB7,0xBF,0xFF,/*"F",16*/
//  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*" ",17*/
//};


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println();

/*  WiFi.begin("flennersphone", "hejmeddig");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
*/

  
  Serial.println("starting");

  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  //set pins to output
  //   pinMode(latchPin,OUTPUT);
  //   pinMode(clockPin,OUTPUT);
  //   pinMode(dataPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Koden som læser humidity og temperature fra den første sensor og printer den i Serial Monitor

  chk_1 = DHT11_1.read(DHT11PIN_1);

  humidity_1 = DHT11_1.humidity;
  temperature_1 = DHT11_1.temperature;

  Serial.println();
  Serial.println("Humidity - Sensor 1 (%): ");
  Serial.println(humidity_1);

  Serial.println("Temperature - Sensor 1 (C): ");
  Serial.println(temperature_1);

  // Koden som læser humidity og temperature fra den anden sensor og printer den i Serial Monitor

  chk_2 = DHT11_2.read(DHT11PIN_2);

  humidity_2 = DHT11_2.humidity;
  temperature_2 = DHT11_2.temperature;

  Serial.println("Humidity - Sensor 2 (%): ");
  Serial.println(humidity_2);

  Serial.println("Temperature - Sensor 2 (C): ");
  Serial.println(temperature_2);

  int temperature_difference = temperature_1 - temperature_2;

  temperature_difference = abs(temperature_difference);

  Serial.println("Temperature difference: ");
  Serial.println(temperature_difference);

  if (temperature_difference > 7 ) {
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);

  } else if (temperature_difference > 4 ) {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, HIGH);

  } else if (temperature_difference > 0 ) {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, HIGH);

  }

  delay(1000);

  /*
    digitalWrite(ledRed, HIGH);

    digitalWrite(ledRed, LOW);

    digitalWrite(ledYellow, HIGH);

    digitalWrite(ledYellow, LOW);

    digitalWrite(ledGreen, HIGH);

    digitalWrite(ledGreen, LOW);
  */

  /*  for(int n = 0; n < 136; n++)
      {
        for(int t = 0;t < 10;t ++)//Show repeated 10 times
        {
          int dat = 0x01;
          for(int num = n; num < 8+n; num++)
          {
            shiftOut(dataPin,clockPin,MSBFIRST,~data[num]);//control ROW of dot matrix
            shiftOut(dataPin,clockPin,MSBFIRST,~dat); //control COL of dot matrix
            //return the latch pin high to signal chip that it
            //no longer needs to listen for information
            digitalWrite(latchPin,HIGH); //pull the latchPin to save the data
            //delay(1); //wait for a microsecond
            digitalWrite(latchPin,LOW); //ground latchPin and hold low for as long as you are transmitting
            dat = dat<<1;
            delay(1); //wait for a microsecond
          }
        }
      }*/
}
