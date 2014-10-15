int caStartByte = 36; // Packet start byte from comp to arduino
int acStartByte = 64; // Packet start byte from arduino to comp

char inBuffer[3]; // Buffer of packets from comp to arduino
char outBuffer[4]; // Buffer of packets from arduino to comp

int inBufferPull = 0; // Where to get buffered data from
int inBufferPush = 0; // Where to put data to be buffered

int outBufferPull = 0; // Where to get buffered data from
int outBufferPush = 0; // Where to put data to be buffered

int caCounted = 0;

int baudRate = 9600;

int compByte = 0;

void setup() {
  Serial.begin(baudRate);
}

void loop() {
  if(Serial.available()) {
    compByte = Serial.read();
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
    case 0:
    
    case 1:
      
    case 2:
    
    case 3:
    
    case 4:
    
    case 5:
    
    case 6:
    
    case 7:
    
    case 8:
      break;
  }
}
