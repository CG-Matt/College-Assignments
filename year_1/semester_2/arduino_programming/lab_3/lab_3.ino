// constants won't change. They're used here to set pin numbers:
const int sensorPin = A0; // the number of the sensor pin
// variables will change:
float sensorValue = 0; // variable for reading the sensor value
const int numr = 100;
float reads[numr];
int index = 0;
float total = 0;
float avg = 0;

void setup() {
  // initialize the sensor pin as an input:
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  for(int i = 0; i < numr; i++)
  {
    reads[i] = 0;
  }
}

void loop()
{
  // Recalculate total without summing all values
  total -= reads[index];
  sensorValue = analogRead(sensorPin);
  reads[index] = sensorValue;
  total += reads[index];
  index++;
  // Once we have gathered enough samples calculate the average
  if(index >= numr)
  {
    index = 0;        // Reset index
    avg = total/numr; // Calculate average
    float voltage = 5*sensorValue/1024.0; // Calculate current voltage from ADC value
    float smooth_volavge = 5*avg/1024.0;  // Calculate average voltage
    Serial.print(smooth_volavge); // Print the smooth voltage (Value 1)
    Serial.print(",");
    Serial.println(voltage);  // Print the raw voltage (Value 2)
    delay(10);
  }
}