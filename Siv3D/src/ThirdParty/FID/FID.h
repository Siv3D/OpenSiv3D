/*
	MIT License

	Copyright (c) 2017 hec

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

// FID.h
#ifndef __FID_H_INCLUDED__
#define __FID_H_INCLUDED__

class FID
{
private:
	const size_t smallSize = 8; // lg(n) / 2
	const size_t largeSize = 256; // lg(n) ^ 2
	//const size_t popCountLength = 256; // 2^smallSize

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
