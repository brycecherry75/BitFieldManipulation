/*

  BitFieldManipulation advanced function demo by Bryce Cherry

  Commands:
  NULL_ARRAY - nulls the contents of ByteArray
  READ_ARRAY_SINGLE BitStart BitWidth - reads a byte with its LSB corresponding to BitStart from ByteArray constrained by BitWidth
  READ_ARRAY_TO_ARRAY SourceBitStart SourceBitWidth DestinationBitStart - reads to an array with its LSB corresponding to BitStart from ByteArray constrained by BitWidth
  WRITE_TO_ARRAY_SINGLE BitStart BitWidth DestinationBitStart hexadecimal_data - writes hexadecimal_data (byte) with its LSB corresponding to BitStart from ByteArray constrained by BitWidth
  WRITE_TO_ARRAY_USING_ARRAY SourceBitStart SourceBitWidth DestinationBitStart hexadecimal_data - writes hexadecimal_data (no more than 32 bits) with its LSB corresponding to BitStart from ByteArray constrained by BitWidth
  REVERSE_ARRAY - reverses the element order and the bit order of each individual element of ByteArray
  BITSHIFT_ARRAY(_SIGNED) bits_to_shift_signed - performs a bitshift on ByteArray; if bits_to_shift_signed is positive, a left bitshift will be performed; otherwise, a right bitshift will be performed and if the _SIGNED suffix is used and the MSB of ByteArray is 1, sign extension will be performed

  MSB of an array is the MSB in Element 0 and its LSB is Bit 0 in Element (array_size - 1).

*/

#include <BitFieldManipulation.h>

const uint8_t BFMsize = 6;
const uint8_t TempArraySize = 4;
uint8_t ByteArray[BFMsize];

// ensures that the serial port is flushed fully on request
const unsigned long SerialPortRate = 9600;
const byte SerialPortRateTolerance = 5; // +percent - increase to 50 for rates above 115200 up to 4000000
const byte SerialPortBits = 10; // start (1), data (8), stop (1)
const unsigned long TimePerByte = ((((1000000ULL * SerialPortBits) / SerialPortRate) * (100 + SerialPortRateTolerance)) / 100); // calculated on serial port rate + tolerance and rounded down to the nearest uS, long caters for even the slowest serial port of 75 bps

const word commandSize = 50;
char command[commandSize];
const byte FieldSize = 30;

void FlushSerialBuffer() {
  while (true) {
    if (Serial.available() > 0) {
      byte dummy = Serial.read();
      while (Serial.available() > 0) { // flush additional bytes from serial buffer if present
        dummy = Serial.read();
      }
      if (TimePerByte <= 16383) {
        delayMicroseconds(TimePerByte); // delay in case another byte may be received via the serial port
      }
      else { // deal with delayMicroseconds limitation
        unsigned long DelayTime = TimePerByte;
        DelayTime /= 1000;
        if (DelayTime > 0) {
          delay(DelayTime);
        }
        DelayTime = TimePerByte;
        DelayTime %= 1000;
        if (DelayTime > 0) {
          delayMicroseconds(DelayTime);
        }
      }
    }
    else {
      break;
    }
  }
}

void getField (char* buffer, int index) {
  int commandPos = 0;
  int fieldPos = 0;
  int spaceCount = 0;
  while (commandPos < commandSize) {
    if (command[commandPos] == 0x20) {
      spaceCount++;
      commandPos++;
    }
    else if (command[commandPos] == 0x0D || command[commandPos] == 0x0A) {
      break;
    }
    if (spaceCount == index) {
      buffer[fieldPos] = command[commandPos];
      fieldPos++;
    }
    commandPos++;
  }
  for (int ch = 0; ch < strlen(buffer); ch++) { // correct case of command
    buffer[ch] = toupper(buffer[ch]);
  }
  buffer[fieldPos] = '\0';
}

void PrintHexByteWithLeadingZeros(byte value) {
  if ((value & 0xF0) == 0) {
    Serial.print(F("0"));
  }
  Serial.print(value, HEX);
}

void DumpByteArray() {
  Serial.print(F("ByteArray contents: "));
  for (int i = 0; i < BFMsize; i++) {
    PrintHexByteWithLeadingZeros(ByteArray[i]);
    Serial.print(F(" "));
  }
  Serial.println(F(""));
}

void setup() {
  BitFieldManipulation.NullArray_byte(BFMsize, ByteArray);
  Serial.begin(SerialPortRate);
}

void loop() {
  static int ByteCount = 0;
  if (Serial.available() > 0) {
    char inData = Serial.read();
    if (inData != '\n' && ByteCount < commandSize) {
      command[ByteCount] = inData;
      ByteCount++;
    }
    else {
      ByteCount = 0;
      char field[FieldSize];
      getField(field, 0);
      if (strcmp(field, "NULL_ARRAY") == 0) {
        BitFieldManipulation.NullArray_byte(BFMsize, ByteArray);
        DumpByteArray();
      }
      else if (strcmp(field, "READ_ARRAY_SINGLE") == 0) {
        getField(field, 1);
        uint16_t BitStart = atol(field);
        getField(field, 2);
        uint16_t BitWidth = atol(field);
        uint8_t dataByte = 0;
        dataByte = BitFieldManipulation.ReadBF_ByteArrayToByte(BitStart, BitWidth, BFMsize, ByteArray); // Single element read from array with source bitwidth same as destination element bitwidth
        Serial.print(F("Single byte element contents: "));
        Serial.println(dataByte, HEX);
        uint32_t dwordByte = 0;
        dwordByte = BitFieldManipulation.ReadBF_ByteArrayToDword(BitStart, BitWidth, BFMsize, ByteArray); // Single element read from array with source bitwidth smaller than destination element bitwidth
        Serial.print(F("ReadBF_ByteArrayToDword result: "));
        Serial.println(dwordByte, HEX);
        DumpByteArray();
      }
      else if (strcmp(field, "READ_ARRAY_TO_ARRAY") == 0) {
        uint8_t TempArray[TempArraySize];
        BitFieldManipulation.NullArray_byte(TempArraySize, TempArray);
        getField(field, 1);
        uint16_t SourceBitStart = atol(field);
        getField(field, 2);
        uint16_t SourceBitWidth = atol(field);
        getField(field, 3);
        uint16_t DestinationBitStart = atol(field);
        BitFieldManipulation.TransferByteArrayToByteArray(SourceBitStart, SourceBitWidth, BFMsize, DestinationBitStart, TempArraySize, TempArray, ByteArray); // Array-array transfer with element bitwidth same as destination bitwidth
        Serial.print(F("Selected array contents: "));
        for (int i = 0; i < TempArraySize; i++) {
          PrintHexByteWithLeadingZeros(TempArray[i]);
          Serial.print(F(" "));
        }
        Serial.println(F(""));
        uint16_t WordArray[TempArraySize];
        BitFieldManipulation.NullArray_word(TempArraySize, WordArray);
        BitFieldManipulation.TransferByteArrayToWordArray(SourceBitStart, SourceBitWidth, BFMsize, DestinationBitStart, TempArraySize, WordArray, ByteArray); // Array-array transfer with element bitwidth smaller than destination bitwidth
        Serial.print(F("WordArray contents: "));
        for (int i = 0; i < TempArraySize; i++) {
          uint16_t mask = 0xF000;
          uint8_t ZerosRequired = 0;
          for (int ZerosToPrint = 0; ZerosToPrint < 3; ZerosToPrint++) {
            if ((WordArray[i] & mask) == 0) {
              Serial.print(F("0"));
            }
            else {
              break;
            }
            mask >>= 4;
          }
          Serial.print(WordArray[i], HEX);
          Serial.print(F(" "));
        }
        Serial.println(F(""));
        BitFieldManipulation.NullArray_byte(BFMsize, ByteArray);
        BitFieldManipulation.TransferWordArrayToByteArray(SourceBitStart, SourceBitWidth, TempArraySize, DestinationBitStart, BFMsize, ByteArray, WordArray); // Array-array transfer with element bitwidth smaller than destination bitwidth
        DumpByteArray();
      }
      else if (strcmp(field, "WRITE_TO_ARRAY_SINGLE") == 0) {
        getField(field, 1);
        uint16_t BitStart = atol(field);
        getField(field, 2);
        uint16_t BitWidth = atol(field);
        getField(field, 3);
        uint8_t data = strtoul(field, NULL, 16);
        BitFieldManipulation.WriteBF_ByteToByteArray(BitStart, BitWidth, BFMsize, ByteArray, data); // Single element write to array with source bitwidth same as destination element bitwidth
        DumpByteArray();
        BitFieldManipulation.WriteBF_ByteToByteArray(BitStart, BitWidth, BFMsize, ByteArray, 0);
        DumpByteArray();
        uint16_t WordArray[TempArraySize];
        BitFieldManipulation.NullArray_word(TempArraySize, WordArray);
        BitFieldManipulation.WriteBF_ByteToWordArray(BitStart, BitWidth, BFMsize, WordArray, data); // Single element write to array with source bitwidth smaller than destination element bitwidth
        for (int i = 0; i < TempArraySize; i++) {
          uint16_t mask = 0xF000;
          uint8_t ZerosRequired = 0;
          for (int ZerosToPrint = 0; ZerosToPrint < 3; ZerosToPrint++) {
            if ((WordArray[i] & mask) == 0) {
              Serial.print(F("0"));
            }
            else {
              break;
            }
            mask >>= 4;
          }
          Serial.print(WordArray[i], HEX);
          Serial.print(F(" "));
        }
        Serial.println(F(""));
        DumpByteArray();
      }
      else if (strcmp(field, "WRITE_TO_ARRAY_USING_ARRAY") == 0) {
        uint8_t TempArray[TempArraySize];
        BitFieldManipulation.NullArray_byte(TempArraySize, TempArray);
        getField(field, 1);
        uint16_t SourceBitStart = atol(field);
        getField(field, 2);
        uint16_t SourceBitWidth = atol(field);
        getField(field, 3);
        uint16_t DestinationBitStart = atol(field);
        getField(field, 4);
        uint32_t data = strtoul(field, NULL, 16);
        for (int i = (TempArraySize - 1); i >= 0; i--) {
          TempArray[i] = (data & 0xFF);
          data >>= 8;
        }
        Serial.print(F("Contents starting at Bit "));
        Serial.print(SourceBitStart);
        Serial.print(F(" to transfer to ByteArray starting at Bit "));
        Serial.println(DestinationBitStart);
        for (int i = 0; i < TempArraySize; i++) {
          PrintHexByteWithLeadingZeros(TempArray[i]);
          Serial.print(F(" "));
        }
        Serial.println(F(""));
        BitFieldManipulation.TransferByteArrayToByteArray(SourceBitStart, SourceBitWidth, TempArraySize, DestinationBitStart, BFMsize, ByteArray, TempArray); // Array-array transfer with element bitwidth same as destination
        DumpByteArray();
        BitFieldManipulation.NullArray_byte(TempArraySize, TempArray);
        uint32_t DwordTemp = 0;
        DwordTemp = BitFieldManipulation.ReadBF_ByteArrayToDword(SourceBitStart, SourceBitWidth, BFMsize, ByteArray); // Single element read from array with source bitwidth smaller than destination element bitwidth
        Serial.print(F("ReadBF_ByteArrayToDword result: "));
        Serial.println(DwordTemp, HEX);
        BitFieldManipulation.NullArray_byte(BFMsize, ByteArray);
        BitFieldManipulation.WriteBF_DwordToByteArray(SourceBitStart, SourceBitWidth, BFMsize, ByteArray, DwordTemp); // Single element write to array with source bitwidth larger than destination element bitwidth
        Serial.println(F("WriteBF_DwordToByteArray complete"));
        DumpByteArray();
      }
      else if (strcmp(field, "REVERSE_ARRAY") == 0) {
        BitFieldManipulation.ReverseBitOrder_byteArray(BFMsize, ByteArray);
        DumpByteArray();
      }
      else if (strcmp(field, "BITSHIFT_ARRAY") == 0 || strcmp(field, "BITSHIFT_ARRAY_SIGNED") == 0) {
        bool IsSigned = false;
        if (strcmp(field, "BITSHIFT_ARRAY_SIGNED") == 0) {
          IsSigned = true;
        }
        getField(field, 1);
        int32_t BitshiftsRequired = atol(field);
        BitFieldManipulation.BitshiftArray_byte(BitshiftsRequired, BFMsize, IsSigned, ByteArray);
        DumpByteArray();
      }
      FlushSerialBuffer();
    }
  }
}