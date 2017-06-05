#ifndef PlugPlayREST_h
#define PlugPlayREST_h

#include <RestClient.h>
#include <ArduinoJson.h>

// MQTT_MAX_PAYLOAD_SIZE : Maximum payload size inside a message
#ifndef MQTT_MAX_PAYLOAD_SIZE
#define MQTT_MAX_PAYLOAD_SIZE 100
#endif

class PlugPlayREST: public RestClient {
    private:
        const char* _userKey; 
        const char* _boardId;
        String _authGetTopic, _authPutTopic;
        char payload[MQTT_MAX_PAYLOAD_SIZE];
    public:
        using RestClient::RestClient;
        PlugPlayREST& setAuth( const char* userKey, const char* boardId);
        int getPlugPlay(const char* topic);
    	int getPlugPlay(const char* topic, String* response);
        int putPlugPlay(const char* topic, const char* body);
		int putPlugPlay(const char* topic, const char* body, String* response);
        
        char* createMsg(String dvName, float data0);
        char* createMsg(String dvName, float data0, float data1);
        char* createMsg(String dvName, float data0, float data1, float data2);
        
        String   getName(const char* payload);
        float    getData(const char* payload, const char* type);
};

#endif