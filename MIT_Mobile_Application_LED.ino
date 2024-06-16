#include <WiFi.h>
const char WiFiPassword[] = "1234567890";
const char AP_NameChar[] = "embedclub" ;
WiFiServer server(80);
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><title>LED Control</title></head><body><div id='main'><h2>LED Control</h2>";
String html_2 = "<form id='F1' action='LEDON'><input class='button' type='submit' value='LED ON' ></form><br>";
String html_3 = "<form id='F2' action='LEDOFF'><input class='button' type='submit' value='LED OFF' ></form><br>";
String html_4 = "</div></body></html>";
 String request = "";
int LED_Pin = 2; // Use GPIO2 for the LED on ESP32
void setup() {
                pinMode(LED_Pin, OUTPUT); 
                digitalWrite(LED_Pin, HIGH); // Turn off LED initially (assuming active low)
                boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
                server.begin();
}
void loop() {
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)  {  return;  }

    // Read the first line of the request
    request = client.readStringUntil('\r');

    if (request.indexOf("LEDON") > 0)  { 
        digitalWrite(LED_Pin, LOW);  // Turn the LED on (assuming active low)
    } 
    else if (request.indexOf("LEDOFF") > 0) { 
        digitalWrite(LED_Pin, HIGH);  // Turn the LED off
    }
    client.flush();
    client.print(header);
    client.print(html_1);
    client.print(html_2);
    client.print(html_3);
    client.print(html_4);
    delay(5);
    // The client will actually be disconnected when the function returns and 'client' object is destroyed
}
