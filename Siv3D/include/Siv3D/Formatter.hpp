//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <array>
# include <vector>
# if  __has_include(<compare>)
#	include <compare>
# endif

# include "Common.hpp"
# include "FormatData.hpp"
# include "SIMD.hpp"

namespace s3d
{
	void Formatter(FormatData& formatData, bool value);

	void Formatter(FormatData& formatData, int8 value);

	void Formatter(FormatData& formatData, uint8 value);

	void Formatter(FormatData& formatData, int16 value);

	void Formatter(FormatData& formatData, uint16 value);

	void Formatter(FormatData& formatData, int32 value);

	void Formatter(FormatData& formatData, uint32 value);

	void Formatter(FormatData& formatData, long value);

	void Formatter(FormatData& formatData, unsigned long value);

	void Formatter(FormatData& formatData, long long value);

	void Formatter(FormatData& formatData, unsigned long long value);

	void Formatter(FormatData& formatData, float value);

	void Formatter(FormatData& formatData, double value);

	void Formatter(FormatData& formatData, long double value);

	void Formatter(FormatData& formatData, char ch);

	void Formatter(FormatData& formatData, char8_t ch);

	void Formatter(FormatData& formatData, char16_t ch);

	void Formatter(FormatData& formatData, wchar_t ch);

	void Formatter(FormatData& formatData, char32_t ch);

	void Formatter(FormatData& formatData, std::nullptr_t);

	void Formatter(FormatData& formatData, const void* value);

	void Formatter(FormatData& formatData, const char*) = delete;

	void Formatter(FormatData& formatData, const char8_t*) = delete;

	void Formatter(FormatData& formatData, const char16_t*) = delete;

	void Formatter(FormatData& formatData, const wchar_t*) = delete;

	void Formatter(FormatData& formatData, const char32_t*);

	void Formatter(FormatData& formatData, const std::u32string& s);

# if __cpp_lib_three_way_comparison

	void Formatter(FormatData& formatData, std::strong_ordering value);

	void Formatter(FormatData& formatData, std::weak_ordering value);

	void Formatter(FormatData& formatData, std::partial_ordering value);

# endif

	template <class ForwardIt>
	inline void Formatter(FormatData& formatData, ForwardIt first, ForwardIt last);

	template <class Type, size_t N>
	inline void Formatter(FormatData& formatData, const Type(&values)[N]);

	template <class Type, size_t N>
	inline void Formatter(FormatData& formatData, const std::array<Type, N>& v);

	template <class Type, class Allocator = std::allocator<Type>>
	inline void Formatter(FormatData& formatData, const std::vector<Type, Allocator>& v);

	template <class Type>
	inline void Formatter(FormatData& formatData, const std::initializer_list<Type>& ilist);

	template <class Fitrst, class Second>
	inline void Formatter(FormatData& formatData, const std::pair<Fitrst, Second>& pair);

# if __cpp_lib_concepts
	namespace Concept
	{
		template <class Type>
		concept Formattable = requires (Type x) { Formatter(std::declval<FormatData&>(), x); };
	}
# endif
}

# include "detail/Formatter.ipp"

# if SIV3D_INTRINSIC(SSE)
# else
#	undef SIMDE_ENABLE_NATIVE_ALIASES
# endif
