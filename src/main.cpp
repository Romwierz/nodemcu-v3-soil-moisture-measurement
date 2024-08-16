#include <ESP8266WiFi.h>
#include <FS.h>
#include "web_server.h"
#include "sensor.h"

char ssid[32];
char password[64];

void readConfig()
{
  File file = SPIFFS.open("/config.txt", "r");
  if (!file)
  {
    Serial.println("Failed to open config file");
    return;
  }

  String line;
  while (file.available())
  {
    line = file.readStringUntil('\n');
    line.trim();  // Remove any trailing whitespace

    if (line.startsWith("ssid:"))
    {
      line.remove(0, 5);  // Remove the "ssid:" part
      line.toCharArray(ssid, sizeof(ssid));
    }
    else if (line.startsWith("password:"))
    {
      line.remove(0, 9);  // Remove the "password:" part
      line.toCharArray(password, sizeof(password));
    }
  }

  file.close();
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  delay(10);

  if (!SPIFFS.begin())
  {
    Serial.println("Failed to mount file system");
    return;
  }

  readConfig();
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println("Adres IP ESP8266: " + WiFi.localIP().toString());

  setUpSensors();
  setupWebServer();
}

void loop()
{
  server.handleClient();
  isClientInactive();
}