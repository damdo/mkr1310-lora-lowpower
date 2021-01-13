#include <RTCZero.h>
#include <ArduinoLowPower.h>
#include <LoRa.h>

#define RTC_MATCH_SECOND 10

RTCZero rtc;
int counter = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  rtc.begin();
  // detach USB so the chip is asleep
  USBDevice.detach();
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);

  // wake up the LoRa chip
  if (!LoRa.begin(868E6)) {
    while (1);
  }

  // transmit packet
  LoRa.beginPacket();
  LoRa.print(counter);
  LoRa.endPacket();

  // put LoRa module to sleep
  LoRa.end();

  // put LoRa SPI pins to LOW
  // otherwise the LoRa module still pulls 8mA
  // even after the LoRa.end()
  digitalWrite(LORA_IRQ_DUMB, LOW);
  digitalWrite(LORA_BOOT0, LOW);
  digitalWrite(LORA_RESET, LOW);

  // also set those pins as INPUT
  // they were set as OUTPUT by LoRa.begin()
  // but they can be set back
  // to INPUT to reduce consumption by ~0.30mA
  pinMode(LORA_IRQ_DUMB, INPUT);
  pinMode(LORA_BOOT0, INPUT);
  pinMode(LORA_RESET, INPUT);

  digitalWrite(LED_BUILTIN, LOW);

  rtc.setAlarmSeconds(RTC_MATCH_SECOND);
  // match only seconds. In other words
  // a periodic alarm every minute,
  // at second RTC_MATCH_SECOND)
  rtc.enableAlarm(RTCZero::MATCH_SS);
  rtc.attachInterrupt(alarmMatch);

  LowPower.deepSleep();

  // waking up again here
  // and carrying on with the loop()
  counter++;
}

void alarmMatch()
{
  // this function is be called on
  // device wakeup and executed
  // in the interrupt context
}
