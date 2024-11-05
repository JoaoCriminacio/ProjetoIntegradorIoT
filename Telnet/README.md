# Controle de Lâmpada com ESP8266 via Telnet e Atualizações OTA

Este projeto utiliza o ESP8266 para controlar uma lampada remotamente através de uma conexão Telnet e realizar atualizações OTA. O sistema é ideal para monitoramento remoto e permite a fácil atualização do firmware do ESP8266 sem necessidade de conexão física com o dispositivo.

## Descrição das Funcionalidades

- **Conexão Wi-Fi e Controle Remoto:** Conecta o ESP8266 à rede Wi-Fi para comunicação remota.
- **Servidor Telnet:** Permite o controle da lampada por meio de comandos enviados via Telnet, proporcionando um monitoramento remoto fácil e eficiente.
- **Atualizações OTA (Over-the-Air):** Suporta atualização do código via OTA, permitindo que o firmware do ESP8266 seja atualizado remotamente sem precisar conectar o dispositivo fisicamente.

## Objetivos

O principal objetivo deste projeto é oferecer uma solução prática para controlar uma lampada através do Telnet. Utilizando a tecla 0 para desligar a lampada e a tecla 1 para ligar a lampada.

## Requisitos

- **ESP8266**
- **Lâmpada**
- **Módulo Relé 1 canal 5v**
- **2 metros de fio de 1,5mm²**
- **Plug Macho Tomada**
- **Plug Tomada Fêmea**
- **Soquete Bocal de Lâmpada**
- **Rede Wi-Fi**
- **Visual Studio Code**
- **PlatformIO**

## Detalhamento do Código

### Bibliotecas Necessárias
---------------------------------------------------------------------------------------------

Este projeto usa as bibliotecas:

```cpp
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
```

Essas bibliotecas permitem a conexão Wi-Fi e a criação de um servidor web no ESP8266.

### Configurações de Rede
---------------------------------------------------------------------------------------------

No início do código, insira o nome (SSID) e a senha da rede Wi-Fi:

```cpp
const char* ssid = "Nome_da_rede";
const char* password = "Senha_da_rede";
```

### Declaração de Variáveis
---------------------------------------------------------------------------------------------

```cpp
WiFiServer server(23);
WiFiClient client;
```

<code>WiFiServer server(23)</code>: Cria uma instância do servidor WiFi que escuta na porta 23, padrão para Telnet. <br>
<code>WiFiClient client</code>: Declara um cliente WiFi que será usado para gerenciar a conexão com o cliente Telnet.

### Função setup()
---------------------------------------------------------------------------------------------

```cpp
void setup() {
```

A função <code>setup()</code> é chamada uma vez quando o dispositivo é ligado. Ela configura o ambiente inicial do microcontrolador.

### Configuração do LED e Serial
---------------------------------------------------------------------------------------------

```cpp
pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
```

<code>pinMode(LED_PIN, OUTPUT)</code>: Configura o pino do LED como saída. <br>
<code>Serial.begin(9600)</code>: Inicializa a comunicação serial a 9600 bps para debug.

### Conexão WiFi
---------------------------------------------------------------------------------------------

```cpp
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
```

<code>WiFi.mode(WIFI_STA)</code>: Configura o modo WiFi como estação (STA) para se conectar a uma rede existente. <br>
<code>WiFi.begin(ssid, password)</code>: Inicia a conexão com a rede WiFi usando o SSID e a senha definidos.

### Verificação de Conexão
---------------------------------------------------------------------------------------------

```cpp
while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Conexão falhou, tentando novamente...");
    WiFi.begin(ssid, password);
    delay(5000);
  }
```

Um loop que tenta conectar-se à rede WiFi até que a conexão seja bem-sucedida, com mensagens de erro exibidas no console.

### Configuração de Atualização OTA
---------------------------------------------------------------------------------------------

```cpp
ArduinoOTA.onStart([]() {
    Serial.println("Iniciando atualização OTA...");
  });
```

<code>ArduinoOTA.onStart</code>: Configura um callback para ser chamado ao iniciar uma atualização OTA.

```cpp
ArduinoOTA.onEnd([]() {
  Serial.println("\nAtualização concluída.");
});
```

<code>ArduinoOTA.onEnd</code>: Callback que é executado quando a atualização é concluída.

```cpp
ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
  Serial.printf("Progresso: %u%%\r", (progress / (total / 100)));
});
```

<code>ArduinoOTA.onProgress</code>: Callback que exibe o progresso da atualização OTA.

```cpp
ArduinoOTA.onError([](ota_error_t error) {
  Serial.printf("Erro[%u]: ", error);
  if (error == OTA_AUTH_ERROR) Serial.println("Falha na autenticação");
  else if (error == OTA_BEGIN_ERROR) Serial.println("Falha no início");
  else if (error == OTA_CONNECT_ERROR) Serial.println("Falha na conexão");
  else if (error == OTA_RECEIVE_ERROR) Serial.println("Falha no recebimento");
  else if (error == OTA_END_ERROR) Serial.println("Falha no finalização");
});
```

<code>ArduinoOTA.onError</code>: Callback que trata erros durante o processo de OTA, detalhando o tipo de erro ocorrido.

```cpp
ArduinoOTA.begin();
Serial.println("Pronto para atualizações OTA.");
Serial.print("Endereço IP: ");
Serial.println(WiFi.localIP());
```

<code>ArduinoOTA.begin()</code>: Inicializa o serviço OTA. <br>
<code>Serial.print</code>: Exibe o endereço IP local do microcontrolador.

```cpp
server.begin();
server.setNoDelay(true);
Serial.println("Servidor Telnet iniciado...");
```

<code>server.begin()</code>: Inicia o servidor Telnet. <br>
<code>server.setNoDelay(true)</code>: Configura o servidor para não ter delay, melhorando a performance.

### Função loop()
---------------------------------------------------------------------------------------------

A função <code>loop()</code> é chamada repetidamente e gerencia as interações em tempo real.

```cpp
void loop()
```

### Manutenção da Conexão OTA
---------------------------------------------------------------------------------------------

```cpp
ArduinoOTA.handle();
```

<code>ArduinoOTA.handle()</code>: Processa as atualizações OTA, permitindo que o microcontrolador responda a solicitações de atualização.

### Gerenciamento de Clientes Telnet
---------------------------------------------------------------------------------------------

```cpp
if (server.hasClient()) {
  if (!client || !client.connected()) {
    if (client) client.stop();
    client = server.available();
    Serial.println("Cliente conectado via Telnet.");
    client.println("Digite '1' para ligar o LED e '0' para desligar o LED.");
  } else {
    server.available().stop();
  }
}
```

<code>server.hasClient()</code>: Verifica se há um cliente tentando se conectar. <br>
O código dentro do bloco gerencia a conexão com o cliente e exibe uma mensagem de boas-vindas.

### Leitura e Execução de Comandos
---------------------------------------------------------------------------------------------

```cpp
if (client && client.connected() && client.available()) {
    char command = client.read();
```

<code>client.available()</code>: Verifica se há dados disponíveis do cliente.

```cpp
if (command == '1') {
    digitalWrite(LED_PIN, LOW); 
    client.println("LED ligado.");
    Serial.println("LED ligado.");
} else if (command == '0') {
    digitalWrite(LED_PIN, HIGH); 
    client.println("LED desligado.");
    Serial.println("LED desligado.");
  } else {
    client.println("Comando inválido. Digite '1' para ligar o LED e '0' para desligar o LED.");
}
```

O código verifica o comando recebido ('1' ou '0') e liga ou desliga o LED correspondente, enviando uma resposta ao cliente via Telnet.
