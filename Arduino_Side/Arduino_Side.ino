int caStartByte = 36; // Packet start byte from comp to arduino
int acStartByte = 64; // Packet start byte from arduino to comp
int caSerialEndByte = 255; // Byte to stop serial stream

char inBuffer[3]; // Buffer of packets from comp to arduino
char outBuffer[4]; // Buffer of packets from arduino to comp

int caCounted = 0;

int baudRate = 9600;

int compByte = 0;

byte dRead[32];
byte aRead[32];

byte drBufferPull = 0;
byte drBufferPush = 0;

byte arBufferPull = 0;
byte arBufferPush = 0;

boolean listenDigital[54];
boolean listenAnalog[16];

byte listenDPriority[54];
byte listenAPriority[16];

byte serialForward = -1;

void setup() {
  Serial.begin(baudRate);
}

void loop() {
  if(Serial.available()) {
    compByte = Serial.read();
    if(serialForward != -1) {
      if(compByte = caSerialEndByte) {
        serialForward = -1;
        continue;
      }
      switch(serialForward) {
        case 0:
          Serial.write(compByte);
          break;
        case 1:
          Serial1.write(compByte);
          break;
        case 2:
          Serial2.write(compByte);
          break;
        case 3:
          Serial3.write(compByte);
          break;
      }
      continue;
    }
    if(compByte == caStartByte) {
      Serial.readBytes(inBuffer, 3);
      execute(inBuffer);
    }
  }
}

void execute(char packet[3]) {
  byte pin = ((byte)(packet[0])) & 01111111;
  boolean digital = (((byte)packet[0]) & 10000000) >> 7;
  
  switch((int) packet[1]) {
    case 0: // Add to read buffer
      if(digital) {
        dRead[drBufferPush] = pin;
        drBufferPush++;
      } else {
        aRead[arBufferPush] = pin;
        arBufferPush++;
      }
      break;
    case 1: // Write
      if(digital) {
        digitalWrite(pin, ((byte)(packet[2]) & 00000001));
      } else {
        analogWrite(pin, packet[2]);
      }
      break;
    case 2: // Serial it
    
    case 3: // Define as input
      if(digital) {
        pinMode(pin, INPUT);
      }
      break;
    case 4: // Define as output
      if(digital) {
        pinMode(pin, OUTPUT);
      }
      break'
    case 5: // Add to the listener array
      if(digital) {
        if(packet[2] == 0) {
          listenDigital[pin] = false;
        } else {
          listenDigital[pin] = true;
        }
      } else {
        if(packet[2] == 0) {
          listenAnalog[pin] = false;
        } else {
          listenAnalog[pin] = true;
        }
      }
      break;
    case 6: // Set Priority
      if(digital) {
        listenDPriority[pin] = packet[2];
      } else {
        listenAPriority[pin] = packet[2];
      }
      break;
  }
}
