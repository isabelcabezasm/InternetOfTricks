//RF Transmitter pin = digital pin 11
//Led de control
#define rfTransmitPin 11
//Onboard LED = digital pin 13
#define ledPin 13

// Pin “interruptor” 
// (si llega corriente, empieza la emisión)
int ibut = 10;

// El tiempo depende del color 
int tiempo = 4000;

int emitiendo = 0;

// Inicialmente está apagado
int estadoboton = 0;
int primeravez = 1;


// Configuración inicial del Sketch


void setup(){
pinMode(rfTransmitPin, OUTPUT);
pinMode(ledPin, OUTPUT);
pinMode(ibut, INPUT);
digitalWrite(ledPin, LOW);
}


void loop(){
if (emitiendo == 0 && primeravez <= 1) {
if (digitalRead(ibut) == HIGH) {
emitiendo = 1;
primeravez = 0;
digitalWrite(ledPin, HIGH); //Transmit a HIGH signal
analogWrite(rfTransmitPin, 1200); 
delay(tiempo); //Wait for 1 second
analogWrite(rfTransmitPin, LOW);
digitalWrite(ledPin, LOW); //Turn the LED off
emitiendo = 0;
}
}
}

