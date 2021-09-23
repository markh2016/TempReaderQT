// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 3
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 
void setup(void) 
{ 
 // start serial port 
 Serial.begin(9600); 
  
 // Start up the library 
 sensors.begin(); 
} 
void loop(void) 
{ 

  String SerialData="";
  
  sensors.requestTemperatures();
  
  double temp = sensors.getTempCByIndex(0);
  // Convert double to string 
  SerialData = String(temp ,2) ;

  // Concat C to string 
  SerialData.concat(" C") ;

  // now send this out on the serial port 
  Serial.print(SerialData) ;

    
  delay(1000) ;
  temp = sensors.getTempFByIndex(0);
  // Convert double to string 
  SerialData = String(temp ,2);
  SerialData.concat(" F") ;

  // now send this out on the serial port 
  
  Serial.print(SerialData);
  
  Serial.flush();

  
  delay(1000);
} 
