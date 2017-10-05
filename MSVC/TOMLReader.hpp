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

#pragma once
#include 

namespace s3d
{
	class TOMLValue;
}

namespace s3d
{
	void Formatter(FormatData& formatData, const TOMLValue& value);
}


namespace s3d
{
	enum class TOMLValueType {
		Empty,
		Table,
		Array,
		TableArray,
		String,
		Number,
		Bool,
		Date,
		DateTime,
		Unknown
	};

	class TOMLValue;
	struct TOMLTableMember;

	class TOMLTableIterator
	{
	private:

		cpptoml::table::iterator m_detail;

	public:

		TOMLTableIterator() = default;

		explicit TOMLTableIterator(const cpptoml::table::iterator& itr)
			: m_detail(itr) {}

		TOMLTableIterator operator ++()
		{
			++m_detail;

			return *this;
		}

		TOMLTableIterator operator ++(int)
		{
			auto tmp = m_detail;

			++m_detail;

			return TOMLTableIterator(tmp);
		}

		TOMLTableMember operator *() const;

		bool operator ==(const TOMLTableIterator& other) const noexcept
		{
			return m_detail == other.m_detail;
		}

		bool operator !=(const TOMLTableIterator& other) const noexcept
		{
			return m_detail != other.m_detail;
		}

	};

	class TOMLTableView
	{
	private:

		TOMLTableIterator m_begin, m_end;

	public:

		TOMLTableView() = default;
		TOMLTableView(const TOMLTableIterator& begin, const TOMLTableIterator& end) noexcept
			: m_begin(begin)
			, m_end(end) {}

		TOMLTableIterator begin() const
		{
			return m_begin;
		}

		TOMLTableIterator end() const
		{
			return m_end;
		}
	};

	class TOMLArrayIterator
	{
	private:

		cpptoml::array::iterator m_detail;

	public:

		TOMLArrayIterator() = default;

		explicit TOMLArrayIterator(const cpptoml::array::iterator& itr)
			: m_detail(itr) {}

		TOMLArrayIterator operator ++()
		{
			++m_detail;

			return *this;
		}

		TOMLArrayIterator operator ++(int)
		{
			auto tmp = m_detail;

			++m_detail;

			return TOMLArrayIterator(tmp);
		}

		TOMLArrayIterator operator +(size_t index) const
		{
			return TOMLArrayIterator(m_detail + index);
		}

		TOMLValue operator *() const;

		bool operator ==(const TOMLArrayIterator& other) const noexcept
		{
			return m_detail == other.m_detail;
		}

		bool operator !=(const TOMLArrayIterator& other) const noexcept
		{
			return m_detail != other.m_detail;
		}

	};

	class TOMLArrayView
	{
	private:

		TOMLArrayIterator m_begin, m_end;

	public:

		TOMLArrayView() = default;
		TOMLArrayView(cpptoml::array::iterator begin, cpptoml::array::iterator end) noexcept
			: m_begin(begin)
			, m_end(end) {}

		TOMLArrayIterator begin() const
		{
			return m_begin;
		}

		TOMLArrayIterator end() const
		{
			return m_end;
		}

		TOMLValue operator [](size_t index) const;
	};

	class TOMLTableArrayIterator
	{
	private:

		cpptoml::table_array::iterator m_detail;

	public:

		TOMLTableArrayIterator() = default;

		explicit TOMLTableArrayIterator(const cpptoml::table_array::iterator& itr)
			: m_detail(itr) {}

		TOMLTableArrayIterator operator ++()
		{
			++m_detail;

			return *this;
		}

		TOMLTableArrayIterator operator ++(int)
		{
			auto tmp = m_detail;

			++m_detail;

			return TOMLTableArrayIterator(tmp);
		}

		TOMLTableArrayIterator operator +(size_t index) const
		{
			return TOMLTableArrayIterator(m_detail + index);
		}

		TOMLValue operator *() const;

		bool operator ==(const TOMLTableArrayIterator& other) const noexcept
		{
			return m_detail == other.m_detail;
		}

		bool operator !=(const TOMLTableArrayIterator& other) const noexcept
		{
			return m_detail != other.m_detail;
		}

	};

	class TOMLTableArrayView
	{
	private:

		TOMLTableArrayIterator m_begin, m_end;

	public:

		TOMLTableArrayView() = default;
		TOMLTableArrayView(cpptoml::table_array::iterator begin, cpptoml::table_array::iterator end) noexcept
			: m_begin(begin)
			, m_end(end) {}

		TOMLTableArrayIterator begin() const
		{
			return m_begin;
		}

		TOMLTableArrayIterator end() const
		{
			return m_end;
		}

		TOMLValue operator [](size_t index) const;
	};

	class TOMLValue
	{
	protected:

		std::shared_ptr<cpptoml::base> m_detail;

		template<class Type, std::enable_if_t<!std::is_integral<Type>::value>* = nullptr>
		Optional<Type> getOpt_() const
		{
			if (auto p = m_detail->as<Type>())
			{
				return p->get();
			}

			return none;
		}

		template <class Type, std::enable_if_t<std::is_integral<Type>::value>* = nullptr>
		Optional<Type> getOpt_() const
		{
			if (auto p = m_detail->as<bool>())
			{
				return p->get();
			}
			if (auto p = m_detail->as<int64_t>())
			{
				return static_cast<Type>(p->get());
			}
			if (auto p = m_detail->as<double>())
			{
				return static_cast<Type>(p->get());
			}

			return none;
		}

		friend void s3d::Formatter(FormatData& formatData, const TOMLValue& value);

		struct Visitor
		{
			String& str;

			template <typename Type>
			void visit(Type&& val) const
			{
				std::stringstream ss;
				ss << val;

				str = CharacterSet::FromUTF8(ss.str());
			}
		};

	public:

		TOMLValue()
			: m_detail(nullptr) {}

		explicit TOMLValue(const std::shared_ptr<cpptoml::base>& p)
			: m_detail(p) {}

		template <typename Type>
		Type get() const
		{
			return getOpt<Type>().value_or(Type());
		}

		template <typename Type, typename U>
		Type getOr(U&& defaultValue) const
		{
			return getOpt<Type>().value_or(std::forward<U>(defaultValue));
		}

		template <typename Type>
		Optional<Type> getOpt() const
		{
			return getOpt_<Type>();
		}

		bool isEmpty() const
		{
			return m_detail == nullptr;
		}

		TOMLValueType getType() const
		{
			if (isEmpty())
			{
				return TOMLValueType::Empty;
			}

			if (m_detail->is_table())
			{
				return TOMLValueType::Table;
			}
			if (m_detail->is_array())
			{
				return TOMLValueType::Array;
			}
			if (m_detail->is_table_array())
			{
				return TOMLValueType::TableArray;
			}
			if (m_detail->is_value())
			{
				if (m_detail->as<std::string>())
				{
					return TOMLValueType::String;
				}
				if (m_detail->as<double>())
				{
					return TOMLValueType::Number;
				}
				if (m_detail->as<bool>())
				{
					return TOMLValueType::Bool;
				}

				if (m_detail->as<cpptoml::local_date>())
				{
					return TOMLValueType::Date;
				}

				return TOMLValueType::DateTime;
			}

			return TOMLValueType::Unknown;
		}

		bool isTable() const
		{
			return getType() == TOMLValueType::Table;
		}
		bool isArray() const
		{
			return getType() == TOMLValueType::Array;
		}
		bool isTableArray() const
		{
			return getType() == TOMLValueType::TableArray;
		}
		bool isString() const
		{
			return getType() == TOMLValueType::String;
		}
		bool isBool() const
		{
			return getType() == TOMLValueType::Bool;
		}
		bool isNumber() const
		{
			return getType() == TOMLValueType::Number;
		}
		bool isDate() const
		{
			return getType() == TOMLValueType::Date;
		}
		bool isDateTime() const
		{
			return getType() == TOMLValueType::DateTime;
		}

		////////////////////////////////
		//
		//  Table
		//

		size_t memberCount() const
		{
			if (isEmpty())
			{
				return 0;
			}

			if (auto&& table = m_detail->as_table())
			{
				return table->size();
			}

			return 0;
		}

		bool hasMember(const String& name) const
		{
			if (isEmpty())
			{
				return false;
			}

			if (auto&& table = m_detail->as_table())
			{
				return table->contains(name.toUTF8());
			}

			return false;
		}

		TOMLTableView tableView() const
		{
			if (isEmpty())
			{
				return TOMLTableView();
			}

			if (auto&& table = m_detail->as_table())
			{
				return TOMLTableView(TOMLTableIterator(table->begin()), TOMLTableIterator(table->end()));
			}

			return TOMLTableView();
		}

		TOMLValue operator [](const String& path) const
		{
			if (isEmpty())
			{
				return TOMLValue();
			}

			if (auto&& table = m_detail->as_table())
			{
				try
				{
					return TOMLValue(table->get_qualified(path.toUTF8()));
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
		//  Array/TableArray
		//

		size_t arrayCount() const
		{
			if (isEmpty())
			{
				return 0;
			}

			if (auto&& arr = m_detail->as_array())
			{
				return arr->get().size();
			}
			if (auto&& arr = m_detail->as_table_array())
			{
				return arr->get().size();
			}

			return 0;
		}

		TOMLArrayView arrayView() const
		{
			if (isEmpty())
			{
				return TOMLArrayView();
			}

			if (auto&& arr = m_detail->as_array())
			{
				return TOMLArrayView(arr->begin(), arr->end());
			}

			return TOMLArrayView();
		}

		TOMLTableArrayView tableArrayView() const
		{
			if (isEmpty())
			{
				return TOMLTableArrayView();
			}

			if (auto&& arr = m_detail->as_table_array())
			{
				return TOMLTableArrayView(arr->begin(), arr->end());
			}

			return TOMLTableArrayView();
		}

		////////////////////////////////
		//
		//  String
		//

		String getString() const
		{
			if (isEmpty())
			{
				return String();
			}

			if (auto&& str = m_detail->as<std::string>())
			{
				return CharacterSet::FromUTF8(str->get());
			}

			return String();
		}

		////////////////////////////////
		//
		//  Date
		//

		Date getDate()
		{
			if (isEmpty())
			{
				return Date();
			}

			if (auto&& date_ = m_detail->as<cpptoml::local_date>())
			{
				auto&& date = date_->get();

				return Date(date.year, date.month, date.day);
			}

			return Date();
		}

		////////////////////////////////
		//
		//  DateTime
		//

		DateTime getDateTime()
		{
			if (isEmpty())
			{
				return DateTime();
			}

			if (auto&& dateTime_ = m_detail->as<cpptoml::offset_datetime>())
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

				ret += std::chrono::minutes(Time::UtcOffsetMinutes() - offset);

				return ret;
			}

			if (auto&& localDateTime_ = m_detail->as<cpptoml::local_datetime>())
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

	};

	TOMLValue TOMLArrayIterator::operator *() const
	{
		return TOMLValue(*m_detail);
	}

	TOMLValue TOMLArrayView::operator [](size_t index) const
	{
		return TOMLValue(*(m_begin + index));
	}

	TOMLValue TOMLTableArrayIterator::operator *() const
	{
		return TOMLValue(*m_detail);
	}

	TOMLValue TOMLTableArrayView::operator [](size_t index) const
	{
		return TOMLValue(*(m_begin + index));
	}

	struct TOMLTableMember
	{
		String name;

		TOMLValue value;
	};

	TOMLTableMember TOMLTableIterator::operator *() const
	{
		return { CharacterSet::FromUTF8(m_detail->first), TOMLValue(m_detail->second) };
	}

	class TOMLReader : public TOMLValue
	{
	public:

		TOMLReader()
			: TOMLValue() {}

		explicit TOMLReader(const FilePath& path)
			: TOMLReader()
		{
			open(path);
		}

		template <typename Reader, std::enable_if_t<std::is_base_of<IReader, Reader>::value && !std::is_lvalue_reference<Reader>::value, nullptr_t>* = nullptr>
		explicit TOMLReader(Reader&& reader)
			: TOMLReader()
		{
			open(std::forward<Reader>(reader));
		}

		explicit TOMLReader(const std::shared_ptr<IReader>& reader)
			: TOMLReader()
		{
			open(reader);
		}

		bool open(const FilePath& path)
		{
			try {
				m_detail = cpptoml::parse_file(path.toUTF8());
			}
			catch (...) {
				return false;
			}

			return !isEmpty();
		}

		bool open(const std::shared_ptr<IReader>& reader)
		{
			if (isOpened())
			{
				close();
			}

			std::stringstream ss;
			ss << TextReader(reader).readAll();

			try {
				m_detail = cpptoml::parser(ss).parse();
			}
			catch (...) {
				return false;
			}

			return m_detail != nullptr;
		}

		void close()
		{
			m_detail.reset();
		}

		bool isOpened() const
		{
			return m_detail != nullptr;
		}

		explicit operator bool() const
		{
			return isOpened();
		}
	};

	void Formatter(FormatData& formatData, const toml::TOMLValue& value)
	{
		if (value.isEmpty())
		{
			return;
		}

		String str;
		value.m_detail->accept(toml::TOMLValue::Visitor{ str });

		formatData.string.append(str.c_str());
	}

	void Formatter(FormatData& formatData, const toml::TOMLReader& reader)
	{
		if (reader.isEmpty())
		{
			return;
		}

		Formatter(formatData, static_cast<toml::TOMLValue>(reader));
	}
}

