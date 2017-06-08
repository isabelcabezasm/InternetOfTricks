// Main.cpp : Defines the entry point for the console application.
//
//#include <cpprest/http_client.h>
//#include <cpprest/filestream.h>
#include "stdafx.h"
#include "arduino.h"
#include "wchar.h"
#include <Windows.h>
#include <ostream>
#include <sstream>
#include <string>

#define rfReceivePin A0  //RF Receiver pin = Analog pin 0
#define ledPin 13        //Onboard LED = digital pin 13

unsigned int data = 0;   // variable used to store received data
const unsigned int upperThreshold = 900;  //upper threshold value
const unsigned int lowerThreshold = 500;  //lower threshold value
TCHAR debugOutput[256];
int tiempoMuestra = 500;
int potenciaAnalogica = 0;
int potenciaDigital_old = 0;
int potenciaDigital = 0;
int potenciaMuestra = 3;
int midiendo = 0;
unsigned long timeIni;
unsigned long timeFin;
int color = 0;


int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}



void setup()
{
    // TODO: Add your code here
	//pinMode(led, OUTPUT);       // Configure the pin for OUTPUT so you can turn on the LED.
	pinMode(ledPin, OUTPUT);
	Serial.begin(9600);
	timeIni = millis();
}

// the loop routine runs over and over again forever:
void loop()
{
	data = analogRead(rfReceivePin);    //listen for data on Analog pin 0
	if (data >= lowerThreshold)
	{
		digitalWrite(ledPin, HIGH);   //If a LOW signal is received, turn LED OFF
		potenciaAnalogica++;
	}

	if (millis() - timeIni > tiempoMuestra)
	{
		timeIni = millis();
		if (potenciaAnalogica > potenciaMuestra)
		{
			potenciaDigital++;
		}
		else
		{
			if (potenciaDigital > 1 && potenciaDigital < 4)
			{
				color = 1; // RED
			}
			else if(potenciaDigital > 3 && potenciaDigital < 6)
			{
				color = 2; // GREEN
			}
			else if (potenciaDigital > 5 && potenciaDigital < 8)
			{
				color = 3; // BLUE
			}
			else if (potenciaDigital > 7)
			{
				color = 4; // YELLOW
			}
			potenciaDigital = 0;
		}
		potenciaAnalogica = 0;
	}

	if (potenciaDigital_old != potenciaDigital)
		{
			swprintf(debugOutput, _T("Potencia %d.\n "), potenciaDigital);
			OutputDebugString(debugOutput);
			potenciaDigital_old = potenciaDigital;
		}
	
	if (color != 0)
	{
		//enviarcolor
		color = 0;
	/*	web::http::client::http_client client(U("http://internetoftricks.azurewebsites.net"));
		web::http::uri_builder builder(U("/api/color"));
		client.request(web::http::methods::POST, builder.to_string(), L"{Color:'naranja'}", L"application/json");
*/
	}

	digitalWrite(ledPin, LOW);   //If a HIGH signal is received, turn LED ON
	
}