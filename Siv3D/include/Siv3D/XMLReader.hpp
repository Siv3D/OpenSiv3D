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
# include <memory>
# include "Common.hpp"
# include "PredefinedNamedParameter.hpp"
# include "PredefinedYesNo.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "IReader.hpp"
# include "Optional.hpp"

namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
}

namespace s3d
{
	class XMLElement
	{
	public:

		SIV3D_NODISCARD_CXX20
		XMLElement();

		SIV3D_NODISCARD_CXX20
		XMLElement(const std::shared_ptr<tinyxml2::XMLDocument>& doc, const tinyxml2::XMLElement* element);

		SIV3D_NODISCARD_CXX20
		XMLElement(XMLElement&& other);

		~XMLElement();

		XMLElement& operator =(XMLElement&& other);

		[[nodiscard]]
		bool isNull() const;

		[[nodiscard]]
		explicit operator bool() const;

		[[nodiscard]]
		String name() const;

		[[nodiscard]]
		String text() const;

		[[nodiscard]]
		XMLElement firstChild() const;

		[[nodiscard]]
		XMLElement nextSibling() const;

		[[nodiscard]]
		XMLElement parent() const;

		[[nodiscard]]
		Array<std::pair<String, String>> attributes() const;

		[[nodiscard]]
		Optional<String> attribute(const String& name) const;

	protected:

		struct XMLElementDetail;

		std::unique_ptr<XMLElementDetail> m_detail;
	};

	/// @brief XML の読み込み
	class XMLReader : public XMLElement
	{
	public:

		SIV3D_NODISCARD_CXX20
		XMLReader() = default;

		SIV3D_NODISCARD_CXX20
		explicit XMLReader(FilePathView path, PreserveWhitespace preserveWhitespace = PreserveWhitespace::No);

		SIV3D_NODISCARD_CXX20
		explicit XMLReader(Arg::code_<String> code, PreserveWhitespace preserveWhitespace = PreserveWhitespace::No);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		explicit XMLReader(Reader&& reader, PreserveWhitespace preserveWhitespace = PreserveWhitespace::No);

		SIV3D_NODISCARD_CXX20
		explicit XMLReader(std::unique_ptr<IReader>&& reader, PreserveWhitespace preserveWhitespace = PreserveWhitespace::No);

		bool open(FilePathView path, PreserveWhitespace preserveWhitespace = PreserveWhitespace::No);

		bool open(Arg::code_<String> code, PreserveWhitespace preserveWhitespace = PreserveWhitespace::No);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool open(Reader&& reader, PreserveWhitespace preserveWhitespace = PreserveWhitespace::No);

		bool open(std::unique_ptr<IReader>&& reader, PreserveWhitespace preserveWhitespace = PreserveWhitespace::No);

		void close();

		[[nodiscard]]
		bool isOpen() const;

		[[nodiscard]]
		explicit operator bool() const;
	};
}

# include "detail/XMLReader.ipp"
