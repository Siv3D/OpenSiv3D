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

# pragma once
# include "IAudioFormat.hpp"
# include <Siv3D/Array.hpp>
# include <Siv3D/AudioFormat.hpp>

namespace s3d
{
	class CAudioFormat : public ISiv3DAudioFormat
	{
	private:

		Array<std::unique_ptr<IAudioFormat>> m_audioFormats;

		Array<std::unique_ptr<IAudioFormat>>::const_iterator findFormat(AudioFormat format) const;

		Array<std::unique_ptr<IAudioFormat>>::const_iterator findFormat(const IReader& reader, const FilePath& pathHint) const;

	public:

		CAudioFormat();

		~CAudioFormat() override;

		bool init() override;

		AudioFormat getFormatFromReader(const IReader& reader, const FilePath& pathHint) const override;

		AudioFormat getFormatFromFilePath(const FilePath& path) const override;

		Wave load(const FilePath& path) const override;

		Wave decode(IReader&& reader, AudioFormat format) const override;
	};
}
