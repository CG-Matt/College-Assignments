int sensor_value = 0;

// Define which physical pins are to be used
#define LED_PIN     PIN2
#define SENSOR_PIN  A7
#define VREF        5.0

void setup() {
  Serial.begin(9600);
  // Initialise the required pins for operation
  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
}

inline float calc_voltage(int sensor_value)
{
  return (VREF * sensor_value) / 1024;
}

void loop() {
  // Read value from the sensor
  sensor_value = analogRead(SENSOR_PIN);
  Serial.print("The sensor reading was - ");
  Serial.print(sensor_value);
  Serial.print(", ");
  Serial.print(calc_voltage(sensor_value));
  Serial.println("V");
  // Turn the LED ON
  digitalWrite(LED_PIN, HIGH);
  // The delay depends on the value read in from the sensor
  delay(sensor_value);
  // Turn the LED OFF
  digitalWrite(LED_PIN,LOW);
  // The delay depends on the value read in from the sensor
  delay(sensor_value);
}
