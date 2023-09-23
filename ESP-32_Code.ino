#include <WiFi.h>

#include <ESP_Mail_Client.h>

#define WIFI_SSID "Your_Wifi_Name"

#define WIFI_PASSWORD "Wifi_Password"

#define SMTP_server "smtp.gmail.com"

#define SMTP_Port 465

#define sender_email "Your_email"

#define sender_password "Your_password"

#define Recipient_email "Recever_Email"

#define Recipient_name "Recever_Name"

SMTPSession smtp;
const int emailTriggerPin = 13;
const int gasDetected = 14;


void setup(){
  pinMode(emailTriggerPin, INPUT);
  pinMode(gasDetected, INPUT);
  Serial.begin(115200);

  Serial.println();

  Serial.print("Connecting...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)

  { Serial.print(".");

    delay(200);

   }

  Serial.println("");

  Serial.println("WiFi connected.");

  Serial.println("IP address: ");

  Serial.println(WiFi.localIP());

  Serial.println();

  smtp.debug(1);

 
}

void loop(){

   int triggerSignal = digitalRead(emailTriggerPin);
  int gas = digitalRead(gasDetected);
   if(gas == HIGH){
    Serial.println("GAS Detected!");
    sendEmail(2);
  }
  if (triggerSignal == HIGH) {
    // When the trigger signal is HIGH, send the email for fire
    sendEmail(1);
  }
 

}

void sendEmail(int fire){
  
   ESP_Mail_Session session;

  session.server.host_name = SMTP_server ;

  session.server.port = SMTP_Port;

  session.login.email = sender_email;

  session.login.password = sender_password;

  session.login.user_domain = "";

  /* Declare the message class */

  SMTP_Message message;

  message.sender.name = "Home Security!";
 
  message.sender.email = sender_email;
  if(fire == 1){
    message.subject = "Fire Alert!";
  }
  else if(fire == 2){
    message.subject = "Gas Alert!";
  }
  

  message.addRecipient(Recipient_name,Recipient_email);

  String htmlMsg;
   //Send HTML message
  if(fire == 1){
     htmlMsg = "<div style=\"color:#000000;\"><h1> Fire Detected. </h1><p> Trying to put off the fire. Please get home first & contact Fire Service.</p></div>";
  }
  else{
     htmlMsg = "<div style=\"color:#000000;\"><h1> Gas Leakage Detected. </h1><p> Please, get home fist & contact Fire Service.</p></div>";
  }
  

  message.html.content = htmlMsg.c_str();

  message.html.content = htmlMsg.c_str();

  message.text.charSet = "us-ascii";

  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

 /* //Send simple text message

  String textMsg = "How are you doing";

  message.text.content = textMsg.c_str();

  message.text.charSet = "us-ascii";

  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;*/

  if (!smtp.connect(&session))

    return;

  if (!MailClient.sendMail(&smtp, &message))

    Serial.println("Error sending Email, " + smtp.errorReason());

}



