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

# pragma once
# include <Siv3D/INIReader.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/CharacterEncoding.hpp>

namespace s3d
{
	class INIReader::CINIReader
	{
	private:

		Array<String> m_sections;

		Array<INIKey> m_keys;

		FilePath m_path;

		CharacterEncoding m_encoding = CharacterEncoding::Default;

		bool init(const FilePath& path);

	public:

		CINIReader();

		~CINIReader();

		bool open(const FilePath& path, bool trackFile);

		bool open(const std::shared_ptr<IReader>& reader);

		void close();

		bool isOpened() const;

		const FilePath& path() const;

		CharacterEncoding encoding() const;

		const Array<Section>& getSections() const;

		const Array<INIKey>& getKeys() const;
	};
}
