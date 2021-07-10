#BitFieldManipulation Library#

BitFieldManipulation manipulates a bit field without modifying anything other than the bit field being manipulated

Revisions:
1.0.0	First release

## Usage

BitFieldManipulation.WriteBF_(byte/word/dword/qword)(BitStart, BitWidth, data_source, data_field) - returns the data source with the field defined by BitStart/BitWidth changed to the value in the data field
BitFieldManipulation.ReadBF_(byte/word/dword/qword)(BitStart, BitWidth, data_source) - returns the field defined by BitStart/BitWidth extracted from the data source

Quad word (uint64_t/long long) is currently untested and requires compiler support inclduing bitshift operations.