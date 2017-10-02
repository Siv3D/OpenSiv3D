﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Wave.hpp>
# include <Siv3D/AudioFormat.hpp>

namespace s3d
{
	class AudioFormat_MP3 : public IAudioFormat
	{
	public:

		AudioFormat format() const override;

		const Array<String>& possibleExtexsions() const override;

		bool isHeader(const uint8(&bytes)[16]) const override;

		Wave decode(IReader& reader) const override;

		//bool encode(const Image& image, IWriter& writer) const override;

		//bool save(const Image& image, const FilePath& path) const override;
	};
}

# endif
