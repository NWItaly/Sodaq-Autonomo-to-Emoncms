#include "Config.h"
#include <Wire.h>
#include <Sodaq_BMP085.h>
#include <Sodaq_SHT2x.h>
#include <Sodaq_WifiBee.h>
#include <Sodaq_wdt.h>

#define SerialMonitor SerialUSB
#define Reset_AVR() sodaq_wdt_enable(WDT_PERIOD_1DIV32); while(1) {}

#define TEST 1
#if TEST == 1
#define Sprintln(a) SerialMonitor.println(a)
#define Sprint(a) SerialMonitor.print(a)
#else
#define Sprintln(a)
#define Sprint(a)
#endif

unsigned long lastConnectionTime = 0; // last time you connected to the server, in milliseconds
byte postingInterval = 10; // delay between updates, in seconds
byte failedAttempts = 0;
const byte retryBeforeReboot = 10;

//Serial Connections
#define BeeSerial Serial1
//You can add multiple headers each must be followed by "\r\n"
#define TEST_HEADERS "Accept: */*\r\n"
Sodaq_WifiBee wifiBee;

/* TPH BMP sensor */
#define BMP085_Enabled 1
#if BMP085_Enabled == 1
Sodaq_BMP085 bmp;
#endif

void setup() {
  //  turn on serial (for debugging)
  delay(2000);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  SerialMonitor.begin(57600);
  BeeSerial.begin(9600);

  // Setup indicator LED
  Sprintln(F("Setup LED to inform when it sends data."));
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  #if TEST == 1
    Sprint(F("Device Type: "));
    Sprintln(String(wifiBee.getDeviceType()));
  
    Sprint(F("SSID: "));
    Sprintln(SSID);

    Sprint(F("Password: "));
    Sprintln(PASSWORD);
  #endif

  wifiBee.init(BeeSerial, BEE_VCC, BEEDTR, BEECTS, 1024);
  wifiBee.connectionSettings(SSID, "", PASSWORD);
  
  //This sets the WifiBee to debug mode over Serial
  wifiBee.setDiag(SerialMonitor);

  #if BMP085_Enabled == 1
    Sprintln(F("Setup TPH BMP sensor with wire protocol"));
    //Initialise the wire protocol for the TPH sensors  
    Wire.begin();  
    //Initialise the TPH BMP sensor  
    bmp.begin();
  #else
    Sprintln(F("BMP085 disabled"));
  #endif
  
  Sprintln(F("Setup ends"));
}//setup

void loop() {

  // if at least <postingInterval> seconds have passed sinceyour last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval * 1000) {
    String uri = "/emoncms/input/post.json?data={";
    
    #if BMP085_Enabled == 1
      uri += "Temperature1:";
      uri += String(SHT2x.GetTemperature());
      uri += ",Temperature2:";
      uri += String(bmp.readTemperature());
      uri += ",Pressure:";
      uri += String(bmp.readPressure());
      uri += ",Humidity:";
      uri += String(SHT2x.GetHumidity());
    #endif

    uri += "}";
    if (myEmonData_node != 255) {
      uri += "&node=";
      uri += myEmonData_node;
    }
    uri += "&apikey=";
    uri += myEmonData_apiKey;
    
    Sprintln(F("###Data to send###"));
    Sprintln(uri);
    Sprintln(F("######"));
    
    uint16_t code = 0;
    if (wifiBee.HTTPGet(myEmonData_serverIP, myEmonData_serverPort, uri, TEST_HEADERS, code)) {
      Sprint(F("Response Code: "));
      Sprintln(code);
      
      if(code == 200) {
        failedAttempts = 0;
      }
      else {
        #if TEST == 1
          char buffer[1024];
          size_t bytesRead;
          if (wifiBee.readResponseAscii(buffer, sizeof(buffer), bytesRead)) {
              Sprintln(F("--------------"));
              Sprintln(F("Full Response:"));
              Sprintln(F("--------------"));
              Sprint(buffer);
          }
          else {
            Sprintln(F("No repsonse")); 
          }
        #endif
        ErrorBlink();
        failedAttempts++;//Count how many error happens
      }
    }
    else {
      Sprintln(F("Failed connection"));
      ErrorBlink();
      failedAttempts++;//Count how many error happens
    }
    // note the time that the connection was made
    lastConnectionTime = millis();
  }

  //Check error and Reboot
  if (failedAttempts >= retryBeforeReboot) {
    Reset_AVR();
    ErrorBlink();
    failedAttempts = 0;
  }

}//loop

void ErrorBlink() {
  for (int index = 0; index < 5; index++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
  }
}//ErrorBlink
