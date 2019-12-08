//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------
// s3d::TOMLReader is originally created by azaika (OpenSiv3D Project)
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "String.hpp"
# include "Optional.hpp"
# include "Parse.hpp"
# include "DateTime.hpp"
# include "Unicode.hpp"

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

		[[nodiscard]] TOMLTableMember operator *() const;

		[[nodiscard]] bool operator ==(const TOMLTableIterator& other) const noexcept;

		[[nodiscard]] bool operator !=(const TOMLTableIterator& other) const noexcept;
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

		[[nodiscard]] TOMLTableIterator begin() const
		{
			return m_begin;
		}

		[[nodiscard]] TOMLTableIterator end() const
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

		[[nodiscard]] TOMLValue operator *() const;

		[[nodiscard]] bool operator ==(const TOMLArrayIterator& other) const noexcept;

		[[nodiscard]] bool operator !=(const TOMLArrayIterator& other) const noexcept;
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

		[[nodiscard]] TOMLArrayIterator begin() const
		{
			return m_begin;
		}

		[[nodiscard]] TOMLArrayIterator end() const
		{
			return m_end;
		}

		[[nodiscard]] TOMLValue operator [](size_t index) const;
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

		[[nodiscard]] TOMLValue operator *() const;

		[[nodiscard]] bool operator ==(const TOMLTableArrayIterator& other) const noexcept;

		[[nodiscard]] bool operator !=(const TOMLTableArrayIterator& other) const noexcept;
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

		[[nodiscard]] TOMLTableArrayIterator begin() const
		{
			return m_begin;
		}

		[[nodiscard]] TOMLTableArrayIterator end() const
		{
			return m_end;
		}

		[[nodiscard]] TOMLValue operator [](size_t index) const;
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

		template <class Type, std::enable_if_t<!std::is_arithmetic_v<Type>>* = nullptr>
		Optional<Type> getOpt_() const
		{
			return ParseOpt<Type>(getString());
		}

		Optional<String> getOptString() const;

		Optional<int64> getOptInt64() const;

		Optional<double> getOptDouble() const;

		Optional<bool> getOptBool() const;

		Optional<Date> getOptDate() const;

		Optional<DateTime> getOptDateTime() const;

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
		[[nodiscard]] Type get() const
		{
			return getOpt<Type>().value_or(Type());
		}

		template <class Type, class U>
		[[nodiscard]] Type getOr(U&& defaultValue) const
		{
			return getOpt<Type>().value_or(std::forward<U>(defaultValue));
		}

		template <class Type>
		[[nodiscard]] Optional<Type> getOpt() const
		{
			return getOpt_<Type>();
		}

		template <>
		[[nodiscard]] inline Optional<String> getOpt<String>() const;

		template <>
		[[nodiscard]] inline Optional<int64> getOpt<int64>() const;

		template <>
		[[nodiscard]] inline Optional<double> getOpt<double>() const;

		template <>
		[[nodiscard]] inline Optional<bool> getOpt<bool>() const;

		template <>
		[[nodiscard]] inline Optional<Date> getOpt<Date>() const;

		template <>
		[[nodiscard]] inline Optional<DateTime> getOpt<DateTime>() const;

		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] TOMLValueType getType() const;

		[[nodiscard]] bool isTable() const noexcept;
		
		[[nodiscard]] bool isArray() const noexcept;

		[[nodiscard]] bool isTableArray() const noexcept;

		[[nodiscard]] bool isString() const noexcept;

		[[nodiscard]] bool isBool() const noexcept;

		[[nodiscard]] bool isNumber() const noexcept;

		[[nodiscard]] bool isDate() const noexcept;

		[[nodiscard]] bool isDateTime() const noexcept;

		[[nodiscard]] bool hasMember(const String& name) const;

		[[nodiscard]] TOMLTableView tableView() const;

		[[nodiscard]] TOMLValue operator [](const String& path) const;

		[[nodiscard]] size_t arrayCount() const;

		[[nodiscard]] TOMLArrayView arrayView() const;

		[[nodiscard]] TOMLTableArrayView tableArrayView() const;

		[[nodiscard]] String getString() const;

		[[nodiscard]] Date getDate() const;

		[[nodiscard]] DateTime getDateTime() const;

		[[nodiscard]] String format() const;
	};
	
	struct TOMLTableMember
	{
		String name;

		TOMLValue value;
	};

	class TOMLReader : public TOMLValue
	{
	public:

		TOMLReader() = default;

		explicit TOMLReader(FilePathView path);

		explicit TOMLReader(const std::shared_ptr<IReader>& reader);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		explicit TOMLReader(Reader&& reader)
		{
			open(std::make_shared<Reader>(std::forward<Reader>(reader)));
		}

		bool open(FilePathView path);

		bool open(const std::shared_ptr<IReader>& reader);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool open(Reader&& reader)
		{
			return open(std::make_shared<Reader>(std::forward<Reader>(reader)));
		}

		void close();

		[[nodiscard]] bool isOpened() const noexcept;

		[[nodiscard]] explicit operator bool() const noexcept;
	};

	template <>
	[[nodiscard]] inline Optional<String> TOMLValue::getOpt<String>() const
	{
		return getOptString();
	}

	template <>
	[[nodiscard]] inline Optional<int64> TOMLValue::getOpt<int64>() const
	{
		return getOptInt64();
	}

	template <>
	[[nodiscard]] inline Optional<double> TOMLValue::getOpt<double>() const
	{
		return getOptDouble();
	}

	template <>
	[[nodiscard]] inline Optional<bool> TOMLValue::getOpt<bool>() const
	{
		return getOptBool();
	}

	template <>
	[[nodiscard]] inline Optional<Date> TOMLValue::getOpt<Date>() const
	{
		return getOptDate();
	}

	template <>
	[[nodiscard]] inline Optional<DateTime> TOMLValue::getOpt<DateTime>() const
	{
		return getOptDateTime();
	}

	void Formatter(FormatData& formatData, const TOMLValue& value);

	void Formatter(FormatData& formatData, const TOMLReader& reader);
}
