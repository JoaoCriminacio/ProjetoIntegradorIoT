# Projeto: Controle de LED via Servidor Web com NodeMCU

<p>Este projeto cria um servidor web em um microcontrolador, permitindo o controle remoto de um LED conectado ao pino D1 através de uma interface web.</p>

<h2>Funcionalidades</h2>

<ul>
  <li>Conexão do NodeMCU a uma rede Wi-Fi usando SSID e senha.</li>
  <li>Configuração de um servidor web na porta 80, acessível pela rede local.</li>
  <li>Interface web com botões para ligar e desligar o LED remotamente.</li>
</ul>

<h2>Componentes Necessários</h2>

<ul>
  <li>NodeMCU.</li>
  <li>Lâmpada.</li>
  <li>2 metros de fio de 1,5mm².</li>
  <li>Plug Macho Tomada.</li>
  <li>Soquete Bocal de Lâmpada.</li>
  <li>Plug Tomada Fêmea.</li>
</ul>

<h2>Código do Projeto</h2>

<h3>Bibliotecas Necessárias</h3>

<p>Este projeto usa as bibliotecas:</p>

```cpp
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

<p>Essas bibliotecas permitem a conexão Wi-Fi e a criação de um servidor web no ESP8266.</p> 

<h3>Configurações de Rede</h3> 

<p>No início do código, insira o nomde (SSID) e a senha da rede Wi-Fi:</p>

```cpp
const char* ssid = "Nome_da_rede";
const char* password = "Senha_da_rede";

<p>Em seguida, configure o endereço IP do NodeMCU colocando um IP da sua faixa de rede:</p>

```cpp
IPAddress local_IP(192,168,227,241); // Altere para o IP desejado
IPAddress gateway(192,168,227,217);
IPAddress subnet(255,255,255,0);

<h3>Funções do Servidor Web</h3> 

<ul> 
    <li><strong>Página Inicial (<code>handleRoot</code>)</strong>: Envia uma interface HTML com botões <code>ON</code> e <code>OFF</code> para controle da lâmpada.</li>
    <li><strong>Ligar a lâmpada (<code>handleOn</code>)</strong>: Liga a lâmpada e envia uma mensagem de confirmação.</li> 
    <li><strong>Desligar a lâmpada (<code>handleOff</code>)</strong>: Desliga a lâmpada e envia uma mensagem de confirmação.</li>
</ul> 

<h3>Configuração do Servidor e Loop Principal</h3> 

<p>No <code>setup()</code>, o NodeMCU conecta-se ao Wi-Fi e configura as rotas do servidor:</p> 
<ul> 
    <li><code>/</code>: Página principal com os botões.</li> 
    <li><code>/5/on</code>: Rota para ligar a lâmpada.</li> 
    <li><code>/5/off</code>: Rota para desligar a lâmpada.</li> 
</ul> 
<p>O <code>loop()</code> mantém o servidor ativo, permitindo a recepção de novas requisições.</p> 

<h2>Código Completo Presente no Arquivo <strong>main.cpp</strong></h2>