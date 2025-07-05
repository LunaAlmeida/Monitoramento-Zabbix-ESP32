#include <DHT.h>
#include <IRremote.hpp>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define DHTTYPE DHT11
#define DHT11PIN 19
DHT dht(DHT11PIN, DHTTYPE);

#define redLed 12
#define blueLed 13
#define LDRPin 32

const int redLed_RGB = 23;
const int greenLed_RGB = 22;
const int blueLed_RGB = 21;

const int button1Pin = 36;
const int button2Pin = 39;

const int potPin = 34;

const int tempPin = 35;

const int BUZZER_PIN = 15;

const int IR_RECEIVER_PIN = 33;

size_t ligarDesligar = 'A';
size_t timer = 'B';
size_t nebula = '3';
size_t aumentarBrilho = '1';
size_t diminuirBrilho = '5';
size_t aumentarGiro = '4';
size_t diminuirGiro = '2';
size_t diminuirEstrelas = 'C';
size_t aumentarEstrelas = 'D';
size_t modoEstelar = 'E';
size_t ligarDesligarEstrelas = 'F';
size_t reset = '1A';

int button1State = 0;
int button2State = 0;

int shireNotas[] = { 659, 659, 659, 523, 659, 784, 392, 523, 392, 330, 440, 494, 466, 440, 392, 659, 784, 880, 698, 784, 659, 523, 587, 494 };
int shireDuracao[] = { 250, 125, 125, 250, 250, 250, 250, 125, 125, 250, 250, 125, 125, 125, 125, 250, 250, 250, 250, 125, 125, 250, 250, 250 };

int mordorNotas[] = { 220, 196, 165, 220, 196, 165, 220, 196, 165, 247, 220, 196, 165 };
int mordorDuracao[] = { 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500 };

const char* ssid = "Luna";
const char* password = "qtsi8070";

const char* mqtt_server = "10.144.0.182";
const int mqtt_port = 1883;
const char*  mqtt_user = "zabbix";
const char* mqtt_password = "zabbix";

WiFiClient espClient;
PubSubClient client(espClient);

#define statusTopic "sensores/HYM302"

#define temp1Topic statusTopic "/temperaturaDHT11"
#define temp2Topic statusTopic "/temperaturaLM35"
#define humTopic statusTopic "/umidade"
#define luzTopic statusTopic "/luz"
#define ledAzulTopic statusTopic "/ledAzul"
#define ledVermelhoTopic statusTopic "/ledVermelho"
#define potTopic statusTopic "/potenciometro"
#define receptorIRTopic statusTopic "/receptorIR"
#define botao1Topic statusTopic "/botao1"
#define botao2Topic statusTopic "/botao2"
#define redeTopic statusTopic "/rssi"

void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("Ender. de IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while(!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    if(client.connect("ESP32Client", mqtt_user, mqtt_password)){
      Serial.println("conectado");
    }else{

      Serial.print("failed rc=");
      Serial.print(client.state());
      Serial.println(" tentando de novo em 5 segundos");
      delay(5000);
    }
  }
}

void melodia(int notas[], int duracao[], int tempo)
{
  for (int i = 0; i < tempo; i++) {
    if (notas[i] == 0) {  
      delay(duracao[i]);
    } else {
      tone(BUZZER_PIN, notas[i], duracao[i]);
      delay(duracao[i] * 1.1);  
    }
    noTone(BUZZER_PIN);
  }
}

int setColor(int red, int green, int blue)
{
  analogWrite(redLed_RGB, red);
  analogWrite(greenLed_RGB, green);
  analogWrite(blueLed_RGB, blue);

  return 1;
}

void checkPotentiometer()
{
  static int lastPotValue = 0;
  int currentPotValue =  analogRead(potPin);

  if(abs(currentPotValue - lastPotValue)  > 50)
  {
    lastPotValue = currentPotValue;
    int newSpeed = map(currentPotValue, 0, 4095, 5, 100);
    Serial.print("Nova velocidade de transicao: ");
    Serial.print(newSpeed);
    Serial.println("ms");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  dht.begin();

  IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK);
  Serial.print("Protocolos suportados: ");
  printActiveIRProtocols(&Serial);

  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  pinMode(redLed_RGB, OUTPUT);
  pinMode(greenLed_RGB, OUTPUT);
  pinMode(blueLed_RGB, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

  client.setKeepAlive(60);

  client.setSocketTimeout(30);
}

void loop() {
  if(!client.connected()){
    reconnect();
  }

  client.loop();

  StaticJsonDocument<256> doc;
  doc["rssi"] = WiFi.RSSI();
// ------- BUTTONS -------

  button1State = digitalRead(button1Pin);
  doc["button_1"] = button1State;

  int redLedStatus = 0;
  int blueLedStatus = 0;

  if(button1State == LOW){
    digitalWrite(redLed, HIGH);
    redLedStatus = 1;
    
  }else{
    
    digitalWrite(redLed, LOW);
  }
  doc["Led_vermelho"] = redLedStatus;

  button2State = digitalRead(button2Pin);
  doc["button_2"] = button2State;
  
  if(button2State == LOW){
    digitalWrite(blueLed, HIGH);
    blueLedStatus = 1;
  }else{
    
    digitalWrite(blueLed, LOW);
  }
  doc["Led_azul"] = blueLedStatus;

// ------- DHT11 -------
  Serial.println("\n");
  delay(2000);

  Serial.println("Leitura do sensor DHT11: ");

  float umidade = dht.readHumidity();
  doc["humidity"] = umidade;

  float temperatura = dht.readTemperature();
  doc["temp_DHT11"] = temperatura;

  if(isnan(umidade) || isnan(temperatura))
  {
    Serial.println("Falha ao ler o DHT11");
    return;
  }

  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println("%");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");
  Serial.println();

// ------- POTENTIOMETER -------

  int potValue = analogRead(potPin);
  int transitionSpeed = map(potValue, 0, 4095, 5, 100);
  doc["potentiometer"] = transitionSpeed;

  int RGBSStatus = 0;
// ------- LED RGB -------
  for(int i = 0;  i < 256; i++) {
    RGBSStatus = setColor(255 - i, i, 0);
    delay(transitionSpeed);
    checkPotentiometer();
  }

  for(int i = 0;  i < 256; i++) {
    RGBSStatus = RGBSStatus + setColor(0, 255 - i, i);
    delay(transitionSpeed);
    checkPotentiometer();
  }

  for(int i = 0;  i < 256; i++) {
    RGBSStatus = RGBSStatus + setColor(0, 255 - i, i);
    delay(transitionSpeed);
    checkPotentiometer();
  }
  doc["RGB"] = RGBSStatus;

// ------- LM35 -------
  float tempC;
  float temperaturaLM;

  tempC = (analogRead(tempPin) * 3.3) / 4095.0;
  delay(10);
  temperaturaLM = tempC * 100.0;
  doc["temp_LM35"] = temperaturaLM;
  Serial.print("Temperatura LM35 - ");
  Serial.print(temperaturaLM, 1);
  Serial.println(" °C");
  delay(1000);

// ------- LDR e BUZZER-------
  float ldrValue = analogRead(LDRPin);
  doc["Luminosidade"] = ldrValue;

  float voltage = ldrValue * (3.3 / 4095.0);

  Serial.print("Valor do brilho da luz: ");
  Serial.print(ldrValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.println("V");

  delay(1000);

  if (ldrValue < 1500) { 
    Serial.println("Escuroo...");
    melodia(mordorNotas, mordorDuracao, sizeof(mordorNotas) / sizeof(int));
    doc["musica"] = "mordor";
    
  } else {
    Serial.println("Claroo!!!");
    melodia(shireNotas, shireDuracao, sizeof(shireNotas) / sizeof(int));
    doc["musica"] = "shire";
  }
  delay(5000);

// -------IR RECEIVER-------
  if(IrReceiver.decode())
  {
    Serial.print("Protocolo: ");
    Serial.print(getProtocolString(IrReceiver.decodedIRData.protocol));
    doc["protocolo"] = getProtocolString(IrReceiver.decodedIRData.protocol);
    Serial.print(", Valor: ");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    int comando = IrReceiver.decodedIRData.command;
    Serial.print("Bits: ");
    Serial.println(IrReceiver.decodedIRData.numberOfBits);
    doc["comando"] = comando;

    IrReceiver.resume();
  }

  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer);
  client.publish(temp1Topic, jsonBuffer);

  if (client.state()) {
    Serial.print("Publish failed, state=");
    
    Serial.println("Publish failed!");
  }else {
    Serial.println("-----------------------------------------------------"); 
    Serial.println(client.state()); 
    Serial.println("-----------------------------------------------------"); 
  }

  delay(100);
}
