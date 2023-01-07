# Temperatursensor DS18B20

Stand: 29.12.2022\
\
 *  Als Temperatursensor wird ein DS18B20 verwendet.\
 *  Das Signal wird per W-Lan an ThingSpeak gesendet\
 *  Als Board wird ein "NodeMCU V3 Arduino ESP8266 ESP-12 E LUA CH340 WiFI WLan IoT Board Lolin" verwendet. Ein PDF ist beigeführ um das Board in der Arduino-IDE selektieren zu können.\
 *  Der Sensor DS18B20 ist an GPIO 4 bzw. D2 angeschlossen (gelb: Data, schwarz: Masse, rot: +5V). Zwischen +5V und Data ist ein 4,7k Widerstand zu schalten. Ein Anschlussbild ist als PDF-Dokument beigefügt.\
 *  Thingspeak-Bibliothek (ThingSpeak von MathWorks) installieren.\
 *  DallasTemperature von Miles Burton installieren.\
 *  Als Board ein NodeMCU 1.0 (ESP-12E Module) in der Arduino IDE auswählen.\
 *  W-Lan Password und SSID im Code eingeben.\
 *  ThingSpeak API Daten im Code eingeben.\
 *  Der Code sendet alle 6 Minuten an ThingSpeak und alle 6 Sekunden über den seriellen Monitor (115200 Baud) die Daten.\
 *  ThingSpeak Channel ID: 1996100, uzo47339@cdfaq.com\
 \
 7.1.2023: Alle 30 Minuten wird in Field 1 gespeichert, alle 2h in Field 2.