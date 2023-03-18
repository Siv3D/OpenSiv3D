//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <ThirdParty/cpptoml/cpptoml.h>
# include <Siv3D/TOMLReader.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/TextReader.hpp>

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
				: ptr{ _value } {}
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

	bool TOMLValue::isTable() const noexcept
	{
		return getType() == TOMLValueType::Table;
	}

	bool TOMLValue::isArray() const noexcept
	{
		return getType() == TOMLValueType::Array;
	}

	bool TOMLValue::isTableArray() const noexcept
	{
		return getType() == TOMLValueType::TableArray;
	}

	bool TOMLValue::isString() const noexcept
	{
		return getType() == TOMLValueType::String;
	}

	bool TOMLValue::isBool() const noexcept
	{
		return getType() == TOMLValueType::Bool;
	}

	bool TOMLValue::isNumber() const noexcept
	{
		return getType() == TOMLValueType::Number;
	}

	bool TOMLValue::isDate() const noexcept
	{
		return getType() == TOMLValueType::Date;
	}

	bool TOMLValue::isDateTime() const noexcept
	{
		return getType() == TOMLValueType::DateTime;
	}

	Optional<int64> TOMLValue::getOptInt64() const
	{
		if (not isNumber())
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

	Optional<double> TOMLValue::getOptDouble() const
	{
		if (not isNumber())
		{
			return none;
		}
		if (auto p = m_detail->ptr->as<double>())
		{
			return p->get();
		}

		return none;
	}

	Optional<bool> TOMLValue::getOptBool() const
	{
		if (not isBool())
		{
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

	Optional<String> TOMLValue::getOptString() const
	{
		if (not isString())
		{
			return none;
		}

		return getString();
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

	Optional<Date> TOMLValue::getOptDate() const
	{
		if (not isDate())
		{
			return none;
		}

		return getDate();
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

	String TOMLValue::format() const
	{
		if (isEmpty())
		{
			return String();
		}

		String str;

		m_detail->ptr->accept(TOMLValue::Visitor{ str });

		return str;
	}

	Optional<DateTime> TOMLValue::getOptDateTime() const
	{
		if (not isDateTime())
		{
			return none;
		}

		return getDateTime();
	}

	////////////////////////////////
	//
	//  TOMLReader
	//
	TOMLReader::TOMLReader(const FilePathView path)
	{
		open(path);
	}

	TOMLReader::TOMLReader(std::unique_ptr<IReader>&& reader)
	{
		open(std::move(reader));
	}

	bool TOMLReader::open(const FilePathView path)
	{
		if (isOpen())
		{
			close();
		}

		TextReader textReader{ path };

		if (not textReader)
		{
			return false;
		}

		std::stringstream ss;
		ss << textReader.readAll().toUTF8();

		try
		{
			m_detail = std::make_shared<detail::TOMLValueDetail>(std::shared_ptr<cpptoml::base>(cpptoml::parser(ss).parse()));
		}
		catch (...)
		{
			return false;
		}

		return m_detail != nullptr;
	}

	bool TOMLReader::open(std::unique_ptr<IReader>&& reader)
	{
		if (isOpen())
		{
			close();
		}

		TextReader textReader{ std::move(reader) };

		if (not textReader)
		{
			return false;
		}

		std::stringstream ss;
		ss << textReader.readAll().toUTF8();

		try
		{
			m_detail = std::make_shared<detail::TOMLValueDetail>(std::shared_ptr<cpptoml::base>(cpptoml::parser(ss).parse()));
		}
		catch (...)
		{
			return false;
		}

		return m_detail != nullptr;
	}

	void TOMLReader::close()
	{
		m_detail.reset();
	}

	bool TOMLReader::isOpen() const noexcept
	{
		return m_detail != nullptr;
	}

	TOMLReader::operator bool() const noexcept
	{
		return isOpen();
	}

	////////////////////////////////
	//
	//  Format
	//

	void Formatter(FormatData& formatData, const TOMLValue& value)
	{
		formatData.string.append(value.format());
	}

	void Formatter(FormatData& formatData, const TOMLReader& reader)
	{
		if (reader)
		{
			Formatter(formatData, static_cast<TOMLValue>(reader));
		}
	}
}
