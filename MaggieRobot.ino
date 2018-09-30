#include "IRremote.h"

int receiver = 13;       // Signal Pin of IR receiver to Arduino Digital Pin 11
IRrecv irrecv(receiver); // create instance of 'irrecv'
decode_results results;  // create instance of 'decode_results'

// Right motor
const int rightMotor = 0;
const int pin_motor1en = 8;
const int pin_motor1fwd = 10;
const int pin_motor1rev = 9;

// Left motor
const int leftMotor = 1;
const int pin_motor2en = 4;
const int pin_motor2fwd = 6;
const int pin_motor2rev = 5;

const int pin_En[] = {pin_motor1en, pin_motor2en};
const int pin_Fwd[] = {pin_motor1fwd, pin_motor2fwd};
const int pin_Rev[] = {pin_motor1rev, pin_motor2rev};

const int motors = 2;

void setup()
{
    Serial.begin(9600);

    // Initialize all the motors and enable them.
    for (int i = 0; i < motors; i++)
    {
        pinMode(pin_En[i], OUTPUT);
        pinMode(pin_Fwd[i], OUTPUT);
        pinMode(pin_Rev[i], OUTPUT);
        digitalWrite(pin_En[i], true);
    }

    irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
        Serial.println("loop");
    if (irrecv.decode(&results)) // have we received an IR signal?

    {
        translateIR();
        irrecv.resume(); // receive the next value
    }

    delay(500);
}

void translateIR()
{
    Serial.println("translateIR");
    switch (results.value)

    {
    case 0xFFA25D:
        Serial.println("POWER");
        break;
    case 0xFFE21D:
        Serial.println("FUNC/STOP");
        break;
    case 0xFF629D:
        Serial.println("VOL+");
        CmdGoForward();
        break;
    case 0xFF22DD:
        Serial.println("FAST BACK");
        CmdGoRight();
        break;
    case 0xFF02FD:
        Serial.println("PAUSE");
        CmdStop();
        break;
    case 0xFFC23D:
        Serial.println("FAST FORWARD");
        CmdGoLeft();
        break;
    case 0xFFE01F:
        Serial.println("DOWN");
        break;
    case 0xFFA857:
        Serial.println("VOL-");
        CmdGoBackwards();
        break;
    case 0xFF906F:
        Serial.println("UP");
        break;
    case 0xFF9867:
        Serial.println("EQ");
        break;
    case 0xFFB04F:
        Serial.println("ST/REPT");
        break;
    case 0xFF6897:
        Serial.println("0");
        break;
    case 0xFF30CF:
        Serial.println("1");
        break;
    case 0xFF18E7:
        Serial.println("2");
        break;
    case 0xFF7A85:
        Serial.println("3");
        break;
    case 0xFF10EF:
        Serial.println("4");
        break;
    case 0xFF38C7:
        Serial.println("5");
        break;
    case 0xFF5AA5:
        Serial.println("6");
        break;
    case 0xFF42BD:
        Serial.println("7");
        break;
    case 0xFF4AB5:
        Serial.println("8");
        break;
    case 0xFF52AD:
        Serial.println("9");
        break;
    case 0xFFFFFFFF:
        Serial.println(" REPEAT");
        break;

    default:
        Serial.println(" other button   ");

    } // End Case
}

void SetMotorSpeed(int motor, int speed)
{
    speed = SanitizeSpeed(speed);

    if (speed > 0)
    {
        digitalWrite(pin_Rev[motor], false);
        digitalWrite(pin_Fwd[motor], true);
    }
    else if (speed < 0)
    {
        digitalWrite(pin_Fwd[motor], false);
        digitalWrite(pin_Rev[motor], true);
    }
    else
    {
        digitalWrite(pin_Fwd[motor], false);
        digitalWrite(pin_Rev[motor], false);
    }
}

int SanitizeSpeed(int speed)
{
    if (speed > 100)
    {
        speed = 100;
    };
    if (speed < -100)
    {
        speed = -100;
    };

    return speed;
}

void CmdGoForward()
{
    SetMotorSpeed(rightMotor, 100);
    SetMotorSpeed(leftMotor, 100);
}
void CmdGoBackwards()
{
    SetMotorSpeed(rightMotor, -100);
    SetMotorSpeed(leftMotor, -100);
}
void CmdGoLeft()
{
    SetMotorSpeed(rightMotor, 100);
    SetMotorSpeed(leftMotor, -100);
}
void CmdGoRight()
{
    SetMotorSpeed(rightMotor, -100);
    SetMotorSpeed(leftMotor, 100);
}
void CmdStop()
{
    SetMotorSpeed(rightMotor, 0);
    SetMotorSpeed(leftMotor, 0);
}