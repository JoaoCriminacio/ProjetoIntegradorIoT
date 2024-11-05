# Controle de LED via Servidor Web com NodeMCU

Este projeto cria um servidor web no microcontrolador NodeMCU, permitindo o controle remoto de um LED integrado através de uma interface web simples. Além disso, o NodeMCU oferece suporte para atualizações de firmware OTA.

## Funcionalidades

- Conexão à rede Wi-Fi configurada pelo usuário.
- Configuração de um servidor web local na porta 80.
- Interface web para ligar e desligar o LED remotamente.
- Suporte a atualizações OTA para facilitar a manutenção do código.

## Componentes Necessários

- NodeMCU (ESP8266).
- LED (integrado ao NodeMCU).
- Rede Wi-Fi
- Visual Studio Code
- PlataformIO

## Bibliotecas Utilizadas

O projeto faz uso das seguintes bibliotecas para conectar o microcontrolador à rede Wi-Fi, criar o servidor web e habilitar atualizações OTA:

```cpp
#include <ArduinoOTA.h>        // Suporte para atualizações Over-The-Air
#include <ESP8266WiFi.h>       // Conexão Wi-Fi no ESP8266
#include <ESP8266WebServer.h>  // Criação de servidor web no ESP8266
```

## Configurações de Rede

No início do código, você precisa configurar o nome (SSID) e a senha da rede Wi-Fi para conectar o NodeMCU:

```cpp
const char* ssid = "Galaxy M515ABA";   // Substitua pelo nome da sua rede
const char* password = "";  // Substitua pela senha da sua rede
```

Em seguida, configure o endereço IP do NodeMCU, que será usado para acessá-lo na rede:

```cpp
IPAddress local_IP(192,168,227,241); // IP estático desejado
IPAddress gateway(192,168,227,217);  // Gateway da rede
IPAddress subnet(255,255,255,0);     // Máscara de sub-rede
```

## Funções do Código

### 1. Configurar Wi-Fi

Esta função conecta o NodeMCU à rede Wi-Fi utilizando o SSID e a senha fornecidos, e tenta configurar um IP estático.

```cpp
void configureWiFi() {
  WiFi.mode(WIFI_STA);  // Define o NodeMCU no modo de estação (STA)
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Falha ao configurar IP.");
  }
  WiFi.begin(ssid, password);  // Inicia a conexão com a rede Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  // Aguarda a conexão
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  // Exibe o IP na serial
}
```

### 2. Página Inicial do Servidor Web

Esta função serve a página HTML com dois botões: um para ligar o LED e outro para desligá-lo.

```cpp
void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<link rel=\"icon\" href=\"data:,\">";
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background-color: #4b5563; color: #f8fafc;}";
  html += ".button { background-color: #22c55e; border: none; color: white; padding: 16px 40px;";
  html += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
  html += ".button2 {background-color: #ef4444;}</style></head>";
  html += "<body><h1>Turning on LED of NodeMCU</h1>";
  html += "<h2>Buttons</h2>";
  html += "<button onclick=\"toggleLED('on')\" class=\"button\">ON</button>";
  html += "<button onclick=\"toggleLED('off')\" class=\"button button2\">OFF</button>";
  html += "<script>";
  html += "function toggleLED(state) {";
  html += "  var xhr = new XMLHttpRequest();";
  html += "  xhr.open('GET', '/' + state, true);";
  html += "  xhr.send();";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);  // Envia a página HTML para o cliente
}
```

### 3. Ligar e Desligar o LED

As duas funções abaixo ligam ou desligam o LED integrado ao NodeMCU (LED_BUILTIN). A resposta HTTP é uma mensagem de confirmação enviada ao cliente.

```cpp
void turnOnLED() {
  digitalWrite(LED_BUILTIN, LOW);  // Liga o LED (inverte porque o LED é ativo em LOW)
  server.send(200, "text/plain", "LED Ligado!");  // Envia mensagem de confirmação
  Serial.println("LED foi ligado.");
}

void turnOffLED() {
  digitalWrite(LED_BUILTIN, HIGH);  // Desliga o LED
  server.send(200, "text/plain", "LED Desligado!");  // Envia mensagem de confirmação
  Serial.println("LED foi desligado.");
}
```

### 4. Configurações de Atualizações OTA

O código abaixo configura o suporte para atualizações OTA (Over-The-Air), permitindo atualizar o firmware do NodeMCU sem precisar de conexão física. O código lida com o progresso e erros da atualização.

```cpp
void setupOTA() {
  ArduinoOTA.setPassword("vaiCurintia");  // Define uma senha para as atualizações OTA

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));  // Exibe progresso
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
  });

  ArduinoOTA.begin();  // Inicializa o OTA
}
```

## Configuração do Servidor Web

No `setup()`, o código inicializa a conexão Wi-Fi e configura as rotas do servidor para controlar o LED via HTTP.

```cpp
void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial

  pinMode(LED_BUILTIN, OUTPUT);  // Define o pino do LED como saída
  digitalWrite(LED_BUILTIN, HIGH);  // Mantém o LED desligado inicialmente

  configureWiFi();  // Configura o Wi-Fi
  setupOTA();  // Configura o OTA

  server.on("/", HTTP_GET, handleRoot);  // Rota para a página inicial
  server.on("/on", HTTP_GET, turnOnLED);  // Rota para ligar o LED
  server.on("/off", HTTP_GET, turnOffLED);  // Rota para desligar o LED

  server.begin();  // Inicializa o servidor
  Serial.println("Pronto para uso.");
}
```

## Loop Principal

O `loop()` mantém o servidor rodando e processa as atualizações OTA.

```cpp
void loop() {
  ArduinoOTA.handle();  // Processa atualizações OTA
  server.handleClient();  // Mantém o servidor web ativo
}
```

## Conclusão

Este projeto é ideal para aprender a controlar dispositivos remotamente usando um servidor web simples. O suporte para atualizações OTA facilita a manutenção e evolução do firmware sem a necessidade de desconectar o hardware.
