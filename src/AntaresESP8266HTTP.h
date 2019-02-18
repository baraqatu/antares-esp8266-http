#ifndef AntaresESP8266PHTTP_H
#define AntaresESP8266HTTP_H
#include <Arduino.h>
#include <time.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

// CA certificates
static const unsigned char caCert[] PROGMEM = {
  0x30, 0x82, 0x03, 0x75, 0x30, 0x82, 0x02, 0x5d, 0xa0, 0x03, 0x02, 0x01,
  0x02, 0x02, 0x0b, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x15, 0x4b, 0x5a,
  0xc3, 0x94, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d,
  0x01, 0x01, 0x05, 0x05, 0x00, 0x30, 0x57, 0x31, 0x0b, 0x30, 0x09, 0x06,
  0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x42, 0x45, 0x31, 0x19, 0x30, 0x17,
  0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x10, 0x47, 0x6c, 0x6f, 0x62, 0x61,
  0x6c, 0x53, 0x69, 0x67, 0x6e, 0x20, 0x6e, 0x76, 0x2d, 0x73, 0x61, 0x31,
  0x10, 0x30, 0x0e, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x07, 0x52, 0x6f,
  0x6f, 0x74, 0x20, 0x43, 0x41, 0x31, 0x1b, 0x30, 0x19, 0x06, 0x03, 0x55,
  0x04, 0x03, 0x13, 0x12, 0x47, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x53, 0x69,
  0x67, 0x6e, 0x20, 0x52, 0x6f, 0x6f, 0x74, 0x20, 0x43, 0x41, 0x30, 0x1e,
  0x17, 0x0d, 0x39, 0x38, 0x30, 0x39, 0x30, 0x31, 0x31, 0x32, 0x30, 0x30,
  0x30, 0x30, 0x5a, 0x17, 0x0d, 0x32, 0x38, 0x30, 0x31, 0x32, 0x38, 0x31,
  0x32, 0x30, 0x30, 0x30, 0x30, 0x5a, 0x30, 0x57, 0x31, 0x0b, 0x30, 0x09,
  0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x42, 0x45, 0x31, 0x19, 0x30,
  0x17, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x10, 0x47, 0x6c, 0x6f, 0x62,
  0x61, 0x6c, 0x53, 0x69, 0x67, 0x6e, 0x20, 0x6e, 0x76, 0x2d, 0x73, 0x61,
  0x31, 0x10, 0x30, 0x0e, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x07, 0x52,
  0x6f, 0x6f, 0x74, 0x20, 0x43, 0x41, 0x31, 0x1b, 0x30, 0x19, 0x06, 0x03,
  0x55, 0x04, 0x03, 0x13, 0x12, 0x47, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x53,
  0x69, 0x67, 0x6e, 0x20, 0x52, 0x6f, 0x6f, 0x74, 0x20, 0x43, 0x41, 0x30,
  0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7,
  0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00, 0x30,
  0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01, 0x00, 0xda, 0x0e, 0xe6, 0x99,
  0x8d, 0xce, 0xa3, 0xe3, 0x4f, 0x8a, 0x7e, 0xfb, 0xf1, 0x8b, 0x83, 0x25,
  0x6b, 0xea, 0x48, 0x1f, 0xf1, 0x2a, 0xb0, 0xb9, 0x95, 0x11, 0x04, 0xbd,
  0xf0, 0x63, 0xd1, 0xe2, 0x67, 0x66, 0xcf, 0x1c, 0xdd, 0xcf, 0x1b, 0x48,
  0x2b, 0xee, 0x8d, 0x89, 0x8e, 0x9a, 0xaf, 0x29, 0x80, 0x65, 0xab, 0xe9,
  0xc7, 0x2d, 0x12, 0xcb, 0xab, 0x1c, 0x4c, 0x70, 0x07, 0xa1, 0x3d, 0x0a,
  0x30, 0xcd, 0x15, 0x8d, 0x4f, 0xf8, 0xdd, 0xd4, 0x8c, 0x50, 0x15, 0x1c,
  0xef, 0x50, 0xee, 0xc4, 0x2e, 0xf7, 0xfc, 0xe9, 0x52, 0xf2, 0x91, 0x7d,
  0xe0, 0x6d, 0xd5, 0x35, 0x30, 0x8e, 0x5e, 0x43, 0x73, 0xf2, 0x41, 0xe9,
  0xd5, 0x6a, 0xe3, 0xb2, 0x89, 0x3a, 0x56, 0x39, 0x38, 0x6f, 0x06, 0x3c,
  0x88, 0x69, 0x5b, 0x2a, 0x4d, 0xc5, 0xa7, 0x54, 0xb8, 0x6c, 0x89, 0xcc,
  0x9b, 0xf9, 0x3c, 0xca, 0xe5, 0xfd, 0x89, 0xf5, 0x12, 0x3c, 0x92, 0x78,
  0x96, 0xd6, 0xdc, 0x74, 0x6e, 0x93, 0x44, 0x61, 0xd1, 0x8d, 0xc7, 0x46,
  0xb2, 0x75, 0x0e, 0x86, 0xe8, 0x19, 0x8a, 0xd5, 0x6d, 0x6c, 0xd5, 0x78,
  0x16, 0x95, 0xa2, 0xe9, 0xc8, 0x0a, 0x38, 0xeb, 0xf2, 0x24, 0x13, 0x4f,
  0x73, 0x54, 0x93, 0x13, 0x85, 0x3a, 0x1b, 0xbc, 0x1e, 0x34, 0xb5, 0x8b,
  0x05, 0x8c, 0xb9, 0x77, 0x8b, 0xb1, 0xdb, 0x1f, 0x20, 0x91, 0xab, 0x09,
  0x53, 0x6e, 0x90, 0xce, 0x7b, 0x37, 0x74, 0xb9, 0x70, 0x47, 0x91, 0x22,
  0x51, 0x63, 0x16, 0x79, 0xae, 0xb1, 0xae, 0x41, 0x26, 0x08, 0xc8, 0x19,
  0x2b, 0xd1, 0x46, 0xaa, 0x48, 0xd6, 0x64, 0x2a, 0xd7, 0x83, 0x34, 0xff,
  0x2c, 0x2a, 0xc1, 0x6c, 0x19, 0x43, 0x4a, 0x07, 0x85, 0xe7, 0xd3, 0x7c,
  0xf6, 0x21, 0x68, 0xef, 0xea, 0xf2, 0x52, 0x9f, 0x7f, 0x93, 0x90, 0xcf,
  0x02, 0x03, 0x01, 0x00, 0x01, 0xa3, 0x42, 0x30, 0x40, 0x30, 0x0e, 0x06,
  0x03, 0x55, 0x1d, 0x0f, 0x01, 0x01, 0xff, 0x04, 0x04, 0x03, 0x02, 0x01,
  0x06, 0x30, 0x0f, 0x06, 0x03, 0x55, 0x1d, 0x13, 0x01, 0x01, 0xff, 0x04,
  0x05, 0x30, 0x03, 0x01, 0x01, 0xff, 0x30, 0x1d, 0x06, 0x03, 0x55, 0x1d,
  0x0e, 0x04, 0x16, 0x04, 0x14, 0x60, 0x7b, 0x66, 0x1a, 0x45, 0x0d, 0x97,
  0xca, 0x89, 0x50, 0x2f, 0x7d, 0x04, 0xcd, 0x34, 0xa8, 0xff, 0xfc, 0xfd,
  0x4b, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01,
  0x01, 0x05, 0x05, 0x00, 0x03, 0x82, 0x01, 0x01, 0x00, 0xd6, 0x73, 0xe7,
  0x7c, 0x4f, 0x76, 0xd0, 0x8d, 0xbf, 0xec, 0xba, 0xa2, 0xbe, 0x34, 0xc5,
  0x28, 0x32, 0xb5, 0x7c, 0xfc, 0x6c, 0x9c, 0x2c, 0x2b, 0xbd, 0x09, 0x9e,
  0x53, 0xbf, 0x6b, 0x5e, 0xaa, 0x11, 0x48, 0xb6, 0xe5, 0x08, 0xa3, 0xb3,
  0xca, 0x3d, 0x61, 0x4d, 0xd3, 0x46, 0x09, 0xb3, 0x3e, 0xc3, 0xa0, 0xe3,
  0x63, 0x55, 0x1b, 0xf2, 0xba, 0xef, 0xad, 0x39, 0xe1, 0x43, 0xb9, 0x38,
  0xa3, 0xe6, 0x2f, 0x8a, 0x26, 0x3b, 0xef, 0xa0, 0x50, 0x56, 0xf9, 0xc6,
  0x0a, 0xfd, 0x38, 0xcd, 0xc4, 0x0b, 0x70, 0x51, 0x94, 0x97, 0x98, 0x04,
  0xdf, 0xc3, 0x5f, 0x94, 0xd5, 0x15, 0xc9, 0x14, 0x41, 0x9c, 0xc4, 0x5d,
  0x75, 0x64, 0x15, 0x0d, 0xff, 0x55, 0x30, 0xec, 0x86, 0x8f, 0xff, 0x0d,
  0xef, 0x2c, 0xb9, 0x63, 0x46, 0xf6, 0xaa, 0xfc, 0xdf, 0xbc, 0x69, 0xfd,
  0x2e, 0x12, 0x48, 0x64, 0x9a, 0xe0, 0x95, 0xf0, 0xa6, 0xef, 0x29, 0x8f,
  0x01, 0xb1, 0x15, 0xb5, 0x0c, 0x1d, 0xa5, 0xfe, 0x69, 0x2c, 0x69, 0x24,
  0x78, 0x1e, 0xb3, 0xa7, 0x1c, 0x71, 0x62, 0xee, 0xca, 0xc8, 0x97, 0xac,
  0x17, 0x5d, 0x8a, 0xc2, 0xf8, 0x47, 0x86, 0x6e, 0x2a, 0xc4, 0x56, 0x31,
  0x95, 0xd0, 0x67, 0x89, 0x85, 0x2b, 0xf9, 0x6c, 0xa6, 0x5d, 0x46, 0x9d,
  0x0c, 0xaa, 0x82, 0xe4, 0x99, 0x51, 0xdd, 0x70, 0xb7, 0xdb, 0x56, 0x3d,
  0x61, 0xe4, 0x6a, 0xe1, 0x5c, 0xd6, 0xf6, 0xfe, 0x3d, 0xde, 0x41, 0xcc,
  0x07, 0xae, 0x63, 0x52, 0xbf, 0x53, 0x53, 0xf4, 0x2b, 0xe9, 0xc7, 0xfd,
  0xb6, 0xf7, 0x82, 0x5f, 0x85, 0xd2, 0x41, 0x18, 0xdb, 0x81, 0xb3, 0x04,
  0x1c, 0xc5, 0x1f, 0xa4, 0x80, 0x6f, 0x15, 0x20, 0xc9, 0xde, 0x0c, 0x88,
  0x0a, 0x1d, 0xd6, 0x66, 0x55, 0xe2, 0xfc, 0x48, 0xc9, 0x29, 0x26, 0x69,
  0xe0
};
static const unsigned int caCertLen = 889;

class AntaresESP8266HTTP
{
    public:
      AntaresESP8266HTTP(String accessKey);
      String createDevice(String projectName, String deviceName);
      String retrieveAllDevice(String projectName,int limit=0);
      String storeData(String projectName, String deviceName, String nameData[], String valueData[], int sizeParameter);
      void begin(); // Initiate JSON buffer
      /*
        Overloaded functions start
        Antares::push()

        These functions are meant to push data into the
        initiated JSON buffer (created in
        the begin() function)
      */
      void add(String key, String value);
      void add(String key, int value);
      void add(String key, float value);
      void add(String key, double value);
      /* Overloaded functions end */
      void send(String projectName, String deviceName); // Store data in buffer to database
      void printData(); // Print waiting list data to serial monitor
      void end();  // Clear JSON buffer
      String retrieveAllData(String projectName, String deviceName,int limit=0);
      String retrieveLatestData(String projectName, String deviceName);
      void get(String projectName, String deviceName);
      void getSecure(String projectName, String deviceName);
      void getNonSecure(String projectName, String deviceName);
      void sendSecure(String projectName, String deviceName);
      void sendNonSecure(String projectName, String deviceName);
      void getTest(String projectName, String deviceName);
      void getLatestTest(String projectName, String deviceName);
      /*
        Antares::get() functions

        These functions are meant to fetch data from the
        JSON buffer.
      */
      String getString(String key);
      int getInt(String key);
      float getFloat(String key);
      double getDouble(String key);
      /* Overloaded functions end */
      bool getSuccess();
      bool wifiConnection(String SSID, String wifiPassword);
      bool checkWifiConnection();
      void setDebug(bool trueFalse);
      void setServer(String domain,String port);
      void setAntaresCse(String nameAntaresCse);
      void setAntaresId(String nameAntaresId);

      void measureSize();
      void measureGetSize();

    private:
      void printDebug(String text);
      String ipToString(IPAddress ip);
      String _accessKey;
      String _server = "http://platform.antares.id";
      const char* _serverNoHttp = "platform.antares.id";
      String _port = "8080";
      String _portSecure = "8443";
      uint16_t _portNum = 8080;
      uint16_t _portSecureNum = 8443;
      String _antaresCse = "antares-cse";
      String _antaresId = "antares-id";
      char* _wifiSSID;
      char* _wifiPass;
      bool _debug=false;
      bool _getSuccess=false;
      char* tempDebug;
      String jsonString = "{}";
      String jsonGetString;
};

#endif
