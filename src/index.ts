import { SerialPort, ReadlineParser } from 'serialport';

const port = new SerialPort({
  path: '/dev/tty.usbserial-10', // 연결된 포트 경로
  baudRate: 9600, // 아두이노 보드레이트
});

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

port.on('open', () => {
  console.log('Serial Port Opened');

  // 3초마다 'T' 명령 전송
  setInterval(() => {
    const command = 'T\n'; // 토글 명령
    port.write(command); // 아두이노로 토글 명령 전송
    console.log(`Sent to Arduino: ${command.trim()}`);
  }, 3000); // 3000ms = 3초
});

parser.on('data', (data) => {
  console.log(`Received from Arduino: ${data}`);
});

port.on('error', (err) => {
  console.error('Error: ', err.message);
});
