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

namespace s3d
{
	class OpusEncoder : public IAudioEncoder
	{
	public:

		static constexpr int32 DefaultBitrate = 128;

		[[nodiscard]]
		StringView name() const override;

		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		bool save(const Wave& wave, FilePathView path) const override;

		bool save(const Wave& wave, FilePathView path, int32 bitrate) const;

		bool encode(const Wave& wave, IWriter& writer) const override;

		bool encode(const Wave& wave, IWriter& writer, int32 bitrate) const;

		[[nodiscard]]
		Blob encode(const Wave& wave) const override;

		[[nodiscard]]
		Blob encode(const Wave& wave, int32 bitrate) const;
	};
}
