// Inclui as bibliotecas necessárias
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

// Define constantes para conexão Wi-Fi e SinricPro
#define WIFI_SSID "Galaxy M515ABA"
#define WIFI_PASS "pediuasenha=mamou"
#define APP_KEY "82057f31-8da3-47c0-8ff1-baec887b4197"
#define APP_SECRET "b9394af3-dad1-4e1c-bfc2-cf6a6cf2a260-d5d2aeae-96ca-4762-8145-f1e65aea7dcf"
#define SWITCH_ID "6733d40b88a12c713ba8e70e"
#define BAUD_RATE 9600

// Define os pinos GPIO para o botão e o rele
#define BUTTON_PIN 0 // GPIO para o BOTÃO (inverso: LOW = pressionado, HIGH = liberado)
#define RELE_PIN 5
bool myPowerState = false; // Indica o estado atual do dispositivo (ligado/desligado)
unsigned long lastBtnPress = 0; // Última vez que o botão foi pressionado (usado para debounce)


// Esta função é chamada quando o dispositivo é controlado remotamente via SinricPro
bool onPowerState(const String &deviceId, bool &state) {
  // Exibe no Serial Monitor o estado atual
  Serial.printf("Device %s turned %s (via SinricPro) \r\n", deviceId.c_str(), state?"on":"off");

  myPowerState = state;

  // Define o estado do rele com base no estado do dispositivo (Operador Ternário)
  digitalWrite(RELE_PIN, myPowerState?LOW:HIGH);
  return true;
}

// Esta função trata a pressão do botão físico
void handleButtonPress() {
  unsigned long actualMillis = millis();

  if (digitalRead(BUTTON_PIN) == LOW && actualMillis - lastBtnPress > 1000) {
    myPowerState = !myPowerState;
    digitalWrite(RELE_PIN, myPowerState?LOW:HIGH);

    // Envia o novo estado para o servidor SinricPro
    SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];
    mySwitch.sendPowerStateEvent(myPowerState);
    Serial.printf("Device %s turned %s (manually via flashbutton)\r\n",
    mySwitch.getDeviceId().c_str(), myPowerState?"on":"off");
    lastBtnPress = actualMillis;
  }
}

// Função para conectar o ESP8266 ao Wi-Fi
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }

  Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
}

// Função para configurar a conexão com SinricPro
void setupSinricPro() {
  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];
  mySwitch.onPowerState(onPowerState);
  // Configura callbacks para a conexão com SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); });
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

// Função principal de configuração
void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, HIGH);
  Serial.begin(BAUD_RATE);

  setupWiFi();
  setupSinricPro();
}
// Loop principal
void loop() {
  handleButtonPress();
  SinricPro.handle(); // Constantemente verifica e trata solicitações da plataforma SinricPro
}