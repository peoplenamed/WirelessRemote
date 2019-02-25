/*********
  Peter Black

  Inspired by Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "BlackNet";
const char* password = "NadersRaiders2020";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
//String header;

// Auxiliar variables to store the current output state
String OnBoardLEDState = "off";

// Assign output variables to GPIO pins
const int OnBoardLED = 2;
const int IRLED = 2;

void setup() {
  Serial.begin(115200);
  
  setupLEDPins();
  startWiFiServer();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    handleClient(client);
    disconnectClient(client);
  }
}

void startWiFiServer(){
  Serial.println("startWiFiServer...");
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin(); 
}

void setupLEDPins() {
  // Initialize the output variables as outputs
  Serial.println("Setting up LED Pins...");

  // Setup on-board LED for testing.
  pinMode(OnBoardLED, OUTPUT);
  digitalWrite(OnBoardLED, LOW);

  // Setup IR LED    
  pinMode(IRLED, OUTPUT);
  digitalWrite(IRLED, LOW);
}
