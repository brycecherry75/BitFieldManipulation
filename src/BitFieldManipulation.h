#ifndef BitFieldManipulation_h
#define BitFieldManipulation_h

#include <Arduino.h>

// for CalculateShiftParameters array return
#define BitFieldManipulation_LSBoffset 0
#define BitFieldManipulation_LSBwidth 1
#define BitFieldManipulation_MSBbits 2
#define BitFieldManipulation_ShiftParameterCount 3 // array elements

class BitFieldManipulationClass {
  public:

    // Bit order reversal

    uint8_t ReverseBitOrder_byte(uint8_t data_source);
    uint16_t ReverseBitOrder_word(uint16_t data_source);
    uint32_t ReverseBitOrder_dword(uint32_t data_source);
    uint64_t ReverseBitOrder_qword(uint64_t data_source);
    void ReverseBitOrder_byteArray(uint16_t array_elements, uint8_t *data_source);
    void ReverseBitOrder_wordArray(uint16_t array_elements, uint16_t *data_source);
    void ReverseBitOrder_dwordArray(uint16_t array_elements, uint32_t *data_source);
    void ReverseBitOrder_qwordArray(uint16_t array_elements, uint64_t *data_source);

    // Nulling arrays

    void NullArray_byte(uint16_t array_elements, uint8_t *data_source);
    void NullArray_word(uint16_t array_elements, uint16_t *data_source);
    void NullArray_dword(uint16_t array_elements, uint32_t *data_source);
    void NullArray_qword(uint16_t array_elements, uint64_t *data_source);

    // Reading/writing a bitfield

    uint8_t WriteBF_byte(uint8_t BitStart, uint8_t BitWidth, uint8_t data_source, uint8_t data_field);
    uint16_t WriteBF_word(uint8_t BitStart, uint8_t BitWidth, uint16_t data_source, uint16_t data_field);
    uint32_t WriteBF_dword(uint8_t BitStart, uint8_t BitWidth, uint32_t data_source, uint32_t data_field);
    uint64_t WriteBF_qword(uint8_t BitStart, uint8_t BitWidth, uint64_t data_source, uint64_t data_field);
    uint8_t ReadBF_byte(uint8_t BitStart, uint8_t BitWidth, uint8_t data_source);
    uint16_t ReadBF_word(uint8_t BitStart, uint8_t BitWidth, uint16_t data_source);
    uint32_t ReadBF_dword(uint8_t BitStart, uint8_t BitWidth, uint32_t data_source);
    uint64_t ReadBF_qword(uint8_t BitStart, uint8_t BitWidth, uint64_t data_source);

    // Single element write to array with source bitwidth same as destination element bitwidth

    void WriteBF_ByteToByteArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint8_t *data_destination, uint8_t data_field);
    void WriteBF_WordToWordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint16_t *data_destination, uint16_t data_field);
    void WriteBF_DwordToDwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint32_t *data_destination, uint32_t data_field);
    void WriteBF_QwordToQwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint64_t *data_destination, uint64_t data_field);

    // Single element read from array with source bitwidth same as destination element bitwidth

    uint8_t ReadBF_ByteArrayToByte(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint8_t *data_source);
    uint16_t ReadBF_WordArrayToWord(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint16_t *data_source);
    uint32_t ReadBF_DwordArrayToDword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint32_t *data_source);
    uint64_t ReadBF_QwordArrayToQword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint64_t *data_source);

    // Single element write to array with source bitwidth larger than destination element bitwidth

    void WriteBF_WordToByteArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint8_t *data_destination, uint16_t data_field);
    void WriteBF_DwordToByteArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint8_t *data_destination, uint32_t data_field);
    void WriteBF_QwordToByteArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint8_t *data_destination, uint64_t data_field);
    void WriteBF_DwordToWordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint16_t *data_destination, uint32_t data_field);
    void WriteBF_QwordToWordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint16_t *data_destination, uint64_t data_field);
    void WriteBF_QwordToDwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint32_t *data_destination, uint64_t data_field);

    // Single element read from array with source bitwidth larger than destination element bitwidth

    uint8_t ReadBF_WordArrayToByte(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint16_t *data_source);
    uint8_t ReadBF_DwordArrayToByte(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint32_t *data_source);
    uint16_t ReadBF_DwordArrayToWord(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint32_t *data_source);
    uint8_t ReadBF_QwordArrayToByte(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint64_t *data_source);
    uint16_t ReadBF_QwordArrayToWord(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint64_t *data_source);
    uint32_t ReadBF_QwordArrayToDword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint64_t *data_source);

    // Single element write to array with source bitwidth smaller than destination element bitwidth

    void WriteBF_ByteToWordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint16_t *data_destination, uint8_t data_field);
    void WriteBF_ByteToDwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint32_t *data_destination, uint8_t data_field);
    void WriteBF_ByteToQwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint64_t *data_destination, uint8_t data_field);
    void WriteBF_WordToDwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint32_t *data_destination, uint16_t data_field);
    void WriteBF_WordToQwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint64_t *data_destination, uint16_t data_field);
    void WriteBF_DwordToQwordArray(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, uint64_t *data_destination, uint32_t data_field);

    // Single element read from array with source bitwidth smaller than destination element bitwidth

    uint16_t ReadBF_ByteArrayToWord(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint8_t *data_source);
    uint32_t ReadBF_ByteArrayToDword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint8_t *data_source);
    uint64_t ReadBF_ByteArrayToQword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint8_t *data_source);
    uint32_t ReadBF_WordArrayToDword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint16_t *data_source);
    uint64_t ReadBF_WordArrayToQword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint16_t *data_source);
    uint64_t ReadBF_DwordArrayToQword(uint16_t BitStart, uint8_t BitWidth, uint16_t ArraySize, const uint32_t *data_source);

    // Array-array transfer with element bitwidth same as destination element bitwidth

    void TransferByteArrayToByteArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements,  uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint8_t *data_destination, const uint8_t *data_source);
    void TransferWordArrayToWordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements,  uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint16_t *data_destination, const uint16_t *data_source);
    void TransferDwordArrayToDwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint32_t *data_destination, const uint32_t *data_source);
    void TransferQwordArrayToQwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint64_t *data_destination, const uint64_t *data_source);

    // Array-array transfer with source element bitwidth larger than destination element bitwidth

    void TransferWordArrayToByteArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint8_t *data_destination, const uint16_t *data_source);
    void TransferDwordArrayToByteArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint8_t *data_destination, const uint32_t *data_source);
    void TransferQwordArrayToByteArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint8_t *data_destination, const uint64_t *data_source);
    void TransferDwordArrayToWordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint16_t *data_destination, const uint32_t *data_source);
    void TransferQwordArrayToWordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint16_t *data_destination, const uint64_t *data_source);
    void TransferQwordArrayToDwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint32_t *data_destination, const uint64_t *data_source);

    // Array-array transfer with source element bitwidth smaller than destination element bitwidth

    void TransferByteArrayToWordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint16_t *data_destination, const uint8_t *data_source);
    void TransferByteArrayToDwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint32_t *data_destination, const uint8_t *data_source);
    void TransferByteArrayToQwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint64_t *data_destination, const uint8_t *data_source);
    void TransferWordArrayToDwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint32_t *data_destination, const uint16_t *data_source);
    void TransferWordArrayToQwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint64_t *data_destination, const uint16_t *data_source);
    void TransferDwordArrayToQwordArray(uint16_t SourceBitStart, uint16_t SourceBitWidth, uint16_t SourceArrayElements, uint16_t DestinationBitStart, uint16_t DestinationArrayElements, uint64_t *data_destination, const uint32_t *data_source);

    // Array bitshifts

    void BitshiftArray_byte(int32_t BitshiftsRequired, uint16_t ArraySize, bool IsSigned, uint8_t *data_source);
    void BitshiftArray_word(int32_t BitshiftsRequired, uint16_t ArraySize, bool IsSigned, uint16_t *data_source);
    void BitshiftArray_dword(int32_t BitshiftsRequired, uint16_t ArraySize, bool IsSigned, uint32_t *data_source);
    void BitshiftArray_qword(int32_t BitshiftsRequired, uint16_t ArraySize, bool IsSigned, uint64_t *data_source);

    private:
    uint16_t CalculateShiftParameters(uint16_t MaximumBit, uint16_t BitStart, uint8_t BitWidth, uint8_t ElementSize, uint8_t *ParametersToReturn);
    uint16_t CalculateMaximumBit(uint16_t ArraySize, uint8_t ElementSize);
};

extern BitFieldManipulationClass BitFieldManipulation;

#endif