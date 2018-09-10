#define LIGHT_PIN   A0  //Analog pin for the onboard light sensor
#define BUTTON_PIN  4   //Digital pin for push button
#define MOTOR_PIN   5   //Digital MOSEFT-enabled pin for providing power to the motor
#define RED_PIN     8   //Digital pin for red LED
#define BUZZER_PIN  9   //DIgital pin for the onboard buzzer
#define GREEN_PIN   13  //Digital pin for green LED
#define BLUE_PIN    12  //Digital pin for blue LED
#define BATTERY_PIN A6  //Analog pin for monitoring voltage from the battery
#define SENSOR_PIN  A7   //Digital pin for the pressure sensor

#define LOW_VOLTAGE_S1 3.5  //First voltage stage for the battery
#define LOW_VOLTAGE_S2 3.3  //Second voltage stage for the battery

#define ANALOG_REF_TO_VOLTAGE(analogValue) ((analogValue) * 3.3 / 1023)

volatile int analog_raw = 0;
volatile float voltage = 0;

void setup() 
{
  Serial.begin(9600);

  //Initialize pins
  pinMode(MOTOR_PIN, OUTPUT);

  //Set pins
  digitalWrite(MOTOR_PIN, LOW);
  
  //Initialize analog reference to 3.3V default resolution
  analogReference(DEFAULT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  analog_raw = analogRead(SENSOR_PIN);
  voltage = ANALOG_REF_TO_VOLTAGE(analog_raw);

  Serial.print("analogRead: "); 
  Serial.print(analog_raw);
  Serial.print(" Voltage: "); 
  Serial.print(voltage);
  Serial.println("V"); 

  if(voltage > 3.25)
    digitalWrite(MOTOR_PIN, HIGH);
  else
    digitalWrite(MOTOR_PIN, LOW);
}