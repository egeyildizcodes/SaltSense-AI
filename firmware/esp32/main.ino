/*
  SaltSense AI - ESP32 Demonstration Firmware

  This file is intentionally simulation-first. It demonstrates Bluetooth
  commands, profile selection, sensor placeholders, heater/fan placeholders,
  and a virtual waveform model without driving a human-contact output.

  The project is a research prototype. Hardware output stages must be reviewed,
  measured, isolated, and approved before any real-world testing.
*/

#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

struct Profile {
  const char* name;
  int intensity;
  int thermalBias;
  int aromaBias;
  int textureBias;
};

Profile profiles[] = {
  {"SOFT", 20, 10, 10, 5},
  {"MEDIUM", 45, 20, 20, 10},
  {"STRONG", 70, 30, 30, 15},
  {"UMAMI", 50, 15, 45, 20},
  {"COLD_FOOD", 55, 40, 25, 10},
  {"LOW_SODIUM", 60, 25, 35, 20}
};

const int PROFILE_COUNT = sizeof(profiles) / sizeof(profiles[0]);
int activeProfile = 0;
bool armed = false;
bool running = false;

unsigned long lastStatus = 0;

void sendLine(const String& msg) {
  Serial.println(msg);
  if (SerialBT.hasClient()) {
    SerialBT.println(msg);
  }
}

int estimateTasteScore(const Profile& p, int hydration, int activity, int foodTemp) {
  int score = p.intensity;
  score += activity / 8;
  score -= max(0, 60 - hydration) / 6;
  score += (foodTemp < 30) ? 10 : 0;
  score += p.aromaBias / 3;
  score += p.textureBias / 2;
  return constrain(score, 0, 100);
}

void printStatus() {
  Profile& p = profiles[activeProfile];

  // Placeholder values. In a final build these would come from sensors/app data.
  int hydrationScore = 70;
  int activityScore = 35;
  int foodTempC = 32;
  int tasteScore = estimateTasteScore(p, hydrationScore, activityScore, foodTempC);

  sendLine("--- SaltSense AI Status ---");
  sendLine("armed=" + String(armed ? "true" : "false"));
  sendLine("running=" + String(running ? "true" : "false"));
  sendLine("profile=" + String(p.name));
  sendLine("estimatedTasteScore=" + String(tasteScore));
  sendLine("thermalBias=" + String(p.thermalBias));
  sendLine("aromaBias=" + String(p.aromaBias));
  sendLine("textureBias=" + String(p.textureBias));
  sendLine("mode=SIMULATION_ONLY");
}

void printHelp() {
  sendLine("Commands:");
  sendLine("HELP");
  sendLine("STATUS");
  sendLine("ARM");
  sendLine("DISARM");
  sendLine("START");
  sendLine("STOP");
  sendLine("PROFILE SOFT");
  sendLine("PROFILE MEDIUM");
  sendLine("PROFILE STRONG");
  sendLine("PROFILE UMAMI");
  sendLine("PROFILE COLD_FOOD");
  sendLine("PROFILE LOW_SODIUM");
}

void setProfile(String name) {
  name.trim();
  name.toUpperCase();

  for (int i = 0; i < PROFILE_COUNT; i++) {
    if (name == profiles[i].name) {
      activeProfile = i;
      sendLine("profileSet=" + String(profiles[i].name));
      return;
    }
  }
  sendLine("error=unknownProfile");
}

void handleCommand(String cmd) {
  cmd.trim();
  String upper = cmd;
  upper.toUpperCase();

  if (upper == "HELP") {
    printHelp();
  } else if (upper == "STATUS") {
    printStatus();
  } else if (upper == "ARM") {
    armed = true;
    sendLine("armed=true");
  } else if (upper == "DISARM") {
    armed = false;
    running = false;
    sendLine("armed=false running=false");
  } else if (upper == "START") {
    if (!armed) {
      sendLine("error=notArmed");
      return;
    }
    running = true;
    sendLine("running=true");
  } else if (upper == "STOP") {
    running = false;
    sendLine("running=false");
  } else if (upper.startsWith("PROFILE ")) {
    setProfile(cmd.substring(8));
  } else {
    sendLine("error=unknownCommand");
  }
}

void pollInputs() {
  if (Serial.available()) {
    handleCommand(Serial.readStringUntil('\n'));
  }
  if (SerialBT.available()) {
    handleCommand(SerialBT.readStringUntil('\n'));
  }
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("SaltSense-AI");
  delay(300);

  sendLine("SaltSense AI simulation firmware booted.");
  sendLine("No human-contact output is driven by this firmware.");
  printHelp();
}

void loop() {
  pollInputs();

  if (millis() - lastStatus > 5000) {
    lastStatus = millis();
    if (running) {
      printStatus();
    }
  }

  delay(20);
}
