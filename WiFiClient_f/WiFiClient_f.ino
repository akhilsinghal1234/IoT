#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTTYPE  DHT11

const char* ssid     = "abc";
const char* password = "abababab";

const char* host = "akhilsinghal1234.000webhostapp.com";
int t   = 0;
int h = 0;

#define DHTPIN            2 
DHT dht(DHTPIN, DHTTYPE);

//////////////// ip-address //////////////
IPAddress ip(192,168,43,151);                                       
           IPAddress gateway(192,168,43,1);
       IPAddress subnet(255, 255, 255, 0);

//////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 WiFi.config( ip, gateway, subnet );
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
  ++value;
  t = dht.readTemperature();
  h = dht.readHumidity();
  
  String temp = String(t);
  String humidity = String(h);
  
  Serial.println("temperature = ");
  Serial.print(temp);
  Serial.println("Humidity = ");
  Serial.print(humidity);
  
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/insert.php/?temp=";
  url += temp;
  url += "&humidity=";
  url += humidity;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  client.print("Success");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    //Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  delay(10000);
}

/*
http://akhilsinghal1234.000webhostapp.com/
access this website to view the entered data in the database
 */

