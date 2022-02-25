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
# include "Common.hpp"
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

	class TOMLTableIterator;
	class TOMLTableView;
	class TOMLArrayIterator;
	class TOMLArrayView;
	class TOMLTableArrayIterator;
	class TOMLTableArrayView;
	class TOMLValue;
	struct TOMLTableMember;
	class TOMLReader;

	enum class TOMLValueType : uint8
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
	public:

		SIV3D_NODISCARD_CXX20
		TOMLTableIterator() = default;

		SIV3D_NODISCARD_CXX20
		explicit TOMLTableIterator(const detail::TOMLTableIteratorDetail&);

		TOMLTableIterator operator ++();

		TOMLTableIterator operator ++(int);

		[[nodiscard]]
		TOMLTableMember operator *() const;

		[[nodiscard]]
		bool operator ==(const TOMLTableIterator& other) const noexcept;

		[[nodiscard]]
		bool operator !=(const TOMLTableIterator& other) const noexcept;
	
	private:

		std::shared_ptr<detail::TOMLTableIteratorDetail> m_detail;
	};

	class TOMLTableView
	{
	public:

		SIV3D_NODISCARD_CXX20
		TOMLTableView() = default;
		
		SIV3D_NODISCARD_CXX20
		TOMLTableView(const TOMLTableIterator& begin, const TOMLTableIterator& end) noexcept;

		[[nodiscard]]
		TOMLTableIterator begin() const noexcept;

		[[nodiscard]]
		TOMLTableIterator end() const noexcept;

	private:

		TOMLTableIterator m_begin, m_end;
	};

	class TOMLArrayIterator
	{
	public:

		SIV3D_NODISCARD_CXX20
		TOMLArrayIterator() = default;

		SIV3D_NODISCARD_CXX20
		explicit TOMLArrayIterator(const detail::TOMLArrayIteratorDetail&);

		TOMLArrayIterator operator ++();

		TOMLArrayIterator operator ++(int);

		TOMLArrayIterator operator +(size_t index) const;

		[[nodiscard]]
		TOMLValue operator *() const;

		[[nodiscard]]
		bool operator ==(const TOMLArrayIterator& other) const noexcept;

		[[nodiscard]]
		bool operator !=(const TOMLArrayIterator& other) const noexcept;

	private:

		std::shared_ptr<detail::TOMLArrayIteratorDetail> m_detail;
	};

	class TOMLArrayView
	{
	public:

		SIV3D_NODISCARD_CXX20
		TOMLArrayView() = default;
		
		SIV3D_NODISCARD_CXX20
		TOMLArrayView(const TOMLArrayIterator& begin, const TOMLArrayIterator& end) noexcept;

		[[nodiscard]]
		TOMLArrayIterator begin() const noexcept;

		[[nodiscard]]
		TOMLArrayIterator end() const noexcept;

		[[nodiscard]]
		TOMLValue operator [](size_t index) const;

	private:

		TOMLArrayIterator m_begin, m_end;
	};

	class TOMLTableArrayIterator
	{
	public:

		SIV3D_NODISCARD_CXX20
		TOMLTableArrayIterator() = default;
		
		SIV3D_NODISCARD_CXX20
		explicit TOMLTableArrayIterator(const detail::TOMLTableArrayIteratorDetail&);
		
		TOMLTableArrayIterator operator ++();

		TOMLTableArrayIterator operator ++(int);

		TOMLTableArrayIterator operator +(size_t index) const;

		[[nodiscard]]
		TOMLValue operator *() const;

		[[nodiscard]]
		bool operator ==(const TOMLTableArrayIterator& other) const noexcept;

		[[nodiscard]]
		bool operator !=(const TOMLTableArrayIterator& other) const noexcept;

	private:

		std::shared_ptr<detail::TOMLTableArrayIteratorDetail> m_detail;
	};

	class TOMLTableArrayView
	{
	public:

		SIV3D_NODISCARD_CXX20
		TOMLTableArrayView() = default;

		SIV3D_NODISCARD_CXX20
		TOMLTableArrayView(const TOMLTableArrayIterator& begin, const TOMLTableArrayIterator& end) noexcept;

		[[nodiscard]]
		TOMLTableArrayIterator begin() const noexcept;

		[[nodiscard]]
		TOMLTableArrayIterator end() const noexcept;

		[[nodiscard]]
		TOMLValue operator [](size_t index) const;

	private:

		TOMLTableArrayIterator m_begin, m_end;
	};

	class TOMLValue
	{
	public:

		SIV3D_NODISCARD_CXX20
		TOMLValue() = default;

		SIV3D_NODISCARD_CXX20
		explicit TOMLValue(const detail::TOMLValueDetail&);

		template <class Type>
		[[nodiscard]]
		Type get() const;

		template <class Type, class U>
		[[nodiscard]]
		Type getOr(U&& defaultValue) const;

		template <class Type>
		[[nodiscard]]
		Optional<Type> getOpt() const;

# if SIV3D_PLATFORM(WINDOWS) || SIV3D_PLATFORM(MACOS)

		template <>
		[[nodiscard]]
		inline Optional<String> getOpt<String>() const;

		template <>
		[[nodiscard]]
		inline Optional<int64> getOpt<int64>() const;

		template <>
		[[nodiscard]]
		inline Optional<double> getOpt<double>() const;

		template <>
		[[nodiscard]]
		inline Optional<bool> getOpt<bool>() const;

		template <>
		[[nodiscard]]
		inline Optional<Date> getOpt<Date>() const;

		template <>
		[[nodiscard]]
		inline Optional<DateTime> getOpt<DateTime>() const;

# endif

		[[nodiscard]]
		bool isEmpty() const;

		[[nodiscard]]
		TOMLValueType getType() const;

		[[nodiscard]]
		bool isTable() const noexcept;
		
		[[nodiscard]]
		bool isArray() const noexcept;

		[[nodiscard]]
		bool isTableArray() const noexcept;

		[[nodiscard]]
		bool isString() const noexcept;

		[[nodiscard]]
		bool isBool() const noexcept;

		[[nodiscard]]
		bool isNumber() const noexcept;

		[[nodiscard]]
		bool isDate() const noexcept;

		[[nodiscard]]
		bool isDateTime() const noexcept;

		[[nodiscard]]
		bool hasMember(const String& name) const;

		[[nodiscard]]
		TOMLTableView tableView() const;

		[[nodiscard]]
		TOMLValue operator [](const String& path) const;

		[[nodiscard]]
		size_t arrayCount() const;

		[[nodiscard]]
		TOMLArrayView arrayView() const;

		[[nodiscard]]
		TOMLTableArrayView tableArrayView() const;

		[[nodiscard]]
		String getString() const;

		[[nodiscard]]
		Date getDate() const;

		[[nodiscard]]
		DateTime getDateTime() const;

		[[nodiscard]]
		String format() const;

		friend void Formatter(FormatData& formatData, const TOMLValue& value);

	protected:

		std::shared_ptr<detail::TOMLValueDetail> m_detail;

		template <class Type, std::enable_if_t<std::is_integral_v<Type> && !std::is_same_v<bool, std::decay_t<Type>>>* = nullptr>
		Optional<Type> getOpt_() const;

		template <class Type, std::enable_if_t<std::is_floating_point_v<Type>>* = nullptr>
		Optional<Type> getOpt_() const;

		template <class Type, std::enable_if_t<!std::is_arithmetic_v<Type>>* = nullptr>
		Optional<Type> getOpt_() const;

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
	};
	
	struct TOMLTableMember
	{
		String name;

		TOMLValue value;
	};

	class TOMLReader : public TOMLValue
	{
	public:

		SIV3D_NODISCARD_CXX20
		TOMLReader() = default;

		SIV3D_NODISCARD_CXX20
		explicit TOMLReader(FilePathView path);

		SIV3D_NODISCARD_CXX20
		explicit TOMLReader(std::unique_ptr<IReader>&& reader);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		explicit TOMLReader(Reader&& reader);

		bool open(FilePathView path);

		bool open(std::unique_ptr<IReader>&& reader);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool open(Reader&& reader);

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		friend void Formatter(FormatData& formatData, const TOMLReader& reader);
	};
}

# include "detail/TOMLReader.ipp"
