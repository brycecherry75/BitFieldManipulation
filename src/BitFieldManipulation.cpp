#include "BitFieldManipulation.h"

// Bit order reversal

uint8_t BitFieldManipulationClass::ReverseBitOrder_byte(uint8_t data_source) {
  uint8_t value = 0;
  uint8_t mask1 = 0x80;
  uint8_t mask2 = 0x01;
  for (int i = 0; i < 8; i++) {
    if ((data_source & mask1) != 0) {
      value |= mask2;
    }
    mask1 >>= 1;
    if (mask1 > 0x40) { // deal with unwanted sign bit
      mask1 = 0x40;
    }
    mask2 <<= 1;
  }
  return value;
}

uint16_t BitFieldManipulationClass::ReverseBitOrder_word(uint16_t data_source) {
  uint16_t value = 0;
  uint16_t mask1 = 0x8000;
  uint16_t mask2 = 0x0001;
  for (int i = 0; i < 16; i++) {
    if ((data_source & mask1) != 0) {
      value |= mask2;
    }
    mask1 >>= 1;
    if (mask1 > 0x4000) { // deal with unwanted sign bit
      mask1 = 0x4000;
    }
    mask2 <<= 1;
  }
  return value;
}

uint32_t BitFieldManipulationClass::ReverseBitOrder_dword(uint32_t data_source) {
  uint32_t value = 0;
  uint32_t mask1 = 0x80000000;
  uint32_t mask2 = 0x00000001;
  for (int i = 0; i < 32; i++) {
    if ((data_source & mask1) != 0) {
      value |= mask2;
    }
    mask1 >>= 1;
    if (mask1 > 0x40000000) { // deal with unwanted sign bit
      mask1 = 0x40000000;
    }
    mask2 <<= 1;
  }
  return value;
}

uint64_t BitFieldManipulationClass::ReverseBitOrder_qword(uint64_t data_source) {
  uint64_t value = 0;
  uint64_t mask1 = 9223372036854775808ULL;
  uint64_t mask2 = 1;
  for (int i = 0; i < 64; i++) {
    if ((data_source & mask1) != 0) {
      value |= mask2;
    }
    mask1 >>= 1;
    if (mask1 > 4611686018427387904ULL) { // deal with unwanted sign bit
      mask1 = 4611686018427387904ULL;
    }
    mask2 <<= 1;
  }
  return value;
}

void BitFieldManipulationClass::ReverseBitOrder_byteArray(uint16_t array_elements, uint8_t *data_source) {
  for (uint16_t i = 0; i < array_elements; i++) {
    data_source[i] = ReverseBitOrder_byte(data_source[i]);
  }
  for (uint16_t i = 0; i < (array_elements / 2); i++) {
    uint8_t data = data_source[i];
    uint16_t temp = array_elements;
    temp -= i;
    temp--;
    data_source[i] = data_source[temp];
    data_source[temp] = data;
  }
}

void BitFieldManipulationClass::ReverseBitOrder_wordArray(uint16_t array_elements, uint16_t *data_source) {
  for (uint16_t i = 0; i < array_elements; i++) {
    data_source[i] = ReverseBitOrder_word(data_source[i]);
  }
  for (uint16_t i = 0; i < (array_elements / 2); i++) {
    uint16_t data = data_source[i];
    uint16_t temp = array_elements;
    temp -= i;
    temp--;
    data_source[i] = data_source[temp];
    data_source[temp] = data;
  }
}

void BitFieldManipulationClass::ReverseBitOrder_dwordArray(uint16_t array_elements, uint32_t *data_source) {
  for (uint16_t i = 0; i < array_elements; i++) {
    data_source[i] = ReverseBitOrder_dword(data_source[i]);
  }
  for (uint16_t i = 0; i < (array_elements / 2); i++) {
    uint32_t data = data_source[i];
    uint16_t temp = array_elements;
    temp -= i;
    temp--;
    data_source[i] = data_source[temp];
    data_source[temp] = data;
  }
}

void BitFieldManipulationClass::ReverseBitOrder_qwordArray(uint16_t array_elements, uint64_t *data_source) {
  for (uint16_t i = 0; i < array_elements; i++) {
    data_source[i] = ReverseBitOrder_qword(data_source[i]);
  }
  for (uint16_t i = 0; i < (array_elements / 2); i++) {
    uint64_t data = data_source[i];
    uint16_t temp = array_elements;
    temp -= i;
    temp--;
    data_source[i] = data_source[temp];
    data_source[temp] = data;
  }
}

// Nulling arrays

void BitFieldManipulationClass::NullArray_byte(uint16_t array_elements, uint8_t *data_source) {
  for (uint16_t i = 0; i < array_elements; i++) {
    data_source[i] = 0;
  }
}

void BitFieldManipulationClass::NullArray_word(uint16_t array_elements, uint16_t *data_source) {
  for (uint16_t i = 0; i < array_elements; i++) {
    data_source[i] = 0;
  }
}

void BitFieldManipulationClass::NullArray_dword(uint16_t array_elements, uint32_t *data_source) {
  for (uint16_t i = 0; i < array_elements; i++) {
    data_source[i] = 0;
  }
}

void BitFieldManipulationClass::NullArray_qword(uint16_t array_elements, uint64_t *data_source) {
  for (uint16_t i = 0; i < array_elements; i++) {
    data_source[i] = 0;
  }
}

// Writing a bitfield

uint8_t BitFieldManipulationClass::WriteBF_byte(uint8_t BitStart, uint8_t BitWidth, uint8_t data_source, uint8_t data_field) {
  uint8_t mask = 1;
  mask <<= BitWidth; // 0x40 if BitStart = 6;
  mask--; // now 0x3F; // now 0x3F - 6 consecutive bits from 0 set
  data_field &= mask; // do not exceed BitWidth
  mask <<= BitStart; // shift to the destination field
  data_source &= (~mask); // clear the destination field for a write
  data_field <<= BitStart; // 0x3F00 if BitStart = 8;
  data_source |= data_field; // write to the destination field
  return data_source;
}

uint16_t BitFieldManipulationClass::WriteBF_word(uint8_t BitStart, uint8_t BitWidth, uint16_t data_source, uint16_t data_field) {
  uint16_t mask = 1;
  mask <<= BitWidth; // 0x40 if BitStart = 6;
  mask--; // now 0x3F; // now 0x3F - 6 consecutive bits from 0 set
  data_field &= mask; // do not exceed BitWidth
  mask <<= BitStart; // shift to the destination field
  data_source &= (~mask); // clear the destination field for a write
  data_field <<= BitStart; // 0x3F00 if BitStart = 8;
  data_source |= data_field; // write to the destination field
  return data_source;
}

uint32_t BitFieldManipulationClass::WriteBF_dword(uint8_t BitStart, uint8_t BitWidth, uint32_t data_source, uint32_t data_field) {
  uint32_t mask = 1;
  mask <<= BitWidth; // 0x40 if BitStart = 6;
  mask--; // now 0x3F; // now 0x3F - 6 consecutive bits from 0 set
  data_field &= mask; // do not exceed BitWidth
  mask <<= BitStart; // shift to the destination field
  data_source &= (~mask); // clear the destination field for a write
  data_field <<= BitStart; // 0x3F00 if BitStart = 8;
  data_source |= data_field; // write to the destination field
  return data_source;
}

uint64_t BitFieldManipulationClass::WriteBF_qword(uint8_t BitStart, uint8_t BitWidth, uint64_t data_source, uint64_t data_field) {
  uint64_t mask = 1;
  mask <<= BitWidth; // 0x40 if BitStart = 6;
  mask--; // now 0x3F; // now 0x3F - 6 consecutive bits from 0 set
  data_field &= mask; // do not exceed BitWidth
  mask <<= BitStart; // shift to the destination field
  data_source &= (~mask); // clear the destination field for a write
  data_field <<= BitStart; // 0x3F00 if BitStart = 8;
  data_source |= data_field; // write to the destination field
  return data_source;
}

// Reading a bitfield

uint8_t BitFieldManipulationClass::ReadBF_byte(uint8_t BitStart, uint8_t BitWidth, uint8_t data_source) {
  data_source >>= BitStart; // if data = 0x103E00 and BitStart = 8, data is now 0x103E
  uint8_t mask = 1;
  mask <<= BitWidth; // 0x40 if BitStart = 6;
  mask--; // now 0x3F - 6 consecutive bits from 0 set
  data_source &= mask; // data is now 0x3E
  return data_source;
}

uint16_t BitFieldManipulationClass::ReadBF_word(uint8_t BitStart, uint8_t BitWidth, uint16_t data_source) {
  data_source >>= BitStart; // if data = 0x103E00 and BitStart = 8, data is now 0x103E
  uint16_t mask = 1;
  mask <<= BitWidth; // 0x40 if BitStart = 6;
  mask--; // now 0x3F - 6 consecutive bits from 0 set
  data_source &= mask; // data is now 0x3E
  return data_source;
}

uint32_t BitFieldManipulationClass::ReadBF_dword(uint8_t BitStart, uint8_t BitWidth, uint32_t data_source) {
  data_source >>= BitStart; // if data = 0x103E00 and BitStart = 8, data is now 0x103E
  uint32_t mask = 1;
  mask <<= BitWidth; // 0x40 if BitStart = 6;
  mask--; // now 0x3F - 6 consecutive bits from 0 set
  data_source &= mask; // data is now 0x3E
  return data_source;
}

uint64_t BitFieldManipulationClass::ReadBF_qword(uint8_t BitStart, uint8_t BitWidth, uint64_t data_source) {
  data_source >>= BitStart; // if data = 0x103E00 and BitStart = 8, data is now 0x103E
  uint64_t mask = 1;
  mask <<= BitWidth; // 0x40 if BitStart = 6;
  mask--; // now 0x3F - 6 consecutive bits from 0 set
  data_source &= mask; // data is now 0x3E
  return data_source;
}

// Private functions for calculating shift parameters

uint16_t BitFieldManipulationClass::CalculateShiftParameters(uint16_t MaximumBit, uint16_t BitStart, uint8_t BitWidth, uint8_t ElementSize, uint8_t *ParametersToReturn) {
  MaximumBit -= BitStart; // initially 31, now 19/31/30/7/8/28/31 single element, 27/31/20/21 array
  uint16_t ElementStart = MaximumBit; // is 19/31/30/7/8/28/31 single element, 27/31/20/21 array
  ElementStart /= ElementSize; // final result is 2/3/3/0/1/3/3 single element, 3/3/2/2 array - where the LSBs are
  MaximumBit %= ElementSize; // ElementSize is 8; now 3/7/6/7/0/4/7 single element, 3/7/4/5 array
  ParametersToReturn[BitFieldManipulation_LSBoffset] = MaximumBit; // is 3/7/6/7/0/4/7 single element, 3/7/4/5 array
  ParametersToReturn[BitFieldManipulation_LSBoffset] = ((ElementSize - 1) - ParametersToReturn[BitFieldManipulation_LSBoffset]); // (ElementSize - 1) is 7; final result is now 4/0/1/0/7/3/0 single element, 4/0/3/2 array
  ParametersToReturn[BitFieldManipulation_LSBwidth] = (ElementSize - ParametersToReturn[BitFieldManipulation_LSBoffset]); // is 4/8/7/8/1/5/8 single element, final value 4/8/5/6 array
  if (BitWidth < ElementSize) { // do not go beyond the boundaries for a single element
    if (ParametersToReturn[BitFieldManipulation_LSBwidth] > BitWidth) { // single element
      ParametersToReturn[BitFieldManipulation_LSBwidth] = BitWidth; // final result is 4/7/7/7/1/8 single element
    }
    ParametersToReturn[BitFieldManipulation_MSBbits] = BitWidth; // is 8
    ParametersToReturn[BitFieldManipulation_MSBbits] -= ParametersToReturn[BitFieldManipulation_LSBwidth]; // final result is 3/0/0/0/6/3/0 for single element
  }
  else { // full element or array
    BitWidth -= ParametersToReturn[BitFieldManipulation_LSBwidth]; // now 17/13/16/15 for array
    BitWidth %= ElementSize; // now 1/5/0/7 for array
    ParametersToReturn[BitFieldManipulation_MSBbits] = BitWidth; // final result is 1/5/0/7 for array
  }
  return ElementStart;
}

uint16_t BitFieldManipulationClass::CalculateMaximumBit(uint16_t ArraySize, uint8_t ElementSize) {
  uint16_t MaximumBit = ArraySize;
  MaximumBit *= ElementSize;
  MaximumBit--;
  return MaximumBit;
}

// Single element write to array with source bitwidth same as destination element bitwidth

void BitFieldManipulationClass::WriteBF_ByteToByteArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint8_t *data_destination, uint8_t data_field) {
  if (BitWidth > 0 && BitWidth <= 8 && ArraySize > 0 && ArraySize < 8192) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 8);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 8, ShiftParameters);
      data_destination[ElementStart] = WriteBF_word(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_destination[ElementStart], data_field); // write LSBs to array - excess bits in data_field will be masked out by WriteBF
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint8_t MSBshifts = 8;
        MSBshifts -= ShiftParameters[BitFieldManipulation_MSBbits];
        data_field >>= MSBshifts;
        data_destination[ElementStart] = WriteBF_word(0, ShiftParameters[BitFieldManipulation_MSBbits], data_destination[ElementStart], data_field); // if any, write MSBs to array - excess bits in data_field will be masked out by WriteBF
      }
    }
  }
}

void BitFieldManipulationClass::WriteBF_WordToWordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint16_t *data_destination, uint16_t data_field) {
  if (BitWidth > 0 && BitWidth <= 16 && ArraySize > 0 && ArraySize < 4096) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 16);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 16, ShiftParameters);
      data_destination[ElementStart] = WriteBF_word(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_destination[ElementStart], data_field); // write LSBs to array - excess bits in data_field will be masked out by WriteBF
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint8_t MSBshifts = 16;
        MSBshifts -= ShiftParameters[BitFieldManipulation_MSBbits];
        data_field >>= MSBshifts;
        data_destination[ElementStart] = WriteBF_word(0, ShiftParameters[BitFieldManipulation_MSBbits], data_destination[ElementStart], data_field); // if any, write MSBs to array - excess bits in data_field will be masked out by WriteBF
      }
    }
  }
}

void BitFieldManipulationClass::WriteBF_DwordToDwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint32_t *data_destination, uint32_t data_field) {
  if (BitWidth > 0 && BitWidth <= 32 && ArraySize > 0 && ArraySize < 2048) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 32);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 32, ShiftParameters);
      data_destination[ElementStart] = WriteBF_dword(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_destination[ElementStart], data_field); // write LSBs to array - excess bits in data_field will be masked out by WriteBF
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint8_t MSBshifts = 32;
        MSBshifts -= ShiftParameters[BitFieldManipulation_MSBbits];
        data_field >>= MSBshifts;
        data_destination[ElementStart] = WriteBF_dword(0, ShiftParameters[BitFieldManipulation_MSBbits], data_destination[ElementStart], data_field); // if any, write MSBs to array - excess bits in data_field will be masked out by WriteBF
      }
    }
  }
}

void BitFieldManipulationClass::WriteBF_QwordToQwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint64_t *data_destination, uint64_t data_field) {
  if (BitWidth > 0 && BitWidth <= 64 && ArraySize > 0 && ArraySize < 1024) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 64);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 64, ShiftParameters);
      data_destination[ElementStart] = WriteBF_qword(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_destination[ElementStart], data_field); // write LSBs to array - excess bits in data_field will be masked out by WriteBF
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint8_t MSBshifts = 64;
        MSBshifts -= ShiftParameters[BitFieldManipulation_MSBbits];
        data_field >>= MSBshifts;
        data_destination[ElementStart] = WriteBF_qword(0, ShiftParameters[BitFieldManipulation_MSBbits], data_destination[ElementStart], data_field); // if any, write MSBs to array - excess bits in data_field will be masked out by WriteBF
      }
    }
  }
}

// Single element read from array with source bitwidth same as destination element bitwidth

uint8_t BitFieldManipulationClass::ReadBF_ByteArrayToByte(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint8_t *data_source) {
  uint8_t value = 0;
  if (BitWidth > 0 && BitWidth <= 8) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 8);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 8, ShiftParameters);
      value = ReadBF_byte(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_source[ElementStart]);
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint8_t temp = ReadBF_byte(0, ShiftParameters[BitFieldManipulation_MSBbits], data_source[ElementStart]);
        temp <<= ShiftParameters[BitFieldManipulation_LSBwidth];
        value |= temp;
      }
    }
  }
  return value;
}

uint16_t BitFieldManipulationClass::ReadBF_WordArrayToWord(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint16_t *data_source) {
  uint16_t value = 0;
  if (BitWidth > 0 && BitWidth <= 16) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 16);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 16, ShiftParameters);
      value = ReadBF_word(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_source[ElementStart]);
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint8_t temp = ReadBF_word(0, ShiftParameters[BitFieldManipulation_MSBbits], data_source[ElementStart]);
        temp <<= ShiftParameters[BitFieldManipulation_LSBwidth];
        value |= temp;
      }
    }
  }
  return value;
}

uint32_t BitFieldManipulationClass::ReadBF_DwordArrayToDword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint32_t *data_source) {
  uint32_t value = 0;
  if (BitWidth > 0 && BitWidth <= 32) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 32);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 32, ShiftParameters);
      value = ReadBF_dword(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_source[ElementStart]);
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint32_t temp = ReadBF_dword(0, ShiftParameters[BitFieldManipulation_MSBbits], data_source[ElementStart]);
        temp <<= ShiftParameters[BitFieldManipulation_LSBwidth];
        value |= temp;
      }
    }
  }
  return value;
}

uint64_t BitFieldManipulationClass::ReadBF_QwordArrayToQword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint64_t *data_source) {
  uint64_t value = 0;
  if (BitWidth > 0 && BitWidth <= 64) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 64);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 64, ShiftParameters);
      value = ReadBF_qword(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_source[ElementStart]);
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint64_t temp = ReadBF_qword(0, ShiftParameters[BitFieldManipulation_MSBbits], data_source[ElementStart]);
        temp <<= ShiftParameters[BitFieldManipulation_LSBwidth];
        value |= temp;
      }
    }
  }
  return value;
}

// Single element write to array with source bitwidth larger than destination element bitwidth

void BitFieldManipulationClass::WriteBF_WordToByteArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint8_t *data_destination, uint16_t data_field) {
  if (BitWidth > 0 && BitWidth <= 16) {
    uint16_t BitsRemaining = BitWidth;
    while (true) {
      if (BitsRemaining >= 8) {
        WriteBF_ByteToByteArray(BitStart, 8, ArraySize, data_destination, (data_field & 0xFF));
      }
      else {
        WriteBF_ByteToByteArray(BitStart, BitsRemaining, ArraySize, data_destination, (data_field & 0xFF));
        break;
      }
      BitsRemaining -= 8;
      if (BitsRemaining == 0) {
        break;
      }
      BitStart += 8;
      data_field >>= 8;
    }
  }
}

void BitFieldManipulationClass::WriteBF_DwordToByteArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint8_t *data_destination, uint32_t data_field) {
  if (BitWidth > 0 && BitWidth <= 32) {
    uint16_t BitsRemaining = BitWidth;
    while (true) {
      if (BitsRemaining >= 8) {
        WriteBF_ByteToByteArray(BitStart, 8, ArraySize, data_destination, (data_field & 0xFF));
      }
      else {
        WriteBF_ByteToByteArray(BitStart, BitsRemaining, ArraySize, data_destination, (data_field & 0xFF));
        break;
      }
      BitsRemaining -= 8;
      if (BitsRemaining == 0) {
        break;
      }
      BitStart += 8;
      data_field >>= 8;
    }
  }
}

void BitFieldManipulationClass::WriteBF_QwordToByteArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint8_t *data_destination, uint64_t data_field) {
  if (BitWidth > 0 && BitWidth <= 64) {
    uint16_t BitsRemaining = BitWidth;
    while (true) {
      if (BitsRemaining >= 8) {
        WriteBF_ByteToByteArray(BitStart, 8, ArraySize, data_destination, (data_field & 0xFF));
      }
      else {
        WriteBF_ByteToByteArray(BitStart, BitsRemaining, ArraySize, data_destination, (data_field & 0xFF));
        break;
      }
      BitsRemaining -= 8;
      if (BitsRemaining == 0) {
        break;
      }
      BitStart += 8;
      data_field >>= 8;
    }
  }
}

void BitFieldManipulationClass::WriteBF_DwordToWordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint16_t *data_destination, uint32_t data_field) {
  if (BitWidth > 0 && BitWidth <= 32) {
    uint16_t BitsRemaining = BitWidth;
    while (true) {
      if (BitsRemaining >= 16) {
        WriteBF_WordToWordArray(BitStart, 8, ArraySize, data_destination, (data_field & 0xFFFF));
      }
      else {
        WriteBF_WordToWordArray(BitStart, BitsRemaining, ArraySize, data_destination, (data_field & 0xFFFF));
        break;
      }
      BitsRemaining -= 16;
      if (BitsRemaining == 0) {
        break;
      }
      BitStart += 16;
      data_field >>= 16;
    }
  }
}

void BitFieldManipulationClass::WriteBF_QwordToWordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint16_t *data_destination, uint64_t data_field) {
  if (BitWidth > 0 && BitWidth <= 64) {
    uint16_t BitsRemaining = BitWidth;
    while (true) {
      if (BitsRemaining >= 16) {
        WriteBF_WordToWordArray(BitStart, 8, ArraySize, data_destination, (data_field & 0xFFFF));
      }
      else {
        WriteBF_WordToWordArray(BitStart, BitsRemaining, ArraySize, data_destination, (data_field & 0xFFFF));
        break;
      }
      BitsRemaining -= 16;
      if (BitsRemaining == 0) {
        break;
      }
      BitStart += 16;
      data_field >>= 16;
    }
  }
}

void BitFieldManipulationClass::WriteBF_QwordToDwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint32_t *data_destination, uint64_t data_field) {
  if (BitWidth > 0 && BitWidth <= 64) {
    uint16_t BitsRemaining = BitWidth;
    while (true) {
      if (BitsRemaining >= 32) {
        WriteBF_DwordToDwordArray(BitStart, 32, ArraySize, data_destination, (data_field & 0xFFFFFFFF));
      }
      else {
        WriteBF_DwordToDwordArray(BitStart, BitsRemaining, ArraySize, data_destination, (data_field & 0xFFFFFFFF));
        break;
      }
      BitsRemaining -= 32;
      if (BitsRemaining == 0) {
        break;
      }
      BitStart += 32;
      data_field >>= 32;
    }
  }
}

// Single element read from array with source bitwidth larger than destination element bitwidth

uint8_t BitFieldManipulationClass::ReadBF_WordArrayToByte(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint16_t *data_source) {
  uint8_t value = 0;
  if (BitWidth > 0 && BitWidth <= 8) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 16);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 16, ShiftParameters);
      value = ReadBF_byte(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_source[ElementStart]);
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint8_t temp = ReadBF_byte(0, ShiftParameters[BitFieldManipulation_MSBbits], data_source[ElementStart]);
        temp <<= ShiftParameters[BitFieldManipulation_LSBwidth];
        value |= temp;
      }
    }
  }
  return value;
}

uint8_t BitFieldManipulationClass::ReadBF_DwordArrayToByte(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint32_t *data_source) {
  uint8_t value = 0;
  if (BitWidth > 0 && BitWidth <= 8) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 32);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 32, ShiftParameters);
      value = ReadBF_byte(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_source[ElementStart]);
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint8_t temp = ReadBF_byte(0, ShiftParameters[BitFieldManipulation_MSBbits], data_source[ElementStart]);
        temp <<= ShiftParameters[BitFieldManipulation_LSBwidth];
        value |= temp;
      }
    }
  }
  return value;
}

uint16_t BitFieldManipulationClass::ReadBF_DwordArrayToWord(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint32_t *data_source) {
  uint16_t value = 0;
  if (BitWidth > 0 && BitWidth <= 16) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 32);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 32, ShiftParameters);
      value = ReadBF_word(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_source[ElementStart]);
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint8_t temp = ReadBF_word(0, ShiftParameters[BitFieldManipulation_MSBbits], data_source[ElementStart]);
        temp <<= ShiftParameters[BitFieldManipulation_LSBwidth];
        value |= temp;
      }
    }
  }
  return value;
}

uint8_t BitFieldManipulationClass::ReadBF_QwordArrayToByte(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint64_t *data_source) {
  uint8_t value = 0;
  if (BitWidth > 0 && BitWidth <= 8) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 64);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 64, ShiftParameters);
      value = ReadBF_byte(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_source[ElementStart]);
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint8_t temp = ReadBF_byte(0, ShiftParameters[BitFieldManipulation_MSBbits], data_source[ElementStart]);
        temp <<= ShiftParameters[BitFieldManipulation_LSBwidth];
        value |= temp;
      }
    }
  }
  return value;
}

uint16_t BitFieldManipulationClass::ReadBF_QwordArrayToWord(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint64_t *data_source) {
  uint16_t value = 0;
  if (BitWidth > 0 && BitWidth <= 16) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 64);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 64, ShiftParameters);
      value = ReadBF_word(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_source[ElementStart]);
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint8_t temp = ReadBF_word(0, ShiftParameters[BitFieldManipulation_MSBbits], data_source[ElementStart]);
        temp <<= ShiftParameters[BitFieldManipulation_LSBwidth];
        value |= temp;
      }
    }
  }
  return value;
}

uint32_t BitFieldManipulationClass::ReadBF_QwordArrayToDword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint64_t *data_source) {
  uint64_t value = 0;
  if (BitWidth > 0 && BitWidth <= 32) {
    uint16_t MaximumBit = CalculateMaximumBit(ArraySize, 64);
    if (((BitStart + BitWidth) - 1) <= MaximumBit) { // do not go beyond the array
      uint8_t ShiftParameters[BitFieldManipulation_ShiftParameterCount];
      uint16_t ElementStart = CalculateShiftParameters(MaximumBit, BitStart, BitWidth, 64, ShiftParameters);
      value = ReadBF_qword(ShiftParameters[BitFieldManipulation_LSBoffset], ShiftParameters[BitFieldManipulation_LSBwidth], data_source[ElementStart]);
      if (ShiftParameters[BitFieldManipulation_MSBbits] != 0) {
        ElementStart--;
        uint64_t temp = ReadBF_qword(0, ShiftParameters[BitFieldManipulation_MSBbits], data_source[ElementStart]);
        temp <<= ShiftParameters[BitFieldManipulation_LSBwidth];
        value |= temp;
      }
    }
  }
  return value;
}

// Single element write to array with source bitwidth smaller than destination element bitwidth

void BitFieldManipulationClass::WriteBF_ByteToWordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint16_t *data_destination, uint8_t data_field) {
  WriteBF_WordToWordArray(BitStart, BitWidth, ArraySize, data_destination, data_field);
}

void BitFieldManipulationClass::WriteBF_ByteToDwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint32_t *data_destination, uint8_t data_field) {
  WriteBF_DwordToDwordArray(BitStart, BitWidth, ArraySize, data_destination, data_field);
}

void BitFieldManipulationClass::WriteBF_WordToDwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint32_t *data_destination, uint16_t data_field) {
  WriteBF_DwordToDwordArray(BitStart, BitWidth, ArraySize, data_destination, data_field);
}

void BitFieldManipulationClass::WriteBF_ByteToQwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint64_t *data_destination, uint8_t data_field) {
  WriteBF_QwordToQwordArray(BitStart, BitWidth, ArraySize, data_destination, data_field);
}

void BitFieldManipulationClass::WriteBF_WordToQwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint64_t *data_destination, uint16_t data_field) {
  WriteBF_QwordToQwordArray(BitStart, BitWidth, ArraySize, data_destination, data_field);
}

void BitFieldManipulationClass::WriteBF_DwordToQwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint64_t *data_destination, uint32_t data_field) {
  WriteBF_QwordToQwordArray(BitStart, BitWidth, ArraySize, data_destination, data_field);
}

// Single element read from array with source bitwidth smaller than destination element bitwidth

uint16_t BitFieldManipulationClass::ReadBF_ByteArrayToWord(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint8_t *data_source) {
  uint16_t data_to_return = 0;
  if (BitWidth > 0 && BitWidth <= 16) {
    uint16_t BitsRemaining = BitWidth;
    uint8_t ElementAt = 0;
    uint8_t tempArray[2] = {0, 0}; // LSB will be in Element 0
    while (true) {
      if (BitsRemaining >= 8) {
        tempArray[ElementAt] = ReadBF_ByteArrayToByte(BitStart, 8, ArraySize, data_source);
      }
      else {
        tempArray[ElementAt] = ReadBF_ByteArrayToByte(BitStart, BitsRemaining, ArraySize, data_source);
        break;
      }
      BitsRemaining -= 8;
      if (BitsRemaining == 0) {
        break;
      }
      BitStart += 8;
      ElementAt++;
    }
    for (int i = 0; i < 2; i++) { // LSB will be in Element 0
      uint16_t temp = 0;
      temp = tempArray[i];
      temp <<= (8 * i);
      data_to_return |= temp;
    }
  }
  return data_to_return;
}

uint32_t BitFieldManipulationClass::ReadBF_ByteArrayToDword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint8_t *data_source) {
  uint32_t data_to_return = 0;
  if (BitWidth > 0 && BitWidth <= 32) {
    uint16_t BitsRemaining = BitWidth;
    uint8_t ElementAt = 0;
    uint8_t tempArray[4] = {0, 0, 0, 0}; // LSB will be in Element 0
    while (true) {
      if (BitsRemaining >= 8) {
        tempArray[ElementAt] = ReadBF_ByteArrayToByte(BitStart, 8, ArraySize, data_source);
      }
      else {
        tempArray[ElementAt] = ReadBF_ByteArrayToByte(BitStart, BitsRemaining, ArraySize, data_source);
        break;
      }
      BitsRemaining -= 8;
      if (BitsRemaining == 0) {
        break;
      }
      BitStart += 8;
      ElementAt++;
    }
    for (int i = 0; i < 4; i++) { // LSB will be in Element 0
      uint32_t temp = 0;
      temp = tempArray[i];
      temp <<= (8 * i);
      data_to_return |= temp;
    }
  }
  return data_to_return;
}

uint64_t BitFieldManipulationClass::ReadBF_ByteArrayToQword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint8_t *data_source) {
  uint64_t data_to_return = 0;
  if (BitWidth > 0 && BitWidth <= 64) {
    uint16_t BitsRemaining = BitWidth;
    uint8_t ElementAt = 0;
    uint8_t tempArray[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // LSB will be in Element 0
    while (true) {
      if (BitsRemaining >= 8) {
        tempArray[ElementAt] = ReadBF_ByteArrayToByte(BitStart, 8, ArraySize, data_source);
      }
      else {
        tempArray[ElementAt] = ReadBF_ByteArrayToByte(BitStart, BitsRemaining, ArraySize, data_source);
        break;
      }
      BitsRemaining -= 8;
      if (BitsRemaining == 0) {
        break;
      }
      BitStart += 8;
      ElementAt++;
    }
    for (int i = 0; i < 8; i++) { // LSB will be in Element 0
      uint64_t temp = 0;
      temp = tempArray[i];
      temp <<= (8 * i);
      data_to_return |= temp;
    }
  }
  return data_to_return;
}

uint32_t BitFieldManipulationClass::ReadBF_WordArrayToDword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint16_t *data_source) {
  uint32_t data_to_return = 0;
  if (BitWidth > 0 && BitWidth <= 32) {
    uint16_t BitsRemaining = BitWidth;
    uint8_t ElementAt = 0;
    uint16_t tempArray[2] = {0, 0}; // LSB will be in Element 0
    while (true) {
      if (BitsRemaining >= 16) {
        tempArray[ElementAt] = ReadBF_WordArrayToWord(BitStart, 16, ArraySize, data_source);
      }
      else {
        tempArray[ElementAt] = ReadBF_WordArrayToWord(BitStart, BitsRemaining, ArraySize, data_source);
        break;
      }
      BitsRemaining -= 16;
      if (BitsRemaining == 0) {
        break;
      }
      BitStart += 16;
      ElementAt++;
    }
    for (int i = 0; i < 2; i++) { // LSB will be in Element 0
      uint32_t temp = 0;
      temp = tempArray[i];
      temp <<= (16 * i);
      data_to_return |= temp;
    }
  }
  return data_to_return;
}

uint64_t BitFieldManipulationClass::ReadBF_WordArrayToQword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint16_t *data_source) {
  uint64_t data_to_return = 0;
  if (BitWidth > 0 && BitWidth <= 64) {
    uint16_t BitsRemaining = BitWidth;
    uint8_t ElementAt = 0;
    uint16_t tempArray[4] = {0, 0, 0, 0}; // LSB will be in Element 0
    while (true) {
      if (BitsRemaining >= 16) {
        tempArray[ElementAt] = ReadBF_WordArrayToWord(BitStart, 16, ArraySize, data_source);
      }
      else {
        tempArray[ElementAt] = ReadBF_WordArrayToWord(BitStart, BitsRemaining, ArraySize, data_source);
        break;
      }
      BitsRemaining -= 16;
      if (BitsRemaining == 0) {
        break;
      }
      BitStart += 16;
      ElementAt++;
    }
    for (int i = 0; i < 4; i++) { // LSB will be in Element 0
      uint64_t temp = 0;
      temp = tempArray[i];
      temp <<= (16 * i);
      data_to_return |= temp;
    }
  }
  return data_to_return;
}

uint64_t BitFieldManipulationClass::ReadBF_DwordArrayToQword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint32_t *data_source) {
  uint64_t data_to_return = 0;
  if (BitWidth > 0 && BitWidth <= 64) {
    uint16_t BitsRemaining = BitWidth;
    uint8_t ElementAt = 0;
    uint16_t tempArray[2] = {0, 0}; // LSB will be in Element 0
    while (true) {
      if (BitsRemaining >= 32) {
        tempArray[ElementAt] = ReadBF_DwordArrayToDword(BitStart, 32, ArraySize, data_source);
      }
      else {
        tempArray[ElementAt] = ReadBF_DwordArrayToDword(BitStart, BitsRemaining, ArraySize, data_source);
        break;
      }
      BitsRemaining -= 32;
      if (BitsRemaining == 0) {
        break;
      }
      BitStart += 32;
      ElementAt++;
    }
    for (int i = 0; i < 2; i++) { // LSB will be in Element 0
      uint64_t temp = 0;
      temp = tempArray[i];
      temp <<= (32 * i);
      data_to_return |= temp;
    }
  }
  return data_to_return;
}

// Array-array transfer with element bitwidth same as destination

void BitFieldManipulationClass::TransferByteArrayToByteArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint8_t *data_destination, const uint8_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 8);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 8);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      if (SourceBitWidth >= 8) {
        uint8_t temp = ReadBF_ByteArrayToByte(SourceBitStart, 8, SourceArrayElements, data_source);
        WriteBF_ByteToByteArray(DestinationBitStart, 8, DestinationArrayElements, data_destination, temp);
      }
      else {
        uint8_t temp = ReadBF_ByteArrayToByte(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_ByteToByteArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 8;
      if (SourceBitWidth == 0) { // no more bits need to be transferred
        break;
      }
      SourceBitStart += 8;
      DestinationBitStart += 8;
    }
  }
}

void BitFieldManipulationClass::TransferWordArrayToWordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint16_t *data_destination, const uint16_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 16);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 16);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      if (SourceBitWidth >= 16) {
        uint16_t temp = ReadBF_WordArrayToWord(SourceBitStart, 16, SourceArrayElements, data_source);
        WriteBF_WordToWordArray(DestinationBitStart, 16, DestinationArrayElements, data_destination, temp);
      }
      else {
        uint16_t temp = ReadBF_WordArrayToWord(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_WordToWordArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 16;
      if (SourceBitWidth == 0) { // no more bits need to be transferred
        break;
      }
      SourceBitStart += 16;
      DestinationBitStart += 16;
    }
  }
}

void BitFieldManipulationClass::TransferDwordArrayToDwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint32_t *data_destination, const uint32_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 32);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 32);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      if (SourceBitWidth >= 32) {
        uint32_t temp = ReadBF_DwordArrayToDword(SourceBitStart, 32, SourceArrayElements, data_source);
        WriteBF_DwordToDwordArray(DestinationBitStart, 32, DestinationArrayElements, data_destination, temp);
      }
      else {
        uint32_t temp = ReadBF_DwordArrayToDword(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_DwordToDwordArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 32;
      if (SourceBitWidth == 0) { // no more bits need to be transferred
        break;
      }
      SourceBitStart += 32;
      DestinationBitStart += 32;
    }
  }
}

void BitFieldManipulationClass::TransferQwordArrayToQwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint64_t *data_destination, const uint64_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 64);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 64);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      if (SourceBitWidth >= 64) {
        uint64_t temp = ReadBF_QwordArrayToQword(SourceBitStart, 64, SourceArrayElements, data_source);
        WriteBF_QwordToQwordArray(DestinationBitStart, 64, DestinationArrayElements, data_destination, temp);
      }
      else {
        uint64_t temp = ReadBF_QwordArrayToQword(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_QwordToQwordArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 64;
      if (SourceBitWidth == 0) { // no more bits need to be transferred
        break;
      }
      SourceBitStart += 64;
      DestinationBitStart += 64;
    }
  }
}

// Array-array transfer with source element bitwidth larger than destination element bitwidth

void BitFieldManipulationClass::TransferWordArrayToByteArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint8_t *data_destination, const uint16_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 16);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 8);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      uint16_t temp = 0;
      if (SourceBitWidth >= 16) {
        temp = ReadBF_WordArrayToWord(SourceBitStart, 16, SourceArrayElements, data_source);
        WriteBF_WordToByteArray(DestinationBitStart, 16, DestinationArrayElements, data_destination, temp);
      }
      else {
        temp = ReadBF_WordArrayToWord(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_WordToByteArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 16;
      if (SourceBitWidth == 0) {
        break;
      }
      SourceBitStart += 16;
      DestinationBitStart += 16;
    }
  }
}

void BitFieldManipulationClass::TransferDwordArrayToByteArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint8_t *data_destination, const uint32_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 32);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 8);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      uint32_t temp = 0;
      if (SourceBitWidth >= 32) {
        temp = ReadBF_DwordArrayToDword(SourceBitStart, 32, SourceArrayElements, data_source);
        WriteBF_DwordToByteArray(DestinationBitStart, 32, DestinationArrayElements, data_destination, temp);
      }
      else {
        temp = ReadBF_DwordArrayToDword(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_DwordToByteArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 32;
      if (SourceBitWidth == 0) {
        break;
      }
      SourceBitStart += 32;
      DestinationBitStart += 32;
    }
  }
}

void BitFieldManipulationClass::TransferQwordArrayToByteArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint8_t *data_destination, const uint64_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 64);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 8);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      uint64_t temp = 0;
      if (SourceBitWidth >= 64) {
        temp = ReadBF_QwordArrayToQword(SourceBitStart, 64, SourceArrayElements, data_source);
        WriteBF_QwordToByteArray(DestinationBitStart, 64, DestinationArrayElements, data_destination, temp);
      }
      else {
        temp = ReadBF_QwordArrayToQword(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_QwordToByteArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 64;
      if (SourceBitWidth == 0) {
        break;
      }
      SourceBitStart += 64;
      DestinationBitStart += 64;
    }
  }
}

void BitFieldManipulationClass::TransferDwordArrayToWordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint16_t *data_destination, const uint32_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 32);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 16);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      uint32_t temp = 0;
      if (SourceBitWidth >= 32) {
        temp = ReadBF_DwordArrayToDword(SourceBitStart, 32, SourceArrayElements, data_source);
        WriteBF_DwordToWordArray(DestinationBitStart, 32, DestinationArrayElements, data_destination, temp);
      }
      else {
        temp = ReadBF_DwordArrayToDword(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_DwordToWordArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 32;
      if (SourceBitWidth == 0) {
        break;
      }
      SourceBitStart += 32;
      DestinationBitStart += 32;
    }
  }
}

void BitFieldManipulationClass::TransferQwordArrayToWordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint16_t *data_destination, const uint64_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 64);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 16);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      uint64_t temp = 0;
      if (SourceBitWidth >= 64) {
        temp = ReadBF_QwordArrayToQword(SourceBitStart, 64, SourceArrayElements, data_source);
        WriteBF_QwordToWordArray(DestinationBitStart, 64, DestinationArrayElements, data_destination, temp);
      }
      else {
        temp = ReadBF_QwordArrayToQword(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_QwordToWordArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 64;
      if (SourceBitWidth == 0) {
        break;
      }
      SourceBitStart += 64;
      DestinationBitStart += 64;
    }
  }
}

void BitFieldManipulationClass::TransferQwordArrayToDwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint32_t *data_destination, const uint64_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 64);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 32);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      uint64_t temp = 0;
      if (SourceBitWidth >= 64) {
        temp = ReadBF_QwordArrayToQword(SourceBitStart, 64, SourceArrayElements, data_source);
        WriteBF_QwordToDwordArray(DestinationBitStart, 64, DestinationArrayElements, data_destination, temp);
      }
      else {
        temp = ReadBF_QwordArrayToQword(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_QwordToDwordArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 64;
      if (SourceBitWidth == 0) {
        break;
      }
      SourceBitStart += 64;
      DestinationBitStart += 64;
    }
  }
}

// Array-array transfer with source element bitwidth smaller than destination element bitwidth

void BitFieldManipulationClass::TransferByteArrayToWordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint16_t *data_destination, const uint8_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 8);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 16);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      uint16_t temp = 0;
      if (SourceBitWidth >= 16) {
        temp = ReadBF_ByteArrayToWord(SourceBitStart, 16, SourceArrayElements, data_source);
        WriteBF_WordToWordArray(DestinationBitStart, 16, DestinationArrayElements, data_destination, temp);
      }
      else {
        temp = ReadBF_ByteArrayToWord(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_WordToWordArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 16;
      if (SourceBitWidth == 0) {
        break;
      }
      SourceBitStart += 16;
      DestinationBitStart += 16;
    }
  }
}

void BitFieldManipulationClass::TransferByteArrayToDwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint32_t *data_destination, const uint8_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 8);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 32);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      uint32_t temp = 0;
      if (SourceBitWidth >= 32) {
        temp = ReadBF_ByteArrayToDword(SourceBitStart, 32, SourceArrayElements, data_source);
        WriteBF_DwordToDwordArray(DestinationBitStart, 32, DestinationArrayElements, data_destination, temp);
      }
      else {
        temp = ReadBF_ByteArrayToDword(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_DwordToDwordArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 32;
      if (SourceBitWidth == 0) {
        break;
      }
      SourceBitStart += 32;
      DestinationBitStart += 32;
    }
  }
}

void BitFieldManipulationClass::TransferByteArrayToQwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint64_t *data_destination, const uint8_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 8);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 64);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      uint64_t temp = 0;
      if (SourceBitWidth >= 64) {
        temp = ReadBF_ByteArrayToQword(SourceBitStart, 64, SourceArrayElements, data_source);
        WriteBF_QwordToQwordArray(DestinationBitStart, 64, DestinationArrayElements, data_destination, temp);
      }
      else {
        temp = ReadBF_ByteArrayToQword(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_QwordToQwordArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 64;
      if (SourceBitWidth == 0) {
        break;
      }
      SourceBitStart += 64;
      DestinationBitStart += 64;
    }
  }
}

void BitFieldManipulationClass::TransferWordArrayToDwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint32_t *data_destination, const uint16_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 16);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 32);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      uint32_t temp = 0;
      if (SourceBitWidth >= 32) {
        temp = ReadBF_WordArrayToDword(SourceBitStart, 32, SourceArrayElements, data_source);
        WriteBF_DwordToDwordArray(DestinationBitStart, 32, DestinationArrayElements, data_destination, temp);
      }
      else {
        temp = ReadBF_WordArrayToDword(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_DwordToDwordArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 32;
      if (SourceBitWidth == 0) {
        break;
      }
      SourceBitStart += 32;
      DestinationBitStart += 32;
    }
  }
}

void BitFieldManipulationClass::TransferWordArrayToQwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint64_t *data_destination, const uint16_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 16);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 64);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      uint64_t temp = 0;
      if (SourceBitWidth >= 64) {
        temp = ReadBF_WordArrayToQword(SourceBitStart, 64, SourceArrayElements, data_source);
        WriteBF_QwordToQwordArray(DestinationBitStart, 64, DestinationArrayElements, data_destination, temp);
      }
      else {
        temp = ReadBF_WordArrayToQword(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_QwordToQwordArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 64;
      if (SourceBitWidth == 0) {
        break;
      }
      SourceBitStart += 64;
      DestinationBitStart += 64;
    }
  }
}

void BitFieldManipulationClass::TransferDwordArrayToQwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint64_t *data_destination, const uint32_t *data_source) {
  uint16_t SourceMaximumBit = CalculateMaximumBit(SourceArrayElements, 16);
  uint16_t DestinationMaximumBit = CalculateMaximumBit(DestinationArrayElements, 64);
  if (SourceArrayElements != 0 && DestinationArrayElements != 0 && ((SourceBitStart + SourceBitWidth) - 1) <= DestinationMaximumBit) { // do not write beyond the destination array bounds
    while (true) {
      uint64_t temp = 0;
      if (SourceBitWidth >= 64) {
        temp = ReadBF_DwordArrayToQword(SourceBitStart, 64, SourceArrayElements, data_source);
        WriteBF_QwordToQwordArray(DestinationBitStart, 64, DestinationArrayElements, data_destination, temp);
      }
      else {
        temp = ReadBF_DwordArrayToQword(SourceBitStart, SourceBitWidth, SourceArrayElements, data_source);
        WriteBF_QwordToQwordArray(DestinationBitStart, SourceBitWidth, DestinationArrayElements, data_destination, temp);
        break;
      }
      SourceBitWidth -= 64;
      if (SourceBitWidth == 0) {
        break;
      }
      SourceBitStart += 64;
      DestinationBitStart += 64;
    }
  }
}

// Array bitshifts

void BitFieldManipulationClass::BitshiftArray_byte(int32_t BitshiftsRequired, uint16_t ArraySize, bool IsSigned, uint8_t *data_source) {
  if (BitshiftsRequired != 0 && BitshiftsRequired <= 65535L && BitshiftsRequired >= -65535L) {
    uint16_t MaximumArrayElement = ArraySize;
    MaximumArrayElement--;
    bool NegativeShift = false;
    if (BitshiftsRequired < 0) { // negative value will shift right; otherwise, will shift left
      NegativeShift = true;
      BitshiftsRequired ^= 0xFFFFFFFF; // invert it
      BitshiftsRequired++; // correct it
    }
    uint8_t BitsToShift = BitshiftsRequired; // no concern about higher bits here
    BitsToShift %= 8;
    uint16_t ByteShiftsRequired = BitshiftsRequired;
    ByteShiftsRequired /= 8;
    uint8_t PaddingByte = 0;
    if (NegativeShift == true && IsSigned == true && (data_source[0] & 0x80) != 0) {
      PaddingByte = 0xFF;
    }
    if (ByteShiftsRequired != 0) {
      if (NegativeShift == true) { // shifting right
        for (uint16_t ByteShiftCount = 0; ByteShiftCount < ByteShiftsRequired; ByteShiftCount++) {
          for (uint16_t BytesShifted = MaximumArrayElement; BytesShifted > 0; BytesShifted--) {
            data_source[BytesShifted] = data_source[(BytesShifted - 1)];
          }
          data_source[0] = PaddingByte;
        }
      }
      else { // shifting left
        for (uint16_t ByteShiftCount = 0; ByteShiftCount < ByteShiftsRequired; ByteShiftCount++) {
          for (uint16_t BytesShifted = 0; BytesShifted < MaximumArrayElement; BytesShifted++) {
            data_source[BytesShifted] = data_source[(BytesShifted + 1)];
          }
          data_source[MaximumArrayElement] = PaddingByte;
        }
      }
    }
    if (BitsToShift != 0) {
      if (NegativeShift == true) { // shifting right
        for (uint8_t BitshiftCount = 0; BitshiftCount < BitsToShift; BitshiftCount++) {
          for (uint16_t ElementCount = MaximumArrayElement; ElementCount > 0; ElementCount--) {
            data_source[ElementCount] >>= 1;
            if ((data_source[(ElementCount - 1)] & 0x01) != 0) { // if high, move the LSB from the previous element to the MSB on the current element
              data_source[ElementCount] |= 0x80;
            }
            else { // deal with unwanted sign bit
              data_source[ElementCount] &= (~0x80);
            }
          }
          data_source[ByteShiftsRequired] >>= 1;
          if (PaddingByte != 0) { // extend the sign if necessary
            data_source[ByteShiftsRequired] |= 0x80;
          }
          else { // deal with unwanted sign bit
            data_source[ByteShiftsRequired] &= (~0x80);
          }
        }
      }
      else { // shifting left
        for (uint8_t BitshiftCount = 0; BitshiftCount < BitsToShift; BitshiftCount++) {
          data_source[0] <<= 1;
          for (uint16_t ElementCount = 0; ElementCount < MaximumArrayElement; ElementCount++) {
            if ((data_source[(ElementCount + 1)] & 0x80) != 0) { // if high, move the MSB from the next element to the LSB on the current element
              data_source[ElementCount] |= 0x01;
            }
            data_source[(ElementCount + 1)] <<= 1;
          }
        }
      }
    }
  }
}

void BitFieldManipulationClass::BitshiftArray_word(int32_t BitshiftsRequired, uint16_t ArraySize, bool IsSigned, uint16_t *data_source) {
  if (BitshiftsRequired != 0 && BitshiftsRequired <= 65535L && BitshiftsRequired >= -65535L) {
    uint16_t MaximumArrayElement = ArraySize;
    MaximumArrayElement--;
    bool NegativeShift = false;
    if (BitshiftsRequired < 0) { // negative value will shift right; otherwise, will shift left
      NegativeShift = true;
      BitshiftsRequired ^= 0xFFFFFFFF; // invert it
      BitshiftsRequired++; // correct it
    }
    uint8_t BitsToShift = BitshiftsRequired; // no concern about higher bits here
    BitsToShift %= 16;
    uint16_t ByteShiftsRequired = BitshiftsRequired;
    ByteShiftsRequired /= 16;
    uint8_t PaddingByte = 0;
    if (NegativeShift == true && IsSigned == true && (data_source[0] & 0x8000) != 0) {
      PaddingByte = 0xFF;
    }
    if (ByteShiftsRequired != 0) {
      if (NegativeShift == true) { // shifting right
        for (uint16_t ByteShiftCount = 0; ByteShiftCount < ByteShiftsRequired; ByteShiftCount++) {
          for (uint16_t BytesShifted = MaximumArrayElement; BytesShifted > 0; BytesShifted--) {
            data_source[BytesShifted] = data_source[(BytesShifted - 1)];
          }
          data_source[0] = PaddingByte;
        }
      }
      else { // shifting left
        for (uint16_t ByteShiftCount = 0; ByteShiftCount < ByteShiftsRequired; ByteShiftCount++) {
          for (uint16_t BytesShifted = 0; BytesShifted < MaximumArrayElement; BytesShifted++) {
            data_source[BytesShifted] = data_source[(BytesShifted + 1)];
          }
          data_source[MaximumArrayElement] = PaddingByte;
        }
      }
    }
    if (BitsToShift != 0) {
      if (NegativeShift == true) { // shifting right
        for (uint8_t BitshiftCount = 0; BitshiftCount < BitsToShift; BitshiftCount++) {
          for (uint16_t ElementCount = MaximumArrayElement; ElementCount > 0; ElementCount--) {
            data_source[ElementCount] >>= 1;
            if ((data_source[(ElementCount - 1)] & 0x01) != 0) { // if high, move the LSB from the previous element to the MSB on the current element
              data_source[ElementCount] |= 0x8000;
            }
            else { // deal with unwanted sign bit
              data_source[ElementCount] &= (~0x8000);
            }
          }
          data_source[ByteShiftsRequired] >>= 1;
          if (PaddingByte != 0) { // extend the sign if necessary
            data_source[ByteShiftsRequired] |= 0x8000;
          }
          else { // deal with unwanted sign bit
            data_source[ByteShiftsRequired] &= (~0x8000);
          }
        }
      }
      else { // shifting left
        for (uint8_t BitshiftCount = 0; BitshiftCount < BitsToShift; BitshiftCount++) {
          data_source[0] <<= 1;
          for (uint16_t ElementCount = 0; ElementCount < MaximumArrayElement; ElementCount++) {
            if ((data_source[(ElementCount + 1)] & 0x8000) != 0) { // if high, move the MSB from the next element to the LSB on the current element
              data_source[ElementCount] |= 0x01;
            }
            data_source[(ElementCount + 1)] <<= 1;
          }
        }
      }
    }
  }
}

void BitFieldManipulationClass::BitshiftArray_dword(int32_t BitshiftsRequired, uint16_t ArraySize, bool IsSigned, uint32_t *data_source) {
  if (BitshiftsRequired != 0 && BitshiftsRequired <= 65535L && BitshiftsRequired >= -65535L) {
    uint16_t MaximumArrayElement = ArraySize;
    MaximumArrayElement--;
    bool NegativeShift = false;
    if (BitshiftsRequired < 0) { // negative value will shift right; otherwise, will shift left
      NegativeShift = true;
      BitshiftsRequired ^= 0xFFFFFFFF; // invert it
      BitshiftsRequired++; // correct it
    }
    uint8_t BitsToShift = BitshiftsRequired; // no concern about higher bits here
    BitsToShift %= 32;
    uint16_t ByteShiftsRequired = BitshiftsRequired;
    ByteShiftsRequired /= 32;
    uint8_t PaddingByte = 0;
    if (NegativeShift == true && IsSigned == true && (data_source[0] & 0x80000000) != 0) {
      PaddingByte = 0xFF;
    }
    if (ByteShiftsRequired != 0) {
      if (NegativeShift == true) { // shifting right
        for (uint16_t ByteShiftCount = 0; ByteShiftCount < ByteShiftsRequired; ByteShiftCount++) {
          for (uint16_t BytesShifted = MaximumArrayElement; BytesShifted > 0; BytesShifted--) {
            data_source[BytesShifted] = data_source[(BytesShifted - 1)];
          }
          data_source[0] = PaddingByte;
        }
      }
      else { // shifting left
        for (uint16_t ByteShiftCount = 0; ByteShiftCount < ByteShiftsRequired; ByteShiftCount++) {
          for (uint16_t BytesShifted = 0; BytesShifted < MaximumArrayElement; BytesShifted++) {
            data_source[BytesShifted] = data_source[(BytesShifted + 1)];
          }
          data_source[MaximumArrayElement] = PaddingByte;
        }
      }
    }
    if (BitsToShift != 0) {
      if (NegativeShift == true) { // shifting right
        for (uint8_t BitshiftCount = 0; BitshiftCount < BitsToShift; BitshiftCount++) {
          for (uint16_t ElementCount = MaximumArrayElement; ElementCount > 0; ElementCount--) {
            data_source[ElementCount] >>= 1;
            if ((data_source[(ElementCount - 1)] & 0x01) != 0) { // if high, move the LSB from the previous element to the MSB on the current element
              data_source[ElementCount] |= 0x80000000;
            }
            else { // deal with unwanted sign bit
              data_source[ElementCount] &= (~0x80000000);
            }
          }
          data_source[ByteShiftsRequired] >>= 1;
          if (PaddingByte != 0) { // extend the sign if necessary
            data_source[ByteShiftsRequired] |= 0x80000000;
          }
          else { // deal with unwanted sign bit
            data_source[ByteShiftsRequired] &= (~0x80000000);
          }
        }
      }
      else { // shifting left
        for (uint8_t BitshiftCount = 0; BitshiftCount < BitsToShift; BitshiftCount++) {
          data_source[0] <<= 1;
          for (uint16_t ElementCount = 0; ElementCount < MaximumArrayElement; ElementCount++) {
            if ((data_source[(ElementCount + 1)] & 0x80000000) != 0) { // if high, move the MSB from the next element to the LSB on the current element
              data_source[ElementCount] |= 0x01;
            }
            data_source[(ElementCount + 1)] <<= 1;
          }
        }
      }
    }
  }
}

void BitFieldManipulationClass::BitshiftArray_qword(int32_t BitshiftsRequired, uint16_t ArraySize, bool IsSigned, uint64_t *data_source) {
  if (BitshiftsRequired != 0 && BitshiftsRequired <= 65535L && BitshiftsRequired >= -65535L) {
    uint16_t MaximumArrayElement = ArraySize;
    MaximumArrayElement--;
    bool NegativeShift = false;
    if (BitshiftsRequired < 0) { // negative value will shift right; otherwise, will shift left
      NegativeShift = true;
      BitshiftsRequired ^= 0xFFFFFFFF; // invert it
      BitshiftsRequired++; // correct it
    }
    uint8_t BitsToShift = BitshiftsRequired; // no concern about higher bits here
    BitsToShift %= 64;
    uint16_t ByteShiftsRequired = BitshiftsRequired;
    ByteShiftsRequired /= 64;
    uint8_t PaddingByte = 0;
    if (NegativeShift == true && IsSigned == true && (data_source[0] & 9223372036854775808ULL) != 0) {
      PaddingByte = 0xFF;
    }
    if (ByteShiftsRequired != 0) {
      if (NegativeShift == true) { // shifting right
        for (uint16_t ByteShiftCount = 0; ByteShiftCount < ByteShiftsRequired; ByteShiftCount++) {
          for (uint16_t BytesShifted = MaximumArrayElement; BytesShifted > 0; BytesShifted--) {
            data_source[BytesShifted] = data_source[(BytesShifted - 1)];
          }
          data_source[0] = PaddingByte;
        }
      }
      else { // shifting left
        for (uint16_t ByteShiftCount = 0; ByteShiftCount < ByteShiftsRequired; ByteShiftCount++) {
          for (uint16_t BytesShifted = 0; BytesShifted < MaximumArrayElement; BytesShifted++) {
            data_source[BytesShifted] = data_source[(BytesShifted + 1)];
          }
          data_source[MaximumArrayElement] = PaddingByte;
        }
      }
    }
    if (BitsToShift != 0) {
      if (NegativeShift == true) { // shifting right
        for (uint8_t BitshiftCount = 0; BitshiftCount < BitsToShift; BitshiftCount++) {
          for (uint16_t ElementCount = MaximumArrayElement; ElementCount > 0; ElementCount--) {
            data_source[ElementCount] >>= 1;
            if ((data_source[(ElementCount - 1)] & 0x01) != 0) { // if high, move the LSB from the previous element to the MSB on the current element
              data_source[ElementCount] |= 9223372036854775808ULL;
            }
            else { // deal with unwanted sign bit
              data_source[ElementCount] &= (~9223372036854775808ULL);
            }
          }
          data_source[ByteShiftsRequired] >>= 1;
          if (PaddingByte != 0) { // extend the sign if necessary
            data_source[ByteShiftsRequired] |= 9223372036854775808ULL;
          }
          else { // deal with unwanted sign bit
            data_source[ByteShiftsRequired] &= (~9223372036854775808ULL);
          }
        }
      }
      else { // shifting left
        for (uint8_t BitshiftCount = 0; BitshiftCount < BitsToShift; BitshiftCount++) {
          data_source[0] <<= 1;
          for (uint16_t ElementCount = 0; ElementCount < MaximumArrayElement; ElementCount++) {
            if ((data_source[(ElementCount + 1)] & 9223372036854775808ULL) != 0) { // if high, move the MSB from the next element to the LSB on the current element
              data_source[ElementCount] |= 0x01;
            }
            data_source[(ElementCount + 1)] <<= 1;
          }
        }
      }
    }
  }
}

BitFieldManipulationClass BitFieldManipulation;