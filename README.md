# RestClient for Arduino

HTTP Request library for Arduino.

This library is derived almost entirely from the great work done here: https://github.com/csquared/arduino-restclient

## Examples

The library comes with a number of example sketches. See File > Examples > PlugPlayREST
within the Arduino application.

## Limitations

## Compatible Hardware

The library uses the Arduino Ethernet Client api for interacting with the
underlying network hardware. This means it Just Works with a growing number of
boards and shields, including:

 - Arduino Ethernet
 - Arduino Ethernet Shield
 - Arduino YUN – use the included `YunClient` in place of `EthernetClient`, and
   be sure to do a `Bridge.begin()` first
 - Arduino WiFi Shield
 - Sparkfun WiFly Shield – [library](https://github.com/dpslwk/WiFly)
 - TI CC3000 WiFi - [library](https://github.com/sparkfun/SFE_CC3000_Library)
 - Intel Galileo/Edison
 - ESP8266

## Install

Clone (or download and unzip) the repository to `~/Documents/Arduino/libraries`
where `~/Documents/Arduino` is your sketchbook directory.

    > cd ~/Documents/Arduino
    > mkdir libraries
    > cd libraries
    > git clone https://github.com/plugplayco/plugplay-arduino-rest.git PlugPlayREST

## Usage

### Include

You need to have the `Ethernet` library already included.

```c++
#include <Ethernet.h>
#include <SPI.h>
#include "PlugPlayREST.h"
```

### PlugPlayREST(host/ip, [port])

Constructor to create an PlugPlayREST object to make requests against.

Use domain name and default to port 80:
```c++
PlugPlayREST client("plugplay.co");
```

Use a local IP and an explicit port:
```c++
PlugPlayREST client("192.168.1.50",5000);
```
### setAuth( const char* userKey, const char* boardId)

Set authentication to connect to PlugPlay

Arguments: 
- *userKey* - user Key of your user account.
- *boardId* - board Id of board you want to GET/PUT to.

### dhcp()

Sets up `EthernetClient` with a mac address of `DEADBEEFFEED`. Returns `true` or `false` to indicate if setting up DHCP
was successful or not

```c++
  client.dhcp()
```

Note: you can have multiple PlugPlayREST objects but only need to call
this once.

Note: if you have multiple Arduinos on the same network, you'll need
to give each one a different mac address.

### begin(byte mac[])

It just wraps the `EthernetClient` call to `begin` and DHCPs.
Use this if you need to explicitly set the mac address.

```c++
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  if (client.begin(mac) == 0) {
     Serial.println("Failed to configure Ethernet using DHCP");
  }
```

### Manual Ethernet Setup

You can skip the above methods and just configure the EthernetClient yourself:

```c++
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  //the IP address for the shield:
  byte ip[] = { 192, 168, 2, 11 };
  Ethernet.begin(mac,ip);
```

```c++
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  Ethernet.begin(mac);
```

This is especially useful for debugging network connection issues.

### char* createMsg(String dvName, float data0)
### char* createMsg(String dvName, float data0, float data1)
### char* createMsg(String dvName, float data0, float data1, float data2)

Create a message to send a PUT request

Arguments: 
- *dvName* - device name
- *data0* - first data
- *data1* - second data
- *data2* - third data

## RESTful methods

All methods return an HTTP status code or 0 if there was an error.

### int getPlugPlay(const char* topic)
### int getPlugPlay(const char* topic, String* response)

Start making requests!

```c++
int statusCode = client.getPlugPlay("inTopic");
```

Pass in a string *by reference* for the response:
```c++
String response = "";
int statusCode = client.getPlugPlay("inTopic", &response);
```

### int putPlugPlay(const char* topic, const char* body)
### int putPlugPlay(const char* topic, const char* body, String* response)

```c++
int statusCode = 0;
char* msg = client.createMsg("arduino", 0, 1, 2);
statusCode = client.putPlugPlay("outTopic", msg);
String response = "";
statusCode = client.putPlugPlay("outTopic", msg, &response);
```

### String getName(const char* payload)

Get device name from a received response

```c++
String response = "";
int statusCode = client.getPlugPlay("inTopic", &response);
client.getName(response.c_str());
```

### float getData(const char* payload, const char* type)

Get data from a received response

```c++
String response = "";
int statusCode = client.getPlugPlay("inTopic", &response);
// Get the first data
client.getData(response.c_str(),"data0");
// Get the second data
client.getData(response.c_str(),"data1");
// Get the third data
client.getData(response.c_str(),"data2");
```

### Other functions

You can refer here: https://github.com/csquared/arduino-restclient

## Debug Mode

If you're having trouble, you can always open `RestClient.cpp` and throw at the top:

```c++
#define HTTP_DEBUG
```

Everything happening in the client will get printed to the Serial port.

## License

This code is released under the MIT License.
