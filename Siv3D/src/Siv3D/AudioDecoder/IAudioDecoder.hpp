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

# pragma once
# include <Siv3D/Common.hpp>
//# include <Siv3D/AudioInfo.hpp>
# include <Siv3D/AudioFormat.hpp>
# include <Siv3D/Wave.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/Grid.hpp>
# include <Siv3D/IAudioDecoder.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DAudioDecoder
	{
	public:

		static ISiv3DAudioDecoder* Create();

		virtual ~ISiv3DAudioDecoder() = default;

		virtual void init() = 0;

		virtual AudioFormat getAudioFormat(IReader& reader) = 0;

		//virtual Optional<AudioInfo> getAudioInfo(IReader& reader, FilePathView pathHint, AudioFormat imageFormat) = 0;

		virtual Wave decode(IReader& reader, FilePathView pathHint, AudioFormat audioFormat) = 0;

		virtual Wave decode(IReader& reader, StringView decoderName) = 0;

		virtual bool add(std::unique_ptr<IAudioDecoder>&& decoder) = 0;

		virtual void remove(StringView name) = 0;

		virtual const Array<std::unique_ptr<IAudioDecoder>>& enumDecoder() const noexcept = 0;
	};
}
