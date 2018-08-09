void setup() {
  Serial.println("DHT11 Test");
}

void loop() {
  byte data[5] = {0};
  float T = 0.0, H = 0.0;
  int tmp;
  
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  delay(1);
  digitalWrite(4, LOW);
  delay(18);
  digitalWrite(4, HIGH);
  delayMicroseconds(40);
  
  pinMode(4, INPUT);

  if (digitalRead(4) == HIGH) { return; }

  delayMicroseconds(80);
  if (digitalRead(4) == LOW) { return; }

  delayMicroseconds(80);
  if (digitalRead(4) == HIGH) { return; }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 8; j++) {
      if (j < 7) {
        data[i] |= value();
        data[i] = data[i] << 1;
      } else { data[i] |= value(); }
    }
  }
  for (int i = 0; i < 4; i++) { tmp += data[i]; }

  if (data[4] == (tmp & 0xFF)) {
    H = data[0];
    T = data[2];
      
    Serial.print("Temperature: ");
    Serial.print(T);
    Serial.print(" ,Humidity: ");
    Serial.println(H);
  } else { Serial.println("Parity Error"); }

  delay(2000);
}

byte value() {
  byte va = 0;

  while (digitalRead(4) == LOW);

  delayMicroseconds(28);

  if (digitalRead(4) == HIGH) {
    va |= 1;
    while (digitalRead(4) == HIGH);
  }

  return va;
}
