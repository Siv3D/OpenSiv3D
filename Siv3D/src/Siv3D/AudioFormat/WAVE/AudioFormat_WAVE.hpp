//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Wave.hpp>
# include <Siv3D/AudioFormat.hpp>

namespace s3d
{
	class AudioFormat_WAVE : public IAudioFormat
	{
	public:

		AudioFormat format() const override;

		const Array<String>& possibleExtexsions() const override;

		bool isHeader(const uint8(&bytes)[16]) const override;

		Wave decodeFromFile(const FilePath& path) const override;

		Wave decode(IReader& reader) const override;

		bool encode(const Wave& wave, IWriter& writer, WAVEFormat format) const;
	};
}
