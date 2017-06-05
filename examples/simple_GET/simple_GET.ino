/* RestClient simple GET request
 *
 * by Thang Phan
 */

#include <Ethernet.h>
#include <SPI.h>
#include <PlugPlayREST.h>

#define USER_KEY  "........"
#define BOARD_ID  "........"

// Init variables
String response;
String deviceName;
float data0, data1, data2;

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
  int statusCode = client.getPlugPlay("inTopic", &response);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);

  // Print device name  
  deviceName = client.getName(response.c_str());
  Serial.print("Device name: ");
  Serial.println(deviceName);

  // Print data values 
  data0 = client.getData(response.c_str(), "data0");
  Serial.print("data0: ");
  Serial.println(data0);

  data1 = client.getData(response.c_str(), "data1");
  Serial.print("data1: ");
  Serial.println(data1);

  data2 = client.getData(response.c_str(), "data2");
  Serial.print("data2: ");
  Serial.println(data2);

  delay(1000);
}
