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
#include "Fwd.hpp"
#include "String.hpp"

namespace s3d
{
	namespace detail
	{
		struct TOMLTableIteratorDetail;
		struct TOMLArrayIteratorDetail;
		struct TOMLTableArrayIteratorDetail;
		struct TOMLValueDetail;
	}

	enum class TOMLValueType
	{
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

	class TOMLTableIterator
	{
	private:

		std::shared_ptr<detail::TOMLTableIteratorDetail> m_detail;

	public:

		TOMLTableIterator() = default;

		explicit TOMLTableIterator(const detail::TOMLTableIteratorDetail&);

		TOMLTableIterator operator ++();

		TOMLTableIterator operator ++(int);

		TOMLTableMember operator *() const;

		bool operator ==(const TOMLTableIterator& other) const noexcept;

		bool operator !=(const TOMLTableIterator& other) const noexcept;
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

		std::shared_ptr<detail::TOMLArrayIteratorDetail> m_detail;

	public:

		TOMLArrayIterator() = default;

		explicit TOMLArrayIterator(const detail::TOMLArrayIteratorDetail&);

		TOMLArrayIterator operator ++();

		TOMLArrayIterator operator ++(int);

		TOMLArrayIterator operator +(size_t index) const;

		TOMLValue operator *() const;

		bool operator ==(const TOMLArrayIterator& other) const noexcept;

		bool operator !=(const TOMLArrayIterator& other) const noexcept;
	};

	class TOMLArrayView
	{
	private:

		TOMLArrayIterator m_begin, m_end;

	public:

		TOMLArrayView() = default;
		
		TOMLArrayView(const TOMLArrayIterator& begin, const TOMLArrayIterator& end) noexcept
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

		std::shared_ptr<detail::TOMLTableArrayIteratorDetail> m_detail;

	public:

		TOMLTableArrayIterator() = default;
		
		explicit TOMLTableArrayIterator(const detail::TOMLTableArrayIteratorDetail&);
		
		TOMLTableArrayIterator operator ++();

		TOMLTableArrayIterator operator ++(int);

		TOMLTableArrayIterator operator +(size_t index) const;

		TOMLValue operator *() const;

		bool operator ==(const TOMLTableArrayIterator& other) const noexcept;

		bool operator !=(const TOMLTableArrayIterator& other) const noexcept;
	};

	class TOMLTableArrayView
	{
	private:

		TOMLTableArrayIterator m_begin, m_end;

	public:

		TOMLTableArrayView() = default;

		TOMLTableArrayView(const TOMLTableArrayIterator& begin, const TOMLTableArrayIterator& end) noexcept
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

		std::shared_ptr<detail::TOMLValueDetail> m_detail = nullptr;

		template <class Type, std::enable_if_t<std::is_integral_v<Type> && !std::is_same_v<bool, std::decay_t<Type>>>* = nullptr>
		Optional<Type> getOpt_() const
		{
			if (auto&& tmp = getOpt<int64>())
			{
				return static_cast<Type>(tmp.value());
			}
			
			return none;
		}

		template <class Type, std::enable_if_t<std::is_floating_point_v<Type>>* = nullptr>
		Optional<Type> getOpt_() const
		{
			if (auto&& tmp = getOpt<double>())
			{
				return static_cast<Type>(tmp.value());
			}

			return none;
		}

		struct Visitor
		{
			String& str;

			template <class Type>
			void visit(Type&& val) const
			{
				std::stringstream ss;
				
				ss << val;

				str = Unicode::FromUTF8(ss.str());
			}
		};

	public:

		TOMLValue() = default;

		explicit TOMLValue(const detail::TOMLValueDetail&);

		template <class Type>
		Type get() const
		{
			return getOpt<Type>().value_or(Type());
		}

		template <class Type, class U>
		Type getOr(U&& defaultValue) const
		{
			return getOpt<Type>().value_or(std::forward<U>(defaultValue));
		}

		template <class Type>
		Optional<Type> getOpt() const
		{
			return getOpt_<Type>();
		}

		bool isEmpty() const;

		TOMLValueType getType() const;

		bool isTable() const noexcept
		{
			return getType() == TOMLValueType::Table;
		}
		
		bool isArray() const noexcept
		{
			return getType() == TOMLValueType::Array;
		}

		bool isTableArray() const noexcept
		{
			return getType() == TOMLValueType::TableArray;
		}

		bool isString() const noexcept
		{
			return getType() == TOMLValueType::String;
		}

		bool isBool() const noexcept
		{
			return getType() == TOMLValueType::Bool;
		}

		bool isNumber() const noexcept
		{
			return getType() == TOMLValueType::Number;
		}

		bool isDate() const noexcept
		{
			return getType() == TOMLValueType::Date;
		}

		bool isDateTime() const noexcept
		{
			return getType() == TOMLValueType::DateTime;
		}

		size_t memberCount() const;

		bool hasMember(const String& name) const;

		TOMLTableView tableView() const;

		TOMLValue operator [](const String& path) const;

		size_t arrayCount() const;

		TOMLArrayView arrayView() const;

		TOMLTableArrayView tableArrayView() const;

		String getString() const;

		Date getDate() const;

		DateTime getDateTime() const;

		String format() const;
	};

	template <>
	Optional<String> TOMLValue::getOpt<String>() const;

	template <>
	Optional<int64> TOMLValue::getOpt<int64>() const;

	template <>
	Optional<double> TOMLValue::getOpt<double>() const;

	template <>
	Optional<bool> TOMLValue::getOpt<bool>() const;

	template <>
	Optional<Date> TOMLValue::getOpt<Date>() const;

	template <>
	Optional<DateTime> TOMLValue::getOpt<DateTime>() const;
	
	struct TOMLTableMember
	{
		String name;

		TOMLValue value;
	};

	class TOMLReader : public TOMLValue
	{
	public:

		TOMLReader() = default;

		explicit TOMLReader(const FilePath& path);

		explicit TOMLReader(const std::shared_ptr<IReader>& reader);

		template <class Reader, std::enable_if_t<std::is_base_of<IReader, Reader>::value && !std::is_lvalue_reference<Reader>::value, nullptr_t>* = nullptr>
		explicit TOMLReader(Reader&& reader)
		{
			open(std::make_shared<Reader>(std::forward<Reader>(reader)));
		}

		bool open(const FilePath& path);

		bool open(const std::shared_ptr<IReader>& reader);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool open(Reader&& reader)
		{
			return open(std::make_shared<Reader>(std::forward<Reader>(reader)));
		}

		void close();

		bool isOpened() const noexcept;

		explicit operator bool() const noexcept
		{
			return isOpened();
		}
	};

	void Formatter(FormatData& formatData, const TOMLValue& value);

	inline void Formatter(FormatData& formatData, const TOMLReader& reader)
	{
		if (!reader.isEmpty())
		{
			Formatter(formatData, static_cast<TOMLValue>(reader));
		}
	}
}
