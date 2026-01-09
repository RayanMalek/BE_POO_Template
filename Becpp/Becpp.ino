
#include "ultrasonicsensor.hpp"
#include "pushupdetector.hpp"
#include "pushbutton.hpp"
#include "lcdscreen.hpp"


#define UltrasonicPin  D6
#define PushButtonPin D5
const int  th= 10;
const unsigned long cooldownMs = 400;  // ignore repeats for 0.4s after a rep
const unsigned long readPeriodMs = 50; // sensor read rate
static unsigned long lastSampleMs = 0;
ultrasonicsensor sensor(UltrasonicPin);
pushbutton activate(PushButtonPin);
pushupdetector detector(th,cooldownMs, readPeriodMs);
lcdscreen screen  (20,2);

bool started = false;
int counter = 0;


void setup(){
  pinMode(LED_BUILTIN, OUTPUT); // to see if setup is made 
  digitalWrite(LED_BUILTIN, LOW);  // LED on
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH); // LED off


  screen.begin();
  screen.printtext(0, 0, "Push-up counter");
  screen.printtext(1, 0, "Press button");
  sensor.begin() ;
  Serial.begin(9600);  // start serial communication
  delay(1000);   
  activate.begin();
  Serial.println(" press the button to get started");
}
void loop (){
  if(!started){
    if (activate.ishigh()){ 
      started = true;
      counter=0;
      screen.clear();
      screen.printtext(0, 0, "Counting...");
      screen.printtext(1, 0, "Reps: 0");
      Serial.println("Started Counting");
      delay(300);
    }
    return;
  }

   long d = sensor.MeasureInCentimeters();
  
  Serial.print("d = ");
  Serial.println(d);
  delay(100);
  unsigned long now = millis();
  if (now - lastSampleMs < readPeriodMs) return;   // pace the sensor itself
  lastSampleMs = now;

  
  
  if(detector.update(d,now) ){
  
      counter++;
       screen.printtext(1, 0, "Reps:      ");
       screen.printnumber(1, 6, counter);
    
    
      Serial.print("d=");
      Serial.print(d);


      Serial.print(" cm push up : ");
      Serial.println(counter);
    }   
  
}