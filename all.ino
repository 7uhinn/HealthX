#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
 
#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;
int val;
int tempPin = 1;
char n = 0;
int airquality = 0;
                               // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {   

  Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
    BTserial.begin(9600); 
  }
}



void loop() {

 
     if (BTserial.available())
    {  
        n = BTserial.read();
        Serial.write(n);
    }
 

 if (n=='1'){
 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 

if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 BTserial.write("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 BTserial.write("BPM: ");                        // Print phrase "BPM: " 
 BTserial.write(myBPM);
 BTserial.write("\n");                        // Print the value inside of myBPM. 
}

  delay(20);}                    // considered best practice in a simple sketch.

if (n=='2'){
val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
float cel = mv/10;
char fin; 
fin = (char)cel;
float farh = (cel*9)/5 + 32;

BTserial.write("TEMPRATURE = ");
BTserial.write(fin);
BTserial.write("*C");
BTserial.write("\n");
delay(1000);}

if (n=='3'){
    int sensorValue = analogRead(A0);
  BTserial.write("Air Quality = ");
  BTserial.write(sensorValue);

  BTserial.write("*PPM");
  BTserial.write("\n");
  delay(1000);

}
}

