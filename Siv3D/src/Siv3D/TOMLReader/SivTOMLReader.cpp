//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

#include "../../ThirdParty/cpptoml/cpptoml.h"
#include <Siv3D/TOMLReader.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Time.hpp>
#include <Siv3D/DateTime.hpp>
#include <Siv3D/TextReader.hpp>
#include <Siv3D/Format.hpp>

namespace s3d
{
	namespace detail
	{
		struct TOMLTableIteratorDetail
		{
			cpptoml::table::const_iterator it;

			TOMLTableIteratorDetail() = default;

			explicit TOMLTableIteratorDetail(const cpptoml::table::const_iterator& _it)
				: it(_it) {}
		};

		struct TOMLArrayIteratorDetail
		{
			cpptoml::array::const_iterator it;

			TOMLArrayIteratorDetail() = default;

			explicit TOMLArrayIteratorDetail(const cpptoml::array::const_iterator& _it)
				:it(_it) {}
		};

		struct TOMLTableArrayIteratorDetail
		{
			cpptoml::table_array::const_iterator it;

			TOMLTableArrayIteratorDetail() = default;

			explicit TOMLTableArrayIteratorDetail(const cpptoml::table_array::const_iterator& _it)
				:it(_it) {}
		};

		struct TOMLValueDetail
		{
			std::shared_ptr<cpptoml::base> ptr;

			TOMLValueDetail() = default;

			explicit TOMLValueDetail(const std::shared_ptr<cpptoml::base>& _value)
				: ptr(_value) {}
		};
	}

	////////////////////////////////
	//
	//	TOMLTableIterator
	//

	TOMLTableIterator::TOMLTableIterator(const detail::TOMLTableIteratorDetail& p)
		: m_detail(std::make_shared<detail::TOMLTableIteratorDetail>(p.it))
	{
		
	}

	TOMLTableIterator TOMLTableIterator::operator ++()
	{
		++m_detail->it;

		return TOMLTableIterator(*m_detail);
	}

	TOMLTableIterator TOMLTableIterator::operator ++(int)
	{
		const detail::TOMLTableIteratorDetail tmp (m_detail->it);

		++m_detail->it;

		return TOMLTableIterator(tmp);
	}

	bool TOMLTableIterator::operator ==(const TOMLTableIterator& other) const noexcept
	{
		return m_detail->it == other.m_detail->it;
	}

	bool TOMLTableIterator::operator !=(const TOMLTableIterator& other) const noexcept
	{
		return m_detail->it != other.m_detail->it;
	}

	TOMLTableMember TOMLTableIterator::operator *() const
	{
		return TOMLTableMember{
			Unicode::FromUTF8(m_detail->it->first),
			TOMLValue(detail::TOMLValueDetail(m_detail->it->second))
		};
	}

	////////////////////////////////
	//
	//	TOMLArrayIterator
	//

	TOMLArrayIterator::TOMLArrayIterator(const detail::TOMLArrayIteratorDetail& p)
		: m_detail(std::make_shared<detail::TOMLArrayIteratorDetail>(p.it))
	{
	
	}

	TOMLArrayIterator TOMLArrayIterator::operator ++()
	{
		++m_detail->it;

		return TOMLArrayIterator(*m_detail);
	}

	TOMLArrayIterator TOMLArrayIterator::operator ++(int)
	{
		const detail::TOMLArrayIteratorDetail tmp(m_detail->it);

		++m_detail->it;

		return TOMLArrayIterator(tmp);
	}

	TOMLArrayIterator TOMLArrayIterator::operator +(size_t index) const
	{
		return TOMLArrayIterator(detail::TOMLArrayIteratorDetail(m_detail->it + index));
	}

	bool TOMLArrayIterator::operator ==(const TOMLArrayIterator& other) const noexcept
	{
		return m_detail->it == other.m_detail->it;
	}

	bool TOMLArrayIterator::operator !=(const TOMLArrayIterator& other) const noexcept
	{
		return m_detail->it != other.m_detail->it;
	}

	TOMLValue TOMLArrayIterator::operator *() const
	{
		return TOMLValue(detail::TOMLValueDetail(*m_detail->it));
	}

	////////////////////////////////
	//
	//	TOMLArrayView
	//

	TOMLValue TOMLArrayView::operator [](size_t index) const
	{
		return TOMLValue(*(m_begin + index));
	}

	////////////////////////////////
	//
	//	TOMLTableArrayIterator
	//

	TOMLTableArrayIterator::TOMLTableArrayIterator(const detail::TOMLTableArrayIteratorDetail& p)
		: m_detail(std::make_shared<detail::TOMLTableArrayIteratorDetail>(p.it))
	{

	}

	TOMLTableArrayIterator TOMLTableArrayIterator::operator ++()
	{
		++m_detail->it;

		return TOMLTableArrayIterator(*m_detail);
	}

	TOMLTableArrayIterator TOMLTableArrayIterator::operator ++(int)
	{
		const detail::TOMLTableArrayIteratorDetail tmp(m_detail->it);

		++m_detail->it;

		return TOMLTableArrayIterator(tmp);
	}

	TOMLTableArrayIterator TOMLTableArrayIterator::operator +(size_t index) const
	{
		return TOMLTableArrayIterator(detail::TOMLTableArrayIteratorDetail(m_detail->it + index));
	}

	bool TOMLTableArrayIterator::operator ==(const TOMLTableArrayIterator& other) const noexcept
	{
		return m_detail->it == other.m_detail->it;
	}

	bool TOMLTableArrayIterator::operator !=(const TOMLTableArrayIterator& other) const noexcept
	{
		return m_detail->it != other.m_detail->it;
	}

	TOMLValue TOMLTableArrayIterator::operator *() const
	{
		return TOMLValue(detail::TOMLValueDetail(*m_detail->it));
	}

	////////////////////////////////
	//
	//	TOMLTableArrayView
	//

	TOMLValue TOMLTableArrayView::operator [](size_t index) const
	{
		return TOMLValue(*(m_begin + index));
	}

	////////////////////////////////
	//
	//	TOMLValue
	//

	s3d::TOMLValue::TOMLValue(const detail::TOMLValueDetail& p)
		: m_detail(std::make_shared<detail::TOMLValueDetail>(p.ptr))
	{

	}

	bool TOMLValue::isEmpty() const
	{
		return !(m_detail && m_detail->ptr);
	}

	TOMLValueType TOMLValue::getType() const
	{
		if (isEmpty())
		{
			return TOMLValueType::Empty;
		}

		const auto& value = m_detail->ptr;

		if (value->is_table())
		{
			return TOMLValueType::Table;
		}
		if (value->is_array())
		{
			return TOMLValueType::Array;
		}
		if (value->is_table_array())
		{
			return TOMLValueType::TableArray;
		}
		if (value->is_value())
		{
			if (value->as<std::string>())
			{
				return TOMLValueType::String;
			}
			if (value->as<double>())
			{
				return TOMLValueType::Number;
			}
			if (value->as<bool>())
			{
				return TOMLValueType::Bool;
			}

			if (value->as<cpptoml::local_date>())
			{
				return TOMLValueType::Date;
			}

			return TOMLValueType::DateTime;
		}

		return TOMLValueType::Unknown;
	}

	template <>
	Optional<int64> TOMLValue::getOpt<int64>() const
	{
		if (!isNumber())
		{
			return none;
		}
		if (auto p = m_detail->ptr->as<bool>())
		{
			return static_cast<int64>(p->get());
		}
		if (auto p = m_detail->ptr->as<int64_t>())
		{
			return p->get();
		}
		if (auto p = m_detail->ptr->as<double>())
		{
			return static_cast<int64>(p->get());
		}

		return none;
	}

	template <>
	Optional<double> TOMLValue::getOpt<double>() const
	{
		if (!isNumber())
		{
			return none;
		}
		if (auto p = m_detail->ptr->as<double>())
		{
			return p->get();
		}

		return none;
	}

	template <>
	Optional<bool> TOMLValue::getOpt<bool>() const
	{
		if (!isBool()) {
			return none;
		}

		if (auto p = m_detail->ptr->as<bool>())
		{
			return p->get();
		}

		return none;
	}

	////////////////////////////////
	//
	//  TOMLValue(Table)
	//

	size_t TOMLValue::memberCount() const
	{
		if (isEmpty())
		{
			return 0;
		}

		if (auto&& table = m_detail->ptr->as_table())
		{
			return table->size();
		}

		return 0;
	}

	bool TOMLValue::hasMember(const String& name) const
	{
		if (isEmpty())
		{
			return false;
		}

		if (auto&& table = m_detail->ptr->as_table())
		{
			return table->contains(name.toUTF8());
		}

		return false;
	}

	TOMLTableView TOMLValue::tableView() const
	{
		if (isEmpty())
		{
			return TOMLTableView();
		}

		if (auto&& table = m_detail->ptr->as_table())
		{
			return TOMLTableView(
				TOMLTableIterator(detail::TOMLTableIteratorDetail(table->begin())),
				TOMLTableIterator(detail::TOMLTableIteratorDetail(table->end()))
			);
		}

		return TOMLTableView();
	}

	TOMLValue TOMLValue::operator [](const String& path) const
	{
		if (isEmpty())
		{
			return TOMLValue();
		}

		if (auto&& table = m_detail->ptr->as_table())
		{
			try
			{
				return TOMLValue(detail::TOMLValueDetail(table->get_qualified(path.toUTF8())));
			}
			catch (...)
			{
				return TOMLValue();
			}
		}

		return TOMLValue();
	}

	////////////////////////////////
	//
	//  TOMLValue(Array/TableArray)
	//

	size_t TOMLValue::arrayCount() const
	{
		if (isEmpty())
		{
			return 0;
		}

		if (auto&& arr = m_detail->ptr->as_array())
		{
			return arr->get().size();
		}
		if (auto&& arr = m_detail->ptr->as_table_array())
		{
			return arr->get().size();
		}

		return 0;
	}

	TOMLArrayView TOMLValue::arrayView() const
	{
		if (isEmpty())
		{
			return TOMLArrayView();
		}

		if (auto&& arr = m_detail->ptr->as_array())
		{
			return TOMLArrayView(
				TOMLArrayIterator(detail::TOMLArrayIteratorDetail(arr->begin())),
				TOMLArrayIterator(detail::TOMLArrayIteratorDetail(arr->end()))
			);
		}

		return TOMLArrayView();
	}

	TOMLTableArrayView TOMLValue::tableArrayView() const
	{
		if (isEmpty())
		{
			return TOMLTableArrayView();
		}

		if (auto&& arr = m_detail->ptr->as_table_array())
		{
			return TOMLTableArrayView(
				TOMLTableArrayIterator(detail::TOMLTableArrayIteratorDetail(arr->begin())),
				TOMLTableArrayIterator(detail::TOMLTableArrayIteratorDetail(arr->end()))
			);
		}

		return TOMLTableArrayView();
	}

	////////////////////////////////
	//
	//  TOMLValue(String)
	//

	String TOMLValue::getString() const
	{
		if (isEmpty())
		{
			return String();
		}

		if (auto&& str = m_detail->ptr->as<std::string>())
		{
			return Unicode::FromUTF8(str->get());
		}

		return String();
	}

	template <>
	Optional<String> TOMLValue::getOpt<String>() const
	{
		if (!isString())
		{
			return none;
		}

		return Optional<String>(in_place, getString());
	}

	////////////////////////////////
	//
	//  TOMLValue(Date)
	//

	Date TOMLValue::getDate() const
	{
		if (isEmpty())
		{
			return Date();
		}

		if (auto&& date_ = m_detail->ptr->as<cpptoml::local_date>())
		{
			auto&& date = date_->get();

			return Date(date.year, date.month, date.day);
		}

		return Date();
	}

	template <>
	Optional<Date> TOMLValue::getOpt<Date>() const
	{
		if (!isDate())
		{
			return none;
		}

		return Optional<Date>(in_place, getDate());
	}

	////////////////////////////////
	//
	//  TOMLValue(DateTime)
	//

	DateTime TOMLValue::getDateTime() const
	{
		if (isEmpty())
		{
			return DateTime();
		}

		if (auto&& dateTime_ = m_detail->ptr->as<cpptoml::offset_datetime>())
		{
			auto& dateTime = dateTime_->get();
			const int32 offset = dateTime.hour_offset * 60 + dateTime.minute_offset;

			DateTime ret(
				dateTime.year,
				dateTime.month,
				dateTime.day,
				dateTime.hour,
				dateTime.minute,
				dateTime.second,
				dateTime.microsecond / 1000
			);

			ret += std::chrono::minutes(Time::UTCOffsetMinutes() - offset);

			return ret;
		}

		if (auto&& localDateTime_ = m_detail->ptr->as<cpptoml::local_datetime>())
		{
			auto& localDateTime = localDateTime_->get();

			return DateTime(
				localDateTime.year,
				localDateTime.month,
				localDateTime.day,
				localDateTime.hour,
				localDateTime.minute,
				localDateTime.second,
				localDateTime.microsecond / 1000
			);
		}

		return DateTime();
	}

	template <>
	Optional<DateTime> TOMLValue::getOpt<DateTime>() const
	{
		if (!isDateTime())
		{
			return none;
		}

		return Optional<DateTime>(in_place, getDateTime());
	}

	////////////////////////////////
	//
	//  TOMLReader
	//

	bool TOMLReader::open(const FilePath& path)
	{
		try {
			m_detail = std::make_shared<detail::TOMLValueDetail>(std::shared_ptr<cpptoml::base>(cpptoml::parse_file(path.narrow())));
		}
		catch (...) {
			return false;
		}

		return !isEmpty();
	}

	bool TOMLReader::open(const std::shared_ptr<IReader>& reader)
	{
		if (isOpened())
		{
			close();
		}

		std::stringstream ss;
		ss << TextReader(reader).readAll();

		try {
			m_detail = std::make_shared<detail::TOMLValueDetail>(std::shared_ptr<cpptoml::base>(cpptoml::parser(ss).parse()));
		}
		catch (...) {
			return false;
		}

		return m_detail != nullptr;
	}

	////////////////////////////////
	//
	//  Format
	//

	void Formatter(FormatData& formatData, const TOMLValue& value)
	{
		if (value.isEmpty())
		{
			return;
		}

		String str;
		value.m_detail->ptr->accept(TOMLValue::Visitor{ str });

		formatData.string.append(str.c_str());
	}

}