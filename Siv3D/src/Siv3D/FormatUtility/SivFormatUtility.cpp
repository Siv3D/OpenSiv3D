//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/FormatUtility.hpp>

namespace s3d
{
	namespace detail
	{
		const static String bytesUnits[9] =
		{
			U"B",
			U"KiB",
			U"MiB",
			U"GiB",
			U"TiB",
			U"PiB",
			U"EiB",
			U"ZiB",
			U"YiB"
		};
	}

	String FormatDataSize(const int64 bytes)
	{
		double s = static_cast<double>(bytes);

		for (uint32 i = 0; i < 9; ++i)
		{
			if (s < 10.0)
			{
				return ToString(s, 2) + detail::bytesUnits[i];
			}
			else if (s < 100.0)
			{
				return ToString(s, 1) + detail::bytesUnits[i];
			}
			else if (s < 1024.0)
			{
				return ToString(s, 0) + detail::bytesUnits[i];
			}

			s /= 1024.0;
		}

		return String();
	}
}
