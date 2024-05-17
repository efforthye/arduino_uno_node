int ledPin = 5; // 내장 LED 핀 번호

void setup() {
  Serial.begin(9600); // 시리얼 통신 시작
  pinMode(ledPin, OUTPUT); // LED 핀을 출력으로 설정
  Serial.println("Start from Arduino"); // 메시지 송신
}

void loop() {
  // 아두이노의 시리얼 버퍼에 수신된 데이터가 있는지 확인
  if (Serial.available() > 0) {
    char data = Serial.read(); // 데이터를 읽음
    Serial.print("Received: ");
    Serial.println(data);

    // 수신된 데이터에 따라 LED 제어
    if (data == 'H') {
      digitalWrite(ledPin, HIGH); // LED 켜기
    } else if (data == 'L') {
      digitalWrite(ledPin, LOW); // LED 끄기
    }
  }
  delay(100);
}
