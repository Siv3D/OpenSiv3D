//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Optional.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "Parse.hpp"

namespace s3d
{
	namespace detail
	{
		struct JSONArrayIteratorDetail;

		struct JSONMemberIteratorDetail;

		struct JSONValueDetail;

		struct JSONDocumentDetail;
	}

	enum class JSONValueType
	{
		Empty,

		Null,
		
		Object,
		
		Array,
		
		String,
		
		Number,
		
		Bool,
	};

	class JSONArrayIterator
	{
	private:

		std::shared_ptr<detail::JSONArrayIteratorDetail> m_detail;

	public:

		JSONArrayIterator();

		explicit JSONArrayIterator(const detail::JSONArrayIteratorDetail& p);

		JSONArrayIterator operator++();

		JSONArrayIterator operator++(int);

		[[nodiscard]] JSONArrayIterator operator +(size_t index) const;

		[[nodiscard]] JSONValue operator *() const;

		[[nodiscard]] bool operator ==(const JSONArrayIterator& other) const noexcept;

		[[nodiscard]] bool operator !=(const JSONArrayIterator& other) const noexcept;
	};

	class JSONObjectIterator
	{
	private:

		std::shared_ptr<detail::JSONMemberIteratorDetail> m_detail;

	public:

		JSONObjectIterator();

		explicit JSONObjectIterator(const detail::JSONMemberIteratorDetail& it);

		JSONObjectIterator operator ++();

		JSONObjectIterator operator ++(int);

		[[nodiscard]] JSONObjectMember operator *() const;

		[[nodiscard]] bool operator ==(const JSONObjectIterator& other) const noexcept;

		[[nodiscard]] bool operator !=(const JSONObjectIterator& other) const noexcept;
	};

	class JSONArrayView
	{
	private:

		JSONArrayIterator m_begin;

		JSONArrayIterator m_end;

	public:

		JSONArrayView() = default;

		JSONArrayView(JSONArrayIterator begin, JSONArrayIterator end) noexcept
			: m_begin(begin)
			, m_end(end) {}

		[[nodiscard]] JSONArrayIterator begin() const
		{
			return m_begin;
		}

		[[nodiscard]] JSONArrayIterator end() const
		{
			return m_end;
		}

		[[nodiscard]] JSONValue operator [](size_t index) const;
	};

	class JSONObjectView
	{
	private:

		JSONObjectIterator m_begin;

		JSONObjectIterator m_end;

	public:

		JSONObjectView() = default;

		JSONObjectView(JSONObjectIterator begin, JSONObjectIterator end) noexcept
			: m_begin(begin)
			, m_end(end) {}

		[[nodiscard]] JSONObjectIterator begin() const
		{
			return m_begin;
		}

		[[nodiscard]] JSONObjectIterator end() const
		{
			return m_end;
		}
	};

	class JSONValue
	{
	protected:

		std::shared_ptr<detail::JSONValueDetail> m_detail;

		template <class Type, std::enable_if_t<!std::is_arithmetic_v<Type>>* = nullptr>
		Optional<Type> getOpt_() const
		{
			return ParseOpt<Type>(getString());
		}

		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		Optional<Type> getOpt_() const = delete;

	public:

		JSONValue();

		explicit JSONValue(const detail::JSONValueDetail& value);

		[[nodiscard]] JSONValue operator [](const String& path) const;

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
		
		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] explicit operator bool() const
		{
			return !isEmpty();
		}

		////////////////////////////////
		//
		//	Type
		//

		JSONValueType getType() const;

		[[nodiscard]] bool isNull() const
		{
			return getType() == JSONValueType::Null;
		}

		[[nodiscard]] bool isBool() const
		{
			return getType() == JSONValueType::Bool;
		}

		[[nodiscard]] bool isObject() const
		{
			return getType() == JSONValueType::Object;
		}

		[[nodiscard]] bool isArray() const
		{
			return getType() == JSONValueType::Array;
		}

		[[nodiscard]] bool isString() const
		{
			return getType() == JSONValueType::String;
		}

		[[nodiscard]] bool isNumber() const
		{
			return getType() == JSONValueType::Number;
		}

		////////////////////////////////
		//
		//	Object
		//

		[[nodiscard]] size_t memberCount() const;

		[[nodiscard]] bool hasMember(const String& name) const;

		[[nodiscard]] JSONObjectView objectView() const;

		////////////////////////////////
		//
		//	Array
		//

		[[nodiscard]] size_t arrayCount() const;

		[[nodiscard]] JSONArrayView arrayView() const;

		template <class Type>
		[[nodiscard]] Array<Type> getArray() const
		{
			Array<Type> result;

			for (const auto& element : arrayView())
			{
				result << element.get<Type>();
			}

			return result;
		}

		////////////////////////////////
		//
		//	String
		//

		[[nodiscard]] String getString() const;
	};
	
	template <>
	Optional<String> JSONValue::getOpt<String>() const;

	template <>
	Optional<int32> JSONValue::getOpt<int32>() const;
	
	template <>
	Optional<uint32> JSONValue::getOpt<uint32>() const;
	
	template <>
	Optional<int64> JSONValue::getOpt<int64>() const;
	
	template <>
	Optional<uint64> JSONValue::getOpt<uint64>() const;
	
	template <>
	Optional<float> JSONValue::getOpt<float>() const;
	
	template <>
	Optional<double> JSONValue::getOpt<double>() const;

	template <>
	Optional<bool> JSONValue::getOpt<bool>() const;

	struct JSONObjectMember
	{
		String name;

		JSONValue value;
	};

	class JSONReader : public JSONValue
	{
	private:

		std::shared_ptr<detail::JSONDocumentDetail> m_document;

	public:

		JSONReader();

		explicit JSONReader(const FilePath& path);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		explicit JSONReader(Reader&& reader)
			: JSONReader()
		{
			open(std::make_shared<Reader>(std::forward<Reader>(reader)));
		}

		explicit JSONReader(const std::shared_ptr<IReader>& reader);

		bool open(const FilePath& path);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool open(Reader&& reader)
		{
			return open(std::make_shared<Reader>(std::forward<Reader>(reader)));
		}

		bool open(const std::shared_ptr<IReader>& reader);

		void close();

		[[nodiscard]] bool isOpened() const;

		[[nodiscard]] explicit operator bool() const
		{
			return isOpened();
		}
	};
}
