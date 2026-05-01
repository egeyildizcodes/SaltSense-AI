#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

void setup() {
  Serial.begin(115200);
  dac.begin(0x60);
}

void loop() {
  // simple waveform test
  for (int i = 0; i < 4095; i += 10) {
    dac.setVoltage(i, false);
    delay(2);
  }
}
