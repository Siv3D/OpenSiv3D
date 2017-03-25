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

# include <Siv3D/TextWriter.hpp>
# include "CTextWriter.hpp"

namespace s3d
{
	TextWriter::TextWriter()
		: pImpl(std::make_shared<CTextWriter>())
	{

	}

	TextWriter::~TextWriter()
	{

	}

	bool TextWriter::open(const FilePath& path, const OpenMode openMode, const CharacterEncoding encoding)
	{
		return pImpl->open(path, openMode, encoding);
	}

	void TextWriter::close()
	{
		pImpl->close();
	}

	bool TextWriter::isOpened() const
	{
		return pImpl->isOpened();
	}

	void TextWriter::clear()
	{
		pImpl->clear();
	}

	void TextWriter::write(const StringView str)
	{
		pImpl->write(str);
	}

	void TextWriter::writeUTF8(const CStringView str)
	{
		pImpl->writeUTF8(str);
	}

	const FilePath& TextWriter::path() const
	{
		return pImpl->path();
	}
}
