// Pins
const int TRIG_PIN = 7;
const int ECHO_PIN = 8;

// Variables
int cm;
int inches;
unsigned long t1;
unsigned long t2;
unsigned long pulse_width;

// Distance variables
const unsigned int MAX_DIST = 3190; // Anything over 55 cm (3190 us pulse) is "out of stock"
const unsigned int GOOD_DIST = 520;
const unsigned int MED_DIST = 990;
const unsigned int LOW_DIST = 2030;

void setup() 
{
  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  // Use the serial monitor to view the sensor output with 9600 baud
  Serial.begin(9600);
  Serial.println(" DragonBoard is up and running ");
}

void loop() 
{
  measuring();
  delay(500);
  distance_check_good();
  delay(500);
  distance_check_medium();
  delay(500);
  distance_check_low();
  delay(500);
  distance_check_zero();
  delay(500);
  distance_check_out();
  delay(500);
}

void measuring()
{
  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed 
  // of sound in air at sea level (~340 m/s).
  cm = pulse_width / 58.0;
  inches = pulse_width / 148.0;
}

void distance_check_good()
{
  //Print out results good on stock
  if ( pulse_width <= GOOD_DIST ) 
  {
    Serial.print(cm);
    Serial.print(" cm \t");
    Serial.print(inches);
    Serial.println(" in"); 
    Serial.println(" Stock status: Good ");
  } 
  else
  {
    Serial.print(" .. " )
  }
  // Wait at least 60ms before next measurement
  delay(60);
}

void distance_check_medium()
{
  // Print out results medium on stock
  if ( pulse_width <= MED_DIST ) 
  {
    Serial.print(cm);
    Serial.print(" cm \t");
    Serial.print(inches);
    Serial.println(" in"); 
    Serial.println(" Stock status: Medium ");
  } 
  else
  {
    Serial.print(" .. " )
  }
  // Wait at least 60ms before next measurement
  delay(60);
}

void distance_check_low()
{
  // Print out results low on stock
  if ( pulse_width <= LOW_DIST ) 
  {
    Serial.print(cm);
    Serial.print(" cm \t");
    Serial.print(inches);
    Serial.println(" in"); 
    Serial.println(" Stock status: Low ");
  } 
  else
  {
    Serial.print(" .. " )
  }
  // Wait at least 60ms before next measurement
  delay(60);
}

void distance_check_out()
{
  // Print out results low on stock
  if ( pulse_width <= MAX_DIST ) 
  {
    Serial.print(cm);
    Serial.print(" cm \t");
    Serial.print(inches);
    Serial.println(" in"); 
    Serial.println(" Stock status: Low ");
  } 
  else
  {
    Serial.print(" .. " )
  }
  // Wait at least 60ms before next measurement
  delay(60);
}
