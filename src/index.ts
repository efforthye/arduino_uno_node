import { SerialPort, ReadlineParser } from 'serialport';

const port = new SerialPort({
  path: '/dev/tty.usbserial-10',
  baudRate: 9600,
});

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

let ledState = false; // LED 상태를 저장할 변수

port.on('open', () => {
  console.log('Serial Port Opened');

  // 3초마다 LED 상태를 토글
  setInterval(() => {
    ledState = !ledState; // LED 상태 토글
    const command = ledState ? 'H\n' : 'L\n';
    port.write(command); // 아두이노로 명령 전송
    console.log(`Sent to Arduino: ${command.trim()}`);
  }, 1000); // 3000ms = 3초
});

parser.on('data', (data) => {
  console.log(`Received from Arduino: ${data}`);
});

port.on('error', (err) => {
  console.error('Error: ', err.message);
});
