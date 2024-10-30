# Controle de Lâmpada com ESP8266 via Telnet e Atualizações OTA

Este projeto utiliza o ESP8266 para controlar uma lampada remotamente através de uma conexão Telnet e realizar atualizações OTA. O sistema é ideal para monitoramento remoto e permite a fácil atualização do firmware do ESP8266 sem necessidade de conexão física com o dispositivo.



## Funcionalidades

- **Conexão Wi-Fi e Controle Remoto:** Conecta o ESP8266 à rede Wi-Fi para comunicação remota.
- **Servidor Telnet:** Permite o controle da lampada por meio de comandos enviados via Telnet, proporcionando um monitoramento remoto fácil e eficiente.
- **Atualizações OTA (Over-the-Air):** Suporta atualização do código via OTA, permitindo que o firmware do ESP8266 seja atualizado remotamente sem precisar conectar o dispositivo fisicamente.



## Objetivos

O principal objetivo deste projeto é oferecer uma solução prática para controlar uma lampada atraves do Telnet. Utilizando a tecla 0 para desligar a lampada e a tecla 1 para ligar a lampada.




## Requisitos

### Hardware

- ESP8266
- Lampada conectado ao pino D1 (GPIO 5)
- Fonte de alimentação para o ESP8266

### Software

- **Visual Studio Code:** Para editar e fazer o upload do código ao ESP8266.

## Configuração de Rede

- Acesso a uma rede Wi-Fi e as credenciais de login (SSID e senha).

### Configuração

1. Defina o nome da rede (`ssid`) e a senha (`password`) no código para conectar o ESP8266 à sua rede Wi-Fi.
2. Conecte a Lâmpada ao pino D1 (GPIO 5) do ESP8266.

### Upload do Código

- Use o Visual Studio Code para carregar o código no ESP8266.

### Conexão e Monitoramento

1. Abra o Serial Monitor na IDE para verificar o endereço IP atribuído ao ESP8266 ao se conectar ao Wi-Fi.
2. Conecte-se ao dispositivo via Telnet usando o IP exibido e a porta 23.

### Controle da Lâmpada

- Envie o comando `1` para ligar a lampada e `0` para desligá-lo.
- Caso um comando inválido seja enviado, o sistema informará o erro.

### Atualização OTA

- O recurso OTA estará ativo após a conexão Wi-Fi. Para atualizar o firmware remotamente, use a funcionalidade OTA do Arduino IDE.

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests.

## Detalhamento do Código

<h3>Bibliotecas Necessárias</h3>

<p>Este projeto usa as bibliotecas:</p>

```cpp
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
```

<p>Essas bibliotecas permitem a conexão Wi-Fi e a criação de um servidor web no ESP8266.</p> 

<h3>Configurações de Rede</h3> 

<p>No início do código, insira o nome (SSID) e a senha da rede Wi-Fi:</p>

```cpp
const char* ssid = "Nome_da_rede";
const char* password = "Senha_da_rede";
```

Declaração de Variáveis:

```cpp
WiFiServer server(23);
WiFiClient client;
```

<code>WiFiServer server(23)</code>: Cria uma instância do servidor WiFi que escuta na porta 23, padrão para Telnet.
<code>WiFiClient client</code>: Declara um cliente WiFi que será usado para gerenciar a conexão com o cliente Telnet.

Função setup():

```cpp
void setup() {
```

A função <code>setup()</code> é chamada uma vez quando o dispositivo é ligado. Ela configura o ambiente inicial do microcontrolador.

Configuração do LED e Serial:

```cpp
pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
```

<code>pinMode(LED_PIN, OUTPUT)</code>: Configura o pino do LED como saída.
<code>Serial.begin(9600)</code>: Inicializa a comunicação serial a 9600 bps para debug

Conexão WiFi:

```cpp
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
```

<code>WiFi.mode(WIFI_STA)</code>: Configura o modo WiFi como estação (STA) para se conectar a uma rede existente.
<code>WiFi.begin(ssid, password)</code>: Inicia a conexão com a rede WiFi usando o SSID e a senha definidos.

Verificação de Conexão:

```cpp
while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Conexão falhou, tentando novamente...");
    WiFi.begin(ssid, password);
    delay(5000);
  }
```

Um loop que tenta conectar-se à rede WiFi até que a conexão seja bem-sucedida, com mensagens de erro exibidas no console.

Configuração de Atualização OTA:

```cpp
ArduinoOTA.onStart([]() {
    Serial.println("Iniciando atualização OTA...");
  });
```

<code>ArduinoOTA.onStart</code>: Configura um callback para ser chamado ao iniciar uma atualização OTA.:

```cpp
ArduinoOTA.onEnd([]() {
  Serial.println("\nAtualização concluída.");
});
```

<code>ArduinoOTA.onEnd</code>: Callback que é executado quando a atualização é concluída:

```cpp
ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
  Serial.printf("Progresso: %u%%\r", (progress / (total / 100)));
});
```

<code>ArduinoOTA.onProgress</code>: Callback que exibe o progresso da atualização OTA:

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

<code>ArduinoOTA.onError</code>: Callback que trata erros durante o processo de OTA, detalhando o tipo de erro ocorrido:

```cpp
ArduinoOTA.begin();
Serial.println("Pronto para atualizações OTA.");
Serial.print("Endereço IP: ");
Serial.println(WiFi.localIP());
```

<code>ArduinoOTA.begin()</code>: Inicializa o serviço OTA.
<code>Serial.print</code>: Exibe o endereço IP local do microcontrolador:

```cpp
server.begin();
server.setNoDelay(true);
Serial.println("Servidor Telnet iniciado...");
```

<code>server.begin()</code>: Inicia o servidor Telnet.
<code>server.setNoDelay(true)</code>: Configura o servidor para não ter delay, melhorando a performance.

Função loop():

A função <code>loop()</code> é chamada repetidamente e gerencia as interações em tempo real.

```cpp
void loop()
```

Manutenção da Conexão OTA:

```cpp
ArduinoOTA.handle();
```

<code>ArduinoOTA.handle()</code>: Processa as atualizações OTA, permitindo que o microcontrolador responda a solicitações de atualização.

Gerenciamento de Clientes Telnet:

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

<code>server.hasClient()</code>: Verifica se há um cliente tentando se conectar.
O código dentro do bloco gerencia a conexão com o cliente e exibe uma mensagem de boas-vindas.

Leitura e Execução de Comandos:

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
