void handleClient(WiFiClient client) {
    String header;
    Serial.println("New Client.");          // print a message out in the serial port
    while (client.connected()) {            // loop while the client's connected
        if (client.available()) {           // if there's bytes to read from the client,
            String currentLine = "";        // make a String to hold incoming data from the client
            char c = client.read();         // read a byte, then
            Serial.write(c);                // print it out the serial monitor
            header += c;
            if (c == '\n') {
              // if the byte is a newline character
              // if the current line is blank, you got two newline characters in a row.
              // that's the end of the client HTTP request, so send a response:
              if (currentLine.length() == 0) {
                returnOK(client);
                routes(header, client);
                break;
              } else {
                // if you got a newline, then clear currentLine
                currentLine = "";
              }
            } else if (c != '\r') {
              // if you got anything else but a carriage return character,
              // add it to the end of the currentLine
              currentLine += c;
            }
        }
    }
}

void disconnectClient(WiFiClient client) {
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
}

void returnOK(WiFiClient client) {
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
}

void routes(String header, WiFiClient client) {
  if (header.indexOf("GET /test/on") >= 0) {
    Serial.println("test on");    
    developmentView(client, "on");
  } else if (header.indexOf("GET /test/off") >= 0) {
    Serial.println("test off");    
    developmentView(client, "off");
  } else if (header.indexOf("GET /remote/power") >= 0) {
    productionView(client, "power");
  } else if (header.indexOf("GET /remote/channel/up") >= 0) {
    productionView(client, "channel up");
  } else if (header.indexOf("GET /remote/channel/down") >= 0) {
    productionView(client, "channel down");
  } else if (header.indexOf("GET /remote/volume/up") >= 0) {
    productionView(client, "volume up");
  } else if (header.indexOf("GET /remote/volume/down") >= 0) {
    productionView(client, "volume down");
  } else if (header.indexOf("GET /remote/volume/mute") >= 0) {
    productionView(client, "input");
  } else if (header.indexOf("GET /remote/down") >= 0) {
    productionView(client, "down");
  } else if (header.indexOf("GET /remote/up") >= 0) {
    productionView(client, "up");
  } else if (header.indexOf("GET /remote/left") >= 0) {
    productionView(client, "left");
  } else if (header.indexOf("GET /remote/right") >= 0) {
    productionView(client, "right");
  } else if (header.indexOf("GET /remote/ok") >= 0) {
    productionView(client, "ok");
  } else if (header.indexOf("GET /remote/menu") >= 0) {
    productionView(client, "menu");
  } else if (header.indexOf("GET /remote/input") >= 0) {
    productionView(client, "input");
  } else {
    productionView(client, "unknown");
  }
}
