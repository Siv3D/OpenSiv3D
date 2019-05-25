//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "PointVector.hpp"
# include "StringView.hpp"

namespace s3d
{
	//
	// https://note.mu/siv3d/n/n9498c21e25ba
	// https://emojipedia.org/google/android-7.1/
	//
	struct Emoji
	{
		static constexpr Size ImageSize = { 136, 128 };

		String codePoints;

		Emoji() = default;

		explicit Emoji(StringView emoji) noexcept
			: codePoints(emoji) {}

		[[nodiscard]] static Image CreateImage(StringView emoji);

		[[nodiscard]] static Image CreateSilhouetteImage(StringView emoji);
	};
}
