void cetakjarak () {
  Serial.print("jarak ");
  Serial.print(ultraSensor);
  Serial.print("\t");
  //lcd.setCursor(0, 0);
  //lcd.print("jarak ");
  //lcd.setCursor(6, 0);
  //lcd.print(ultraSensor);
  //lcd.print("    ");
  //lcd.setCursor(10, 0);
  //lcd.print("cm");
}
void cetakVolume () {
  Serial.print("volume liter ");
  Serial.print(volumeL);
  Serial.print("\t");
  Serial.print("volume cm3 ");
  Serial.println(volume);
  lcd.setCursor(0, 0);
  lcd.print("Volume");
  lcd.setCursor(0, 1);
  lcd.print(volumeL);
  lcd.print("    ");
  lcd.setCursor(15, 1);
  lcd.print("L");
}
void penuh() {
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(1, HIGH);
}

void empatbar() {
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(1, LOW);
}
void tigabar() {
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(1, LOW);
}
void duabar() {
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  digitalWrite(1, LOW);
}
void satubar() {
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  digitalWrite(1, LOW);
  //digitalWrite(6, LOW);
 
  delay(500);
  digitalWrite(1, LOW);
  delay(500);
}

