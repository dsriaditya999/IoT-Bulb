/// Program for IoT controlled Smart Bulb

String test;
int receive_val;
char char_buf[50];

String sendCommand;
String Wifiname = "**********";
String password = "++++++++++";

int Bulb = 8;


void setup()
{
  Serial.begin(9600);                                   // Start Serial Communication 
  delay(1000);
  Serial.println("AT");                                // AT Commands Start
  pinMode(Bulb,OUTPUT);
  while(!Serial.find("OK"))
  {
  }
  Serial.println("AT+RST");
  while(!Serial.find("OK"))
  {
  }
  delay(1000);
  Serial.println("AT+CWMODE=1");                      // Client Mode
  while(!Serial.find("OK"))
  {
  }
  Serial.println("AT+CWJAP=\""+Wifiname+"\",\""+password+"\"");
  while(!Serial.find("OK"))
  {
    delay(6000);
    Serial.println("AT+CWJAP=\""+Wifiname+"\",\""+password+"\"");
  }

 Serial.println("AT+CIPMUX=0");                     // Connected to only 1 Device
 while(!Serial.find("OK")){
 }
 }


 void loop()
 {
  sendCommand = "GET /channels/^^^^^^^^/fields/1/last.txt";            // Replace ^^^^^ with the Public Channel's ID
  Serial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");     // Start TCP communication 
  while(!Serial.find("CONNECT"))
  {
  delay(5000);
  Serial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");  
  }
  while(!Serial.find("OK"))
  {
    
  }

  delay(20);
  Serial.println("AT+CIPSEND="+String(sendCommand.length()+4));       // Sending Command's Length
  while(!Serial.find("OK"))
  {
    delay(3000);
    Serial.println("AT+CIPSEND="+String(sendCommand.length()+4));
    
  }
  while(!Serial.find(">"))
  {
    
  }
  delay(100);
  Serial.println(sendCommand);                                      // Command sent to retrieve last entry from the specified channel's Field-1
  while(!Serial.find("SEND OK"))
  {
    delay(3000);
    Serial.println(sendCommand);
    
  }

  test = Serial.readString();
  test.toCharArray(char_buf,50);
 receive_val = int(char_buf[11]);
 Serial.println(receive_val);                                       // Receive the ASCII value of the number in the last entry
  if(receive_val == 48){                                            // ASCII Value of "0" is 48 (Relay is Active LOW)
    digitalWrite(Bulb,HIGH);
    }
   else if(receive_val == 49){                                      // ASCII Value of "1" is 49 (Relay is Active LOW)
      digitalWrite(Bulb,LOW);                                       
    }

    
   delay(2000);
  
  

 }
  
  
  
  
  
  
