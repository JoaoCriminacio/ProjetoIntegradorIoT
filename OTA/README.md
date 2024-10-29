<h1 text-center>PROJETO OTA<h1>

Este código é um programa para ESP8266 que configura o dispositivo para se conectar a uma rede Wi-Fi e suporta atualizações OTA. Ele permite enviar novos firmwares para o ESP8266 remotamente, o que facilita a atualização sem necessidade de cabos. Abaixo está uma explicação detalhada das principais partes do código:

### Descrição das Funcionalidades

1. **Conexão Wi-Fi**:

   - O ESP8266 tenta conectar-se a uma rede Wi-Fi usando o SSID e senha fornecidos.
   - A função `WiFi.mode(WIFI_STA);` coloca o dispositivo no modo "Station", permitindo que ele se conecte a um roteador como cliente.
   - `WiFi.begin(ssid, password);` inicia a tentativa de conexão.
   - Um loop de reconexão é implementado com `while(WiFi.waitForConnectResult() != WL_CONNECTED)`, que garante que o ESP8266 continue tentando conectar até que seja bem-sucedido. Caso a conexão falhe, ele exibe uma mensagem e tenta novamente após 5 segundos.

2. **Configuração OTA (Over-The-Air)**:

   - Esta funcionalidade permite atualizações remotas do firmware através de OTA.
   - `ArduinoOTA.onStart` executa uma função de callback quando o processo de atualização começa, indicando o início da atualização.
   - `ArduinoOTA.onEnd` é chamada ao final da atualização, exibindo uma mensagem no console serial.
   - `ArduinoOTA.onProgress` exibe o progresso da atualização em porcentagem.
   - `ArduinoOTA.onError` lida com os erros de OTA, mostrando uma mensagem específica de acordo com o tipo de erro.

3. **Inicialização e Monitoramento da OTA**:
   - `ArduinoOTA.begin()` inicializa o processo OTA, tornando o dispositivo pronto para receber novas atualizações remotamente.
   - Dentro da função `loop`, `ArduinoOTA.handle()` monitora constantemente a conexão OTA, permitindo que o ESP8266 entre em modo de atualização assim que um novo firmware for detectado.

### Objetivo e Utilização

Este código é útil para projetos de IoT onde é necessário atualizar o firmware do ESP8266 de maneira prática e rápida. A funcionalidade OTA elimina a necessidade de conexão física para realizar atualizações, permitindo que dispositivos já instalados em locais de difícil acesso possam receber novas funcionalidades ou correções de forma remota.

## Requisitos
- **ESP8266**
- **Rede Wi-Fi** 
- **Visual Studio Code** 
- **PlataformIO**