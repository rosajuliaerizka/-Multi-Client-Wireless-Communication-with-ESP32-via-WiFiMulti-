#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>

WiFiMulti wifiMulti;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  wifiMulti.addAP("Nothing", "12345678qwert");

  while(wifiMulti.run() != WL_CONNECTED) {
    delay(100);
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (!client.connected()) {
    client.connect("192.168.63.214", 80);
  }

  if (client.connected()) {
    while (Serial.available()) {
      char c = Serial.read();
      client.print(c);
    }

    if (client.available()) {
      char c = client.read();
      Serial.write(c);
    }
  } else {
    client.stop();
  }
}
