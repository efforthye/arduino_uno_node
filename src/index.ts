import { SerialPort, ReadlineParser } from 'serialport';

const port = new SerialPort({
  path: '/dev/tty.usbserial-10', // 아두이노가 연결된 포트 경로로 변경
  baudRate: 9600,
});

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

port.on('open', () => {
  console.log('Serial Port Opened');
  port.write('Hello from Node.js!\n');
});

parser.on('data', (data) => {
  console.log(`Received from Arduino: ${data}`);
});

port.on('error', (err) => {
  console.error('Error: ', err.message);
});