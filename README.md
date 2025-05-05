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

## Implementação  
1. **Configuração do Zabbix**:  
   - Criação de hosts/itens para cada sensor  
   - Definição de triggers (ex.: `{ESP32:temp.last()} > 30°C`)  
