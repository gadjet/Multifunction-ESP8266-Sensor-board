/* This code is made up from otherpeoples code I found on the internet and adapted for my use
This code sends temp and humidity every 15 minutes
*/
#include<ESP8266WiFi.h>
#include<espnow.h>
#include <Adafruit_AHT10.h>
 Adafruit_AHT10 aht;
#include <DallasTemperature.h>

// I used two receivers therefore there's two IP addresses
uint8_t bridgeAddress1[] = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11};   //please update this with the MAC address of your ESP-NOW TO MQTT brigde
//uint8_t bridgeAddress2[] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX};   //please update this with the MAC address of your ESP-NOW TO MQTT brigde

// Set your Board ID (
#define BOARD_ID 12

const int reedSwitch = 13;

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int id;
  char state[7];
  int vBatt;
  float Temp;
  float Humidity;
} struct_message;

// Create a struct_message called test to store variables to be sent
struct_message myData;

// Callback when data is sent (I removed the serial prints to save power)
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  /* Serial.print("\r\nLast Packet Send Status: ");
    if (sendStatus == 0){
     Serial.println("Delivery success");
    }
    else{
     Serial.println("Delivery fail");
    }
  */
}

void setup() {
aht.begin();
  
  // Init Serial Monitor
  //Serial.begin(115200);
  // initialize the reed switch pin as an input:
  pinMode(reedSwitch, INPUT);
  // initialize the wakeup pin as an input:
  pinMode(16, WAKEUP_PULLUP);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    //Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Set ESP-NOW role
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);

  // Once ESPNow is successfully init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer(I used two receivers)
  esp_now_add_peer(bridgeAddress1, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  //esp_now_add_peer(bridgeAddress2, ESP_NOW_ROLE_SLAVE, 2, NULL, 0);
}


void loop() {
sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  // Set values to send
  myData.id = BOARD_ID;
  // Read the state of the reed switch and send open or closed
  if (digitalRead(reedSwitch) == HIGH) {
    strcpy(myData.state, "Closed");
  }
  else {
    strcpy(myData.state, "Open");
  }
  
  myData.vBatt = (analogRead(A0) * 4.2 * 10 / 1023);
  myData.Humidity = humidity.relative_humidity; //temp.temperature;// populate temp and humidity objects with fresh data
  myData.Temp = temp.temperature;
  // Send message via ESP-NOW
  esp_now_send(0, (uint8_t *) &myData, sizeof(myData));
  ESP.deepSleep(900e6); //15 Min's sleep
  delay(200);
}
