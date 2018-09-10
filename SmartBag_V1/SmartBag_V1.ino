#define LIGHT_PIN   A0  //Analog pin for the onboard light sensor
#define BUTTON_PIN  4   //Digital pin for push button
#define MOTOR_PIN   5   //Digital MOSEFT-enabled pin for providing power to the motor
#define RED_PIN     8   //Digital pin for red LED
#define BUZZER_PIN  9   //DIgital pin for the onboard buzzer
#define GREEN_PIN   13  //Digital pin for green LED
#define BLUE_PIN    12  //Digital pin for blue LED
#define BATTERY_PIN A6  //Analog pin for monitoring voltage from the battery
#define SENSOR_PIN  A7  //Digital pin for the pressure sensor

#define LOW_VOLTAGE_S1 3.5  //First voltage stage for the battery
#define LOW_VOLTAGE_S2 3.3  //Second voltage stage for the battery
#define LOW_VOLTAGE_S3 3.1  //Third voltage stage for the battery

#define ANALOG_REF_TO_VOLTAGE(analogValue) ((analogValue) * 5 / 1023)

typedef enum WARNING_STATUS_T
{
  S0 = 0, //No warning
  S1 = 1, //Beeper off. 1 vibration at initialization
  S2 = 2, //Beeper notifies once at initialization. Vibrations every 10 minutes
  S3 = 3, //Beeper and vibrations every 5 minutes
  S4 = 4, //Beeper and vibrations every minute
  S5 = 5, //Beeper and Vibrations every second
  S_ARMED = 6
};

class Timer
{
public:

  Timer()
  {}
  ~Timer()
  {}

  void connect_Timer(Timer * new_Timer) {this->m_Timer = new_Timer;}

private:

  Timer * m_Timer;

}

class LEDControl
{
public:

  LEDControl()
  {}
  ~LEDControl()
  {}

  void connect_Timer(Timer * new_Timer) {this->m_Timer = new_Timer;}

private:

  Timer * m_Timer;
}

class LightControl
{
public:

  LightControl()
  {}
  ~LightControl()
  {}

  void connect_Timer(Timer * new_Timer) {this->m_Timer = new_Timer;}
  
private:

  Timer * m_Timer;
  
};

class BeeperControl
{
public:

  BeeperControl()
  {};
  ~BepperControl()
  {}

  void connect_Timer(Timer * new_Timer) {this->m_Timer = new_Timer;}

private:

  Timer * m_Timer;
  
};

class VibrationControl
{
public:

  VibrationControl()
  {}
  ~VibrationControl()
  {}

  void connect_Timer(Timer * new_Timer) {this->m_Timer = new_Timer;}

private:

  Timer * m_Timer;

};

class WarningControl
{
public:

  WarningControl()
  {
    this->m_Status = S3;
  }
  ~WarningControl()
  {}

  void connect_Timer(Timer * new_Timer)
  {
    this->m_Timer = new_Timer;

    m_LightControl.set_Timer(new_Timer);
    m_BeeperControl.set_Timer(new_Timer);
    m_VibrationControl.set_Timer(new_Timer);
  }
  
  
private:

  WARNING_STATUS_T m_Status;

  Timer * m_Timer;
  LightControl m_LightControl;
  BeeperControl m_BeeperControl;
  VibrationControl m_VibrationControl;
}

// Global Variables ///////////////////////////////////////////////////////////////////////



// Functions //////////////////////////////////////////////////////////////////////////////

void check_TimerOverflow()
{
  //Check to see if the millis counter has overflowed (should happen about every 50 days)
  if(_CurrentTime < _PreviousTime_FLAG)
  {
    _NextTime_LED = 0xFFFFFFFF - _NextTime_LED;
    _NextTime_Motor = 0xFFFFFFFF - _NextTime_Motor;
    _PreviousTime_FLAG = 0;
  }
}

void check_Batt()
{
  float battery_read = ANALOG_REF_TO_VOLTAGE(analogRead(BATTERY_PIN)); //Converts analogRead() value to standard volts

  if(battery_read > LOW_VOLTAGE_S1)
  {
    _Batt_Status = b0;
    _FLAG_Low_Batt = false;
  }
  else
  {
    if(battery_read > LOW_VOLTAGE_S2)
    {
      _Batt_Status = b1;
      _FLAG_Low_Batt = true;
    }
    else
    {
      _Batt_Status = b2;
    }

    _FLAG_Low_Batt = true;
  }

  _PreviousTime_FLAG = _CurrentTime;
}

void check_Sensor()
{
  bool sensor_read = digitalRead(SENSOR_PIN);
  
  if(sensor_read)
    _FLAG_Sensor = false;
  else
  {
    _FLAG_Sensor = true;
    _PreviousTime_FLAG = _CurrentTime;
  }
}

// Run Program ////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
  //Set up digital pins
  pinMode(BUTTON_PIN, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  digitalWrite(MOTOR_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  //Initialize analog reference to 3.3V default resolution
  analogReference(DEFAULT);
}

void loop() 
{
  //Grab current time and check to see if the millis() timer has overflown
  _CurrentTime = millis();
  check_TimerOverflow();

  //Check sensor and battery readings
  check_Batt();
  check_Sensor();

  //Update timing for the motor and LED
  
}
