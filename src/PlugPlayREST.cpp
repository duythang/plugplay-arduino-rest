#include "PlugPlayREST.h"

PlugPlayREST& PlugPlayREST::setAuth( const char* userKey, const char* boardId){
    this->_userKey = userKey;
    this->_boardId = boardId;
    return *this;
}

int PlugPlayREST::getPlugPlay(const char* topic){
	_authGetTopic = "/api/rest/" + String(_userKey) + "&" + String(_boardId) + "&" + String(topic);
	return request("GET", _authGetTopic.c_str(), NULL, NULL);
}

int PlugPlayREST::getPlugPlay(const char* topic, String* response){
	_authGetTopic = "/api/rest/" + String(_userKey) + "&" + String(_boardId) + "&" + String(topic);
	return request("GET", _authGetTopic.c_str(), NULL, response);
}

int PlugPlayREST::putPlugPlay(const char* topic, const char* body){
	_authPutTopic = "/api/rest/" + String(_userKey) + "&" + String(_boardId) + "&" + String(topic);
	return request("PUT", _authPutTopic.c_str(), body, NULL);
}

int PlugPlayREST::putPlugPlay(const char* topic, const char* body, String* response){
	_authPutTopic = "/api/rest/" + String(_userKey) + "&" + String(_boardId) + "&" + String(topic);
	return request("PUT", _authPutTopic.c_str(), body, response);
}

char* PlugPlayREST::createMsg(String dvName, float data0){    
    return createMsg(dvName, data0, 0, 0);
}

char* PlugPlayREST::createMsg(String dvName, float data0, float data1){    
    return createMsg(dvName, data0, data1, 0);
}

char* PlugPlayREST::createMsg(String dvName, float data0, float data1, float data2){    
    StaticJsonBuffer<MQTT_MAX_PAYLOAD_SIZE> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject(); 
    root["device"] = dvName;
    root["data0"] = data0;
    root["data1"] = data1;
    root["data2"] = data2;
    root.printTo(payload, MQTT_MAX_PAYLOAD_SIZE);
    return payload;
}

String PlugPlayREST::getName(const char* payload){
    StaticJsonBuffer<MQTT_MAX_PAYLOAD_SIZE> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(payload);
    if (!root.success()) {
        Serial.println("parseMsg() failed");
        return "";
    }
    return root["device"];
} 

float PlugPlayREST::getData(const char* payload, const char* type){
    StaticJsonBuffer<MQTT_MAX_PAYLOAD_SIZE> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(payload);
    if (!root.success()) {
        Serial.println("parseMsg() failed");
        return 0;
    }    
    return root[type];
}