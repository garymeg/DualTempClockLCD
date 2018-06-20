#include <LiquidCrystal_I2C.h>
#include "Seeed_BME280.h"
#include <Wire.h>
#include "RTClib.h"
#include "DHT.h"
#include <OneWire.h>
#include <DS18B20.h>

#define DSPin 6 // Pin For DS18b20 input

LiquidCrystal_I2C lcd(0x27, 20, 4);
RTC_DS3231 rtc;
BME280 bme280;
DS18B20 ds(DSPin);


char daysOfTheWeek[7][12] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
// Address of the device.
uint8_t address[] = { 40, 250, 31, 218, 4, 0, 0, 52 };

// Indicates if the device was successfully selected.
uint8_t selected;

void Clock();
void ds18b20();
void getBME();

void setup() {
	selected = ds.select(address);

	Serial.begin(9600);
	if (!bme280.init()) {
		Serial.println("Device error!");
	}


	Serial.begin(9600);         // initializes the Serial connection @ 9600 baud

	lcd.init();                      // initialize the lcd 
	lcd.init();
	// Print a message to the LCD.
	lcd.backlight();

	if (!rtc.begin()) {
		Serial.println("Couldn't find RTC");
		while (1);
	}
			// following line sets the RTC to the date & time this sketch was compiled
			// uncomment if you want to set clock dont forget to comment out and
			// re-compile or clock will be reset every time arduino restarted
	//rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
			 
			// or uncomment to sets the RTC with an explicit date & time, for example to set
			// January 21, 2014 at 3am you would call:
	// rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

};

// run loop (forever)
void loop() {
	Clock();
	ds18b20();
	getBME();

};


void Clock() {
	DateTime now = rtc.now();

	for (int x = 0; x < 20; x = x + 1) {
		int hours = now.hour();                           // initialize hours
		int minutes = now.minute();                           // initialize minutes
		int seconds = now.second();
		int day = now.day();
		int month = now.month();
		int year = now.year();


		lcd.setCursor(0, 0);
		String line1;
		if (hours < 10) line1 += ("0");
		line1 += String(hours) + ":";
		if (minutes < 10) line1 += ("0");
		line1 += String(minutes) + ":";
		if (seconds < 10) line1 += ("0");
		line1 += String(seconds);
		lcd.print(line1);
		lcd.setCursor(10, 0);
		line1 = "";
		if (day < 10) line1 += ("0");
		line1 += String(day) + "/";
		if (month < 10) line1 += ("0");
		line1 += String(month) + "/";
		if (year < 10) line1 += ("0");
		line1 += String(year); lcd.print(line1);


	}

}
void ds18b20() {
	float t = ds.getTempC();
	int temp = int(t);
	String TEMP = String(temp);
	TEMP += " C ";

	lcd.setCursor(0, 3);
	String line4 = "";
	line4 = "O " + String(t) + char(0xdf) + "C ";
	lcd.print(line4);


}

void getBME() {
	float pressure;

	//get and print temperatures

	float t = (bme280.getTemperature());
	float p = (pressure = bme280.getPressure()) / 100;
	float a = (bme280.calcAltitude(pressure));
	float h = (bme280.getHumidity());






	int temp = int(t);
	int humi = int(h);
	int presu = int(p);
	int alti = int(a);


	lcd.setCursor(10, 3);
	String line2 = "";
	line2 = " I " + String(t) + char(0xdf) + "C ";
	lcd.print(line2);

	lcd.setCursor(0, 1);
	line2 = "";
	line2 = "  Humidity  " + String(int(h)) + " %Rh ";
	lcd.print(line2);
	lcd.setCursor(0, 2);
	String line3 = "";
	line3 = "";
	line3 = " Pressure " + String(int(p)) + " Mbar ";
	lcd.print(line3);




}