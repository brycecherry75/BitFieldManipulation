#ifndef BitFieldManipulation_h
#define BitFieldManipulation_h

#include <Arduino.h>

class BitFieldManipulationClass {
  public:
    uint8_t WriteBF_byte(uint8_t BitStart, uint8_t BitWidth, uint8_t data_source, uint8_t data_field);
    uint16_t WriteBF_word(uint8_t BitStart, uint8_t BitWidth, uint16_t data_source, uint16_t data_field);
    uint32_t WriteBF_dword(uint8_t BitStart, uint8_t BitWidth, uint32_t data_source, uint32_t data_field);
    uint64_t WriteBF_qword(uint8_t BitStart, uint8_t BitWidth, uint64_t data_source, uint64_t data_field);
    uint8_t ReadBF_byte(uint8_t BitStart, uint8_t BitWidth, uint8_t data_source);
    uint16_t ReadBF_word(uint8_t BitStart, uint8_t BitWidth, uint16_t data_source);
    uint32_t ReadBF_dword(uint8_t BitStart, uint8_t BitWidth, uint32_t data_source);
    uint64_t ReadBF_qword(uint8_t BitStart, uint8_t BitWidth, uint64_t data_source);
};

extern BitFieldManipulationClass BitFieldManipulation;

#endif