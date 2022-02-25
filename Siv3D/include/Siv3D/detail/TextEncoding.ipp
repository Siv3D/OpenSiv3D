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

namespace s3d
{
	namespace Unicode
	{
		inline constexpr int32 GetBOMSize(const TextEncoding encoding) noexcept
		{
			if (encoding == TextEncoding::UTF8_WITH_BOM)
			{
				return 3;
			}
			else if (encoding == TextEncoding::UTF16LE
				|| encoding == TextEncoding::UTF16BE)
			{
				return 2;
			}
			else
			{
				return 0;
			}
		}
	}
}
