/*
 Basic HELTEC ESP32 MQTT example
 This sketch demonstrates the capabilities of the pubsub library in combination
 with the HELTEC ESP32 board/library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
*/

#include <HCSR04.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <U8x8lib.h>

// Initialize  sensor  that  uses  digital pins  13  and 12
UltraSonicDistanceSensor  distanceSensor(5, 17);

// Update these with values suitable for your network.

const char* ssid 		= "dd-wrt";
const char* password 	= "peri2019";

const char* IN_TOPIC	= "in_peri_al";
const char* OUT_TOPIC 	= "out_peri_al";
const char* mqtt_server = "192.168.1.42";
int port 				= 1883;

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);
uint64_t chipid; 
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[100];

void setup_wifi() 
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

/*
- appelée a chaque fois que quelquun sur le reseau envoie un message sur le out_topic
*/
void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  payload[length]=0;
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  Serial2.println((char*)payload);
  u8x8.drawString(0, 2, (char*)payload);
  
}
/* Reconnecter en cas de perte de connextion */
void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "HeltecESP32LoraClient-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) 
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(OUT_TOPIC, "Message to publish");
      // ... and resubscribe
      client.subscribe(IN_TOPIC);
    } else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() 
{
  
  Serial.begin(115200);
  //Serial2.begin(115200); // disrupts the UltraSonic results

  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0, 0, "PERI 2019");
  u8x8.drawString(0, 1, "Collect data");

  chipid=ESP.getEfuseMac();//The chip ID is essentially its MAC address(length: 6 bytes).
  Serial.printf("ESP32 Chip ID = %04X",(uint16_t)(chipid>>32));//print High 2 bytes
  Serial.printf("%08X\n",(uint32_t)chipid);//print Low 4bytes.

  delay(3000);
  
  setup_wifi();
  client.setServer(mqtt_server, port);
  client.setCallback(callback);
}

void loop() 
{

  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 3000) 
  {
    lastMsg = now;
    String value = String(distanceSensor.measureDistanceCm());

    // print message on LCD
    u8x8.drawString(0, 3, value.c_str());
  
    // make message format: "table_name,row_name,value" 
    // ex.: "distance_mesure,distance,100"
    
    // Distance Mesure 
    snprintf(msg, 100, "distance,distance,date,%s,'%s'", value.c_str(), "2012-04-19 22:22:22");
    client.publish(OUT_TOPIC, msg);
    // Chaleur Meusure
	  snprintf(msg, 100, "random,random,date,%ld,'%s'", random(0, 100),"2012-04-19 22:22:22");
    client.publish(OUT_TOPIC, msg);
  }
}
