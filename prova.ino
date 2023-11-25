#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Walid";
const char *password = "Waleedd2020";
const char *thingSpeakApiKey = "WAI7EN8FDWJE4T41";  // Substitua pelo seu API Key do ThingSpeak

ESP8266WebServer server(80);

#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float temperatura;
float umidade;
int sensorValue;

void setup() {
  Serial.begin(115200);
  delay(50);
  dht.begin();

  Serial.println("Conectando a Rede: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("Servidor HTTP inicializado");
}

void loop() {
  server.handleClient();
  int sensorValue = digitalRead(D2);

}

void handle_OnConnect() {
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" ºC");
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");

  // Check if sensor value is 0 (simulating fire condition)
  if (sensorValue == 0) {
    server.send(200, "text/html", EnvioHTMLAlert());
  } else {
    // Send data to ThingSpeak
    sendToThingSpeak(temperatura, umidade);

    server.send(200, "text/html", EnvioHTML(temperatura, umidade));
  }
}

void handle_NotFound() {
  server.send(404, "text/plain", "Não encontrado");
}

String EnvioHTML(float Temperaturastat, float Umidadestat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<meta http-equiv='refresh' content='2'>";
  ptr += "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
  ptr += "<title>Monitor de Temperatura e Umidade</title>\n";
  ptr += "<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #000000;}\n";
  ptr += "body{margin-top: 50px;}\n";
  ptr += "h1 {margin: 50px auto 30px;}\n";
  ptr += "h2 {margin: 40px auto 20px;}\n";
  ptr += "p {font-size: 24px;color: #000000;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Monitor de Temperatura e Umidade</h1>\n";
  ptr += "<h2>NODEMCU ESP8266 Web Server</h2>\n";
  ptr += "<p><b>Temperatura: </b>";
  ptr += (float)Temperaturastat;
  ptr += " Graus Celsius</p>";
  ptr += "<p><b>Umidade: </b>";
  ptr += (float)Umidadestat;
  ptr += " %</p>";
  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

String EnvioHTMLAlert() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<meta http-equiv='refresh' content='2'>";
  ptr += "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
  ptr += "<title>Alerta de Incêndio</title>\n";
  ptr += "<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #000000;}\n";
  ptr += "body{margin-top: 50px;}\n";
  ptr += "h1 {margin: 50px auto 30px;}\n";
  ptr += "h2 {margin: 40px auto 20px;}\n";
  ptr += "p {font-size: 24px;color: #FF0000;margin-bottom: 10px;}\n"; // Red color for alert
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Alerta de Incêndio!</h1>\n";
  ptr += "<p>A temperatura atingiu um nível crítico. Verifique a área imediatamente!</p>";
  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

void sendToThingSpeak(float temperature, float humidity) {
  WiFiClient client;

  String url = "http://api.thingspeak.com/update?api_key=" + String(thingSpeakApiKey) + "&field1=" + String(temperature) + "&field2=" + String(humidity);

  HTTPClient http;
  http.begin(client, url);

  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    Serial.println("Dados enviados para o ThingSpeak com sucesso!");
  } else {
    Serial.print("Falha ao enviar dados para o ThingSpeak. Código de resposta: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
