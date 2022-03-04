/*
  created 20 May 2019
  author Matúš Juštik

  updated 23 May 2019
  by Matúš Juštik
 
*/

#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte serv[] = {192, 168, 0, 103} ; //ip servera
EthernetClient cliente;
int pushButton =2;           // v akom pine je tlačitko
int pushButtonCounter = 0;   // počita stlačenia tlačitka
int buttonState = 0;         // aktuálny stav tlačitka
int lastButtonState = 0;     // stav tlačitka pred
uint32_t period = 60000L;    // 1 minuta (pre priadnie napr. 2 min   = 2* 60000L;)
uint32_t tStart = millis();	 // aktualny cas


void setup() {
pinMode(pushButton, INPUT);
Serial.begin(9600); 
Ethernet.begin(mac);
}


void loop() {

buttonState = digitalRead(pushButton);
int buttonState = digitalRead(pushButton);
      
    if (buttonState != lastButtonState) {           
    tStart = millis();      

	  while((!cliente.connect(serv, 80) && ((millis()-tStart) < period)))      // kym sa nepodari pripojit, vypisuj kazdu sekundu hlasku a skusi sa pripojiť znovu a zároveň je čas do jednej minúty
		Serial.println("connection failed");
		delay(1000);	    
        
        if(cliente.connect(serv, 80)) {
        Serial.println("connected");
        cliente.print("GET /ethernet/data.php?"); //pripojenie a odosielanie dát v databáze
        
            if (buttonState == HIGH) {
            cliente.print("buttonState=");
            cliente.println(buttonState);
            //do seriového monitoru vypisuje údaje
            Serial.print("buttonState=");
            Serial.println(buttonState);
            delay(5);
            cliente.stop(); //zatvára pripojenie
            }
            
            else{
            cliente.print("buttonState=");
            cliente.println(buttonState);
            //do seriového monitoru vypisuje údaje
            Serial.print("buttonState=");
            Serial.println(buttonState);
            delay(5);
            cliente.stop(); //zatvára pripojenie
            }
        }
    
    }

lastButtonState = buttonState;
}
