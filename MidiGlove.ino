/*
  Piezo Keyboard glove

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried & Becky Stern for Adafruit Industries.
  BSD license, all text above must be included in any redistribution

*/
const int indexFinger = A9; // the piezo is connected to analog pin 9 (aka D9)
const int middleFinger = A7; // the piezo is connected to analog pin 7 (aka D6)
const int thumb = A10; // the piezo is connected to analog pin 10 (aka D10)	
const int pinkyFinger = A11; // the piezo is connected to analog pin 11 (aka D12)

const int pins[] = {thumb, indexFinger, middleFinger, pinkyFinger};
String pinData[4]={"", "", "", ""};

char Keys[] =   {'s', 'd', 'a', 'f'};

boolean currentPressed[] = {false, false, false, false};

const int threshold = 90;  // threshold value to decide when the detected sound is a knock or not

void setup()
{
	//while (!Serial)
	Serial.begin(115200);
	Serial.println("start");
	Keyboard.begin();
}


void loop()
{
	for (int i = 0; i < 4; i++)
	{
		delay(1);
		long total1 = 0;
		long start = millis();
		long total =  analogRead(pins[i]);
		if (pinData[i] == "") {
			pinData[i] = (String)total;
		} else {
			pinData[i] = pinData[i] + " " + (String)total;
		}
		// check if we are sensing that a finger is touching
		// and that it wasnt already pressed
		if ((total > threshold) && (! currentPressed[i]))
		{
			Serial.print("Key pressed #");
			Serial.print(i);
			Serial.print(" (");
			Serial.print(Keys[i]);
			Serial.print(total);
			Serial.print(")" );
			Serial.println(pinData[i]);
			pinData[i] = "";
			currentPressed[i] = true;

			Keyboard.press(Keys[i]);
			
		}
		else if ((total <= threshold) && (currentPressed[i]))
		{
			// key was released (no touch, and it was pressed before)
			Serial.print("Key released #");
			Serial.print(i);
			Serial.print(" (");
			Serial.print(Keys[i]);
			Serial.print(total);
			Serial.print(")" );
			Serial.println(pinData[i]);
			pinData[i] = "";
			
			
			currentPressed[i] = false;

			Keyboard.release(Keys[i]);
		}

		delay(5);
	}
}
