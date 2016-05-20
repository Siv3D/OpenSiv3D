//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
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

	bool TextWriter::open(const FilePath& path, const OpenMode openMode, const TextEncoding encoding, const bool writeBOM)
	{
		return pImpl->open(path, openMode, encoding, writeBOM);
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
