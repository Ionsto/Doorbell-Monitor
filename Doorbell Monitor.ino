
void setup()
{
	pinMode(13, OUTPUT);
	Serial.begin(9600);
}
uint32_t TimerStart = 0;
uint32_t TimerMax = 5000;
bool DoorBellOn = false;
uint8_t PINSTATE = 0;
uint8_t buffer[1500];
uint32_t OnThreshold = 200;
void UpdateDetector()
{
	uint32_t SumVal = 0;
	for (int i = 0; i < 2048; ++i)
	{
		SumVal += analogRead(0);
	}
	SumVal >>= 11;
	//Serial.println(SumVal);
	if (SumVal > OnThreshold)
	{
		DoorBellOn = true;
		TimerStart = millis();
		Serial.println("Doorbell!");
	}
}
void UpdateLED()
{
	uint32_t delta = millis() - TimerStart;
	if (delta < TimerMax)
	{
		//Miliseconds elapsed/128 
		uint8_t value = ((delta >> 7) & 1)*HIGH;
		digitalWrite(13, value);
	}
	else
	{
		DoorBellOn = false;
		digitalWrite(13, LOW);
	}
}
void loop()
{
	///13mhz
	if (DoorBellOn)
	{
		UpdateLED();
	}
	else
	{
		UpdateDetector();
	}
}
