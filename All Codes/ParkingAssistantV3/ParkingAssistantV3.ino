// Include the libraries
#include <TM1637Display.h>

// Define HC-SR04 Ultrasonic Sensor Pins and Variables
const int trigPin = 2;
const int echoPin = 1;
long duration;
int distance;
bool STATE        = true;
long TempDistance = 0;          // A variable to store the temporary distance
int counter       = 0;          // Counter value to check if the object has stopped moving
bool flashRainbow = true;
int falseAlarm    = 0;

// Define the pins connected to the TM1637
#define CLK 8
#define DIO 9
TM1637Display display(CLK, DIO); // Create an instance of the TM1637Display

// Use GPIO4 for the buzzer
const int buzzerPin = 4;

// Including Wi-Fi libraries
#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid       = "XXX";
const char* password   = "XXX";
const char* SmartURL   = "http://192.168.XXX.XXX/UpdateCarDistance.php";
// Setting up IP reservation
IPAddress local_IP(192, 168, 0, 211);     // Static IP Address for ESP32-C3
IPAddress subnet(255, 255, 255, 0);       // Subnet Mask
IPAddress gateway(192, 168, 0, 1);        // Default Gateway

// Including NeoPixil Libraries
#include <Adafruit_NeoPixel.h>
#define LED_PIN    3 // NeoPixel GPIO
#define LED_COUNT 24 // How many NeoPixels are attached to the Arduino?

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  // Connect to the Wi-Fi Network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  };
  Serial.println("\nWiFi connected");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());

  // Set the pinmode for the Ultrasonic Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set the display brightness (0-7)
  display.setBrightness(7);

  // Set the pinmode of the buzzer
  pinMode(buzzerPin, OUTPUT);

  // NeoPixel Initialization
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(55); // Set BRIGHTNESS to about 1/5 (max = 255)

  // Self test
  display.showNumberDec(0, true);   // 7-Segment Test. i=value, 'true' to padd the blank segments with 0
  digitalWrite(buzzerPin, HIGH);    // Buzzer Test
  rainbow(2);                       // NeoPixel Test. Flowing rainbow cycle along the whole strip

  // Get the initial distance
  GetDistance();
  TempDistance = distance;
}

void loop() {
  // Get the distance of the approaching object
  GetDistance();

  if(counter < 20) {   // Do the rest if the car is still moving
    // NeoPixel Color controller based on distance
    if (distance < 10) { digitalWrite(buzzerPin, HIGH); _NP_Flash(); } else { digitalWrite(buzzerPin, LOW); }; // Item is way to close - Start the buzzer
    if (distance>=10 && distance<15)   _NP_SetColor(strip.Color(255, 0, 0), 24);    // Red
    if (distance>=15 && distance<20)   _NP_SetColor(strip.Color(255, 0, 0), 23);    // Red
    if (distance>=20 && distance<25)   _NP_SetColor(strip.Color(255, 0, 0), 22);    // Red
    if (distance>=25 && distance<30)   _NP_SetColor(strip.Color(255, 0, 255), 21);  // Pink
    if (distance>=30 && distance<35)   _NP_SetColor(strip.Color(255, 0, 255), 20);  // Pink
    if (distance>=35 && distance<40)   _NP_SetColor(strip.Color(255, 0, 255), 19);  // Pink
    if (distance>=40 && distance<45)   _NP_SetColor(strip.Color(255, 87, 0), 18);   // Orange
    if (distance>=45 && distance<50)   _NP_SetColor(strip.Color(255, 87, 0), 17);   // Orange
    if (distance>=50 && distance<55)   _NP_SetColor(strip.Color(255, 87, 0), 16);   // Orange
    if (distance>=55 && distance<60)   _NP_SetColor(strip.Color(255, 227, 0), 15);  // Yellow
    if (distance>=60 && distance<65)   _NP_SetColor(strip.Color(255, 227, 0), 14);  // Yellow
    if (distance>=65 && distance<70)   _NP_SetColor(strip.Color(255, 227, 0), 13);  // Yellow
    if (distance>=70 && distance<75)   _NP_SetColor(strip.Color(0, 255, 0), 12);    // Green 
    if (distance>=75 && distance<80)   _NP_SetColor(strip.Color(0, 255, 0), 11);    // Green
    if (distance>=80 && distance<85)   _NP_SetColor(strip.Color(0, 255, 0), 10);    // Green
    if (distance>=85 && distance<90)   _NP_SetColor(strip.Color(0, 255, 0), 9);     // Green
    if (distance>=90 && distance<95)   _NP_SetColor(strip.Color(0, 0, 255), 8);     // Blue
    if (distance>=95 && distance<100)  _NP_SetColor(strip.Color(0, 0, 255), 7);     // Blue
    if (distance>=100 && distance<105) _NP_SetColor(strip.Color(0, 0, 255), 6);     // Blue
    if (distance>=105 && distance<110) _NP_SetColor(strip.Color(0, 0, 255), 5);     // Blue
    if (distance>=110 && distance<115) _NP_SetColor(strip.Color(255, 255, 255), 4); // White
    if (distance>=115 && distance<120) _NP_SetColor(strip.Color(255, 255, 255), 3); // White
    if (distance>=120 && distance<125) _NP_SetColor(strip.Color(255, 255, 255), 2); // White
    if (distance>=125 && distance<300) _NP_SetColor(strip.Color(255, 255, 255), 1); // White
  };
    
  // Turn off the lights if the object hasn't moved for 20 cycles (no change in distance)
  if (((distance+5) >= TempDistance) && ((distance-5) <= TempDistance)) {
    if(counter >= 20) { 
      Serial.println("No movement detected, turning off the lights");
      if ( flashRainbow ) { WiFiConnect(); rainbow(2); flashRainbow = false; }; // Send the distance flash the rainbow and turn off
      turnThemAllOff();
    } else { counter++;   };
  } else   { counter = 0; flashRainbow = true; }; // Reset counters if there is a movement
  TempDistance = distance;
  delay(500);
};


//// This function sets the color to the NeoPixels 
void _NP_SetColor(uint32_t color, int howMany) {
    if ( howMany > strip.numPixels() ) howMany = strip.numPixels(); // Make sure the count never goes over the number of available pixels
    strip.clear();                    // Set all pixels in RAM to 0 (off)
    for(int c=0; c<howMany; c++) {
      strip.setPixelColor(c, color);  // Set pixel 'c' to value 'color'
    };
    strip.show();                     // Update strip to match
    showDistanceOn7Segmnet();         // Show the distance 
};


//// This function flashes the NeoPixel
void _NP_Flash() {
  showDistanceOn7Segmnet();                             // Show Distance
  if (STATE) {
    for(int c=0; c<24; c++) {
      strip.setPixelColor(c, strip.Color(127, 0, 0));   // Set pixel 'c' to value 'color'
      strip.show();                                     //  Update strip to match
    };
  } else {
    for(int c=0; c<24; c++) {
      strip.setPixelColor(c, strip.Color(255, 0, 255)); // Set pixel 'c' to value 'color'
      strip.show();                                     //  Update strip to match
    };
  };
  STATE = !STATE;                                       // Reverse the state
};


//// This function turns off everything 
void turnThemAllOff() {
  strip.clear(); strip.show();  // Turn off the NeoPixel.Set all pixels in RAM to 0 (off)
  digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  display.clear();              // Turn off the 7-Segment
};


//// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    strip.rainbow(firstPixelHue);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  };
};


//// This function turns on or off the buzzer if the distance is too close  
void showDistanceOn7Segmnet() {
    display.showNumberDec(distance, false);   // i=value, 'true' to padd the blank segments with 0
};


//// This function calculates the distance of the object
void GetDistance() {
  digitalWrite(trigPin, LOW);  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 74;         // Distance in Inches

  Serial.print("Distance: ");Serial.print(distance);
  Serial.print(" || Temp Distance: ");Serial.print(TempDistance);
  Serial.print(" || Counter: ");Serial.print(counter);
  Serial.print(" || False Alarm CTR: ");Serial.println(falseAlarm);
};


//// Function that establishes a wireless connection and sends the data to the server
void WiFiConnect() {
  String Querystring = String("?DISTANCE=") + distance + String("&Location=Garage");
  if(WiFi.status()== WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;
      String serverPath = SmartURL + Querystring; 
      Serial.println(serverPath);

      http.begin(client, serverPath.c_str());
      int httpResponseCode = http.GET();      // Send HTTP GET request

      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: "); Serial.println(httpResponseCode);
      } else {
        Serial.print("Error code: "); Serial.println(httpResponseCode);
        /** Reboot the device if device is unable to contact the server **/
        ESP.restart();
      };
      http.end();                            // End the connection
  } else {
    Serial.println("WiFi Disconnected");
  };
};