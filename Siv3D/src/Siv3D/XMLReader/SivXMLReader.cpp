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

# include <Siv3D/XMLReader.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/TextReader.hpp>
# include "../../ThirdParty/tinyxml/tinyxml2.h"

namespace s3d
{
	XMLElementDetail::XMLElementDetail(const std::shared_ptr<tinyxml2::XMLDocument>& doc, const tinyxml2::XMLElement* elem)
		: document(doc)
		, element(elem)
	{
	
	}

	XMLElement::XMLElement()
		: m_detail(std::make_unique<XMLElementDetail>())
	{

	}

	XMLElement::XMLElement(const std::shared_ptr<tinyxml2::XMLDocument>& doc, const tinyxml2::XMLElement* element)
		: m_detail(std::make_unique<XMLElementDetail>(doc, element))
	{

	}

	bool XMLElement::isNull() const
	{
		return !m_detail->element;
	}

	String XMLElement::name() const
	{
		if (!m_detail->element)
		{
			return String();
		}

		return Unicode::FromUTF8(m_detail->element->Name());
	}

	String XMLElement::text() const
	{
		if (!m_detail->element)
		{
			return String();
		}

		if (const char* text = m_detail->element->GetText())
		{
			return Unicode::FromUTF8(text);
		}
		else
		{
			return String();
		}
	}

	XMLElement XMLElement::firstChild() const
	{
		if (!m_detail->element)
		{
			return XMLElement();
		}

		if (const auto element = m_detail->element->FirstChildElement())
		{
			return XMLElement(m_detail->document, element);
		}
		else
		{
			return XMLElement();
		}
	}

	XMLElement XMLElement::nextSibling() const
	{
		if (!m_detail->element)
		{
			return XMLElement();
		}

		if (const auto element = m_detail->element->NextSiblingElement())
		{
			return XMLElement(m_detail->document, element);
		}
		else
		{
			return XMLElement();
		}
	}

	XMLElement XMLElement::parent() const
	{
		if (!m_detail->element)
		{
			return XMLElement();
		}

		if (const auto element = m_detail->element->Parent()->ToElement())
		{
			return XMLElement(m_detail->document, element);
		}
		else
		{
			return XMLElement();
		}
	}

	Array<std::pair<String, String>> XMLElement::attributes() const
	{
		Array<std::pair<String, String>> results;

		if (!m_detail->element)
		{
			return results;
		}

		for (auto attribute = m_detail->element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			results.emplace_back(Unicode::FromUTF8(attribute->Name()), Unicode::FromUTF8(attribute->Value()));
		}

		return results;
	}

	Optional<String> XMLElement::attribute(const String& name) const
	{
		if (!m_detail->element)
		{
			return none;
		}

		if (const char* attribute = m_detail->element->Attribute(name.narrow().c_str()))
		{
			return Unicode::FromUTF8(attribute);
		}
		else
		{
			return none;
		}
	}

	XMLReader::XMLReader(const FilePath& path, const bool preserveWhitespace)
	{
		open(path, preserveWhitespace);
	}

	XMLReader::XMLReader(Arg::code_<String> code, const bool preserveWhitespace)
	{
		open(code, preserveWhitespace);
	}

	XMLReader::XMLReader(const std::shared_ptr<IReader>& reader, const bool preserveWhitespace)
	{
		open(reader, preserveWhitespace);
	}

	bool XMLReader::open(const FilePath& path, const bool preserveWhitespace)
	{
		close();

		std::shared_ptr<tinyxml2::XMLDocument> document = std::make_shared<tinyxml2::XMLDocument>(true,
			preserveWhitespace ? tinyxml2::PRESERVE_WHITESPACE : tinyxml2::COLLAPSE_WHITESPACE);

		if (document->LoadFile(path.narrow().c_str()) != tinyxml2::XML_SUCCESS)
		{
			return false;
		}

		const auto root = document->FirstChildElement();

		if (!root)
		{
			return false;
		}

		m_detail = std::make_unique<XMLElementDetail>(document, root);

		return true;
	}

	bool XMLReader::open(Arg::code_<String> code, const bool preserveWhitespace)
	{
		close();

		std::shared_ptr<tinyxml2::XMLDocument> document = std::make_shared<tinyxml2::XMLDocument>(true,
			preserveWhitespace ? tinyxml2::PRESERVE_WHITESPACE : tinyxml2::COLLAPSE_WHITESPACE);

		const std::string text = code->toUTF8();

		if (document->Parse(text.c_str(), text.size()) != tinyxml2::XML_SUCCESS)
		{
			return false;
		}

		const auto root = document->FirstChildElement();

		if (!root)
		{
			return false;
		}

		m_detail = std::make_unique<XMLElementDetail>(document, root);

		return true;
	}

	bool XMLReader::open(const std::shared_ptr<IReader>& reader, const bool preserveWhitespace)
	{
		return open(Arg::code = TextReader(reader).readAll(), preserveWhitespace);
	}

	void XMLReader::close()
	{
		m_detail.reset();
	}

	bool XMLReader::isOpend() const
	{
		return !!m_detail;
	}
}
