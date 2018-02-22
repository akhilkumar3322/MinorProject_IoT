#include <Time.h>
#include <SPI.h>
#include <Ethernet.h>
#define RELAY1 7

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

byte server[] =  { 192, 168, 1, 6 };


IPAddress ip(192, 168, 137, 177);


EthernetClient client, client1;


int inputPin1 = 8;
int inputPin2 = 9;
const int reedpin = 12;
int var1;
int var2;
int val1;
int val2;
int t = 0;
int v = 0;
bool con = false;
String data;
int rel1;
int rel2;
int on = 1;
int off = 0;
int read1;
int read2;

int func();
void calldelayedfactor();
void postdata(int x);

void setup()
{
  pinMode(inputPin1, INPUT);
  pinMode(inputPin2, INPUT);
  pinMode(RELAY1, OUTPUT);

  Serial.begin(9600);
  
  digitalWrite(reedpin,HIGH);
  pinMode(reedpin , INPUT);
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }

  delay(1000);
  Serial.println("connecting...");
  //digitalWrite(RELAY1,HIGH);
}


void loop()
{
  digitalWrite(RELAY1, LOW);
  delay(1000);
  t = t + 1000;
  //int proximity = digitalRead(reedpin);
  //if(proximity == LOW)
  //{
  //  Serial.println("Switch Open");
  //  delay(5000);
  val1 = digitalRead(inputPin1);
  if (val1 == HIGH) {
    var1 = 1;
  }
  else {
    var1 = 0;
  }

  val2 = digitalRead(inputPin2);
  if (val2 == HIGH) {
    var2 = 1;
  } else {
    var2 = 0;
  }
  

if ( t == 20000)
{
	if (var1 == 1 || var2 == 1) 
	{
		Serial.println("PresentA");
		v = 1;
	} else 
	{
			v = func();
			if (v == 0) 
			{
				Serial.println("Not Present");
				calldelayedfactor();
				Serial.println("Hii");
				if (Serial.available() > 0) 
				{
					//read the most recent byte 
					char state = Serial.read();
          if(state == 'B')
          {
            digitalWrite(RELAY1, LOW);
          }
          if(state == 'C')
          {
            digitalWrite(RELAY1, HIGH);
          }
          if(state == 'A')
          {
              rel1 = digitalRead(inputPin1);
              rel2 = digitalRead(inputPin2);
              //digitalWrite(RELAY1,LOW);
              if(rel1 == 0 && rel2 == 0)
              {
                digitalWrite(RELAY1,HIGH);
                delay(2000);
                off = 1;
                on = 0;
                while(on != off && off > on)
                {
                  read1 = digitalRead(inputPin1);
                  read2 = digitalRead(inputPin2);
                  if(read1 == 1 || read2 == 1)
                  {
                    on = 1;
                    off = 0;
                    Serial.println("HEHE");
                    break;                    
                  }
                }
              }
          }
          
				}
				
			} else
			{
			Serial.println("PresentB");
			}
		
		
	}

	postdata(v);
	t = 0;
}
//} 
}


int func() {
  int tt = 0;

  while (tt <= 10000) {
    val1 = digitalRead(inputPin1);

    if (val1 == HIGH) {
      var1 = 1;
    }
    else {
      var1 = 0;
    }

    val2 = digitalRead(inputPin2);
    if (val2 == HIGH) {
      var2 = 1;
    } else {
      var2 = 0;
    }

    if (var1 == 0 && var2 == 0) {
      return 0;
    } else {
      return 1;
    }
    delay(1000);
    tt = tt + 1000;
  }
  return 0;
}

void postdata(int d) {

  connectClient();
  String data = "";

  data = "status=" + String(d) ;
  Serial.println(data);

  // client connection to server
  byte no = client.println("POST /ArduinoPirInterface/add.php HTTP/1.0");
  //Serial.println(no);
  client.println("HOST: 192.168.1.2");
  //client.println("HOST: localhost");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(data.length());
  Serial.println(data.length());
  client.println();
  byte ko = client.print(data);
  //Serial.println(ko);

  client.stop();
}


void calldelayedfactor() {

  connectClient();
  String data1 =  "flag = 1" ;
  Serial.println("flag");

  // client connection to server
  byte no = client.println("POST /ArduinoPirInterface/delayedfactor.php HTTP/1.0");
  //Serial.println(no);
  client.println("HOST: 192.168.1.2");
  //client.println("HOST: localhost");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(data1.length());
  Serial.println(data1.length());
  client.println();
  byte ko = client.print(data1);
  //Serial.println(ko);
  Serial.println("flag1");
  client.stop();
  Serial.println("flag2");

}

void connectClient()
{
  if (client.connect(server, 80))
  {
    Serial.println("Connected");
  }
  else
  {
    Serial.println("Not Connected");
  }
}


/*void onoff(){


  if (client1.connect(server, 80))
  {
    client1.println("GET /ArduinoPirInterface/fan.txt HTTP/1.1");
    client1.println("Host: 192.168.1.2");
    client1.println("Connection: close");
    client1.println();


  }
  else
  {
    Serial.println("Not Conected");
  }
  Serial.print(client1.available());
  if (client1.available()) {
    char cb = client1.read();
    Serial.print(cb);
  }


   client1.stop();

  if (c=='1') {
    digitalWrite(RELAY1, LOW);

  } else {

    digitalWrite(RELAY1, HIGH);
  }


  }*/




