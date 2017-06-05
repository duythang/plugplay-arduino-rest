/* RestClient simple PUT request
 *
 * by Thang Phan
 */

#include <Ethernet.h>
#include <SPI.h>
#include "PlugPlayREST.h"

#define USER_KEY  "........"
#define BOARD_ID  "........"

// Init variables
String response;
char* msg;

PlugPlayREST client("plugplay.co");

//Setup
void setup() {
  Serial.begin(9600);
  // Connect via DHCP
  Serial.println("connect to network");
  client.setAuth(USER_KEY, BOARD_ID);
  client.dhcp();
/*
  // Can still fall back to manual config:
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  //the IP address for the shield:
  byte ip[] = { 192, 168, 2, 11 };
  Ethernet.begin(mac,ip);
*/
  Serial.println("Setup!");
}

void loop(){
  // Create a message
  msg = client.createMsg("arduino", 0, 1, 2);
  // Send PUT request with message to PlugPlay
  int statusCode = client.putPlugPlay("outTopic", msg, &response);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);
  delay(1000);
}
