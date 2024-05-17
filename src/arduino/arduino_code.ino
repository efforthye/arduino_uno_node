void setup() {
  Serial.begin(9600); // 시리얼 통신 시작 (보드레이트(defaultBaudRate): 9600)
}

void loop() {
  Serial.println("Hello from Arduino");
  delay(1000); // 1초 대기
}

// void loop() {
//   if (Serial.available() > 0) {
//     int data = Serial.read();
//     Serial.print("Received: ");
//     Serial.println(data);
//   }
//   delay(100);
// }
