#include "AIS_NB_BC95.h"

String apnName = "palmfuture.nb";

String serverIP = "167.99.77.10"; // Your Server IP
String serverPort = "7781"; // Your Server Port

AIS_NB_BC95 AISnb;

String status_LED = "off";
long start = 0;

void setup()
{
  // set debug enable
  AISnb.debug = true;
  // initial serial
  Serial.begin(9600);
  // initial nb-iot
  AISnb.setupDevice(serverPort);
  String ip1 = AISnb.getDeviceIP();
  delay(1000);
  pingRESP pingR = AISnb.pingIP(serverIP);
  // insert ip address to server
  UDPSend udp = AISnb.sendUDPmsgStr(serverIP, serverPort, "INSERT");
  // initial LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  // request status
  if (millis() - start > 5000) {
    start = millis();
    UDPSend udp = AISnb.sendUDPmsgStr(serverIP, serverPort, "REQUEST");
  }
  // receive data from server
  UDPReceive resp = AISnb.waitResponse();
  if (String(resp.data) != "") {
    if (AISnb.toString(resp.data) == "on") {
      status_LED = "on";
    } else {
      status_LED = "off";
    }
  }
  // update LED
  if (status_LED == "on") {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}



