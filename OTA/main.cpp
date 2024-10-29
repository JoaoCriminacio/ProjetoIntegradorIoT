#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

/* [*] - ponteiro */
const char* ssid = "ssid";
const char* password = "password";

void setup(){
  /* Abrir uma comunicação serial */
  Serial.begin(9600);
  /* Modo do Wi-Fi */
  WiFi.mode(WIFI_STA);
  /* Iniciar colocando as credenciais */
  WiFi.begin(ssid, password);

  /* Enquanto a conexão for diferente de conectado, fica tentanto reconectar */
  while(WiFi.waitForConnectResult() != WL_CONNECTED){
    Serial.println("Conexão falhou! Rebooting...");
    WiFi.begin(ssid, password);
    delay(5000);
  }

  /* Funções assíncronas */
  ArduinoOTA.onStart([](){
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([](){
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total){
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  /* Função assíncrona que lida com os erros */
  ArduinoOTA.onError([](ota_error_t error){
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Pronto");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop(){
  ArduinoOTA.handle();
}