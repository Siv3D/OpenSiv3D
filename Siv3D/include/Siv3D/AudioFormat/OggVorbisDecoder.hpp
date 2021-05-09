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
# include <Siv3D/IAudioDecoder.hpp>

namespace s3d
{
	class OggVorbisDecoder : public IAudioDecoder
	{
	public:

		[[nodiscard]]
		StringView name() const override;

		[[nodiscard]]
		bool isHeader(const uint8(&bytes)[48]) const override;

		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		[[nodiscard]]
		AudioFormat audioFormat() const noexcept override;

		[[nodiscard]]
		Wave decode(FilePathView path) const override;

		[[nodiscard]]
		Wave decode(IReader& reader, FilePathView pathHint = {}) const override;
	};
}
