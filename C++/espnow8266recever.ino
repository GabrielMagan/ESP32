//Programa: ESP-NOW com ESP8266 NodeMCU - Receptor
//Autor: Arduino e Cia

#include <ESP8266WiFi.h>
#include <espnow.h>

//Estrutura para envio dos dados. Deve ser a mesma tanto no emissor como no receptor.
typedef struct struct_message
{
  char a[32];
} struct_message;

//Definicoes led
#define pino_led D1

//Cria uma struct_message chamada myData
struct_message myData;
char buf[30];
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len)
{
  memcpy(&myData, incomingData, sizeof(myData));
 /* Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");*/
  //Serial.println(myData.a);
  String dado_recebido = myData.a;
 
  strcpy(buf,dado_recebido);
  Serial.println(buf);


  //Acende ou apaga o led de acordo com a String recebida
  if (dado_recebido == "L_Led")
  {
    Serial.println("Recebido Liga Led!");
    digitalWrite(pino_led, LOW);
  }

  if (dado_recebido == "D_Led")
  {
    Serial.println("Recebido Desliga Led!");
    digitalWrite(pino_led, HIGH);
  }
}

void setup()
{
  Serial.println("init");
  Serial.begin(115200);

  pinMode(pino_led, OUTPUT);
  digitalWrite(pino_led, HIGH);

  //Coloca o dispositivo no modo Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Inicializa o ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Erro ao inicializar o ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
  
}
