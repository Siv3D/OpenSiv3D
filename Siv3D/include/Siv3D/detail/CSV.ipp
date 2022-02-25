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

namespace s3d
{
	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>*>
	inline CSV::CSV(Reader&& reader, const StringView separators, const StringView quotes, const StringView escapes)
	{
		load(std::move(reader), separators, quotes, escapes);
	}

	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>*>
	inline bool CSV::load(Reader&& reader, const StringView separators, const StringView quotes, const StringView escapes)
	{
		return load(std::make_unique<Reader>(std::move(reader), separators, quotes, escapes));
	}

	inline CSV::operator bool() const noexcept
	{
		return (not isEmpty());
	}

	template <class Type>
	inline Type CSV::get(const size_t row, const size_t column) const
	{
		if (const auto opt = getOpt<Type>(row, column))
		{
			return opt.value();
		}

		return Type();
	}

	template <class Type, class U>
	inline Type CSV::getOr(const size_t row, const size_t column, U&& defaultValue) const
	{
		return getOpt<Type>(row, column).value_or(std::forward<U>(defaultValue));
	}

	template <class Type>
	inline Optional<Type> CSV::getOpt(const size_t row, const size_t column) const
	{
		if (const auto item = getItem(row, column))
		{
			return ParseOpt<Type>(*item);
		}

		return none;
	}

	template <class Type>
	inline void CSV::write(const Type& value)
	{
		write(Format(value));
	}

	template <class ... Args>
	inline void CSV::write(const Args& ... records)
	{
		_write(records...);
	}

	template <class ... Args>
	inline void CSV::writeRow(const Args& ... records)
	{
		_write(records...);

		newLine();
	}

	inline void CSV::_write()
	{
		return;
	}

	template <class Type, class ... Args>
	inline void CSV::_write(const Type& record, const Args& ... records)
	{
		write(Format(record));

		return _write(records...);
	}
}
