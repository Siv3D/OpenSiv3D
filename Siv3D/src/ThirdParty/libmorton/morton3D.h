#pragma once

// Libmorton - Methods to encode/decode 64-bit morton codes from/to 32-bit (x,y,z) coordinates
// Warning: morton.h will always point to the functions that use the fastest available method.

#include <algorithm>
#include <stdint.h>
#include <math.h>
#include "morton3D_LUTs.h"
#include "morton_common.h"

#define EIGHTBITMASK (morton) 0x000000FF
#define NINEBITMASK (morton) 0x000001FF

namespace libmorton {
	// AVAILABLE METHODS FOR ENCODING
	template<typename morton, typename coord> inline morton m3D_e_sLUT(const coord x, const coord y, const coord z);
	template<typename morton, typename coord> inline morton m3D_e_sLUT_ET(const coord x, const coord y, const coord z);
	template<typename morton, typename coord> inline morton m3D_e_LUT(const coord x, const coord y, const coord z);
	template<typename morton, typename coord> inline morton m3D_e_LUT_ET(const coord x, const coord y, const coord z);
	template<typename morton, typename coord> inline morton m3D_e_magicbits(const coord x, const coord y, const coord z);
	template<typename morton, typename coord> inline morton m3D_e_for(const coord x, const coord y, const coord z);
	template<typename morton, typename coord> inline morton m3D_e_for_ET(const coord x, const coord y, const coord z);

	// AVAILABLE METHODS FOR DECODING
	template<typename morton, typename coord> inline void m3D_d_sLUT(const morton m, coord& x, coord& y, coord& z);
	template<typename morton, typename coord> inline void m3D_d_sLUT_ET(const morton m, coord& x, coord& y, coord& z);
	template<typename morton, typename coord> inline void m3D_d_LUT(const morton m, coord& x, coord& y, coord& z);
	template<typename morton, typename coord> inline void m3D_d_LUT_ET(const morton m, coord& x, coord& y, coord& z);
	template<typename morton, typename coord> inline void m3D_d_magicbits(const morton m, coord& x, coord& y, coord& z);
	template<typename morton, typename coord> inline void m3D_d_for(const morton m, coord& x, coord& y, coord& z);
	template<typename morton, typename coord> inline void m3D_d_for_ET(const morton m, coord& x, coord& y, coord& z);

	// ENCODE 3D Morton code : Pre-Shifted LookUpTable (sLUT)
	template<typename morton, typename coord>
	inline morton m3D_e_sLUT(const coord x, const coord y, const coord z) {
		morton answer = 0;
		for (unsigned int i = sizeof(coord); i > 0; --i) {
			unsigned int shift = (i - 1) * 8;
			answer =
				answer << 24 |
				(Morton3D_encode_z_256[(z >> shift) & EIGHTBITMASK] |
					Morton3D_encode_y_256[(y >> shift) & EIGHTBITMASK] |
					Morton3D_encode_x_256[(x >> shift) & EIGHTBITMASK]);
		}
		return answer;
	}

	// ENCODE 3D Morton code : LookUpTable (LUT)
	template<typename morton, typename coord>
	inline morton m3D_e_LUT(const coord x, const coord y, const coord z) {
		morton answer = 0;
		for (unsigned int i = sizeof(coord); i > 0; --i) {
			unsigned int shift = (i - 1) * 8;
			answer =
				answer << 24 |
				(Morton3D_encode_x_256[(z >> shift) & EIGHTBITMASK] << morton(2)) |
				(Morton3D_encode_x_256[(y >> shift) & EIGHTBITMASK] << morton(1)) |
				Morton3D_encode_x_256[(x >> shift) & EIGHTBITMASK];
		}
		return answer;
	}

	// HELPER METHOD for ET LUT encode
	template<typename morton, typename coord>
	inline morton compute3D_ET_LUT_encode(const coord c, const coord *LUT) {
		unsigned long maxbit = 0;
		if (findFirstSetBit<coord>(c, &maxbit) == 0) { return 0; }
		morton answer = 0;
		for (int i = (int)ceil((maxbit + 1) / 8.0f); i >= 0; --i) {
			unsigned int shift = i * 8;
			answer = answer << 24 | (LUT[(c >> shift) & EIGHTBITMASK]);
		}
		return answer;
	}

	// ENCODE 3D Morton code : Pre-shifted LookUpTable (LUT) (Early Termination version)
	// This version tries to terminate early when there are no more bits to process
	// Figuring this out is probably too costly in most cases.
	template<typename morton, typename coord>
	inline morton m3D_e_sLUT_ET(const coord x, const coord y, const coord z) {
		morton answer_x = compute3D_ET_LUT_encode<morton, coord>(x, Morton3D_encode_x_256);
		morton answer_y = compute3D_ET_LUT_encode<morton, coord>(y, Morton3D_encode_y_256);
		morton answer_z = compute3D_ET_LUT_encode<morton, coord>(z, Morton3D_encode_z_256);
		return answer_z | answer_y | answer_x;
	}

	// ENCODE 3D Morton code : LookUpTable (LUT) (Early termination version)
	// This version tries to terminate early when there are no more bits to process
	// Figuring this out is probably too costly in most cases.
	template<typename morton, typename coord>
	inline morton m3D_e_LUT_ET(const coord x, const coord y, const coord z) {
		morton answer_x = compute3D_ET_LUT_encode<morton, coord>(x, Morton3D_encode_x_256);
		morton answer_y = compute3D_ET_LUT_encode<morton, coord>(y, Morton3D_encode_x_256);
		morton answer_z = compute3D_ET_LUT_encode<morton, coord>(z, Morton3D_encode_x_256);
		return (answer_z << 2) | (answer_y << 1) | answer_x;
	}

	// Magicbits masks (3D encode)
	static uint_fast32_t magicbit3D_masks32_encode[6] = { 0x000003ff, 0, 0x30000ff, 0x0300f00f, 0x30c30c3, 0x9249249 }; // we add a 0 on position 1 in this array to use same code for 32-bit and 64-bit cases
	static uint_fast64_t magicbit3D_masks64_encode[6] = { 0x1fffff, 0x1f00000000ffff, 0x1f0000ff0000ff, 0x100f00f00f00f00f, 0x10c30c30c30c30c3, 0x1249249249249249 };

	// HELPER METHOD: Magic bits encoding (helper method)
	template<typename morton, typename coord>
	static inline morton morton3D_SplitBy3bits(const coord a) {
		const morton* masks = (sizeof(morton) <= 4) ? reinterpret_cast<const morton*>(magicbit3D_masks32_encode) : reinterpret_cast<const morton*>(magicbit3D_masks64_encode);
		morton x = ((morton)a) & masks[0];
		if (sizeof(morton) == 8) { x = (x | (uint_fast64_t)x << 32) & masks[1]; } // for 64-bit case
		x = (x | x << 16) & masks[2];
		x = (x | x << 8)  & masks[3];
		x = (x | x << 4)  & masks[4];
		x = (x | x << 2)  & masks[5];
		return x;
	}

	// ENCODE 3D Morton code : Magic bits method
	// This method uses certain bit patterns (magic bits) to split bits in the coordinates
	template<typename morton, typename coord>
	inline morton m3D_e_magicbits(const coord x, const coord y, const coord z) {
		return morton3D_SplitBy3bits<morton, coord>(x) | (morton3D_SplitBy3bits<morton, coord>(y) << 1) | (morton3D_SplitBy3bits<morton, coord>(z) << 2);
	}

	// ENCODE 3D Morton code : For loop
	// This is the most naive way of encoding coordinates into a morton code
	template<typename morton, typename coord>
	inline morton m3D_e_for(const coord x, const coord y, const coord z) {
		morton answer = 0;
		unsigned int checkbits = (sizeof(morton) * 8) / 3;
		for (unsigned int i = 0; i < checkbits; ++i) {
			morton mshifted = static_cast<morton>(1) << i; // Here we need to cast 0x1 to 64bits, otherwise there is a bug when morton code is larger than 32 bits
			unsigned int shift = 2 * i; // because you have to shift back i and forth 3*i
			answer |= ((x & mshifted) << shift)
				| ((y & mshifted) << (shift + 1))
				| ((z & mshifted) << (shift + 2));
		}
		return answer;
	}

	// ENCODE 3D Morton code : For loop (Early termination version)
	// In case of the for loop, figuring out when to stop early has huge benefits.
	template<typename morton, typename coord>
	inline morton m3D_e_for_ET(const coord x, const coord y, const coord z) {
		morton answer = 0;
		unsigned long x_max = 0, y_max = 0, z_max = 0;
		unsigned int checkbits = (sizeof(morton) * 8) / 3;
		findFirstSetBit<morton>(x, &x_max);
		findFirstSetBit<morton>(y, &y_max);
		findFirstSetBit<morton>(z, &z_max);
		checkbits = std::min((unsigned long)checkbits, std::max(z_max, std::max(x_max, y_max)) + (unsigned long)1);
		for (unsigned int i = 0; i < checkbits; ++i) {
			morton m_shifted = static_cast<morton>(1) << i; // Here we need to cast 0x1 to 64bits, otherwise there is a bug when morton code is larger than 32 bits
			unsigned int shift = 2 * i;
			answer |= ((x & m_shifted) << shift)
				| ((y & m_shifted) << (shift + 1))
				| ((z & m_shifted) << (shift + 2));
		}
		return answer;
	}

	// HELPER METHOD for LUT decoding
	// todo: wouldn't this be better with 8-bit aligned decode LUT?
	template<typename morton, typename coord>
	inline coord morton3D_DecodeCoord_LUT256(const morton m, const uint_fast8_t *LUT, const unsigned int startshift) {
		morton a = 0;
		unsigned int loops = (sizeof(morton) <= 4) ? 4 : 7;
		for (unsigned int i = 0; i < loops; ++i) {
			a |= (morton)(LUT[(m >> ((i * 9) + startshift)) & NINEBITMASK] << morton(3 * i));
		}
		return static_cast<coord>(a);
	}

	// DECODE 3D Morton code : Shifted LUT
	template<typename morton, typename coord>
	inline void m3D_d_sLUT(const morton m, coord& x, coord& y, coord& z) {
		x = morton3D_DecodeCoord_LUT256<morton, coord>(m, Morton3D_decode_x_512, 0);
		y = morton3D_DecodeCoord_LUT256<morton, coord>(m, Morton3D_decode_y_512, 0);
		z = morton3D_DecodeCoord_LUT256<morton, coord>(m, Morton3D_decode_z_512, 0);
	}

	// DECODE 3D Morton code : LUT
	template<typename morton, typename coord>
	inline void m3D_d_LUT(const morton m, coord& x, coord& y, coord& z) {
		x = morton3D_DecodeCoord_LUT256<morton, coord>(m, Morton3D_decode_x_512, 0);
		y = morton3D_DecodeCoord_LUT256<morton, coord>(m, Morton3D_decode_x_512, 1);
		z = morton3D_DecodeCoord_LUT256<morton, coord>(m, Morton3D_decode_x_512, 2);
	}

	// DECODE 3D Morton code : Shifted LUT (Early termination version)
	template<typename morton, typename coord>
	inline void m3D_d_sLUT_ET(const morton m, coord& x, coord& y, coord& z) {
		x = 0; y = 0; z = 0;
		unsigned long firstbit_location = 0;
		if (!findFirstSetBit<morton>(m, &firstbit_location)) { return; }
		unsigned int i = 0;
		unsigned int shiftback = 0;
		while (firstbit_location > i) {
			morton m_shifted = (m >> i) & NINEBITMASK;
			x |= (coord)Morton3D_decode_x_512[m_shifted] << shiftback;
			y |= (coord)Morton3D_decode_y_512[m_shifted] << shiftback;
			z |= (coord)Morton3D_decode_z_512[m_shifted] << shiftback;
			shiftback += 3;
			i += 9;
		}
		return;
	}

	// DECODE 3D Morton code : LUT (Early termination version)
	template<typename morton, typename coord>
	inline void m3D_d_LUT_ET(const morton m, coord& x, coord& y, coord& z) {
		x = 0; y = 0; z = 0;
		unsigned long firstbit_location = 0;
		if (!findFirstSetBit<morton>(m, &firstbit_location)) { return; }
		unsigned int i = 0;
		unsigned int shiftback = 0;
		while (i < firstbit_location) {
			x = x | (coord)Morton3D_decode_x_512[(m >> i) & NINEBITMASK] << shiftback;
			y = y | (coord)Morton3D_decode_x_512[(m >> (i + 1)) & NINEBITMASK] << shiftback;
			z = z | (coord)Morton3D_decode_x_512[(m >> (i + 2)) & NINEBITMASK] << shiftback;
			i += 9;
			shiftback += 3;
		}
		return;
	}

	// Magicbits masks (3D decode)
	static uint_fast32_t magicbit3D_masks32_decode[6] = { 0, 0x000003ff, 0x30000ff, 0x0300f00f, 0x30c30c3, 0x9249249 }; // we add a 0 on position 0 in this array to use same code for 32-bit and 64-bit cases
	static uint_fast64_t magicbit3D_masks64_decode[6] = { 0x1fffff, 0x1f00000000ffff, 0x1f0000ff0000ff, 0x100f00f00f00f00f, 0x10c30c30c30c30c3, 0x1249249249249249 };

	// HELPER METHOD for Magic bits decoding
	template<typename morton, typename coord>
	static inline coord morton3D_GetThirdBits(const morton m) {
		morton* masks = (sizeof(morton) <= 4) ? reinterpret_cast<morton*>(magicbit3D_masks32_decode) : reinterpret_cast<morton*>(magicbit3D_masks64_decode);
		morton x = m & masks[5];
		x = (x ^ (x >> 2)) & masks[4];
		x = (x ^ (x >> 4)) & masks[3];
		x = (x ^ (x >> 8)) & masks[2];
		x = (x ^ (x >> 16)) & masks[1];
		if (sizeof(morton) > 4) { x = (x ^ ((uint_fast64_t)x >> 32)) & masks[0]; }
		return static_cast<coord>(x);
	}

	// DECODE 3D Morton code : Magic bits
	// This method splits the morton codes bits by using certain patterns (magic bits)
	template<typename morton, typename coord>
	inline void m3D_d_magicbits(const morton m, coord& x, coord& y, coord& z) {
		x = morton3D_GetThirdBits<morton, coord>(m);
		y = morton3D_GetThirdBits<morton, coord>(m >> 1);
		z = morton3D_GetThirdBits<morton, coord>(m >> 2);
	}

	// DECODE 3D Morton code : For loop
	template<typename morton, typename coord>
	inline void m3D_d_for(const morton m, coord& x, coord& y, coord& z) {
		x = 0; y = 0; z = 0;
		unsigned int checkbits = (sizeof(morton) * 8) / 3;
		for (unsigned int i = 0; i < checkbits; ++i) {
			morton selector = 1;
			unsigned int shift_selector = 3 * i;
			unsigned int shiftback = 2 * i;
			x |= (m & (selector << shift_selector)) >> (shiftback);
			y |= (m & (selector << (shift_selector + 1))) >> (shiftback + 1);
			z |= (m & (selector << (shift_selector + 2))) >> (shiftback + 2);
		}
	}

	// DECODE 3D Morton code : For loop (Early termination version)
	template<typename morton, typename coord>
	inline void m3D_d_for_ET(const morton m, coord& x, coord& y, coord& z) {
		x = 0; y = 0; z = 0;
		unsigned long firstbit_location = 0;
		if (!findFirstSetBit<morton>(m, &firstbit_location)) return;
		unsigned int defaultbits = (sizeof(morton) * 8) / 3;
		unsigned int checkbits = static_cast<unsigned int>(std::min((float) defaultbits, firstbit_location / 3.0f));
		for (unsigned int i = 0; i <= checkbits; ++i) {
			morton selector = 1;
			unsigned int shift_selector = 3 * i;
			unsigned int shiftback = 2 * i;
			x |= (m & (selector << shift_selector)) >> (shiftback);
			y |= (m & (selector << (shift_selector + 1))) >> (shiftback + 1);
			z |= (m & (selector << (shift_selector + 2))) >> (shiftback + 2);
		}
	}
}