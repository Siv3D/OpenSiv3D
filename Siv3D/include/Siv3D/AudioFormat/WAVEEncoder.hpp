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
# include <Siv3D/WAVEFormat.hpp>

namespace s3d
{
	class WAVEEncoder : public IAudioEncoder
	{
	public:

		[[nodiscard]]
		StringView name() const override;

		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		bool save(const Wave& wave, FilePathView path) const override;

		bool save(const Wave& wave, FilePathView path, WAVEFormat format) const;

		bool encode(const Wave& wave, IWriter& writer) const override;

		bool encode(const Wave& wave, IWriter& writer, WAVEFormat format) const;

		[[nodiscard]]
		Blob encode(const Wave& wave) const override;

		[[nodiscard]]
		Blob encode(const Wave& wave, WAVEFormat format) const;
	};
}
