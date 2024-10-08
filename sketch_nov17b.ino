/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL6dVubkZ-g"
#define BLYNK_TEMPLATE_NAME         "Project"
#define BLYNK_AUTH_TOKEN            "KlJ8qhO9ZQnXtI6rSdEVcytoOD4I1yQ_"




#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D8
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

int GAMBUT;
int relay1 = D3;
int led = D5;
int led1 = D1;
int tempC = D8;
int wifi = D6;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

void setup()
{
  // Debug console
  Serial.begin(9600);
 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(relay1, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(wifi, OUTPUT);
  pinMode(tempC, INPUT);
}

BLYNK_WRITE(V1) // this command is listening when something is written to V1
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  
  if (pinValue == 1){
   digitalWrite(relay1, HIGH);
   digitalWrite(led, LOW);
   digitalWrite(led1, HIGH);
  } else if (pinValue == 0) {
  digitalWrite(relay1, LOW);
  digitalWrite(led,HIGH);
  digitalWrite(led1,LOW);
  } 
  
  Serial.print("V1 button value is: "); // printing value to serial monitor
  Serial.println(pinValue);
}

void loop()
{
  if (Blynk.connected()) {
    digitalWrite(wifi, HIGH);
  } else {
    digitalWrite(wifi, LOW);
  }
  //buat cek koneksi wifi nodemcu (HIGH = gak terhubung)

  Blynk.run();
{
  sensors.requestTemperatures(); // Send the command to get temperatures
  float tempC = sensors.getTempCByIndex(0);

  Serial.println(tempC);

  if(tempC >= 32){
    digitalWrite(relay1, HIGH);
  }else(tempC <= 32); {
    digitalWrite(relay1, LOW);
}
}
}
