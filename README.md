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

