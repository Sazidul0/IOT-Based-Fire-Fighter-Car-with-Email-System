// IOT Based Fire Fighter with Email System
 
#include <Servo.h>            //include servo.h library
#include <SoftwareSerial.h>  //include SoftwareSerial.h library

Servo myservo;
 
int pos = 0;    
boolean fire = false;

#define Left 4          // left sensor
#define Right 5         // right sensor
#define Forward 6       //front sensor
#define GAS_SENSOR 7    //Gas sensor
#define LM1 8           // left motor
#define LM2 9           // left motor
#define RM1 10          // right motor
#define RM2 11          // right motor
#define pump 12         //water pumb


const int fireDetected = 2;
const int gasDetected = 3;

void setup()
{
   pinMode(fireDetected, OUTPUT);
  digitalWrite(fireDetected, LOW);
  pinMode(gasDetected, OUTPUT);
  digitalWrite(gasDetected, LOW);

  Serial.begin(115200);
 
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(GAS_SENSOR, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);

  myservo.attach(13);
  myservo.write(90); 
}
 

void put_off_fire()
{
 Serial.println("Controling the fire!!!!!");
    digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);
  digitalWrite(pump, LOW);
    delay(500);
    for (pos = 50; pos <= 130; pos += 1) { 
    myservo.write(pos); 
    delay(10);  
  }
  for (pos = 130; pos >= 50; pos -= 1) { 
    myservo.write(pos); 
    delay(10);
  }
  digitalWrite(pump,LOW);
  
  digitalWrite(pump,HIGH);
  myservo.write(90); 
  fire=false;
}
 
void loop()
{
  fire = false;
  digitalWrite(pump,HIGH);
  myservo.write(90); //Sweep_Servo();  
 
  if (digitalRead(Left) ==1 && digitalRead(Right)==1 && digitalRead(Forward) ==1) 
    {
    delay(500);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    //fire = true;
    }
    else if (digitalRead(Forward) ==0) 
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    fire = true;
    
    }
    
    else if (digitalRead(Left) ==0)
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    fire = true;
    }
    
    else if (digitalRead(Right) ==0) 
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    fire = true;
    }
    delay(400);
    
     if(digitalRead(GAS_SENSOR)== 0)
    {
     Serial.println("Gas is Detected.");
      //send_sms(); 
	    sendEmail(0);
      delay(5000);
    }
   
     while (fire == true)
     {
       Serial.println("Fire is oNN!!!");
	sendEmail(1);
      put_off_fire();
      Serial.println("Fire Detected.");
      
     }
     
 }

void sendEmail(int fire) {
  if(fire == 1){
	  digitalWrite(fireDetected, HIGH); // Signal ESP8266 to send an email
  	delay(1000); // Add a delay for stability
  	digitalWrite(fireDetected, LOW); // Reset the pin to LOW
  }
  else if(fire==0){
    Serial.println("Sending Email for Gas!.");
	digitalWrite(gasDetected, HIGH); // Signal ESP8266 to send an email
  delay(3000); // Add a delay for stability
  digitalWrite(gasDetected, LOW); // Reset the pin to LOW
  }
  
}

