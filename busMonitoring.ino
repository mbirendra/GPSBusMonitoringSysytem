#include <SoftwareSerial.h>
#include <TinyGPS.h>

float gpslat, gpslon;
TinyGPS gps;
SoftwareSerial sgps(4, 5);
SoftwareSerial sgsm(7, 8);
void setup()
{​
Serial.begin(19200);
sgsm.begin(19200);
sgps.begin(19200);
 delay(10000);
Serial.println("GSM SIM900 IS ONLINE...");
delay(3000);
Serial.println("GSM IS ONLINE...");
}​
void loop()
{​
sgps.listen();
while (sgps.available())
{​
int c = sgps.read();
if (gps.encode(c))
{​
gps.f_get_position(&gpslat, &gpslon);
}​
}​
sgsm.listen();
if (sgsm.available() > 0) {​
String c = sgsm.readString();
if (c.indexOf("GET-LOCATION") >= 0) {​
sgsm.print("\r");
delay(1000);
sgsm.print("AT+CMGF=1\r");
delay(1000);
sgsm.print("AT+CMGS=\"+9779802798072\"\r");
delay(1000);
sgsm.print("https://www.google.com/maps/?q=");
sgsm.print(gpslat, 6);
sgsm.print(",");
sgsm.print(gpslon, 6);
delay(1000);
sgsm.write(0x1A);
delay(1000);
}​
}​
}​
