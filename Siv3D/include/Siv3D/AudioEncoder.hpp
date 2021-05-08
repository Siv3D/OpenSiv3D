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
# include "Common.hpp"
# include "Blob.hpp"
# include "AudioFormat.hpp"
# include "IAudioEncoder.hpp"

namespace s3d
{
	namespace AudioEncoder
	{
		bool Save(const Wave& wave, AudioFormat format, FilePathView path);

		bool Save(const Wave& wave, const String& encoderName, FilePathView path);

		bool Encode(const Wave& wave, const AudioFormat format, IWriter& writer);

		bool Encode(const Wave& wave, const String& encoderName, IWriter& writer);

		[[nodiscard]]
		Blob Encode(const Wave& wave, const AudioFormat format);

		[[nodiscard]]
		Blob Encode(const Wave& wave, const String& encoderName);

		bool Add(std::unique_ptr<IAudioEncoder>&& Encoder);

		void Remove(const StringView name);

		[[nodiscard]]
		const Array<std::unique_ptr<IAudioEncoder>>& Enum();
	}
}
