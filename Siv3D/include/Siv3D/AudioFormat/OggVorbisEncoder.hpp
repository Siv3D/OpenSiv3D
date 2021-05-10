//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/IAudioEncoder.hpp>
# include <Siv3D/AudioLoopTiming.hpp>

namespace s3d
{
	class OggVorbisEncoder : public IAudioEncoder
	{
	public:

		static constexpr int32 DefaultQuality = 60;

		[[nodiscard]]
		StringView name() const override;

		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		bool save(const Wave& wave, FilePathView path) const override;

		bool save(const Wave& wave, FilePathView path, int32 quality, const AudioLoopTiming& loopTiming = {}) const;

		bool encode(const Wave& wave, IWriter& writer) const override;

		bool encode(const Wave& wave, IWriter& writer, int32 quality, const AudioLoopTiming& loopTiming = {}) const;

		[[nodiscard]]
		Blob encode(const Wave& wave) const override;

		[[nodiscard]]
		Blob encode(const Wave& wave, int32 quality, const AudioLoopTiming& loopTiming = {}) const;
	};
}
