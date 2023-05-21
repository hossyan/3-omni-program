#include <Arduino.h>
#include <PS4BT.h>
#include <usbhub.h>

#ifdef dobogusinclude
#endif
#include <SPI.h>

USB Usb;
BTD Btd(&Usb);

PS4BT PS4(&Btd, PAIR);

int mo1 = 0;
int mo2 = 0;
int mo3 = 0;

#define mopin1 5;
#define mopin2 6;
#define mopin3 7;

void setup()
{
  Serial.begin(9600);
#if !defined(__MIPSEL__)
  while (!Serial)
    ; // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1)
  {
    Serial.print(F("\r\nOSC did not start"));
    while (1)
      ; // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}

void loop()
{
  Usb.Task();
  if (PS4.connected())
  {
    if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117)
    {
      mo1 = abs(PS4.getAnalogHat(LeftHatX) - 127) / 127 * 200;
      mo2 = (1 / 2 * abs(PS4.getAnalogHat(LeftHatX) - 127) - sqrt(3) / 2 * abs(PS4.getAnalogHat(LeftHatY) - 127)) * 200;
      mo3 = (1 / 2 * abs(PS4.getAnalogHat(LeftHatX) - 127) + sqrt(3) / 2 * abs(PS4.getAnalogHat(LeftHatY) - 127)) * 200;

      Serial.print("mo1:");
      Serial.print(mo1);
      Serial.print("mo2:");
      Serial.print(mo2);
      Serial.print("mo2:");
      Serial.print(mo2);

      analogWrite(mopin1, mo1);
      analogWrite(mopin2, mo2);
      analogWrite(mopin3, mo3);
    }
  }
}