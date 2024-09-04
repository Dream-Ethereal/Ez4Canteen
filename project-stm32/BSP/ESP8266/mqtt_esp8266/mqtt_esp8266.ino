#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "PubSubClient.h"
#include <Crypto.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
// Update these with values suitable for your network.




using experimental::crypto::SHA256;

// 实例化一个对象 wifiMulti
ESP8266WiFiMulti wifiMulti;

WiFiClient espClient;

SoftwareSerial MySerial(9, 10);

PubSubClient client(espClient);

void connetMqtt();
String signHmacSha256(String deviceId, String productKey, String deviceName, String deviceSecret, uint64_t timestamp);
void callback(char *topic, byte *payload, unsigned int length);

const String productKey = "k1n5mT2r22v";                         //替换
const String deviceName = "Ez4Canteen-esp8266";                  //替换
const String deviceSecret = "930c44a939484df8d2711ec7af5b6edb";  //替换
const String subTopic = "/" + productKey + "/" + deviceName + "/user/get";
const String pubTopic = "/" + productKey + "/" + deviceName + "/user/update";
const String regionId = "cn-shanghai";  //替换自己的区域id
const String serverUrl = productKey + ".iot-as-mqtt." + regionId + ".aliyuncs.com";
const int serverPort = 1883;

const char wifiName[] = "Ez4Canteen";      //替换
const char wifiPassword[] = "Ez4Canteen";  //替换

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  MySerial.begin(115200);
  wifiMulti.addAP(wifiName, wifiPassword);
  Serial.println("");
  Serial.println("start connecting wifi...");

  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("============connect wifi success============");
  Serial.print("WiFi:");
  Serial.println(WiFi.SSID());
  Serial.print("localIP:");
  Serial.println(WiFi.localIP());

  connetMqtt();
}

void connetMqtt() {
  Serial.println("start connect mqtt ....");
  client.setKeepAlive(60);  //注意：PubSubClient库的默认keepalive是15s,而官方要求(30~1200s)最小30s，否则会拒绝连接
  client.setServer(serverUrl.c_str(), serverPort);

  String deviceId = String(ESP.getChipId());  //设备芯片唯一序列号
  uint64_t timestamp = micros64();

  String clientId = deviceId + "|securemode=3,signmethod=hmacsha256,timestamp=" + timestamp + "|";
  String password = signHmacSha256(deviceId, productKey, deviceName, deviceSecret, timestamp);
  String username = deviceName + "&" + productKey;
  Serial.print("clientId:");
  Serial.println(clientId);
  Serial.print("username:");
  Serial.println(username);
  Serial.print("password:");
  Serial.println(password);

  client.connect(clientId.c_str(), username.c_str(), password.c_str());

  while (!client.connected()) {
    /* code */
    delay(2000);
    client.connect(clientId.c_str(), username.c_str(), password.c_str());
    Serial.println("try connect mqtt...");
  }
  Serial.println("ok, mqtt connected!");
  client.subscribe(subTopic.c_str());
  client.setCallback(callback);
}

String signHmacSha256(String deviceId, String productKey, String deviceName, String deviceSecret, uint64_t timestamp) {
  const char *key = deviceSecret.c_str();
  String data = "clientId" + deviceId + "deviceName" + deviceName + "productKey" + productKey + "timestamp" + timestamp;
  Serial.print("sha256:");
  Serial.println(data);
  return SHA256::hmac(data, key, strlen(key), SHA256::NATURAL_LENGTH);
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  payload[length] = '\0';
  String message = String((char *)payload);
  Serial.println(message);
  MySerial.println(message);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (client.connected()) {
    client.loop();  //心跳以及消息回调等
  }
}
