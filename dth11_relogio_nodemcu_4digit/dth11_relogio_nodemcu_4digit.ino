/* Funcionalidades
 *  Mede temperatura
 *  Mede umidade
 *  Mede tensão da bateria
 *  Relógio
 *  
 *  Funções do display
 *  segSegments(array de bytes, número de itens, posicao)
 *  
 *  Next function that is simple to use is showNumberDec(). The parameters are:
 *  a) Number of type integer. Values up to 9999.
 *  b) True/false. Display leading zeroes for values up to 999. Default value is false;
 *  c) Correspond to the number of digits to be displayed.
 *  d) Position of the least significant digit (0 – leftmost, 3 – rightmost).
 *  
 *  Connections of DHT sensor:
 *  Connect pin 1 (on the left) of the sensor to +5V
 *  Connect pin 2 of the sensor to whatever your DHTPIN is
 *  Connect pin 4 (on the right) of the sensor to GROUND
 *  Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
 */

/***** MODULO DHT11 (SENSOR DE TEMPERATURA E UMIDADE) *****/

#define DHTPIN D1          // What digital pin we're connected to
#define CLK D2    //Set the CLK pin connection to the display
#define DIO D3    //Set the DIO pin connection to the display

#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

/***** MODULO TM1637 DISPLAY 4 DIGITOS *****/

#include <TM1637Display.h>

uint8_t carac[1];

const uint8_t SEG_FAIL[] = {
  SEG_A | SEG_E | SEG_F | SEG_G,                   // F
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,   // A
  SEG_E | SEG_F,                                   // I
  SEG_D | SEG_E | SEG_F                            // L
  };

TM1637Display display(CLK, DIO);

/***** MODULO WIFI E RELOGIO *****/
#include <ESP8266WiFi.h>
#include <time.h>
const char* ssid = "homewifi";
const char* password = "0102030405";
int ledPin = LED_BUILTIN;
int timezone = 20 * 3600; //horario cuiaba
int dst = 0;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  display.setBrightness(2);  //set the diplay to maximum brightness (0-7)(OLD=0x0f)

  dht.begin();

/***** MODULO WIFI E RELOGIO *****/

  digitalWrite(ledPin,LOW);
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  while(!time(nullptr)){
     Serial.print("*");
     delay(1000);
  }
}

void loop() {

  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

      // Check if any reads failed and exit early (to try again).

  if (isnan(h) || isnan(t)) {
    display.setSegments(SEG_FAIL);
    return;
    }


  display.showNumberDec((int) t, false);
    carac[0] = 0b01111000;  // LETRA t 
    display.setSegments(carac, 1, 0); //segSegments(array, número de itens, posicao)
  delay(2500);
  
  display.showNumberDec((int) h, false);
    carac[0] = 0b00011100;  // LETRA u
    display.setSegments(carac, 1, 0); 
  delay(2500);

  Serial.print((int) t);
  Serial.print("C ");  
  Serial.print((int) h);
  Serial.println("% de umidade ");  

/*  //MOSTRAR TENSAO
    // Leitura da tensão no pino A0 (Pode ser bateria, com divisor de tensão)
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0) * 2; //2 pq divisor de tensao 50%
  
    display.showNumberDec(voltage*100, false, 3, 0);
    carac[0] = 0b00111110;  // V
    display.setSegments(carac, 1, 3); 
  
  delay(2000);*/
  
/* ------ ENVIAR DADOS VIA WIFI??? ------- */

/***** MODULO RELOGIO *****/

  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  Serial.print(p_tm->tm_hour);
  Serial.print(":");
  Serial.println(p_tm->tm_min);    

  uint8_t data[] = {0x0, 0x0, 0x0, 0x0}; 
  display.setSegments(data);    
  //display.showNumberDec(,true,4,3); //true leading zeros, exibir 4 digitos, comeca na casa 3
  display.showNumberDecEx((p_tm->tm_hour)*100 + (p_tm->tm_min),64,true); //mostrar os dois pontos colon
  
  delay(5000); // update every 10 sec

} 
