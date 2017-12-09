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

# define RAPIDJSON_SSE2
# include "../../ThirdParty/rapidjson/rapidjson.h"
# include "../../ThirdParty/rapidjson/document.h"
# include <Siv3D/JSONReader.hpp>
# include <Siv3D/TextReader.hpp>

namespace s3d
{
	namespace detail
	{
		struct JSONArrayIteratorDetail
		{
			const rapidjson::GenericValue<rapidjson::UTF32<char32>>* pValue = nullptr;

			JSONArrayIteratorDetail() = default;

			explicit constexpr JSONArrayIteratorDetail(const rapidjson::GenericValue<rapidjson::UTF32<char32>>* p) noexcept
				: pValue(p) {}
		};

		struct JSONMemberIteratorDetail
		{
			rapidjson::GenericValue<rapidjson::UTF32<char32>>::ConstMemberIterator it;

			JSONMemberIteratorDetail() = default;

			JSONMemberIteratorDetail(const rapidjson::GenericValue<rapidjson::UTF32<char32>>::ConstMemberIterator& _it)
				: it(_it) {}
		};

		struct JSONValueDetail
		{
			Optional<const rapidjson::GenericValue<rapidjson::UTF32<char32>>&> value;

			JSONValueDetail() = default;

			JSONValueDetail(const Optional<const rapidjson::GenericValue<rapidjson::UTF32<char32>>&>& _value)
				: value(_value) {}
		};

		struct JSONDocumentDetail
		{
			rapidjson::GenericDocument<rapidjson::UTF32<char32>> document;
		};
	}

	////////////////////////////////
	//
	//	JSONArrayIterator
	//

	JSONArrayIterator::JSONArrayIterator()
		: m_detail(std::make_shared<detail::JSONArrayIteratorDetail>())
	{

	}

	JSONArrayIterator::JSONArrayIterator(const detail::JSONArrayIteratorDetail& p)
		: m_detail(std::make_shared<detail::JSONArrayIteratorDetail>(p.pValue))
	{

	}

	JSONArrayIterator JSONArrayIterator::operator++()
	{
		++m_detail->pValue;

		return JSONArrayIterator(*m_detail);
	}

	JSONArrayIterator JSONArrayIterator::operator++(int)
	{
		const detail::JSONArrayIteratorDetail tmp(m_detail->pValue);

		++m_detail->pValue;

		return JSONArrayIterator(tmp);
	}

	JSONArrayIterator JSONArrayIterator::operator +(const size_t index) const
	{
		return JSONArrayIterator(detail::JSONArrayIteratorDetail(m_detail->pValue + index));
	}

	JSONValue JSONArrayIterator::operator *() const
	{
		return JSONValue(Optional<const rapidjson::GenericValue<rapidjson::UTF32<char32>>&>(*(m_detail->pValue)));
	}

	bool JSONArrayIterator::operator ==(const JSONArrayIterator& other) const noexcept
	{
		return m_detail->pValue == other.m_detail->pValue;
	}

	bool JSONArrayIterator::operator !=(const JSONArrayIterator& other) const noexcept
	{
		return m_detail->pValue != other.m_detail->pValue;
	}

	////////////////////////////////
	//
	//	JSONObjectIterator
	//

	JSONObjectIterator::JSONObjectIterator()
		: m_detail(std::make_shared<detail::JSONMemberIteratorDetail>())
	{

	}

	JSONObjectIterator::JSONObjectIterator(const detail::JSONMemberIteratorDetail& it)
		: m_detail(std::make_shared<detail::JSONMemberIteratorDetail>(it.it))
	{

	}

	JSONObjectIterator JSONObjectIterator::operator ++()
	{
		++m_detail->it;

		return JSONObjectIterator(detail::JSONMemberIteratorDetail(*m_detail));
	}

	JSONObjectIterator JSONObjectIterator::operator ++(int)
	{
		const detail::JSONMemberIteratorDetail tmp(m_detail->it);

		++m_detail->it;

		return JSONObjectIterator(tmp);
	}

	JSONObjectMember JSONObjectIterator::operator *() const
	{
		return{ String(m_detail->it->name.GetString(), m_detail->it->name.GetStringLength()),
			JSONValue(Optional<const rapidjson::GenericValue<rapidjson::UTF32<char32>>&>(m_detail->it->value)) };
	}

	bool JSONObjectIterator::operator ==(const JSONObjectIterator& other) const noexcept
	{
		return m_detail->it == other.m_detail->it;
	}

	bool JSONObjectIterator::operator !=(const JSONObjectIterator& other) const noexcept
	{
		return m_detail->it != other.m_detail->it;
	}

	////////////////////////////////
	//
	//	JSONArrayView
	//

	JSONValue JSONArrayView::operator [](size_t index) const
	{
		return *(m_begin + index);
	}

	////////////////////////////////
	//
	//	JSONValue
	//

	JSONValue::JSONValue()
		: m_detail(std::make_shared<detail::JSONValueDetail>())
	{

	}

	JSONValue::JSONValue(const detail::JSONValueDetail& value)
		: m_detail(std::make_shared<detail::JSONValueDetail>(value.value))
	{

	}

	JSONValue JSONValue::operator [](const String& path) const
	{
		if (isEmpty())
		{
			return JSONValue();
		}

		auto value = m_detail->value;

		for (const auto& p : path.split(U'.'))
		{
			if (!value->HasMember(p.c_str()))
			{
				return JSONValue();
			}

			value = Optional<const rapidjson::GenericValue<rapidjson::UTF32<char32>>&>((*value)[p.c_str()]);
		}

		return JSONValue(detail::JSONValueDetail(value));

		/*
		if (isEmpty() || !m_detail->value->HasMember(path.c_str()))
		{
			return JSONValue();
		}

		return JSONValue(detail::JSONValueDetail((*m_detail->value)[path.c_str()]));
		*/
	}

	bool JSONValue::isEmpty() const
	{
		return !m_detail->value.has_value();
	}

	JSONValueType JSONValue::getType() const
	{
		if (isEmpty())
		{
			return JSONValueType::Empty;
		}

		switch (m_detail->value->GetType())
		{
		case rapidjson::kNullType:
			return JSONValueType::Null;
		case rapidjson::kFalseType:
		case rapidjson::kTrueType:
			return JSONValueType::Bool;
		case rapidjson::kObjectType:
			return JSONValueType::Object;
		case rapidjson::kArrayType:
			return JSONValueType::Array;
		case rapidjson::kStringType:
			return JSONValueType::String;
		default:
			return JSONValueType::Number;
		}
	}

	size_t JSONValue::memberCount() const
	{
		if (!isObject())
		{
			return 0;
		}

		return m_detail->value->MemberCount();
	}

	bool JSONValue::hasMember(const String& name) const
	{
		if (!isObject())
		{
			return false;
		}

		return m_detail->value->HasMember(name.c_str());
	}

	JSONObjectView JSONValue::objectView() const
	{
		if (!isObject())
		{
			return JSONObjectView();
		}

		return JSONObjectView(
			JSONObjectIterator(detail::JSONMemberIteratorDetail(m_detail->value->MemberBegin())),
			JSONObjectIterator(detail::JSONMemberIteratorDetail(m_detail->value->MemberEnd())));
	}

	////////////////////////////////
	//
	//	Array
	//

	size_t JSONValue::arrayCount() const
	{
		if (!isArray())
		{
			return 0;
		}

		return m_detail->value->End() - m_detail->value->Begin();
	}

	JSONArrayView JSONValue::arrayView() const
	{
		if (!isArray())
		{
			return JSONArrayView();
		}

		return JSONArrayView(
			JSONArrayIterator(detail::JSONArrayIteratorDetail(m_detail->value->Begin())),
			JSONArrayIterator(detail::JSONArrayIteratorDetail(m_detail->value->End())));
	}

	////////////////////////////////
	//
	//	String
	//

	String JSONValue::getString() const
	{
		if (!isString())
		{
			return String();
		}

		return String(m_detail->value->GetString(), m_detail->value->GetStringLength());
	}

	template <>
	Optional<String> JSONValue::getOpt<String>() const
	{
		if (!isString())
		{
			return none;
		}

		return Optional<String>(in_place, m_detail->value->GetString(), m_detail->value->GetStringLength());
	}

	template Optional<String> JSONValue::getOpt<String>() const;

	////////////////////////////////
	//
	//	Number
	//

	template <>
	Optional<int32> JSONValue::getOpt<int32>() const
	{
		if (isEmpty() || !m_detail->value->IsInt())
		{
			return none;
		}

		return m_detail->value->GetInt();
	}

	template <>
	Optional<uint32> JSONValue::getOpt<uint32>() const
	{
		if (isEmpty() || !m_detail->value->IsUint())
		{
			return none;
		}

		return m_detail->value->GetUint();
	}

	template <>
	Optional<int64> JSONValue::getOpt<int64>() const
	{
		if (isEmpty() || !m_detail->value->IsInt64())
		{
			return none;
		}

		return m_detail->value->GetInt64();
	}

	template <>
	Optional<uint64> JSONValue::getOpt<uint64>() const
	{
		if (isEmpty() || !m_detail->value->IsUint64())
		{
			return none;
		}

		return m_detail->value->GetUint64();
	}

	template <>
	Optional<float> JSONValue::getOpt<float>() const
	{
		if (isEmpty() || !m_detail->value->IsFloat())
		{
			return none;
		}

		return m_detail->value->GetFloat();
	}

	template <>
	Optional<double> JSONValue::getOpt<double>() const
	{
		if (isEmpty() || !m_detail->value->IsDouble())
		{
			return none;
		}

		return m_detail->value->GetDouble();
	}

	template Optional<int32> JSONValue::getOpt<int32>() const;
	template Optional<uint32> JSONValue::getOpt<uint32>() const;
	template Optional<int64> JSONValue::getOpt<int64>() const;
	template Optional<uint64> JSONValue::getOpt<uint64>() const;
	template Optional<float> JSONValue::getOpt<float>() const;
	template Optional<double> JSONValue::getOpt<double>() const;

	////////////////////////////////
	//
	//	Bool
	//

	template <>
	Optional<bool> JSONValue::getOpt<bool>() const
	{
		if (!isBool())
		{
			return none;
		}

		return m_detail->value->IsTrue();
	}

	template Optional<bool> JSONValue::getOpt<bool>() const;

	////////////////////////////////
	//
	//	JSONReader
	//

	JSONReader::JSONReader()
		: m_document(std::make_shared<detail::JSONDocumentDetail>())
	{

	}

	bool JSONReader::open(const FilePath& path)
	{
		if (isOpend())
		{
			close();
		}

		const String text = TextReader(path).readAll();

		rapidjson::GenericStringStream<rapidjson::UTF32<char32>> m_stream(text.c_str());

		constexpr uint32 flags = rapidjson::kParseCommentsFlag
			| rapidjson::kParseTrailingCommasFlag
			| rapidjson::kParseNanAndInfFlag;

		m_document->document.ParseStream<flags>(m_stream);

		if (m_document->document.HasParseError())
		{
			return false;
		}

		m_detail->value.emplace(m_document->document);

		return true;
	}

	bool JSONReader::open(const std::shared_ptr<IReader>& reader)
	{
		if (isOpend())
		{
			close();
		}

		const String text = TextReader(reader).readAll();

		rapidjson::GenericStringStream<rapidjson::UTF32<char32>> m_stream(text.c_str());

		constexpr uint32 flags = rapidjson::kParseCommentsFlag
			| rapidjson::kParseTrailingCommasFlag
			| rapidjson::kParseNanAndInfFlag;

		m_document->document.ParseStream<flags>(m_stream);

		if (m_document->document.HasParseError())
		{
			return false;
		}

		m_detail->value.emplace(m_document->document);

		return true;
	}

	void JSONReader::close()
	{
		m_detail->value.reset();

		m_document->document = rapidjson::GenericDocument<rapidjson::UTF32<char32>>{};
	}

	bool JSONReader::isOpend() const
	{
		return m_detail->value.has_value();
	}
}
