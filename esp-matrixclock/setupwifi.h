/*
 * Setupwifi for ESP2866 Arduino
 * code by William Moeur
 */

#define maxSSIDlength 20
#define maxPASSlength 40

// prototypes
void readLine(char buffer[], uint8_t size);
bool startWiFi(void);

// serial IO
void readLine(char buffer[], uint8_t size)
{
	uint8_t i = 0;
	char c;

	do {
		while (!Serial.available()){yield();} // wait for input
		c = Serial.read();
		Serial.write(c); // echo characters back to user.
		if (c == '\r') break;
		if (c != '\n')
			buffer[i++] = c;      
	} while (i < size-1);
	buffer[i] = '\0';
}

// wifi functions
bool startWiFi(void)
{
	uint8_t i;
	// check for persistent wifi connection
	for (i=0;i<10;i++){
		if (WiFi.status() == WL_CONNECTED) return true;
		delay(500);
		Serial.print(".");
	}

	/* didn't work: so ask user to enter credentials over Serial Port */
	char ssid[maxSSIDlength];
	char pass[maxPASSlength];

	// prompt the user for his ssid

	Serial.print("Enter ssid name: ");
	readLine(ssid, maxSSIDlength);
	Serial.println();
	Serial.print("Enter pass phrase: ");
	readLine(pass, maxPASSlength);
	Serial.println();

	Serial.print("Attempting to Connect");
	if (WiFi.begin(ssid, pass) != WL_CONNECTED) {
		for (i=0;i<10;i++){
			if (WiFi.status() == WL_CONNECTED) return true;
			delay(500);
			Serial.print(".");
		}
	}
	Serial.print("Failed to connect to: ");
	Serial.println(ssid);

	Serial.print("using pass phrase: ");
	Serial.println(pass);

	return false;
}
