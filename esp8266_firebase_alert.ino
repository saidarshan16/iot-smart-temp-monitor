#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <DHT.h>

/* ------------ WIFI ------------ */
#define WIFI_SSID "YOUR WIFI NAME"
#define WIFI_PASSWORD "YOUR WIFI PASSWORD"

/* ------------ FIREBASE ------------ */
#define API_KEY "YOUR FIREBASE API KEY"
#define DATABASE_URL "YOUR FIREBASE URL"

/* ------------ PINS ------------ */
#define DHTPIN D4
#define LED_PIN D2
#define BUZZER_PIN D1
#define DHTTYPE DHT11

#define TEMP_THRESHOLD 30   // °C

DHT dht(DHTPIN, DHTTYPE);

/* Firebase objects */
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;

/* ------------ SETUP ------------ */
void setup() {

  Serial.begin(115200);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();

  /* WiFi */
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nWiFi Connected!");
  Serial.println(WiFi.localIP());

  /* Firebase */
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase Auth OK");
    signupOK = true;
  } else {
    Serial.println("Firebase Auth Failed");
  }
}

/* ------------ LOOP ------------ */
void loop() {

  if (!signupOK) return;

  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT read failed");
    delay(2000);
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C | Humidity: ");
  Serial.println(hum);

  String status;

  /* ---------- ALERT LOGIC ---------- */
  if (temp > TEMP_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    status = "HIGH";
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    status = "NORMAL";
  }

  /* ---------- FIREBASE CURRENT DATA ---------- */

  Firebase.RTDB.setFloat(&fbdo,
    "/SmartFactoryNode1/temperature_current", temp);

  Firebase.RTDB.setString(&fbdo,
    "/SmartFactoryNode1/status", status);

  /* ---------- SHIFT HISTORY (20 VALUES) ---------- */

  for (int i = 20; i > 1; i--) {

    String prevPath = "/SmartFactoryNode1/history/" + String(i - 1);
    String newPath  = "/SmartFactoryNode1/history/" + String(i);

    float prevValue;

    if (Firebase.RTDB.getFloat(&fbdo, prevPath)) {
      prevValue = fbdo.floatData();
      Firebase.RTDB.setFloat(&fbdo, newPath, prevValue);
    }
  }

  // Insert newest temperature at history[1]
  Firebase.RTDB.setFloat(&fbdo,
    "/SmartFactoryNode1/history/1", temp);

  Serial.print("Status: ");
  Serial.println(status);
  Serial.println("----------------------");

  delay(3000);
}