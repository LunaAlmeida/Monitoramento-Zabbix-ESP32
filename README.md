# Projeto de Monitoramento Ubíquo com Zabbix, Grafana e ESP32  

## Introdução  
O conceito de **computação ubíqua** refere-se à integração invisível e contínua da tecnologia no cotidiano, facilitando atividades como:  
- 🏡 **Automação residencial** (controle de temperatura/umidade)  
- 🏭 **Gestão industrial** (monitoramento de estoques em tempo real)  
- ❤️ **Saúde digital** (wearables com telemetria)  

## Justificativa  
Como esses sistemas operam **24/7**, exige-se:  
✔️ Alta disponibilidade  
✔️ Monitoramento proativo  
✔️ Visualização intuitiva de dados  

## Solução Proposta  
### Ferramentas  
| Tecnologia          | Função                                                                 |  
|---------------------|-----------------------------------------------------------------------|  
| **Zabbix**          | Coleta e armazena métricas com triggers para alertas                 |  
| **Grafana**         | Dashboard interativo com gráficos personalizados                     |  
| **ESP32**           | Microcontrolador para aquisição de dados dos sensores                |  

### Componentes Utilizados  
- **Sensores**:  
  - 🌡️ `DHT11` (temperatura/umidade)  
  - 🔥 `LM35` (temperatura analógica)  
  - 💡 `LDR` (luminosidade)  
- **Atuadores**:  
  - 🚨 `Buzzer` (alertas sonoros)  
  - 🎨 `LED RGB` (feedback visual)  
# Diagrama de Comunicação
![Diagrama de Comunicação](https://github.com/user-attachments/assets/185a8113-627d-4528-9dbe-139b13974f06)

# Materiais e métodos
Nesta seção será descrito cada um dos componentes utilizados no projeto. Na página de explicação de cada ferramenta, é possível encontrar mais informações e tutoriais sobre como utilizá-las.
- [**ESP32**](https://github.com/LunaAlmeida/Monitoramento-Zabbix-ESP32/tree/main/Componentes/Esp32): microcontrolador acessível, com Wi-Fi, Bluetooth, dual-core e ampla versatilidade para IoT e projetos eletrônicos;
- [**Arduino Shield K596 ou HY-M302**](https://github.com/LunaAlmeida/Monitoramento-Zabbix-ESP32/tree/main/Componentes/Arduino%20Shield%20K596): placa de expansão que adiciona recursos específicos como comunicação, sensores ou atuadores;
- [**MQTT-Mosquitto**](https://github.com/LunaAlmeida/Monitoramento-Zabbix-ESP32/tree/main/Componentes): protocolo de comunicação leve e eficiente, baseado em publish/subscribe, ideal para IoT com baixo consumo de banda e recursos;
- [**Zabbix**](): solução de monitoramento de rede, servidores e aplicações em tempo real, com alertas, gráficos e alta escalabilidade;
- [**Grafana**](): plataforma de visualização e análise de dados em tempo real, com dashboards interativos e suporte a múltiplas fontes de dados.

  # Diagrama dos componentes
  O diagrama abaixo define a configuração física utilizada e a interconexão dos componentes do projeto:
  ![Diagrama do Circuito](https://github.com/user-attachments/assets/dc7d0296-dc59-4293-9770-f92264afc933)

| Pino no HY-M302 (componente)     | Pino no ESP32         |
| -------------------------------- | --------------------- |
| D4 (DHT 11)                      | GPIO 19               |
| D2 (Botão 1)                     | GPIO 39               |
| D3 (Botão 2)                     | GPIO 36               |
| D13 (Led Azul)                   | GPIO 13               |
| D12 (Led Vermelho)               | GPIO 12               |
| D5 (Buzzer)                      | GPIO 15               |
| D6 (Receptor IR)                 | GPIO 33               |
| D9, D10, D11 (Led RGB)           | GPIO 23, 22 e 21      |
| A0 (Potenciômetro)               | GPIO 34               |
| A1 (LDR)                         | GPIO 32               |
| A2 (LM35)                        | GPIO 35               |

# Configuração de Ambiente Local

Pré-requisitos:

➔ Sistema Linux Ubuntu Server 24.04 LTS;

➔ Zabbix 7.0 LTS;

➔ 2 CPU;

➔ 4GB RAM.

Para configurar o ambiente local, siga os passos abaixo. Este arquivo deve conter informações sensíveis como SSID e senha da rede WiFi, além da URL do servidor:
1. Navegue até a pasta `Codigo` do seu projeto.
2. Modifique as seguintes linhas no arquivo `main.ino`:
   
   ```
   const char* ssid = "nome da sua rede"; 
   const char* password = "senha da sua rede";
   const char* mqtt_server = "Endereço de IP do Host";

   const char*  mqtt_user = "seu usuário do broker";
   const char* mqtt_password = "sua senha do broker";
   ```
   # Configuração do Arduino IDE
   - Instale o Arduino IDE.
   - Acesse: Arquivo → Preferências. No campo URLs de gerenciador adicional de placas adicone a seguinte URL: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Na aba Ferramentas no campo Placa escolha `ESP32 DEV Module`;
   - Ainda em Ferramentas adicione a porta em que está conectado o ESP32 no campo Porta.
     
   ## Bibliotecas necessárias
   - Adafruit Unified Sensor by Adafruit;
   - Arduinojson by Benoit Blanchon;
   - DHT sensor library by Adafruit;
   - IRremote by shirriff, z3tO, ArminJo;
   - PubSubClient by Nick O'Leary.
  
   # Configuração do MQTT
   - Instale o MQTT;
   - Crie um arquivo de senhas: `sudo mosquitto_passwd -c /etc/mosquitto/passwd seu_usuário`, após esse comando aparecerá o campo para adicionar a senha do seu broker;
   - Em `sudo nano /etc/mosquitto/mosquitto.conf` tenha a seguinte configuração:
   ![Config MQTT](https://github.com/user-attachments/assets/c1fbf76d-aae8-4569-b997-fc979df14902)
    - Reinicie o MQTT;
    - Pode ocorrer um erro com o firewall na porta 1883, caso ocorra, utilize `sudo ufw allow 1883`.

   
     
