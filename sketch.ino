#define TURBIDITY 34
#define TDS 35
#define PH 32

void setup() {
  Serial.begin(115200);
}

void loop() {
  int rawTds  = analogRead(TDS);
  int rawPh   = analogRead(PH);
  int rawTurb = analogRead(TURBIDITY);

  // Direct reverse of chip math — no voltage step needed
  float mappedPh   = rawPh   * (14.0   / 4095.0);  // 0 - 14
  float mappedTds  = rawTds  * (1000.0 / 4095.0);  // 0 - 1000 ppm
  float mappedTurb = rawTurb * (3000.0 / 4095.0);  // 0 - 3000 NTU

  Serial.print("TDS: ");
  Serial.print((int)round(mappedTds));
  Serial.print(" ppm  |  pH: ");
  Serial.print((int)round(mappedPh));
  Serial.print("  |  Turbidity: ");
  Serial.print((int)round(mappedTurb));
  Serial.println(" NTU");

  delay(1000);
}