//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/INIReader.hpp>
# include "CINIReader.hpp"

namespace s3d
{
	INIReader::INIReader()
		: pImpl(std::make_shared<CINIReader>())
	{

	}

	INIReader::~INIReader()
	{

	}

	bool INIReader::open(const FilePath& path, bool trackFile)
	{
		return pImpl->open(path, trackFile);
	}

	bool INIReader::open(const std::shared_ptr<IReader>& reader)
	{
		return pImpl->open(reader);
	}

	void INIReader::close()
	{
		pImpl->close();
	}

	bool INIReader::isOpened() const
	{
		return pImpl->isOpened();
	}

	const FilePath& INIReader::path() const
	{
		return pImpl->path();
	}

	CharacterEncoding INIReader::encoding() const
	{
		return pImpl->encoding();
	}

	const Array<std::pair<INIReader::Section, INIKey>>& INIReader::getData() const
	{
		return pImpl->getData();
	}
}
