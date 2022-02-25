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
	inline TOMLTableView::TOMLTableView(const TOMLTableIterator& begin, const TOMLTableIterator& end) noexcept
		: m_begin(begin)
		, m_end(end) {}

	inline TOMLTableIterator TOMLTableView::begin() const noexcept
	{
		return m_begin;
	}

	inline TOMLTableIterator TOMLTableView::end() const noexcept
	{
		return m_end;
	}


	inline TOMLArrayView::TOMLArrayView(const TOMLArrayIterator& begin, const TOMLArrayIterator& end) noexcept
		: m_begin(begin)
		, m_end(end) {}

	inline TOMLArrayIterator TOMLArrayView::begin() const noexcept
	{
		return m_begin;
	}

	inline TOMLArrayIterator TOMLArrayView::end() const noexcept
	{
		return m_end;
	}


	inline TOMLTableArrayView::TOMLTableArrayView(const TOMLTableArrayIterator& begin, const TOMLTableArrayIterator& end) noexcept
		: m_begin(begin)
		, m_end(end) {}

	inline TOMLTableArrayIterator TOMLTableArrayView::begin() const noexcept
	{
		return m_begin;
	}

	inline TOMLTableArrayIterator TOMLTableArrayView::end() const noexcept
	{
		return m_end;
	}


	template <class Type>
	inline Type TOMLValue::get() const
	{
		return getOpt<Type>().value_or(Type());
	}

	template <class Type, class U>
	inline Type TOMLValue::getOr(U&& defaultValue) const
	{
		return getOpt<Type>().value_or(std::forward<U>(defaultValue));
	}

	template <class Type>
	inline Optional<Type> TOMLValue::getOpt() const
	{
		return getOpt_<Type>();
	}

	template <class Type, std::enable_if_t<std::is_integral_v<Type> && !std::is_same_v<bool, std::decay_t<Type>>>*>
	inline Optional<Type> TOMLValue::getOpt_() const
	{
		if (auto&& tmp = getOpt<int64>())
		{
			return static_cast<Type>(tmp.value());
		}

		return none;
	}

	template <class Type, std::enable_if_t<std::is_floating_point_v<Type>>*>
	inline Optional<Type> TOMLValue::getOpt_() const
	{
		if (auto&& tmp = getOpt<double>())
		{
			return static_cast<Type>(tmp.value());
		}

		return none;
	}

	template <class Type, std::enable_if_t<!std::is_arithmetic_v<Type>>*>
	inline Optional<Type> TOMLValue::getOpt_() const
	{
		return ParseOpt<Type>(getString());
	}

	template <>
	inline Optional<String> TOMLValue::getOpt<String>() const
	{
		return getOptString();
	}

	template <>
	inline Optional<int64> TOMLValue::getOpt<int64>() const
	{
		return getOptInt64();
	}

	template <>
	inline Optional<double> TOMLValue::getOpt<double>() const
	{
		return getOptDouble();
	}

	template <>
	inline Optional<bool> TOMLValue::getOpt<bool>() const
	{
		return getOptBool();
	}

	template <>
	inline Optional<Date> TOMLValue::getOpt<Date>() const
	{
		return getOptDate();
	}

	template <>
	inline Optional<DateTime> TOMLValue::getOpt<DateTime>() const
	{
		return getOptDateTime();
	}


	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>*>
	inline TOMLReader::TOMLReader(Reader&& reader)
	{
		open(std::make_unique<Reader>(std::forward<Reader>(reader)));
	}

	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>*>
	inline bool TOMLReader::open(Reader&& reader)
	{
		return open(std::make_unique<Reader>(std::forward<Reader>(reader)));
	}
}
