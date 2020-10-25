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


#ifdef __APPLE__


#include "infoware/cpu.hpp"
#include "infoware/detail/sysctl.hpp"
#include <algorithm>
#include <cstring>
#include <utility>


static std::pair<const char* const*, const char* const*> instruction_set_to_names(iware::cpu::instruction_set_t set) {
	static const char* mmx[]       = {"MMX"};
	static const char* threednow[] = {"3DNOW", "3DNOWEXT"};
	static const char* sse[]       = {"SSE"};
	static const char* sse2[]      = {"SSE2"};
	static const char* sse3[]      = {"SSSE3", "SSE3"};
	static const char* avx[]       = {"AVX"};


#define HANDLED_CASE(iset, variable)        \
	case iware::cpu::instruction_set_t::iset: \
		return {variable, variable + (sizeof(variable) / sizeof(*variable))};

	switch(set) {
		HANDLED_CASE(s3d_now, threednow)
		HANDLED_CASE(mmx, mmx)
		HANDLED_CASE(sse, sse)
		HANDLED_CASE(sse2, sse2)
		HANDLED_CASE(sse3, sse3)
		HANDLED_CASE(avx, avx)

		default:
			return {nullptr, nullptr};
	}

#undef HANDLED_CASE
}


bool iware::cpu::instruction_set_supported(iware::cpu::instruction_set_t set) {
	const auto ises = supported_instruction_sets();
	if(std::find(ises.begin(), ises.end(), set) != ises.cend())
		return true;

	const auto set_names = instruction_set_to_names(set);
	if(!set_names.first)
		return false;

	auto ctl_data = iware::detail::sysctl("machdep.cpu.features");
	if(ctl_data.empty())
		return 0;

	for(auto cur_name = std::strtok(ctl_data.data(), " \t\n"); cur_name; cur_name = std::strtok(nullptr, " \t\n"))
		if(std::any_of(set_names.first, set_names.second, [&](auto name) { return name == cur_name; }))
			return true;

	return false;
}


#endif
