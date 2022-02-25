//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "String.hpp"
# include "BinaryReader.hpp"
# include "AudioFormat.hpp"
# include "Wave.hpp"

namespace s3d
{
	struct IAudioDecoder
	{
		virtual ~IAudioDecoder() = default;

		[[nodiscard]]
		virtual StringView name() const = 0;

		[[nodiscard]]
		virtual bool isHeader(const uint8(&bytes)[48]) const = 0;

		[[nodiscard]]
		virtual const Array<String>& possibleExtensions() const = 0;

		[[nodiscard]]
		virtual AudioFormat audioFormat() const noexcept = 0;

		[[nodiscard]]
		virtual Wave decode(FilePathView path) const;

		[[nodiscard]]
		virtual Wave decode(IReader& reader, FilePathView pathHint) const = 0;
	};
}

# include "detail/IAudioDecoder.ipp"
