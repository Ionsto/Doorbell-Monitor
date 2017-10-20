
void setup()
{
	pinMode(13, OUTPUT);
}
uint8_t PINSTATE = 0;
uint8_t buffer[1500];
void loop()
{
	PINSTATE ^= 1;
	digitalWrite(13, PINSTATE);
	for (int i = 0; i < 1500; ++i)
	{
		buffer[i] = analogRead(0);
	}
	for (int i = 0; i < 1500; ++i)
	{
		Serial.print(buffer[i]);
		Serial.print("\n");
	}
}
