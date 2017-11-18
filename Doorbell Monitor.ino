
void setup()
{
	pinMode(13, OUTPUT);
	Serial.begin(9600);
}
uint32_t TimerStart = 0;
uint32_t TimerMax = 5000;
bool DoorBellOn = false;
uint8_t PINSTATE = 0;
uint8_t CountAboveThreshold = 0;
uint32_t OnThreshold = 400;
void UpdateDetector()
{
	uint32_t SumVal = 0;
	for (int i = 0; i < 4096; ++i)
	{
		int val = analogRead(0);
		SumVal += val;
	}
	SumVal >>= 11;
	//Serial.println(SumVal);
	if (SumVal > OnThreshold)
	{
		CountAboveThreshold += 1;
	}
	else
	{
		//It's around 4/5 seconds
		if (abs(CountAboveThreshold - 5) < 2)
		{
			DoorBellOn = true;
			TimerStart = millis();
			Serial.print("Doorbell!");
			Serial.println(SumVal);
		}
		CountAboveThreshold = 0;
	}
}
void Logger()
{
	uint32_t SumVal = 0;
	for (int i = 0; i < 4096; ++i)
	{
		int val = analogRead(0);
		SumVal += val;
	}
	SumVal >>= 11;
	Serial.println(SumVal);
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
	if (DoorBellOn)
	{
		UpdateLED();
	}
	else
	{
		UpdateDetector();
		//Logger();
	}
}
