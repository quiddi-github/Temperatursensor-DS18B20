
#define LED    D4                               // LED auf D4 am Arduino, Blinkkontrolle
#include <ThingSpeak.h>                         // ThingSpeak Bibliothek einbinden
#include <ESP8266WiFi.h>                        // W-Lan Bibliothek einbinden
#include <OneWire.h>                            // BUS-Bibliothek für Sensor einbinden
#include <DallasTemperature.h>                  // Dallas Sensor Bibliothek einbinden

#define ONE_WIRE_BUS 4                          // Temperatursensor an GPIO4 bzw. Pin D2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

unsigned long myChannelNumber = 1996100;         //ThingSpeak Channel ID
const char * myWriteAPIKey = "5ODRXQS14RDPWXGF";

const char* ssid = "Newton";                    // W-Lan Passwörter
const char* password = "3r15t31nE5el!";

WiFiClient  client;

WiFiServer server(80);

unsigned long AktuelleZeit=0;                   //aktuelle Zeit-Variable um delay nicht benutzen zu müssen
unsigned long LetzterLauf=0;
unsigned long LetzterSendelauf=0;
unsigned long LetzterLaufLED=0;
unsigned long LetzterReboot=0;
bool LetzterSendelaufbool = false;

void(* resetFunc) (void) = 0; //0-Funktion Pointer für Reboot

void setup()  
 {  
  Serial.begin(115200);                         // Seriellen Port initialisieren 
  delay(10);
  pinMode(LED, OUTPUT);                         // Setzen des PINs als Ausgang für LED

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    count++;
    if (count > 50){resetFunc();};
  }
  Serial.println("");
  Serial.println("WiFi connected");  

  // Print the IP address
  Serial.println(WiFi.localIP());

ThingSpeak.begin(client);
LetzterReboot = millis();
}  
  
void loop() {
  AktuelleZeit = millis();
  bool arbeiten = false;


// Anfang: Alle 6 Sekunden die Temperatur über den seriellen Monitpr ausgeben
if (AktuelleZeit > (LetzterLauf+6000)) {
  LetzterLauf = AktuelleZeit;
  arbeiten = true;
};
if (arbeiten == true) {
sensors.requestTemperatures();
 Serial.println("Temperatur ist: " + String(sensors.getTempCByIndex(0)) + "°C" + "     " + String(AktuelleZeit));
};
// Ende: Alle 6 Sekunden die Temperatur über den seriellen Monitpr ausgeben

// Anfang: Alle 6 Minuten die Temperatur an ThingSpeak senden
if (!LetzterSendelaufbool) {
ThingSpeak.writeField(myChannelNumber, 1, sensors.getTempCByIndex(0) , myWriteAPIKey);
LetzterSendelaufbool = true;
LetzterSendelauf = AktuelleZeit;
 Serial.println("Temperatur gesendet an TS   " + String(AktuelleZeit));
 if (AktuelleZeit > (LetzterReboot + 7200000)) // alle 2h einen Reboot machen
{
LetzterSendelaufbool = false;
resetFunc(); // Reboot
};
}

// Ende: Alle 6 Minuten die Temperatur an ThingSpeak senden


// Anfang: LED-Blinken ohne delay()-Befehl
if (AktuelleZeit < (LetzterLaufLED+1000) ) {
  digitalWrite(LED, LOW);
};
if (AktuelleZeit > (LetzterLaufLED+1000)) {
  digitalWrite(LED, HIGH);
};
if (AktuelleZeit > (LetzterLaufLED+2000)) {
  LetzterLaufLED = AktuelleZeit;
};
// Ende: LED-Blinken ohne delay()-Befehl


}

