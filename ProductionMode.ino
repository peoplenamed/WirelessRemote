#include <IRremote.h>

IRsend irsend;

unsigned int toshibaPowerOffRaw[] = {9024, 4512, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 1692, 564, 564, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 564, 564, 1692, 564, 564, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 564, 564, 1692, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 1692, 564, 39756};
unsigned int toshibaPowerOnRaw[] = {9024, 4512, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 1692, 564, 564, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 564, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 1692, 564, 39756};
unsigned int toshibaChannelUp[] = {};
unsigned int toshibaVolumeUp[] =   {9024, 4512, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 1692, 564, 564, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 564, 564, 1692, 564, 564, 564, 1692, 564, 564, 564, 1692, 564, 1692, 564, 564, 564, 564, 564, 564, 564, 1692, 564, 564, 564, 1692, 564, 564, 564, 564, 564, 1692, 564, 1692, 564, 1692, 564, 39756};
unsigned int toshibaVolumeDown[] = {9024, 4512, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 564, 1692, 564, 564, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 564, 564, 1692, 564, 564, 564, 1692, 564, 1692, 564, 1692, 564, 1692, 564, 564, 564, 564, 564, 564, 564, 1692, 564, 564, 564, 564, 564, 564, 564, 564, 564, 1692, 564, 1692, 564, 1692, 564, 39756};

void productionView(WiFiClient client, String action){
  triggerAction(client, action);
  loadHTML(client);
}

void loadHTML(WiFiClient client) {
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #555555;}</style></head>");
  
  // Web Page Heading
  client.println("<body>");
  client.println("<p><a href=\"/remote/power\"><button class=\"button\">POWER</button></a></p>");
  client.println("<p><a href=\"/remote/volume/up\"><button class=\"button button2\">VOL +</button></a></p>");
  client.println("<p><a href=\"/remote/volume/down\"><button class=\"button button2\">VOL -</button></a></p>");
  client.println("</body></html>");
}

void triggerAction(WiFiClient client, String action){
  Serial.print("ACTION: ");
  Serial.println(action);
  if (action == "power") {
    Serial.println("Power.");
    blastIR(toshibaPowerOffRaw, 68);
    blastIR(toshibaPowerOnRaw, 68);
  } else if (action == "volume up") {
    Serial.println("Volume up.");
    blastIR(toshibaVolumeUp, 68);
  } else if (action == "volume down") {
    Serial.println("Volume down.");
    blastIR(toshibaVolumeDown, 68);
  } else if (action == "channel up") {
    Serial.println("Channel up.");
    //blastIR(toshibaChannelUp);
  }  
}

void blastIR(unsigned int IRcode[], int arraySize) {
  int khz = 38; // 38kHz carrier frequency for the NEC protocol
  //int arraySize = 68;
  //int arraySize = sizeof(IRcode) / sizeof(IRcode[0]);
  int blastCount = 3;
  Serial.print("Array size: ");
  Serial.println(arraySize);
  for (int j = 0; j < blastCount; j++) {
    // for (int i = 0; i < arraySize; i++) {
      Serial.print("IRcode: ");
      Serial.println(IRcode[0]);
      irsend.sendRaw(IRcode, arraySize, khz);
      delay(200);  
    // }
  }
}

// http://irdb.tk/decode/
// http://irdb.tk/convert/
//
//POWER ON
//0000 006b 0022 0002 015b 00b1 0014 0018 0014 001a 0012 0019 0013 0018 0016 0017 0014 0018 0013 0044 0013 0018 0015 0042 0014 0043 0014 0043 0014 0043 0013 0043 0015 0042 0014 0018 0014 0043 0014 001a 0012 0043 0016 0042 0013 0043 0015 0042 0014 0043 0014 0043 0016 0016 0014 0042 0014 0019 0015 0017 0014 0018 0014 0018 0014 001a 0012 0018 0014 0043 0015 061a 015b 0059 0014 0e93
//+9024 -4512 +564 -564 +564 -564 +564 -564 +564 -564 +564 -564 +564 -564 +564 -1692 +564 -564 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -564 +564 -1692 +564 -564 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -564 +564 -1692 +564 -564 +564 -564 +564 -564 +564 -564 +564 -564 +564 -564 +564 -1692 +564 -39756
//
//POWER OFF
//0000 006b 0022 0002 015b 00b1 0016 0016 0015 0019 0013 0018 0014 0017 0017 0016 0015 0017 0014 0043 0014 0017 0017 0040 0016 0040 0014 0044 0014 0044 0012 0044 0015 0043 0014 0018 0014 0043 0014 0043 0013 0043 0014 0043 0016 0041 0014 0043 0014 0043 0012 0044 0014 001a 0012 0018 0014 0019 0016 0016 0014 0018 0014 0018 0014 001a 0012 0018 0014 0043 0016 0619 015b 0059 0014 0e93
//
//COMPONENT
//0000 0067 0022 0002 0156 00ab 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 003f 0016 0016 0016 003f 0016 003f 0016 003f 0016 003f 0016 003f 0016 003f 0016 0016 0016 003f 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 003f 0016 0016 0016 0016 0016 003f 0016 003f 0016 003f 0016 003f 0016 003f 0016 0016 0016 003f 0016 003f 0016 0593 0160 0058 0016 0dc0
//
//HDMI 1
//0000 0067 0022 0002 0156 00ab 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 003f 0016 0016 0016 003f 0016 003f 0016 003f 0016 003f 0016 003f 0016 003f 0016 0016 0016 003f 0016 003f 0016 0016 0016 0016 0016 0016 0016 0016 0016 003f 0016 0016 0016 0016 0016 0016 0016 003f 0016 003f 0016 003f 0016 003f 0016 0016 0016 003f 0016 003f 0016 0593 0160 0058 0016 0dc0
//
//HDMI 2
//0000 0067 0022 0002 0156 00ab 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 003f 0016 0016 0016 003f 0016 003f 0016 003f 0016 003f 0016 003f 0016 003f 0016 0016 0016 003f 0016 0016 0016 003f 0016 0016 0016 0016 0016 0016 0016 003f 0016 0016 0016 0016 0016 003f 0016 0016 0016 003f 0016 003f 0016 003f 0016 0016 0016 003f 0016 003f 0016 0593 0160 0058 0016 0dc0
//
//PC
//0000 0067 0022 0002 0156 00ab 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 003f 0016 0016 0016 003f 0016 003f 0016 003f 0016 003f 0016 003f 0016 003f 0016 0016 0016 003f 0016 003f 0016 003f 0016 0016 0016 0016 0016 0016 0016 003f 0016 0016 0016 0016 0016 0016 0016 0016 0016 003f 0016 003f 0016 003f 0016 0016 0016 003f 0016 003f 0016 0593 0160 0058 0016 0dc0
//
//
//VOLUME DOWN
//0000 006b 0022 0002 015b 00b1 0014 0018 0016 0016 0015 0017 0014 0018 0014 001b 0011 0019 0013 0044 0013 001a 0012 0043 0014 0043 0014 0043 0014 0043 0015 0041 0014 0043 0014 0018 0015 0042 0015 0017 0015 0042 0015 0042 0016 0040 0015 0042 0014 0018 0015 0019 0013 0017 0014 0043 0015 0017 0014 0019 0014 0017 0015 0017 0016 0041 0015 0042 0015 0042 0014 061b 015c 0058 0017 0e90
//+9024 -4512 +564 -564 +564 -564 +564 -564 +564 -564 +564 -564 +564 -564 +564 -1692 +564 -564 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -564 +564 -1692 +564 -564 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -564 +564 -564 +564 -564 +564 -1692 +564 -564 +564 -564 +564 -564 +564 -564 +564 -1692 +564 -1692 +564 -1692 +564 -39756
//
//VOLUME UP
//0000 006b 0022 0002 015d 00af 0016 0016 0016 0018 0014 0017 0015 0016 0018 0015 0015 0017 0014 0043 0015 0016 0018 003f 0016 0041 0016 0041 0016 0041 0014 0042 0017 0040 0016 0016 0016 0041 0016 0017 0014 0042 0016 0016 0016 0041 0014 0042 0016 0016 0016 0018 0014 0017 0014 0042 0016 0018 0013 0042 0016 0016 0016 0019 0012 0042 0017 0041 0016 0041 0016 0619 015d 0057 0016 0e91
//+9024 -4512 +564 -564 +564 -564 +564 -564 +564 -564 +564 -564 +564 -564 +564 -1692 +564 -564 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -564 +564 -1692 +564 -564 +564 -1692 +564 -564 +564 -1692 +564 -1692 +564 -564 +564 -564 +564 -564 +564 -1692 +564 -564 +564 -1692 +564 -564 +564 -564 +564 -1692 +564 -1692 +564 -1692 +564 -39756
//
//MUTE
//0000 006b 0022 0002 015b 00b1 0015 0017 0014 0017 0015 0019 0013 0018 0014 0018 0017 0014 0015 0043 0014 0017 0017 0040 0014 0043 0015 0042 0015 0042 0014 0042 0016 0041 0016 0017 0014 0042 0015 0019 0013 0017 0016 0015 0018 0014 0015 0042 0015 0017 0016 0017 0014 0017 0015 0042 0015 0042 0015 0042 0014 0042 0016 0015 0015 0043 0016 0040 0015 0043 0015 061a 015b 0059 0015 0e92
//
//CHANNEL DOWN
//0000 006b 0022 0002 015d 00af 0016 0016 0016 0016 0016 0017 0014 0018 0015 0017 0017 0015 0014 0043 0014 0017 0017 0040 0016 0041 0016 0041 0016 0041 0015 0041 0018 003f 0016 0017 0015 0041 0016 0041 0017 003f 0016 0041 0016 0041 0016 0041 0017 0015 0016 0016 0016 0018 0014 0017 0015 0016 0018 0014 0017 0015 0016 0016 0016 0041 0017 0040 0016 0041 0016 0619 015d 0057 0016 0e91
//
//CHANNEL UP
//0000 006b 0022 0002 015c 00b0 0016 0016 0016 0016 0016 0017 0015 0017 0014 0018 0016 0016 0015 0042 0014 0017 0017 0040 0016 0041 0016 0041 0016 0041 0015 0041 0017 0040 0016 0017 0014 0042 0016 0041 0017 003f 0016 0017 0015 0041 0017 0040 0016 0016 0016 0016 0018 0014 0016 0016 0016 0016 0016 0041 0017 0015 0016 0016 0016 0041 0016 0041 0016 0041 0016 0619 015d 0057 0016 0e92
//+9024 -4512 +564 -564 +564 -564 +564 -564 +564 -564 +564 -564 +564 -564 +564 -1692 +564 -564 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -1692 +564 -564 +564 -1692 +564 -1692 +564 -1692 +564 -564 +564 -1692 +564 -1692 +564 -564 +564 -564 +564 -564 +564 -564 +564 -564 +564 -1692 +564 -564 +564 -564 +564 -1692 +564 -1692 +564 -1692 +564 -39756
//
//RECALL
//0000 006b 0022 0002 015d 00af 0016 0016 0016 0016 0016 0018 0014 0016 0016 0017 0016 0016 0016 0041 0014 0017 0017 0040 0016 0041 0016 0041 0016 0041 0014 0042 0017 0040 0016 0016 0016 0041 0016 0041 0017 003f 0016 0042 0018 0014 0017 0040 0016 0016 0016 0016 0017 0015 0016 0016 0016 0019 0012 0018 0015 0041 0016 0019 0012 0042 0016 0041 0016 0041 0017 0618 015c 0058 0015 0e92
//
//INPUT
//0000 006b 0022 0002 015b 00b1 0014 0018 0014 001b 0011 0019 0013 0018 0016 0017 0015 0017 0013 0044 0013 0018 0015 0042 0014 0043 0014 0043 0014 0043 0013 0043 0015 0042 0014 0018 0014 0043 0014 0043 0014 0042 0014 0043 0016 0041 0014 0018 0014 0018 0014 0018 0015 0017 0014 0018 0014 001a 0012 0019 0013 0019 0013 0043 0014 0043 0014 0043 0014 0043 0016 0619 015b 0059 0014 0e93
//
//MENU
//0000 006b 0022 0002 015d 00af 0016 0016 0016 0016 0016 0016 0015 0017 0016 0017 0015 0017 0014 0043 0015 0016 0016 0041 0018 003f 0016 0041 0016 0041 0015 0041 0016 0041 0016 0016 0016 0041 0017 0015 0016 0016 0016 0016 0016 0016 0016 0016 0016 0018 0014 0019 0012 0042 0016 0041 0016 0041 0017 0041 0014 0042 0016 0041 0016 0041 0016 0041 0015 0017 0016 0619 015c 0058 0016 0e91
//
//LEFT
//0000 006d 0000 0022 0158 00ac 0015 0016 0015 0016 0014 0017 0015 0016 0015 0016 0014 0017 0015 0042 0014 0017 0015 0042 0014 0042 0016 0040 0016 0041 0014 0042 0016 0040 0016 0015 0016 0040 0016 0041 0014 0042 0015 0016 0014 0017 0015 0016 0015 0016 0014 0017 0015 0042 0014 0017 0015 0016 0016 0040 0016 0041 0015 0041 0016 0040 0016 0041 0014 0017 0015 05f4
//
//RIGHT
//0000 006c 0022 0002 015a 00ae 0015 0017 0014 0017 0015 0017 0015 0017 0014 0017 0015 0017 0015 0042 0015 0017 0015 0042 0015 0042 0014 0042 0015 0042 0015 0042 0014 0043 0015 0017 0014 0043 0015 0017 0014 0043 0015 0017 0013 0018 0014 0018 0015 0017 0013 0018 0014 0043 0013 0044 0014 0018 0013 0044 0014 0042 0014 0043 0013 0044 0014 0043 0014 0018 0014 0604 015a 0058 0014 0e78
//
//UP
//0000 006b 0022 0002 015d 00af 0017 0015 0016 0016 0017 0015 0016 0016 0016 0017 0014 0018 0015 0042 0016 0015 0017 0040 0017 0040 0016 0041 0016 0041 0014 0042 0016 0041 0016 0016 0016 0041 0016 0016 0017 0040 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0041 0016 0041 0018 0014 0016 0041 0014 0042 0016 0041 0016 0041 0016 0041 0015 0017 0016 0619 015d 0057 0016 0e91
//
//DOWN
//0000 006b 0022 0002 015c 00b0 0016 0016 0016 0016 0016 0017 0014 0018 0014 0018 0016 0016 0014 0043 0015 0016 0018 003f 0016 0041 0016 0041 0016 0041 0014 0042 0017 0040 0016 0016 0016 0041 0016 0041 0017 003f 0016 0017 0015 0018 0014 0017 0016 0016 0017 0015 0016 0041 0014 0018 0017 0015 0016 0041 0015 0041 0016 0041 0016 0041 0016 0041 0015 0017 0016 0619 015d 0057 0016 0e91
//
//OK
//0000 006b 0022 0002 015d 00af 0016 0016 0016 0018 0014 0017 0015 0016 0018 0015 0016 0016 0015 0042 0014 0016 0018 003f 0016 0041 0016 0041 0016 0041 0015 0041 0017 0040 0016 0016 0016 0041 0016 0041 0017 0015 0016 0016 0016 0041 0014 0018 0016 0016 0017 0015 0016 0041 0015 0017 0016 0040 0016 0041 0016 0016 0016 0041 0018 003f 0016 0041 0014 0018 0016 0619 015d 0057 0016 0e91
//
//NUMBER_0
//0000 006b 0022 0002 015c 00b0 0016 0016 0016 0015 0016 0016 0015 0017 0015 0018 0014 0018 0014 0043 0015 0016 0016 0041 0017 0040 0015 0042 0015 0042 0014 0042 0015 0042 0016 0016 0015 0042 0016 0016 0016 0016 0016 0016 0016 0016 0015 0019 0013 0017 0015 0017 0015 001a 0012 0042 0015 0042 0015 0042 0016 0041 0014 0042 0015 0042 0015 0042 0015 0042 0016 0619 015b 0059 0015 0e92
//
//NUMBER_1
//0000 006b 0022 0002 015b 00b1 0014 0018 0014 0018 0014 0019 0013 0018 0016 0017 0014 0018 0013 0044 0013 0018 0016 0041 0014 0043 0014 0043 0014 0043 0013 0043 0015 0042 0014 0018 0014 0043 0014 0043 0015 0017 0014 0018 0015 0017 0014 0018 0014 001a 0012 0019 0013 0018 0016 0016 0015 0042 0014 0043 0014 0043 0013 0043 0014 0043 0015 0042 0014 0043 0014 061b 015b 0059 0014 0e94
//
//NUMBER_2
//0000 006b 0022 0002 015c 00b0 0016 0016 0016 0016 0016 0018 0014 0017 0014 0018 0016 0016 0015 0042 0015 0016 0017 0040 0016 0041 0016 0041 0016 0041 0015 0041 0017 0040 0016 0017 0015 0041 0016 0018 0014 0041 0016 0016 0017 0015 0016 0016 0016 0016 0016 0018 0014 0016 0016 0041 0016 0018 0014 0041 0016 0041 0015 0041 0016 0041 0017 0040 0016 0041 0016 0619 015c 0058 0016 0e91
//
//NUMBER_3
//0000 006b 0022 0002 015c 00b0 0016 0016 0016 0016 0016 0018 0014 0016 0016 0017 0017 0015 0016 0041 0015 0016 0018 003f 0016 0041 0016 0041 0016 0041 0015 0042 0017 0040 0016 0016 0016 0041 0016 0041 0017 003f 0016 0017 0015 0018 0014 0017 0016 0016 0018 0014 0016 0016 0016 0016 0016 0018 0014 0041 0016 0041 0015 0041 0016 0041 0017 0040 0016 0041 0016 0619 015d 0057 0016 0e91
//
//NUMBER_4
//0000 006b 0022 0002 015b 00b1 0014 0018 0015 0019 0013 0018 0014 0017 0017 0016 0015 0017 0014 0044 0015 0016 0017 0040 0015 0043 0015 0041 0016 0041 0014 0042 0017 0041 0015 0017 0016 0040 0015 0018 0014 0016 0015 0043 0016 0015 0016 0016 0016 0018 0012 0018 0014 0017 0017 0040 0015 0041 0015 0017 0016 0041 0014 0042 0016 0042 0014 0044 0014 0043 0014 061c 015b 0059 0015 0e92
//
//NUMBER_5
//0000 006b 0022 0002 015d 00af 0016 0016 0016 0016 0016 0018 0014 0017 0015 0017 0016 0016 0015 0042 0014 0017 0017 0040 0016 0041 0016 0041 0016 0041 0014 0042 0017 0040 0016 0016 0016 0041 0016 0041 0017 0015 0016 0041 0014 0019 0014 0017 0016 0016 0017 0015 0016 0016 0016 0018 0014 0041 0016 0016 0016 0041 0014 0042 0016 0041 0017 0040 0016 0041 0016 0619 015d 0057 0016 0e91
//
//NUMBER_6
//0000 006b 0022 0002 015b 00b1 0015 0016 0016 0016 0015 0018 0015 0016 0014 0018 0016 0016 0015 0042 0014 0017 0017 0040 0016 0041 0015 0042 0016 0041 0014 0041 0016 0042 0016 0016 0015 0041 0015 0019 0013 0043 0015 0042 0013 001b 0010 001b 0012 0018 0014 0018 0015 0017 0014 0043 0014 0018 0014 0018 0014 0043 0012 0044 0014 0043 0014 0043 0014 0044 0014 061b 015b 0059 0013 0e94
//
//NUMBER_7
//0000 006b 0022 0002 015c 00b0 0014 0018 0016 0016 0016 0016 0015 0017 0015 0018 0014 0018 0014 0043 0014 0017 0015 0042 0017 0040 0014 0043 0015 0042 0014 0042 0015 0042 0015 0017 0015 0042 0015 0042 0015 0041 0015 0042 0015 0017 0017 0015 0017 0015 0017 0016 0015 0017 0016 0016 0016 0016 0016 0016 0014 0043 0016 0040 0015 0042 0015 0042 0015 0042 0015 061a 015b 0059 0015 0e92
//
//NUMBER_8
//0000 006b 0022 0002 015b 00b1 0014 0018 0013 0019 0014 001a 0012 0019 0012 001a 0014 0018 0012 0045 0012 0019 0016 0041 0014 0043 0013 0044 0014 0043 0012 0044 0014 0043 0014 0018 0013 0044 0014 001a 0011 0019 0014 0018 0016 0041 0014 0018 0014 0018 0014 0019 0012 0019 0014 0043 0014 0043 0014 0043 0014 0018 0013 0043 0014 0043 0016 0041 0014 0043 0017 0618 015b 0059 0014 0e93
//
//NUMBER_9
//0000 006b 0022 0002 015b 00b1 0014 0018 0014 0018 0014 001a 0012 0019 0013 0019 0015 0017 0013 0044 0014 0017 0017 0040 0014 0043 0015 0042 0015 0042 0014 0042 0016 0041 0014 0019 0014 0042 0014 0043 0016 0016 0015 0017 0016 0041 0014 0018 0015 0017 0015 0017 0017 0015 0016 0016 0015 0042 0016 0041 0014 0018 0014 0042 0015 0042 0016 0041 0016 0041 0016 0619 015c 0058 0014 0e93
