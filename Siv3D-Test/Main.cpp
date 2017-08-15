# include <Siv3D.hpp> // OpenSiv3D v0.1.6
# include "cpptoml/cpptoml.h"

namespace test {
	enum class TOMLValueType {
		Empty,
		Table,
		Array,
		String,
		Number,
		Bool,
		DateTime
	};

	class TOMLValue;

	struct TOMLTableMember
	{
		String name;

		TOMLValue value;
	};

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

		TOMLTableMember operator *() const {
			return { CharacterSet::FromUTF8(m_detail->first), m_detail->second };
		}

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
		TOMLTableView(cpptoml::table::iterator begin, cpptoml::table::iterator end) noexcept
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

		TOMLValue operator *() const
		{
			return *m_detail;
		}

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

		TOMLValue operator [](size_t index) const
		{
			return *(m_begin + index);
		}
	};

	class TOMLValue {
	protected:

		std::shared_ptr<cpptoml::base> m_detail;

		template<class Type, std::enable_if_t<!std::is_arithmetic<Type>::value>* = nullptr>
		Optional<Type> getOpt_() const
		{
			return ParseOpt<Type>(getString());
		}

		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
		Optional<Type> getOpt_() const = delete;

	public:

		TOMLValue()
			: m_detail(std::make_shared<cpptoml::base>()) {}

		TOMLValue(const std::shared_ptr<cpptoml::base>& p)
			: m_detail(std::make_shared<cpptoml::base>(*p)) {}

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

		bool isEmpty() const {
			return m_detail == nullptr;
		}

		TOMLValueType getType() const {
			if (isEmpty())
			{
				return TOMLValueType::Empty;
			}

			if (m_detail->is_table())
			{
				return TOMLValueType::Table;
			}
			if (m_detail->is_array() || m_detail->is_table_array())
			{
				return TOMLValueType::Array;
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
			}

			return TOMLValueType::DateTime;
		}

		bool isTable() const {
			return getType() == TOMLValueType::Table;
		}
		bool isArray() const {
			return getType() == TOMLValueType::Array;
		}
		bool isString() const {
			return getType() == TOMLValueType::String;
		}
		bool isBool() const {
			return getType() == TOMLValueType::Bool;
		}
		bool isNumber() const {
			return getType() == TOMLValueType::Number;
		}
		bool isDateTime() const {
			return getType() == TOMLValueType::DateTime;
		}

		////////////////////////////////
		//
		//  Table
		//

		size_t memberCount() const {
			if (auto&& table = m_detail->as_table())
			{
				return table->size();
			}

			return 0;
		}

		bool hasMember(const String& name) const {
			if (auto&& table = m_detail->as_table())
			{
				return table->contains(name.toUTF8());
			}

			return false;
		}

		TOMLTableView objectView() const {
			if (auto&& table = m_detail->as_table())
			{
				return TOMLTableView(table->begin(), table->end());
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
		//  Array
		//
		
		size_t arrayCount() const {
			if (auto&& arr = m_detail->as_array())
			{
				return arr->get().size();
			}

			return 0;
		}

		TOMLArrayView arrayView() const
		{
			if (auto&& arr = m_detail->as_array())
			{
				return TOMLArrayView(arr->begin(), arr->end());
			}
			
			return TOMLArrayView();
		}

		////////////////////////////////
		//
		//  String
		//

		String getString() const
		{
			if (auto&& str = m_detail->as<std::string>())
			{
				return CharacterSet::FromUTF8(str->get());
			}

			return String();
		}

		////////////////////////////////
		//
		//  DateTime
		//

		Date getDate()
		{
			if (auto&& date_ = m_detail->as<cpptoml::local_date>())
			{
				auto&& date = date_->get();

				return Date(date.year, date.month, date.day);
			}

			return Date();
		}

		DateTime getDateTime()
		{
			if (auto&& dateTime_ = m_detail->as<cpptoml::datetime>())
			{
				auto& dateTime = dateTime_->get();
				const int32 offset = dateTime.hour_offset * 60 + dateTime.minute_offset;
				
				DateTime ret(
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

	template <>
	Optional<String> TOMLValue::getOpt<String>() const
	{
		if (!isString())
		{
			return none;
		}

		return Optional<String>(in_place, getString());
	}

	template <>
	Optional<int64> TOMLValue::getOpt<int64>() const
	{
		std::shared_ptr<cpptoml::value<std::int64_t>> ptr;
		if (isNumber() && (ptr = m_detail->as<int64_t>()))
		{
			return Optional<int64>(in_place, static_cast<int64>(ptr->get()));
		}

		return none;
	}

	template <>
	Optional<double> TOMLValue::getOpt<double>() const
	{
		std::shared_ptr<cpptoml::value<double>> ptr;
		if (isNumber() && (ptr = m_detail->as<double>()))
		{
			return Optional<double>(in_place, static_cast<double>(ptr->get()));
		}

		return none;
	}

	template <>
	Optional<bool> TOMLValue::getOpt<bool>() const
	{
		std::shared_ptr<cpptoml::value<bool>> ptr;
		if (isNumber() && (ptr = m_detail->as<bool>()))
		{
			return Optional<bool>(in_place, static_cast<bool>(ptr->get()));
		}

		return none;
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
			m_detail = cpptoml::parse_file(path.toUTF8());
		}

		bool open(const std::shared_ptr<IReader>& reader)
		{
			if (isOpened())
			{
				close();
			}

			std::stringstream ss;
			ss << TextReader(reader).readAll();

			m_detail = cpptoml::parser(ss).parse();

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
}

void Main()
{
	while (System::Update())
	{
	}
}
