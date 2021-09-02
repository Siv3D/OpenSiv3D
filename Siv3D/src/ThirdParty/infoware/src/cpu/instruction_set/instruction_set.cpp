// infoware - C++ System information Library
//
// Written in 2016-2020 by nabijaczleweli <nabijaczleweli@gmail.com> and ThePhD <phdofthehouse@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>


#include "infoware/cpu.hpp"
#include "infoware/detail/cpuid.hpp"


#if defined(_WIN32) && defined(_MSC_VER)
#include <intrin.h>
#define INFOWARE_XCR_XFEATURE_ENABLED_MASK _XCR_XFEATURE_ENABLED_MASK
#else
#define INFOWARE_XCR_XFEATURE_ENABLED_MASK 0
#endif  // Is MSVC


static bool has_os_avx() {
	bool avxsupport = false;

	std::int32_t cpuinfo[4];
	iware::detail::cpuid(cpuinfo, 1);

	bool osusesxsave_restore = (cpuinfo[2] & (1 << 27)) != 0;
	bool cpusupportsavx      = (cpuinfo[2] & (1 << 28)) != 0;

	if(osusesxsave_restore && cpusupportsavx) {
		const auto xcrFeatureMask = iware::detail::xgetbv(INFOWARE_XCR_XFEATURE_ENABLED_MASK);
		avxsupport                = (xcrFeatureMask & 0x06) == 0x06;
	}

	return avxsupport;
}

static bool has_os_avx_512() {
	if(!has_os_avx())
		return false;

	const auto xcrFeatureMask = iware::detail::xgetbv(INFOWARE_XCR_XFEATURE_ENABLED_MASK);
	return (xcrFeatureMask & 0xE6) == 0xE6;
}


std::vector<iware::cpu::instruction_set_t> iware::cpu::supported_instruction_sets() {
	std::int32_t info[4];
	iware::detail::cpuid(info, 0);
	const auto idinfo = info[0];

	iware::detail::cpuid(info, 0x80000000);
	const std::uint32_t extendedidinfo = info[0];

	std::vector<iware::cpu::instruction_set_t> supported;
	supported.reserve(64);


#define ADD_SET_IF(infoindex, bitindex, name)      \
	if((info[(infoindex)] & (1 << (bitindex))) != 0) \
		supported.push_back(iware::cpu::instruction_set_t::name);


	if(idinfo >= 0x00000001) {
		iware::detail::cpuid(info, 0x00000001);

		ADD_SET_IF(3, 22, mmx_extended);
		ADD_SET_IF(3, 23, mmx);
		ADD_SET_IF(3, 25, sse);
		ADD_SET_IF(3, 26, sse2);

		ADD_SET_IF(2, 0, sse3);
		ADD_SET_IF(2, 9, ssse3);
		ADD_SET_IF(2, 19, sse41);
		ADD_SET_IF(2, 20, sse42);
		ADD_SET_IF(2, 25, aes);
		ADD_SET_IF(2, 28, fma3);
		ADD_SET_IF(2, 12, rd_rand);
	}

	if(idinfo >= 0x00000007) {
		iware::detail::cpuid(info, 0x00000007);

		if(has_os_avx()) {
			// Both must be present to have AVX
			ADD_SET_IF(1, 5, avx2);
		}
		ADD_SET_IF(1, 4, hle);

		ADD_SET_IF(1, 3, bmi1);
		ADD_SET_IF(1, 8, bmi2);
		ADD_SET_IF(1, 19, adx);
		ADD_SET_IF(1, 14, mpx);
		ADD_SET_IF(1, 29, sha);

		if(has_os_avx_512()) {
			supported.push_back(iware::cpu::instruction_set_t::avx_512);

			ADD_SET_IF(1, 16, avx_512_f);
			ADD_SET_IF(1, 28, avx_512_cd);
			ADD_SET_IF(1, 26, avx_512_pf);
			ADD_SET_IF(1, 27, avx_512_er);
			ADD_SET_IF(1, 31, avx_512_vl);
			ADD_SET_IF(1, 30, avx_512_bw);
			ADD_SET_IF(1, 17, avx_512_dq);
			ADD_SET_IF(1, 21, avx_512_ifma);
			ADD_SET_IF(2, 1, avx_512_vbmi);
		}

		ADD_SET_IF(2, 0, prefetch_wt1);
	}

	if(extendedidinfo >= 0x80000001) {
		iware::detail::cpuid(info, 0x80000001);

		ADD_SET_IF(3, 29, x64);
		ADD_SET_IF(3, 0, x87_fpu);
		ADD_SET_IF(3, 30, s3d_now);
		ADD_SET_IF(3, 31, s3d_now_extended);
		ADD_SET_IF(3, 29, x64);
		ADD_SET_IF(2, 5, bmi1);
		ADD_SET_IF(2, 6, bmi2);
		ADD_SET_IF(2, 16, adx);
		ADD_SET_IF(2, 11, mpx);
	}


#undef ADD_SET_IF


	return supported;
}
