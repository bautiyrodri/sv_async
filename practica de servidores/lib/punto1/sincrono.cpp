#include <WiFi.h>
#include <WebServer.h>
const char* ssid = "CESJT";
const char* password = "itisjtsmg";
WebServer server(80);
  String texto;

const char VENTILADOR[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title></title>
</head>

<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>webos</title>
  <style>
    body {text-align: center;display: flex;flex-direction: column; align-items: center; background-color: #ecf0f1}
     h1 { font-family: arial black; color: #2c3e50 }
    .btn {text-align: center; padding: 60px ; width: 180px; font-size: 20px; text-decoration: none;border: 1px solid black; border-radius: 15px; color: white; margin: 10px; display: block }
    .one { background-color: #2980b9; }
    .two { background-color: #27ae60; }
    .three { background-color: #f39c12; }
    .off { background-color: #c0392b; }
  </style>
</head>
<body>
    <h1>CONTROL DE VENTILADOR</h1>
    
    <a href="/animacion1" class="btn one">LOW</a>
    <a href="/animacion2" class="btn two">MEDIUM</a>
    <a href="/animacion3" class="btn three">HIGH</a>
    <a href="/off" class="btn off">OFF</a>
    
    <span>VELOCIDAD ACTUAL: <b>__TXT_MODO__</b></span>
</body>
</html>

</html>

)rawliteral";


void setup() {
  Serial.begin(115200);
Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 int timeout = 20; 
  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    delay(500);
    Serial.print(".");
    timeout--;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFallo la conexion. Reiniciando...");
    delay(1000);
    ESP.restart();
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("Dirección IP: http://");
  Serial.println(WiFi.localIP());


   server.on("/",  []() {
    String pagina = VENTILADOR; 
    pagina.replace("__TXT_MODO__", texto);
    
    server.send(200, "text/html", pagina);
  });

  server.on("/animacion1", []() {
    texto= "LOW";
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "");
  });

    server.on("/animacion2", []() {
    texto= "MEDIUM";
        server.sendHeader("Location", "/");
    server.send(302, "text/plain", "");
  });

    server.on("/animacion3", []() {
    texto= "HIGH";
       server.sendHeader("Location", "/");
    server.send(302, "text/plain", "");
  });

    server.on("/off", []() {
    texto= "APAGADO";
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "");
  });
  
  // Iniciar servidor
  server.begin();
}

void loop() {
 server.handleClient();

}
