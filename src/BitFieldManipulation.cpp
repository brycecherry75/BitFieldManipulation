#include "BitFieldManipulation.h"

BitFieldManipulationClass BitFieldManipulation;

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