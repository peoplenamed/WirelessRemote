void developmentView(WiFiClient client, String LEDState) {
  OnBoardLEDState = LEDState;
  if(LEDState == "on") {
    digitalWrite(OnBoardLED, HIGH);
  } else {
    digitalWrite(OnBoardLED, LOW);
  }
  
  // Display the HTML web page
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  // CSS to style the on/off buttons 
  // Feel free to change the background-color and font-size attributes to fit your preferences
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #555555;}</style></head>");
  
  // Web Page Heading
  client.println("<body><h1>ESP32 Web Server</h1>");
  
  // Display current state, and ON/OFF buttons for GPIO 26  
  client.println("<p>GPIO 26 - State " + OnBoardLEDState + "</p>");
  // If the OnBoardLEDState is off, it displays the ON button       
  if (OnBoardLEDState=="off") {
    client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
  } else {
    client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
  } 

  client.println("</body></html>");
  
  // The HTTP response ends with another blank line
  client.println();
  // Break out of the while loop
}
