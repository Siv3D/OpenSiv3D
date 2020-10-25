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


#ifdef _WIN32


#include "infoware/detail/cpuid.hpp"
#include <cstdint>
#include <intrin.h>


void iware::detail::cpuid(std::int32_t (&out)[4], std::int32_t x) {
	__cpuidex(out, x, 0);
}

std::uint64_t iware::detail::xgetbv(std::uint32_t x) {
	return _xgetbv(x);
}


#endif
