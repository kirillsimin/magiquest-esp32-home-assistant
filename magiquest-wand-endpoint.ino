#include <WiFi.h>
#include <HTTPClient.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>

// WiFi credentials
const char* ssid = "wi-fi-ssid";
const char* password = "super-duper-password";

// Endpoints for on/off actions
const char* on_endpoint = "http://192.168.1.6/api/webhook/wand-off";
const char* off_endpoint = "http://192.168.1.6/api/webhook/wand-on";

// IR receiver pin
const uint16_t kRecvPin = 35;

const uint16_t kCaptureBufferSize = 1024;
const uint8_t kTimeout = 15;  // Works well for non-AC signals
IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);

decode_results results;

// State: false = off, true = on
bool deviceState = true;


void setup() {
  Serial.begin(115200);
  delay(1000);

  // WiFi connect
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected.");
  Serial.println("IP address: " + WiFi.localIP().toString());

  // Start IR
  irrecv.enableIRIn();
  Serial.println("📡 IR Receiver ready on pin 35.");
}

void loop() {
  if (irrecv.decode(&results)) {
    // Print protocol info (shows MAGIQUEST, etc.)
    Serial.println(resultToHumanReadableBasic(&results));

    // Check if the protocol is MAGIQUEST
    if (results.decode_type == decode_type_t::MAGIQUEST) {
      Serial.println("🎯 MAGIQUEST wand detected!");

      // Toggle state
      deviceState = !deviceState;
      Serial.printf("Device state is now: %s\n", deviceState ? "ON" : "OFF");

      const char* endpoint = deviceState ? on_endpoint : off_endpoint;

      // Send HTTP request
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(endpoint);
        int httpCode = http.POST("");
        if (httpCode > 0) {
          Serial.printf("📡 HTTP Response: %d\n", httpCode);
        } else {
          Serial.printf("❌ HTTP Error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
      }

      delay(2000);  // debounce
    }

    irrecv.resume();  // Ready for next signal
  }

  delay(100);
}