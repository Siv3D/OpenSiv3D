// Formatting library for C++
//
// Copyright (c) 2012 - 2016, Victor Zverovich
// All rights reserved.
//
// For the license information refer to format.h.

#include "fmt/format-inl.h"

FMT_BEGIN_NAMESPACE

namespace internal
{

#ifdef FMT_BUILTIN_CLZLL
// Returns the number of decimal digits in n. Leading zeros are not counted
// except for n == 0 in which case count_digits returns 1.
unsigned count_digits(uint64_t n) {
	// Based on http://graphics.stanford.edu/~seander/bithacks.html#IntegerLog10
	// and the benchmark https://github.com/localvoid/cxx-benchmark-count-digits.
	int t = (64 - FMT_BUILTIN_CLZLL(n | 1)) * 1233 >> 12;
	return to_unsigned(t) - (n < data::POWERS_OF_10_64[t]) + 1;
}
#else
	// Fallback version of count_digits used when __builtin_clz is not available.
	unsigned count_digits(uint64_t n) {
	unsigned count = 1;
	for (;;) {
		// Integer division is slow so do it for a group of four digits instead
		// of for every digit. The idea comes from the talk by Alexandrescu
		// "Three Optimization Tips for C++". See speed-test for a comparison.
		if (n < 10) return count;
		if (n < 100) return count + 1;
		if (n < 1000) return count + 2;
		if (n < 10000) return count + 3;
		n /= 10000u;
		count += 4;
	}
}
#endif

#ifdef FMT_BUILTIN_CLZ
	// Optional version of count_digits for better performance on 32-bit platforms.
	unsigned count_digits(uint32_t n) {
		int t = (32 - FMT_BUILTIN_CLZ(n | 1)) * 1233 >> 12;
		return to_unsigned(t) - (n < data::POWERS_OF_10_32[t]) + 1;
	}
#endif

}

template <typename ArgFormatter, typename Char, typename Context>
void format_handler<ArgFormatter, Char, Context>::on_replacement_field(iterator it) {
	context.parse_context().advance_to(pointer_from(it));
	if (visit(internal::custom_formatter<Char, Context>(context), arg))
		return;
	basic_format_specs<Char> specs;
	context.advance_to(visit(ArgFormatter(context, specs), arg));
}

template <typename ArgFormatter, typename Char, typename Context>
typename format_handler<ArgFormatter, Char, Context>::iterator
	format_handler<ArgFormatter, Char, Context>::on_format_specs(iterator it) {
	auto& parse_ctx = context.parse_context();
	parse_ctx.advance_to(pointer_from(it));
	if (visit(internal::custom_formatter<Char, Context>(context), arg))
		return iterator(parse_ctx);
	basic_format_specs<Char> specs;
	using internal::specs_handler;
	internal::specs_checker<specs_handler<Context>>
		handler(specs_handler<Context>(specs, context), arg.type());
	it = parse_format_specs(it, handler);
	if (*it != '}')
		on_error("missing '}' in format string");
	parse_ctx.advance_to(pointer_from(it));
	context.advance_to(visit(ArgFormatter(context, specs), arg));
	return it;
}

template struct format_handler<arg_formatter<back_insert_range<internal::basic_buffer<char>>>, char, basic_format_context<std::back_insert_iterator<internal::basic_buffer<char>>, char>>;
template struct format_handler<arg_formatter<back_insert_range<internal::basic_buffer<char32_t>>>, char32_t, basic_format_context<std::back_insert_iterator<internal::basic_buffer<char32_t>>, char32_t>>;




template <typename T, std::size_t SIZE, typename Allocator>
void basic_memory_buffer<T, SIZE, Allocator>::grow(std::size_t size) {
	std::size_t old_capacity = this->capacity();
	std::size_t new_capacity = old_capacity + old_capacity / 2;
	if (size > new_capacity)
		new_capacity = size;
	T * old_data = this->data();
	T * new_data = internal::allocate<Allocator>(*this, new_capacity);
	// The following code doesn't throw, so the raw pointer above doesn't leak.
	std::uninitialized_copy(old_data, old_data + this->size(),
		internal::make_checked(new_data, new_capacity));
	this->set(new_data, new_capacity);
	// deallocate must not throw according to the standard, but even if it does,
	// the buffer already uses the new storage and will deallocate it in
	// destructor.
	if (old_data != store_)
		Allocator::deallocate(old_data, old_capacity);
}

template class basic_memory_buffer<char, 500, std::allocator<char>>;







format_context::iterator vformat_to(
	internal::buffer& buf, string_view format_str, format_args args) {
	typedef back_insert_range<internal::buffer> range;
	return vformat_to<arg_formatter<range>>(buf, format_str, args);
}

wformat_context::iterator vformat_to(
	internal::wbuffer& buf, wstring_view format_str, wformat_args args) {
	typedef back_insert_range<internal::wbuffer> range;
	return vformat_to<arg_formatter<range>>(buf, format_str, args);
}


std::string vformat(string_view format_str, format_args args) {
	memory_buffer buffer;
	vformat_to(buffer, format_str, args);
	return fmt_s3d::to_string(buffer);
}

std::u32string vformat(wstring_view format_str, wformat_args args) {
	wmemory_buffer buffer;
	vformat_to(buffer, format_str, args);
	return to_string(buffer);
}




namespace internal {
// Force linking of inline functions into the library.
std::string (*vformat_ref)(string_view, format_args) = vformat;
std::u32string (*vformat_wref)(wstring_view, wformat_args) = vformat;
}

template struct internal::basic_data<void>;

// Explicit instantiations for char.

template FMT_API char internal::thousands_sep(locale_provider *lp);

template void basic_fixed_buffer<char>::grow(std::size_t);

template void internal::arg_map<format_context>::init(
    const basic_format_args<format_context> &args);

template FMT_API int internal::char_traits<char>::format_float(
    char *buffer, std::size_t size, const char *format, int precision,
    double value);

template FMT_API int internal::char_traits<char>::format_float(
    char *buffer, std::size_t size, const char *format, int precision,
    long double value);

// Explicit instantiations for wchar_t.

template FMT_API char32_t internal::thousands_sep(locale_provider *lp);

template void basic_fixed_buffer<char32_t>::grow(std::size_t);

template void internal::arg_map<wformat_context>::init(
    const basic_format_args<wformat_context> &args);

template FMT_API int internal::char_traits<char32_t>::format_float(
	char32_t *buffer, std::size_t size, const wchar_t *format,
    int precision, double value);

template FMT_API int internal::char_traits<char32_t>::format_float(
	char32_t *buffer, std::size_t size, const wchar_t *format,
    int precision, long double value);
FMT_END_NAMESPACE
