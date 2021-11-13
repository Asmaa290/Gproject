
#include<AFMotor.h>
#include<SoftwareSerial.h>// soft serial port header file
long RX = A0;
long TX = A1;
long redLed = A2;
long blueLed = A3;
long buzzer = A4;
int dist;// LiDAR actually measured distance value
int strength;// LiDAR signal strength
int check;// check numerical value storage
int i;
int speed ;
int uart[9];// store data measured by LiDAR
const int HEADER = 0x59; // data package frame header
String data;
SoftwareSerial mySerial(RX, TX);


AF_DCMotor Motor1(1, MOTOR12_1KHZ);
AF_DCMotor Motor2(2, MOTOR12_1KHZ);
AF_DCMotor Motor3(3, MOTOR34_1KHZ);
AF_DCMotor Motor4(4, MOTOR34_1KHZ);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //معدل نقل البيانات bit rate
  mySerial.begin(115200);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  speed = 120;
}

void loop()
{
  noTone(buzzer);
  Motor1.setSpeed(speed);
  Motor1.run(FORWARD);
  Motor2.setSpeed(speed);
  Motor2.run(FORWARD);
  Motor3.setSpeed(speed);
  Motor3.run(FORWARD);
  Motor4.setSpeed(speed);
  Motor4.run(FORWARD);

  if (mySerial.available())//check whether the serial port has data input
  {
    if (mySerial.read() == HEADER) // determine data package frame header 0x59
    {
      uart[0] = HEADER;
      if (mySerial.read() == HEADER) //determine data package frame header 0x59
      {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) // store data to array
        {
          uart[i] = mySerial.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff)) // check the received data as per protocols
        {
          dist = uart[2] + uart[3] * 256; // calculate distance value
          strength = uart[4] + uart[5] * 256; // calculate signal strength value
          Serial.print("dist = ");
          Serial.print(dist);// output LiDAR tests distance value

          Serial.print('\t');
          Serial.print("strength = ");
          Serial.print(strength);// output signal strength value
          Serial.print('\n');
        }
      }
    }
  }
  //bi direction communication
  if (Serial.available() > 0)
  {
    Serial.print(dist);//WRITE
    data = Serial.readStringUntil('\n'); // READ
  }
  if (data == "A")
  {
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, LOW);
    speed = 120;
  }
  else if (data == "B")  {
    digitalWrite(blueLed, HIGH); // turn the LED on (HIGH is the voltage level)
  }
  else if ( data == "C")  {
    digitalWrite(blueLed, LOW);
    digitalWrite(redLed, HIGH);
    speed = 50;
    //Generates a square wave of the specified frequency, tone(pin, frequency),1000=frequency
    tone(buzzer, 1000);
  }
  else if ( data == "D")   {
    digitalWrite(blueLed, LOW);
    digitalWrite(redLed, HIGH);
    speed = 0;
    tone(buzzer, 2000);
  }
}
