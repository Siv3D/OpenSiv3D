#include <iostream>
#include <cstring>
#include "FID.h"

FID::~FID() {
	delete[] blockLarge;
	delete[] blockSmall;
	delete[] originalBit;
}

FID::FID(const uint8_t* BIT) {
	// BIT確保の方法は以下のとおり
	// const char* BIT = "1011011100001111..."
	// orignalBit = {0b10110111,00001111,...,}
	originalBitLength = std::strlen((char*)BIT);

	{
		size_t originalBitUint8Length = (originalBitLength + 7) / 8; // ceil(originalBitLength/8) -> (originalBitLength+7)/8
		originalBit = new uint8_t[originalBitUint8Length];
	}

	for (size_t i = 0; i < originalBitLength; ++i)
	{
		const size_t upperPos = i >> 3;
		const size_t lowerPos = i & 0x07;
		const uint8_t lowerPosMask = (1 << (7 - lowerPos));

		if (BIT[i] == '1')
		{
			originalBit[upperPos] |= lowerPosMask;
		}
		else
		{
			originalBit[upperPos] &= ~lowerPosMask;
		}
	}


	// initialize blockLarge
	size_t largeLength = (originalBitLength + largeSize - 1) / largeSize;
	blockLarge = new uint16_t[largeLength + (originalBitLength % largeSize != 0)];

	blockLarge[0] = 0;
	for (size_t i = 0, largeIdx = 0; i < originalBitLength && largeIdx < largeLength;  ++i)
	{
		if (i % largeSize == 0) {
			++largeIdx;
			blockLarge[largeIdx] = blockLarge[largeIdx - 1];
		}
		const size_t upperPos = i >> 3;
		const size_t lowerPos = i & 0x07;
		const uint8_t lowerPosMask = (1 << (7 - lowerPos));

		if ( originalBit[upperPos] & lowerPosMask) {
			++blockLarge[largeIdx];
		}
	}

	// initialize blockSmall
	size_t smallLength = (originalBitLength + smallSize - 1) / smallSize;
	blockSmall = new uint8_t[smallLength + (originalBitLength % smallSize != 0)];

	blockSmall[0] = 0;

	for (size_t i = 0, smallIdx = 0; i < originalBitLength && smallIdx < smallLength; ++i)
	{
		if (i % smallSize == 0)
		{
			if (i % largeSize == 0)
			{
				blockSmall[smallIdx] = 0;
			}

			++smallIdx;
			blockSmall[smallIdx] = blockSmall[smallIdx - 1];
		}

		const size_t upperPos = i >> 3;
		const size_t lowerPos = i & 0x07;
		const size_t lowerPosMask = (1 << (7 - lowerPos));

		if ( originalBit[upperPos] & lowerPosMask)
		{
			++blockSmall[smallIdx];
		}
	}

	return;
}

uint16_t FID::rank(int pos, int digit) {
	// bitmask: #tailing zero is (pos % smallSize)
	// Ex. 11100000 #tailing zero is 5
	const uint8_t mask = 0xff << (smallSize - (pos % smallSize));
	const uint8_t lowerBit = originalBit[pos >> 3];

	uint16_t result = blockLarge[pos / largeSize] + blockSmall[pos / smallSize] + popCount(lowerBit & mask);
	if (digit == 0) result = static_cast<uint16_t>(pos - result);
	return result;
}

uint16_t FID::select(int idx, int digit)
{
	uint16_t lower = 0, upper = static_cast<uint16_t>(originalBitLength);
	while (upper - lower > 1)
	{
		const uint16_t mid = (lower + upper) / 2;
		if (rank(mid, digit) <= idx)
		{
			lower = mid;
		}
		else
		{
			upper = mid;
		}
	}
	return lower;
}


uint8_t FID::popCount(uint8_t bits)
{
    bits = (bits & 0x55) + (bits >> 1 & 0x55);
    bits = (bits & 0x33) + (bits >> 2 & 0x33);
    return (bits & 0x0f) + (bits >> 4 & 0x0f);
}


/*
int main() {
	const uint8_t* B = "111010000000010100010101001100000000101010000000111000101111000000000000010001010010100001000001010100010001010001001001010000101000010001000101001010000100000101010001000101000100100101000010100001000100010100101000010000010101000100010100010010010100001010000100";
	FID fid = FID(B);
	const int lenB = strlen(B);

	for (int i = 0, r = 0; i < lenB; ++i) {
		if (i != 0) r += B[i - 1] - '0';

		if (fid.rank(i, 1) != r) {
			printf("rank(B,%d,0):%d [counted naively:%d]\n", i, fid.rank(i, 0), i - r);
			printf("rank(B,%d,1):%d [counted naively:%d]\n", i, fid.rank(i, 1), r);
		}
	}

	for (int i = 0, r = 0; i < lenB; ++i) {
		r += B[i] - '0';
		if (B[i] == '1') {
			printf("select(B,%d,1):%d [counted naively:%d]\n", r - 1, fid.select(r - 1, 1), i);
		} else {
			printf("select(B,%d,0):%d [counted naively:%d]\n", i - r , fid.select(i - r, 0), i);
		}
	}
}
*/