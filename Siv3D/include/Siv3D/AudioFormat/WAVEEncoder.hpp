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
	class WAVEEncoder : public IAudioEncoder
	{
	public:

		StringView name() const override;

		const Array<String>& possibleExtensions() const override;

		bool save(const Wave& wave, FilePathView path) const override;

		bool encode(const Wave& wave, IWriter& writer) const override;

		Blob encode(const Wave& wave) const override;
	};
}
