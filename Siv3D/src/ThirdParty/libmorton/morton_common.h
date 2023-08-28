#pragma once

// Libmorton - Common helper methods needed in Morton encoding/decoding

#include <stdint.h>
#if defined(_MSC_VER)
#include <intrin.h>
#endif

namespace libmorton {
	template<typename morton>
	inline bool findFirstSetBitZeroIdx(const morton x, unsigned long* firstbit_location) {
#if defined(_MSC_VER) && !defined(_WIN64)
		// 32 BIT on 32 BIT
		if (sizeof(morton) <= 4) {
			return _BitScanReverse(firstbit_location, x) != 0;
		}
		// 64 BIT on 32 BIT
		else {
			*firstbit_location = 0;
			if (_BitScanReverse(firstbit_location, (x >> 32))) { // check first part
				*firstbit_location += 32;
				return true;
			}
			return _BitScanReverse(firstbit_location, (x & 0xFFFFFFFF)) != 0;
		}
#elif defined(_MSC_VER) && defined(_WIN64)
		// 32 or 64 BIT on 64 BIT
		return _BitScanReverse64(firstbit_location, x) != 0;
#elif defined(__GNUC__)
		if (x == 0) {
			return false;
		}
		else {
			*firstbit_location = static_cast<unsigned long>((sizeof(unsigned long long) * 8) - __builtin_clzll(x) - 1);
			return true;
		}
#endif
	}

	template<typename morton>
	inline bool findFirstSetBit(const morton x, unsigned long* firstbit_location) {
		if (findFirstSetBitZeroIdx(x, firstbit_location)) {
			*firstbit_location += 1;
			return true;
		}
		return false;
	}
}