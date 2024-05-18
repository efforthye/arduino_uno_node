// TCS3200 핀 설정
int S0 = 8;
int S1 = 9;
int S2 = 10;
int S3 = 11;
int sensorOut = 4;

// 내장 LED 핀 번호
int ledPin = 5;

// 색상 측정값 저장 변수
int redFrequency = 0;
int blueFrequency = 0;

// 평균값 계산을 위한 배열과 변수
const int numReadings = 10;
int redReadings[numReadings]; // red 주파수 값 저장 배열
int blueReadings[numReadings]; // blue 주파수 값 저장 배열
int readIndex = 0; // 현재 읽기 인덱스
int totalRed = 0; // red 주파수 값 총합
int totalBlue = 0; // blue 주파수 값 총합

void setup() {
  pinMode(ledPin, OUTPUT); // LED 핀을 출력으로 설정
  Serial.begin(9600); // 시리얼 통신 시작
  Serial.println("Start from Arduino"); // 메시지 송신

  // TCS3200 핀을 출력으로 설정
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // 주파수 스케일링 설정 (S0 HIGH, S1 LOW -> 20%)
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // 배열 초기화
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    redReadings[thisReading] = 0;
    blueReadings[thisReading] = 0;
  }
}

void loop() {
  // 색상 감지 및 출력
  readColor();
  delay(200); // 0.2초 지연 (2초 동안 10번 읽기)
}

void readColor() {
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

  // 이전 값을 총합에서 빼기
  totalRed = totalRed - redReadings[readIndex];
  totalBlue = totalBlue - blueReadings[readIndex];

  // 새 값을 배열에 저장
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redReadings[readIndex] = pulseIn(sensorOut, LOW);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueReadings[readIndex] = pulseIn(sensorOut, LOW);

  // 새 값을 총합에 더하기
  totalRed = totalRed + redReadings[readIndex];
  totalBlue = totalBlue + blueReadings[readIndex];

  // 인덱스 증가
  readIndex = readIndex + 1;

  // 인덱스가 배열 크기를 초과하면 0으로 설정
  if (readIndex >= numReadings) {
    readIndex = 0;

    // 평균값 계산 및 출력
    int averageRed = totalRed / numReadings;
    int averageBlue = totalBlue / numReadings;

    if (averageRed < averageBlue) {
      Serial.println("Detected Color: RED");
    } else {
      Serial.println("Detected Color: BLUE");
    }
  }
  delay(100);
}
