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

# include <ThirdParty/tinyxml/tinyxml2.h>
# include <Siv3D/XMLReader.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	struct XMLElement::XMLElementDetail
	{
		std::shared_ptr<tinyxml2::XMLDocument> document;

		const tinyxml2::XMLElement* element = nullptr;

		XMLElementDetail() = default;

		XMLElementDetail(const std::shared_ptr<tinyxml2::XMLDocument>& doc, const tinyxml2::XMLElement* elem);
	};

	XMLElement::XMLElementDetail::XMLElementDetail(const std::shared_ptr<tinyxml2::XMLDocument>& doc, const tinyxml2::XMLElement* elem)
		: document{ doc }
		, element{ elem } {}

	XMLElement::XMLElement()
		: m_detail{ std::make_unique<XMLElementDetail>() } {}

	XMLElement::XMLElement(const std::shared_ptr<tinyxml2::XMLDocument>& doc, const tinyxml2::XMLElement* element)
		: m_detail{ std::make_unique<XMLElementDetail>(doc, element) } {}

	XMLElement::XMLElement(XMLElement&& other)
		: m_detail{ std::move(other.m_detail) } {}

	XMLElement::~XMLElement() {}

	XMLElement& XMLElement::operator= (XMLElement&& other)
	{
		m_detail = std::move(other.m_detail);

		return *this;
	}

	bool XMLElement::isNull() const
	{
		return (not m_detail->element);
	}

	XMLElement::operator bool() const
	{
		return (not isNull());
	}

	String XMLElement::name() const
	{
		if (not m_detail->element)
		{
			return String();
		}

		return Unicode::FromUTF8(m_detail->element->Name());
	}

	String XMLElement::text() const
	{
		if (not m_detail->element)
		{
			return{};
		}

		if (const char* text = m_detail->element->GetText())
		{
			return Unicode::FromUTF8(text);
		}
		else
		{
			return{};
		}
	}

	XMLElement XMLElement::firstChild() const
	{
		if (not m_detail->element)
		{
			return{};
		}

		if (const auto element = m_detail->element->FirstChildElement())
		{
			return XMLElement{ m_detail->document, element };
		}
		else
		{
			return{};
		}
	}

	XMLElement XMLElement::nextSibling() const
	{
		if (not m_detail->element)
		{
			return{};
		}

		if (const auto element = m_detail->element->NextSiblingElement())
		{
			return XMLElement{ m_detail->document, element };
		}
		else
		{
			return{};
		}
	}

	XMLElement XMLElement::parent() const
	{
		if (not m_detail->element)
		{
			return{};
		}

		if (const auto element = m_detail->element->Parent()->ToElement())
		{
			return XMLElement{ m_detail->document, element };
		}
		else
		{
			return{};
		}
	}

	Array<std::pair<String, String>> XMLElement::attributes() const
	{
		Array<std::pair<String, String>> results;

		if (not m_detail->element)
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
		if (not m_detail->element)
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

	XMLReader::XMLReader(const char32* path, const PreserveWhitespace preserveWhitespace)
	{
		open(path, preserveWhitespace);
	}

	XMLReader::XMLReader(const FilePathView path, const PreserveWhitespace preserveWhitespace)
	{
		open(path, preserveWhitespace);
	}

	XMLReader::XMLReader(const FilePath& path, const PreserveWhitespace preserveWhitespace)
	{
		open(path, preserveWhitespace);
	}

	XMLReader::XMLReader(const Arg::code_<String> code, const PreserveWhitespace preserveWhitespace)
	{
		open(code, preserveWhitespace);
	}

	XMLReader::XMLReader(std::unique_ptr<IReader>&& reader, const PreserveWhitespace preserveWhitespace)
	{
		open(std::move(reader), preserveWhitespace);
	}

	bool XMLReader::open(const char32* path, const PreserveWhitespace preserveWhitespace)
	{
		return open(StringView{ path }, preserveWhitespace);
	}

	bool XMLReader::open(const FilePathView path, const PreserveWhitespace preserveWhitespace)
	{
		close();

		std::shared_ptr<tinyxml2::XMLDocument> document = std::make_shared<tinyxml2::XMLDocument>(true,
			preserveWhitespace ? tinyxml2::PRESERVE_WHITESPACE : tinyxml2::COLLAPSE_WHITESPACE);

		if (document->LoadFile(Unicode::Narrow(path).c_str()) != tinyxml2::XML_SUCCESS)
		{
			return false;
		}

		const auto root = document->FirstChildElement();

		if (not root)
		{
			return false;
		}

		m_detail = std::make_unique<XMLElementDetail>(document, root);

		return true;
	}

	bool XMLReader::open(const FilePath& path, const PreserveWhitespace preserveWhitespace)
	{
		return open(StringView{ path }, preserveWhitespace);
	}

	bool XMLReader::open(Arg::code_<String> code, const PreserveWhitespace preserveWhitespace)
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

		if (not root)
		{
			return false;
		}

		m_detail = std::make_unique<XMLElementDetail>(document, root);

		return true;
	}

	bool XMLReader::open(std::unique_ptr<IReader>&& reader, const PreserveWhitespace preserveWhitespace)
	{
		return open(Arg::code = TextReader{ std::move(reader) }.readAll(), preserveWhitespace);
	}

	void XMLReader::close()
	{
		m_detail.reset();
	}

	bool XMLReader::isOpen() const
	{
		return !!m_detail;
	}

	XMLReader::operator bool() const
	{
		return isOpen();
	}
}
