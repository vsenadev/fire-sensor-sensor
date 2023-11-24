#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <TimeLib.h>

const char *ssid = "Vinicius.2G";
const char *password = "Baldarache";
const char *postUrl = "https://fire-sensor-api.onrender.com/post";

void setup() {
  Serial.begin(115200);

  // Inicialize a biblioteca Time
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");

  // Conecte-se à rede Wi-Fi
  WiFi.begin(ssid, password);
  int attempts = 0;
  
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Conectado ao WiFi");
  } else {
    Serial.println("Falha ao conectar ao WiFi. Verifique suas credenciais.");
  }

  pinMode(D2, INPUT);  // Assuma que o pino D2 está conectado ao seu sensor
}

void loop() {
  int sensorValue = digitalRead(D2);

  if (sensorValue == 0) {
    Serial.println(sensorValue);
    Serial.println("Enviando dado");
    String currentDate = getCurrentDate();
    sendPostRequest(sensorValue, currentDate);
    delay(10000);  // Aguarde 10 segundos antes de fazer a próxima verificação
  } else {
    Serial.println(sensorValue);
    // Aguarde um curto período de tempo para evitar verificações muito frequentes
    delay(1000);
  }
}

void sendPostRequest(int value, String currentDate) {
  WiFiClient client;
  HTTPClient http;

  String postData = "{\"dado\": " + String(value) + ", \"data\": \"" + currentDate + "\"}";

  Serial.println("Enviando POST request...");
  Serial.println(postData);

  http.begin(client, postUrl);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    Serial.print("Resposta do servidor: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Erro na requisição. Código de erro: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

String getCurrentDate() {
  time_t now = time(nullptr);
  struct tm *timeinfo;
  timeinfo = localtime(&now);

  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
  return String(buffer);
}
