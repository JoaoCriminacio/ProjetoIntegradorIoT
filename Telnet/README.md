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

- **Arduino IDE:** Para editar e fazer o upload do código ao ESP8266.

### Bibliotecas

- `ESP8266WiFi.h`: Biblioteca para gerenciar a conexão Wi-Fi do ESP8266.
- `ArduinoOTA.h`: Biblioteca para permitir atualizações OTA.

## Configuração de Rede

- Acesso a uma rede Wi-Fi e as credenciais de login (SSID e senha).

## Utilização

### Configuração

1. Defina o nome da rede (`ssid`) e a senha (`password`) no código para conectar o ESP8266 à sua rede Wi-Fi.
2. Conecte a Lâmpada ao pino D1 (GPIO 5) do ESP8266.

### Upload do Código

- Use o Arduino IDE para carregar o código no ESP8266.

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
