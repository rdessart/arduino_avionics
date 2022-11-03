#include <SPI.h>
#include <WiFiNINA.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
char ssid[] = "arduinoAP";
char pass[] = "arduinopassword";
int keyIndex = 0;
int status = WL_IDLE_STATUS;
SoftwareSerial ss(4, 3);
WiFiUDP Udp;
int localportIn = 50505;
int localportOut = 50506;
char packetBuffer[255];
char ReplyBuffer[] = "data";  
IPAddress ip(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  while (!Serial) 
  {;}
  Serial.println("Access Point Web Server");
  if (WiFi.status() == WL_NO_MODULE) 
  {
    Serial.println("Communication with WiFi module failed!");
    while(1);
  }
  Serial.print("Creating access point named: ");
  Serial.println(ssid);
  WiFi.config(ip, ip, ip, subnet);
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING)
  {
    Serial.println("Creating access point failed");
    while (true);
  }
  Udp.begin(localportIn);
}

void loop() 
{
  bool newData = false;
  long lat, lon;
  unsigned long fix_age, time, date, speed, course;
  unsigned long chars;
  unsigned short sentences, failed_checksum;
  while (ss.available() > 0)
  {
    int c = ss.read();
    Serial.write(c);
    if (gps.encode(c))
    {
      newData = true;
    }
  }
  if(newData)
  {
    gps.get_position(&lat, &lon, &fix_age);
    lat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lat;
    lon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lon;
    gps.get_datetime(&date, &time, &fix_age);
    speed = gps.speed();
    course = gps.course();
    String s;
    s.concat("LAT=");
    s.concat(lat);
    s.concat(" LON=");
    s.concat(lon);
    s.concat(" SAT=");
    s.concat(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    s.concat(" PREC=");
    s.concat(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    Serial.println(s);
  }
}
