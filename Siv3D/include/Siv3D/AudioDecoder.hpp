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
# include "Wave.hpp"
# include "IAudioDecoder.hpp"

namespace s3d
{
	namespace AudioDecoder
	{
		[[nodiscard]]
		Wave Decode(FilePathView path, AudioFormat audioFormat);

		[[nodiscard]]
		Wave Decode(IReader& reader, AudioFormat audioFormat);

		bool Add(std::unique_ptr<IAudioDecoder>&& decoder);

		void Remove(StringView name);

		[[nodiscard]]
		const Array<std::unique_ptr<IAudioDecoder>>& Enum();
	}
}
