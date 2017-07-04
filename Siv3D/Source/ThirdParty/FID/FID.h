// FID.h
#ifndef __FID_H_INCLUDED__
#define __FID_H_INCLUDED__

class FID
{
private:
	const size_t smallSize = 8; // lg(n) / 2
	const size_t largeSize = 256; // lg(n) ^ 2
	const size_t popCountLength = 256; // 2^smallSize

	uint16_t* blockLarge; // lg n bit per element
	uint8_t* blockSmall; // lg largeSize bit per element
	uint8_t* originalBit;  // total: ceil(n / 8) * 8 bit
	size_t originalBitLength;

	uint8_t popCount(uint8_t bits);

public:
	~FID();
	FID(const uint8_t* BIT);
	uint16_t rank(int pos, int digit);
	uint16_t select(int idx, int digit);
};

#endif
