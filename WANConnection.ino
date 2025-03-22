#include <ESP8266HTTPClient.h>

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <ESP8266WebServer.h>
//#include <HTTPClient.h>
//#include <WebServer.h>
#include <EEPROM.h>


//Variables
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "Sayan2005" //Your adafruit name
#define MQTT_PASS "aio_ccoO675Cn4Jeds52AQ2MJSKrD4k6" //Your adafruit AIO key

// Motor Control Pins
#define M1F 13  // D7 (Motor 1 Forward)
#define M1B 12  // D6 (Motor 1 Backward)
#define M2F 2  // D4 (Motor 2 Forward)
#define M2B 14  // D5 (Motor 2 Backward)

int a=0,b=1,ss=0,v=0;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

Adafruit_MQTT_Subscribe light = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/forward");


Adafruit_MQTT_Subscribe light1 = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/backward");


Adafruit_MQTT_Subscribe light2 = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/left");


Adafruit_MQTT_Subscribe light3 = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/right");


int zz=0;
int yy=0;

int i = 0;
int statusCode;
const char* ssid = "Ratul";
const char* passphrase = "12345678";
String st;
String content;
String esid;
String epass = "";
//Function Decalration
bool testWifi(void);
void launchWeb(void);
void setupAP(void);
void MQTT_connect();
//Establishing Local server at port 80
ESP8266WebServer server(80);;
void setup()
{
  Serial.begin(9600);
  // pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.println("Disconnecting current wifi connection");
  WiFi.disconnect();
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);
  pinMode(15, INPUT);
  Serial.println();
  Serial.println();
  Serial.println("Startup");
  //Subscribe to the Lights topic
  Serial.println("OK!");

  //Subscribe to the Lights topic
  mqtt.subscribe(&light);
  mqtt.subscribe(&light1);
  mqtt.subscribe(&light2);
  mqtt.subscribe(&light3);
  
  pinMode(M1F, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2F, OUTPUT);
  pinMode(M2B, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
 // digitalWrite(led, LOW);
 
//  pinMode(led, OUTPUT);
  pinMode(2, OUTPUT);
//  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(M1F, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2F, LOW);
  digitalWrite(M2B, LOW);
  //---------------------------------------- Read eeprom for ssid and pass
  Serial.println("Reading EEPROM ssid");
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);
  WiFi.begin(esid.c_str(), epass.c_str());
}
void loop() {
  if ((WiFi.status() == WL_CONNECTED))
  {
//    for (int i = 0; i < 10; i++)
//    {
//      Serial.print("Connected to ");
//      Serial.print(esid);
//      Serial.println(" Successfully");
//      delay(100);
//    }

///Mqtt Code Start



//Connect/Reconnect to MQTT
  MQTT_connect();


  //Read from our subscription queue until we run out, or
  //wait up to 5 seconds for subscription to update
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    //If we're in here, a subscription updated...
    if (subscription == &light)
    {
      //Print the new value to the serial monitor
      Serial.print("Lights: ");
      Serial.println((char*) light.lastread);

      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) light.lastread, "1"))
      {
        //active low logic
        digitalWrite(M1F, HIGH);
        digitalWrite(M1B, LOW);
        digitalWrite(M2F, HIGH);
        digitalWrite(M2B, LOW);
        //LightsStatus.publish("ON");
      }
      else if (!strcmp((char*) light.lastread, "0"))
      {
        digitalWrite(M1F, LOW);
        digitalWrite(M1B, LOW);
        digitalWrite(M2F, LOW);
        digitalWrite(M2B, LOW);
        //LightsStatus.publish("OFF");

      }
      else
      {
        //LightsStatus.publish("ERROR");
      }
    }
    else
    {
      //LightsStatus.publish("ERROR");
    }





    if (subscription == &light1)
    {
      //Print the new value to the serial monitor
      Serial.print("Lights 1: ");
      Serial.println((char*) light1.lastread);

      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) light1.lastread, "1"))
      {
        //active low logic
        digitalWrite(M1F, LOW);
        digitalWrite(M1B, HIGH);
        digitalWrite(M2F, LOW);
        digitalWrite(M2B, HIGH);
        //LightsStatus.publish("ON");
      }
      else if (!strcmp((char*) light1.lastread, "0"))
      {
        digitalWrite(M1F, LOW);
        digitalWrite(M1B, LOW);
        digitalWrite(M2F, LOW);
        digitalWrite(M2B, LOW);
        //LightsStatus.publish("OFF");

      }
      else
      {
        //LightsStatus.publish("ERROR");
      }
    }
    else
    {
      //LightsStatus.publish("ERROR");
    }


    if (subscription == &light2)
    {
      //Print the new value to the serial monitor
      Serial.print("Lights 2: ");
      Serial.println((char*) light2.lastread);

      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) light2.lastread, "1"))
      {
        //active low logic
        digitalWrite(M1F, HIGH);
        digitalWrite(M1B, LOW);
        digitalWrite(M2F, LOW);
        digitalWrite(M2B, HIGH);
        //LightsStatus.publish("ON");
      }
      else if (!strcmp((char*) light2.lastread, "0"))
      {
        digitalWrite(M1F, LOW);
        digitalWrite(M1B, LOW);
        digitalWrite(M2F, LOW);
        digitalWrite(M2B, LOW);
        //LightsStatus.publish("OFF");

      }
      else
      {
        //LightsStatus.publish("ERROR");
      }
    }
    else
    {
      //LightsStatus.publish("ERROR");
    }



    if (subscription == &light3)
    {
      //Print the new value to the serial monitor
      Serial.print("Lights 3: ");
      Serial.println((char*) light3.lastread);

      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) light3.lastread, "1"))
      {
        //active low logic
        digitalWrite(M1F, LOW);
        digitalWrite(M1B, HIGH);
        digitalWrite(M2F, HIGH);
        digitalWrite(M2B, LOW);
        //LightsStatus.publish("ON");
      }
      else if (!strcmp((char*) light3.lastread, "0"))
      {
        digitalWrite(M1F, LOW);
        digitalWrite(M1B, LOW);
        digitalWrite(M2F, LOW);
        digitalWrite(M2B, LOW);
        //LightsStatus.publish("OFF");

      }
      else
      {
        //LightsStatus.publish("ERROR");
      }
    }
    else
    {
      //LightsStatus.publish("ERROR");
    }

     
    
  }

      



///Mqtt code end







    
  }
  else
  {
  }
  if (testWifi() && (digitalRead(15) != 1))
  {
    Serial.println(" connection status positive");
    return;
  }
  else
  {
    Serial.println("Connection Status Negative / D15 HIGH");
    Serial.println("Turning the HotSpot On");
    launchWeb();
    setupAP();// Setup HotSpot
  }
  Serial.println();
  Serial.println("Waiting.");
  while ((WiFi.status() != WL_CONNECTED))
  {
    Serial.print(".");
    delay(100);
    digitalWrite(2, HIGH);
      delay(100);
      digitalWrite(2, LOW);
    server.handleClient();
  }
  delay(100);
}
//----------------------------------------------- Fuctions used for WiFi credentials saving and connecting to it which you do not need to change
bool testWifi(void)
{
  int c = 0;
  //Serial.println("Waiting for Wifi to connect");
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(500);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}
void launchWeb()
{
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");
}
void setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      //Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  st = "<ol>";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<li>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);
    st += ")";
    //st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st += "</li>";
  }
  st += "</ol>";
  delay(100);
  WiFi.softAP("GROUP_S", "");
  Serial.println("Initializing_softap_for_wifi credentials_modification");
  launchWeb();
  Serial.println("over");
}
void createWebServer()
{
  {
    server.on("/", []() {
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content += "<!DOCTYPE HTML>\r\n<html><body style=\"text-align: center;\"><svg xmlns=\"http://www.w3.org/2000/svg\" width=\"850\" height=\"255\" viewBox=\"0 0 983 255\" version=\"1.1\">";
      content +="<path d=\"M 158.071 9.752 C 147.459 15.163, 144.710 29.245, 152.567 37.943 C 157.116 42.978, 160.666 44.337, 167.900 43.814 C 177.827 43.096, 184.346 36.038, 184.373 25.978 C 184.408 12.850, 169.741 3.801, 158.071 9.752 M 88.113 49.545 C 77.999 51.739, 72.188 53.879, 61.921 59.192 C 38.555 71.283, 20.384 93.399, 12.370 119.500 C 9.788 127.908, 9.603 129.717, 9.553 147 C 9.491 168.671, 10.773 174.732, 18.968 191.500 C 32.840 219.884, 58.966 239.587, 90.674 245.573 C 106.685 248.597, 127.168 246.762, 143.250 240.865 L 149 238.756 149 217.878 C 149 206.395, 148.732 197, 148.404 197 C 148.077 197, 146.537 197.905, 144.984 199.012 C 138.954 203.305, 126.962 208.169, 118.850 209.613 C 91.911 214.405, 64.161 200.262, 51.919 175.500 C 39.638 150.658, 44.282 122.529, 63.906 102.906 C 83.266 83.545, 111.084 78.745, 135.825 90.494 C 139.885 92.422, 143.338 94, 143.498 94 C 143.658 94, 143.957 88.713, 144.161 82.250 C 144.505 71.359, 144.770 70.029, 147.780 64.063 C 149.566 60.523, 150.683 57.293, 150.263 56.885 C 148.683 55.349, 138.195 51.749, 130 49.930 C 119.688 47.641, 97.816 47.440, 88.113 49.545 M 532.481 159.394 C 528.784 161.004, 523.256 167.132, 522.391 170.578 C 521.275 175.024, 522.621 181.815, 525.320 185.353 C 528.606 189.661, 533.575 192, 539.441 192 C 550.431 192, 558.150 183.154, 556.538 172.406 C 554.977 161.995, 542.277 155.125, 532.481 159.394 M 836.970 160.250 C 830.702 163.417, 828 167.859, 828 175 C 828 185.228, 834.813 192, 845.101 192 C 853.534 192, 856 190.606, 856 185.839 C 856 182.199, 854.830 180.848, 853.517 182.973 C 853.186 183.508, 851.151 184.421, 848.994 185.002 C 844.377 186.245, 838.851 184.458, 837.080 181.150 C 834.639 176.589, 836.287 168.551, 840.160 166.132 C 843.023 164.344, 849.552 164.477, 852.461 166.382 C 855.860 168.610, 856 168.519, 856 164.098 C 856 160.620, 855.657 160.076, 852.851 159.098 C 847.872 157.362, 841.816 157.802, 836.970 160.250 M 229.225 175.250 L 229.500 191.500 233.250 191.810 L 237 192.121 237 175.560 L 237 159 232.975 159 L 228.950 159 229.225 175.250 M 316.225 175.250 L 316.500 191.500 320.250 191.810 L 324 192.121 324 181.435 L 324 170.749 332.090 181.374 C 339.583 191.217, 340.431 192, 343.590 192 L 347 192 347 175.500 L 347 159 343.535 159 L 340.070 159 339.785 169.068 L 339.500 179.136 332.046 169.068 C 324.603 159.014, 324.586 159, 320.271 159 L 315.950 159 316.225 175.250 M 426.225 175.250 L 426.500 191.500 430.250 191.810 L 434 192.121 434 185.060 L 434 178 440 178 L 446 178 446 174.500 L 446 171 440 171 C 434.267 171, 434 170.889, 434 168.500 C 434 166.111, 434.267 166, 440 166 L 446 166 446 162.500 L 446 159 435.975 159 L 425.950 159 426.225 175.250 M 631 162.500 C 631 165.917, 631.095 166, 635 166 L 639 166 639 179.060 L 639 192.121 642.750 191.810 L 646.500 191.500 646.780 178.750 L 647.060 166 650.530 166 C 653.829 166, 654 165.828, 654 162.500 L 654 159 642.500 159 L 631 159 631 162.500 M 731 175.500 L 731 192 740.500 192 L 750 192 750 188.500 L 750 185 744.500 185 L 739 185 739 181.500 L 739 178 744.500 178 L 750 178 750 174.500 L 750 171 744.500 171 C 739.300 171, 739 170.864, 739 168.500 C 739 166.136, 739.300 166, 744.500 166 L 750 166 750 162.500 L 750 159 740.500 159 L 731 159 731 175.500 M 934 175.560 L 934 192.121 937.750 191.810 L 941.500 191.500 941.796 184.750 L 942.091 178 948.546 178 L 955 178 955 185 L 955 192 958.500 192 L 962 192 962 175.500 L 962 159 958.500 159 L 955 159 955 165.500 L 955 172 948.500 172 L 942 172 942 165.500 L 942 159 938 159 L 934 159 934 175.560 M 535.020 166.284 C 526.580 170.555, 529.616 185, 538.954 185 C 546.254 185, 550.407 178.793, 547.995 171.486 C 546.179 165.983, 540.285 163.620, 535.020 166.284\" stroke=\"none\" fill=\"#141313\" fill-rule=\"evenodd\"/>";
      content +="<path d=\"M 173.324 47.439 C 164.182 50.298, 155.742 57.986, 151.301 67.500 L 148.500 73.500 148.619 155.286 C 148.685 200.268, 148.978 237.311, 149.270 237.603 C 150.081 238.414, 159.759 233.286, 166.688 228.374 C 174.238 223.022, 179.439 216.846, 182.325 209.805 C 184.487 204.532, 184.502 204.016, 184.779 125.250 L 185.058 46 181.279 46.067 C 179.200 46.104, 175.621 46.721, 173.324 47.439 M 239.972 82.311 C 229.521 84.653, 220.983 91.466, 216.615 100.949 C 215.013 104.429, 214.517 107.500, 214.510 114 C 214.501 121.307, 214.895 123.304, 217.314 128.230 C 221.871 137.511, 230.856 143.493, 241.987 144.656 C 248.404 145.327, 258.688 143.730, 263.297 141.346 C 266.423 139.730, 274 133.164, 274 132.072 C 274 131.689, 272.616 130.353, 270.924 129.102 C 268.129 127.036, 267.691 126.969, 266.137 128.376 C 260.768 133.234, 250.879 134.315, 244.559 130.734 C 232.562 123.935, 232.485 101.488, 244.434 94.486 C 251.643 90.261, 257.671 90.997, 266.093 97.132 C 267.366 98.059, 268.338 97.811, 270.935 95.896 L 274.183 93.500 269.579 89.326 C 262.265 82.696, 250.596 79.931, 239.972 82.311 M 529.871 81.998 C 518.776 83.919, 509.852 90.713, 505.266 100.729 C 501.867 108.154, 501.716 119.303, 504.916 126.558 C 507.749 132.982, 514.007 139.299, 520.401 142.188 C 524.586 144.079, 527.203 144.490, 535 144.478 C 543.094 144.466, 545.314 144.083, 550 141.892 C 556.133 139.024, 562 134.474, 562 132.585 C 562 131.905, 560.978 130.388, 559.728 129.214 L 557.456 127.079 551.587 130.040 C 540.323 135.722, 530.687 132.894, 525.890 122.500 C 522.137 114.367, 524.171 101.768, 530.118 96.317 C 536.537 90.432, 547.218 90.614, 554.196 96.727 C 555.710 98.053, 556.221 97.979, 558.955 96.032 C 562.391 93.586, 562.188 92.657, 557.332 88.604 C 550.531 82.928, 539.635 80.307, 529.871 81.998 M 300.666 83.734 C 294.837 85.677, 286.697 92.737, 283.771 98.387 C 280.525 104.656, 280.129 117.699, 282.956 125.197 C 285.702 132.479, 293.632 140.035, 301.238 142.618 C 308.139 144.961, 319.843 144.967, 326.720 142.632 C 333.644 140.280, 341.078 133.502, 344.106 126.779 C 347.452 119.350, 347.453 105.677, 344.109 98.796 C 341.042 92.486, 334.578 86.734, 327.631 84.135 C 320.606 81.506, 307.918 81.318, 300.666 83.734 M 448.994 82.881 C 440.934 85.505, 433.277 91.720, 429.750 98.500 C 426.833 104.107, 426.225 115.822, 428.453 123.487 C 429.801 128.123, 431.300 130.460, 435.832 134.992 C 442.766 141.926, 448.951 144.328, 460 144.376 C 478.680 144.458, 491.377 133.276, 492.717 115.561 C 493.747 101.943, 488.010 91.141, 476.623 85.259 C 472.251 83, 470.034 82.572, 461.500 82.338 C 456 82.188, 450.372 82.432, 448.994 82.881 M 929.332 83.795 C 915.481 88.732, 907.685 101.714, 909.460 116.883 C 911.172 131.507, 920.667 141.220, 935.961 143.993 C 943.655 145.388, 950.811 144.584, 957.500 141.571 C 964.720 138.320, 968.474 134.740, 971.942 127.800 C 974.603 122.475, 975 120.621, 975 113.518 C 975 99.321, 970.172 90.677, 959.258 85.338 C 951.735 81.657, 937.404 80.919, 929.332 83.795 M 359 113 L 359 143 365.976 143 L 372.952 143 373.226 126.288 L 373.500 109.575 389 126.282 L 404.500 142.989 409.750 142.995 L 415 143 415 113 L 415 83 408 83 L 401 83 401 99.031 L 401 115.062 386.312 99.031 L 371.625 83 365.312 83 L 359 83 359 113 M 572 113 L 572 143 582 143 L 592 143 592 113 L 592 83 582 83 L 572 83 572 113 M 606.623 109.750 C 604.496 124.463, 602.527 137.963, 602.247 139.750 L 601.738 143 608.850 143 C 617.193 143, 616.349 144.557, 618.061 126 C 619.939 105.649, 619.609 105.676, 627.025 125.264 L 633.550 142.500 639.686 142.795 L 645.823 143.091 652.642 125.609 C 656.392 115.994, 659.568 108.235, 659.700 108.366 C 659.932 108.599, 664 140.594, 664 142.193 C 664 142.637, 668.050 143, 673 143 C 679.960 143, 682 142.689, 682 141.628 C 682 140.429, 675.015 95.053, 673.470 86.212 L 672.895 82.924 664.229 83.212 L 655.562 83.500 649.031 100.172 C 645.439 109.341, 642.256 117.085, 641.958 117.381 C 641.660 117.676, 638.510 110.065, 634.958 100.468 L 628.500 83.018 619.495 83.009 L 610.490 83 606.623 109.750 M 692 113 L 692 143 702.500 143 L 713 143 713 113 L 713 83 702.500 83 L 692 83 692 113 M 727 113 L 727 143 751.500 143 L 776 143 776 137.500 L 776 132 761.500 132 L 747 132 747 124.500 L 747 117 757.500 117 L 768 117 768 112 L 768 107 757.500 107 L 747 107 747 101 L 747 95 759.500 95 L 772 95 772 89 L 772 83 749.500 83 L 727 83 727 113 M 786 113 L 786 143 792.976 143 L 799.952 143 800.226 126.280 L 800.500 109.560 816 126.257 L 831.500 142.953 836.750 142.977 L 842 143 842 113 L 842 83 835.025 83 L 828.051 83 827.775 98.707 L 827.500 114.414 813.092 98.707 L 798.684 83 792.342 83 L 786 83 786 113 M 851 89 L 851 95 859 95 L 867 95 867 119 L 867 143 877 143 L 887 143 887 119 L 887 95 895 95 L 903 95 903 89 L 903 83 877 83 L 851 83 851 89 M 309 93.223 C 300.475 97.631, 299.498 125.527, 307.644 131.934 C 312.932 136.094, 319.855 133.998, 323.122 127.247 C 327.462 118.282, 325.489 98.936, 319.752 94.202 C 317.404 92.264, 311.836 91.757, 309 93.223 M 455 93.223 C 451.370 95.100, 448.926 100.943, 448.300 109.237 C 447.657 117.757, 449.285 126.822, 452.102 130.402 C 454.577 133.549, 459.947 134.679, 464.151 132.937 C 469.035 130.915, 471.391 124.588, 471.391 113.500 C 471.391 103.449, 470.067 98.351, 466.614 95.107 C 463.724 92.392, 458.308 91.513, 455 93.223 M 936.106 94.564 C 932.263 97.798, 931.013 102.290, 931.006 112.884 C 930.999 123.169, 932.459 128.367, 936.253 131.559 C 942.516 136.829, 950.527 133.175, 953.027 123.908 C 954.683 117.772, 953.846 103.485, 951.552 98.706 C 948.320 91.975, 941.391 90.117, 936.106 94.564\" stroke=\"none\" fill=\"#f80404\" fill-rule=\"evenodd\"/></svg>";
      content += "<h1>Welcome to conocimientoinfotech Automation Wifi Credentials Update page</h1>";
      //content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
      content += ipStr;
      content += "<p style=\"text-align: center;\"> <strong>Available Network</strong> <br></p>";
      content += "<p style=\"\">  <br>";
      content += st;
      content += "</p><form method='get' action='setting'style=\"text-align: center;\"><label><h2 style=\"color: #202076;\">SSID: </h2></label><br><input style=\"width: 55%;padding: 6px 6px; margin: 8px 0;display: inline-block;border: 8px solid #ccc;box-sizing: border-box;font-size:50px;\" name='ssid' length=32><br><label><h2 style=\"color: #202076;\">Password: </h2></label><br><input style=\"width: 55%;padding: 6px 6px; margin: 8px 0;display: inline-block;border: 8px solid #ccc;box-sizing: border-box;font-size:50px;\" name='pass' length=64><br><br> <br> <br><br><input style =\" font-size:50px; font-family:Arial;   width:500px; height:150px;  border-width:1px;  color:#333333;  border-color:#ffaa22;  font-weight:bold;  border-top-left-radius:6px;  border-top-right-radius:6px;  border-bottom-left-radius:6px;  border-bottom-right-radius:6px;  box-shadow: 0px 1px 0px 0px #fff6af;  text-shadow: 0px 1px 0px #ffee66;  background:linear-gradient(#ffec64, #ffab23)   \" type='submit'></form>";
      content += "</body></html>";
      server.send(200, "text/html", content);
    });
    server.on("/scan", []() {
      //setupAP();
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML>\r\n<html>go back";
      server.send(200, "text/html", content);
    });
    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        for (int i = 0; i < 96; ++i) {
          EEPROM.write(i, 0);
        }
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");
        Serial.println("writing eeprom ssid:");
        for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
          Serial.print("Wrote: ");
          Serial.println(qsid[i]);
        }
        Serial.println("writing eeprom pass:");
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
          Serial.print("Wrote: ");
          Serial.println(qpass[i]);
        }
        EEPROM.commit();
        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        statusCode = 200;
        ESP.restart();
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(statusCode, "application/json", content);
    });
  }
}
void MQTT_connect()
{

  //  // Stop if already connected
  if (mqtt.connected() && mqtt.ping())
  {
    //    mqtt.disconnect();
    return;
  }

  int8_t ret;

  mqtt.disconnect();

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0)
    {
      ESP.reset();
    }
  }
  Serial.println("MQTT Connected!");
}