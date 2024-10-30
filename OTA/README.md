# Projeto OTA

<h5>Este código é um programa para ESP8266 que configura o dispositivo para se conectar a uma rede Wi-Fi e suporta atualizações OTA. Ele permite enviar novos firmwares para o ESP8266 remotamente, o que facilita a atualização sem necessidade de cabos. Abaixo está uma explicação detalhada das principais partes do código:</h5>

## Descrição das Funcionalidades

1. **Conexão Wi-Fi**:

   - O ESP8266 tenta conectar-se a uma rede Wi-Fi usando o SSID e senha fornecidos.
   - A função `WiFi.mode(WIFI_STA);` coloca o dispositivo no modo "Station", permitindo que ele se conecte a um roteador como cliente.
   - `WiFi.begin(ssid, password);` inicia a tentativa de conexão.
   - Um loop de reconexão é implementado com `while(WiFi.waitForConnectResult() != WL_CONNECTED)`, que garante que o ESP8266 continue tentando conectar até que seja bem-sucedido. Caso a conexão falhe, ele exibe uma mensagem e tenta novamente após 5 segundos.

2. **Configuração OTA**:

   - Esta funcionalidade permite atualizações remotas do firmware através de OTA.
   - `ArduinoOTA.onStart` executa uma função de callback quando o processo de atualização começa, indicando o início da atualização.
   - `ArduinoOTA.onEnd` é chamada ao final da atualização, exibindo uma mensagem no console serial.
   - `ArduinoOTA.onProgress` exibe o progresso da atualização em porcentagem.
   - `ArduinoOTA.onError` lida com os erros de OTA, mostrando uma mensagem específica de acordo com o tipo de erro.

3. **Inicialização e Monitoramento da OTA**:
   - `ArduinoOTA.begin()` inicializa o processo OTA, tornando o dispositivo pronto para receber novas atualizações remotamente.
   - Dentro da função `loop`, `ArduinoOTA.handle()` monitora constantemente a conexão OTA, permitindo que o ESP8266 entre em modo de atualização assim que um novo firmware for detectado.

## Objetivo e Utilização

Este código é útil para projetos de IoT onde é necessário atualizar o firmware do ESP8266 de maneira prática e rápida. A funcionalidade OTA elimina a necessidade de conexão física para realizar atualizações, permitindo que dispositivos já instalados em locais de difícil acesso possam receber novas funcionalidades ou correções de forma remota.

## Requisitos

- **ESP8266**
- **Rede Wi-Fi**
- **Visual Studio Code**
- **PlataformIO**

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

No início do código, insira o nomde (SSID) e a senha da rede Wi-Fi:

```cpp
const char* ssid = "Nome_da_rede";
const char* password = "Senha_da_rede";
```

---------------------------------------------------------------------------------------------

```cpp
void setup() {
  /* Abrir uma comunicação serial */
  Serial.begin(9600);
  
  /* Modo do Wi-Fi */
  WiFi.mode(WIFI_STA);
  
  /* Iniciar colocando as credenciais */
  WiFi.begin(ssid, password);
}
```

- **Serial.begin(9600):** Define a taxa de comunicação serial em 9600 bps (bits por segundo), permitindo monitoramento e depuração do ESP8266.
  
- **WiFi.mode(WIFI_STA):** Define o ESP8266 como uma estação (STA), habilitando-o para conectar-se a redes Wi-Fi existentes.
  
- **WiFi.begin(ssid, password):** Tenta conectar o ESP8266 à rede Wi-Fi especificada pelas variáveis `ssid` (nome da rede) e `password` (senha).

Este código é a base para conectar o ESP8266 a uma rede Wi-Fi, preparando-o para comunicação e interação com outros dispositivos na mesma rede.

---------------------------------------------------------------------------------------------

```cpp
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
```

- **ArduinoOTA.onStart:** Define uma função de callback que é executada no início da atualização OTA. Quando a atualização começa, a mensagem `"Start"` é exibida no monitor serial.

- **ArduinoOTA.onEnd:** Define uma função de callback para o final da atualização. Quando a atualização termina, a mensagem `"End"` é exibida no monitor serial.

- **ArduinoOTA.onProgress:** Exibe o progresso da atualização em tempo real. À medida que a atualização ocorre, o monitor serial mostra o progresso percentual, com o valor calculado em relação ao total de dados a serem transferidos.

---------------------------------------------------------------------------------------------

```cpp
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
```

- **ArduinoOTA.onError:** Define uma função de callback para tratamento de erros que podem ocorrer durante a atualização OTA. Dependendo do tipo de erro, diferentes mensagens são exibidas:
  - **OTA_AUTH_ERROR:** Falha na autenticação.
  - **OTA_BEGIN_ERROR:** Falha ao iniciar o processo de atualização.
  - **OTA_CONNECT_ERROR:** Falha na conexão para atualização.
  - **OTA_RECEIVE_ERROR:** Falha ao receber os dados da atualização.

- **ArduinoOTA.begin():** Inicializa o serviço OTA, preparando o ESP8266 para receber atualizações remotas.

- **Serial.println("Pronto") e Serial.print("IP: "):** Informa que o ESP8266 está pronto e exibe o endereço IP obtido na rede Wi-Fi, permitindo fácil identificação do dispositivo para futuras conexões OTA.

---------------------------------------------------------------------------------------------

```cpp
void loop() {
  ArduinoOTA.handle();
}
```

## Explicação
---------------------------------------------------------------------------------------------

- **ArduinoOTA.handle():** Mantém a conexão OTA ativa e verifica se há uma atualização OTA pendente. Sempre que `ArduinoOTA.handle()` é chamado, ele processa solicitações OTA, permitindo que o ESP8266 aceite e aplique atualizações enviadas pela rede.

Essa chamada no loop principal garante que o ESP8266 esteja continuamente pronto para receber atualizações OTA, evitando a necessidade de reiniciar o dispositivo para aplicar uma nova versão do firmware.
