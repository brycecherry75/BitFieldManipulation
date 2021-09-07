#BitFieldManipulation Library#

BitFieldManipulation manipulates a bit field without modifying anything other than the bit field being manipulated

Revisions:
1.0.0	First release
1.1.0	Added support for manipulating arrays including array-array transfers and bitshifts along with inclusion of bit order reversal functions

## Usage

WriteBF_(byte/word/dword/qword)(BitStart, BitWidth, data_source, data_field) - returns the data source with the field defined by BitStart/BitWidth changed to the value in the data field

ReadBF_(byte/word/dword/qword)(BitStart, BitWidth, data_source) - returns the field defined by BitStart/BitWidth extracted from the data source

WriteBF_(Byte/Word/Dword/Qword)To(Byte/Word/Dword/Qword)Array(BitStart, BitWidth, ArraySize, *data_destination, data_field) - writes data_field starting at BitStart with width corresponding to BitWidth

Transfer(Byte/Word/Dword/Qword)ArrayTo(Byte/Word/Dword/Qword)Array(BitStart, BitWidth, DestinationArrayElements, SourceArrayElements, *data_destination, *data_source) - transfers data_source to data_destination with LSB of data_source starting at BitStart

ReadBF_(Byte/Word/Dword/Qword)ArrayTo(Byte/Word/Dword/Qword)(BitStart, BitWidth, ArraySize, *data_source) - returns the field defined by BitStart/BitWidth extracted from the data source

BitShiftBF_(byte/word/dword/qword)(BitShiftsRequired, ArraySize, IsSigned, *data_source) - perform bit shifting on data_source array; BitShfitsRequired is (-65535 right to 65535 left) and IsSigned is a bool which must only be used on a negative BitShiftsRequired value (pads with 1) or otherwise it will pad with 0

ReverseBitOrder_(byte/word/dword/qword)() - reverses the bit order

ReverseBitOrder_(byte/word/dword/qword)Array(array_elements, *data_source) - reverses the bit order in each element of an array and the order of the elements thereof

NullArray_(byte/word/dword/qword)(array_elements, *data_source) - nulls the contents of an array

In many programming lanugages, data_source elements start at 0 from the left and additionally in many component datasheets, MSB to LSB is read from left to right.

Quad word (uint64_t/long long) is currently untested and requires compiler support inclduing bitshift operations.