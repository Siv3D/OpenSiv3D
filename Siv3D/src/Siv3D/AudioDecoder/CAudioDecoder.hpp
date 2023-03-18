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
# include <memory>
# include "IAudioDecoder.hpp"
# include <Siv3D/IAudioDecoder.hpp>
# include <Siv3D/Array.hpp>

namespace s3d
{
	class CAudioDecoder final : public ISiv3DAudioDecoder
	{
	public:

		CAudioDecoder() = default;

		~CAudioDecoder() override;

		void init() override;

		AudioFormat getAudioFormat(IReader& reader) override;

		Wave decode(IReader& reader, FilePathView pathHint, AudioFormat audioFormat) override;

		Wave decode(IReader& reader, StringView decoderName) override;

		bool add(std::unique_ptr<IAudioDecoder>&& decoder) override;

		void remove(StringView name) override;

		const Array<std::unique_ptr<IAudioDecoder>>& enumDecoder() const noexcept override;

	private:

		Array<std::unique_ptr<IAudioDecoder>> m_decoders;

		Array<std::unique_ptr<IAudioDecoder>>::const_iterator findDecoder(AudioFormat imageFormat) const;

		Array<std::unique_ptr<IAudioDecoder>>::const_iterator findDecoder(const IReader& reader, FilePathView pathHint) const;

		Array<std::unique_ptr<IAudioDecoder>>::const_iterator findDecoder(StringView encoderName) const;
	};
}
