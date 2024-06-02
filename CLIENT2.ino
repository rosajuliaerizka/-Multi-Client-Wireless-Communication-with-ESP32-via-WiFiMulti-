#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

WiFiMulti wifiMulti;
WiFiServer server(80);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  wifiMulti.addAP("Nothing", "12345678qwert");

  while(wifiMulti.run() != WL_CONNECTED) {
    delay(100);
  }
  Serial.println("Connected to WiFi");

  server.begin();
}

void loop() {
  if (!client || !client.connected()) {
    client = server.available();
  }

  if (client && client.connected()) {
    while (Serial.available()) {
      char c = Serial.read();
      client.print(c);
    }

    if (client.available()) {
      char c = client.read();
      Serial.write(c);
    }
  } else {
    if (client) {
      client.stop();
    }
  }
}
