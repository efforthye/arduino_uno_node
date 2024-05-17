void setup() {
  Serial.begin(9600); // 시리얼 통신 시작 (보드레이트(defaultBaudRate): 9600)
  Serial.println("Start from Arduino"); // 메시지 송신
}

void loop() {
  // 아두이노의 시리얼 버퍼에 수신된 데이터가 있는지 확인
  if (Serial.available() > 0) {
    int data = Serial.read();
    Serial.print("Received: ");
    Serial.println(data);
  }
  delay(100);
}