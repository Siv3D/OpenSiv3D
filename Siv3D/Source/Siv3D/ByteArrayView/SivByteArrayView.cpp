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

# include <Siv3D/ByteArrayView.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Byte.hpp>

namespace s3d
{
	String ByteArrayView::toHex() const
	{
		auto it = begin(), itEnd = end();

		String result;
		result.reserve(1 + size() * 3);

		result.push_back(S3DCHAR('{'));

		bool isFirst = true;

		while (it != itEnd)
		{
			if (isFirst)
			{
				isFirst = false;
			}
			else
			{
				result.push_back(S3DCHAR(','));
			}

			result.push_back(detail::ToHexU4(static_cast<uint8>(*it) >> 4));
			result.push_back(detail::ToHexU4(static_cast<uint8>(*it) & 0xF));

			++it;
		}

		result.push_back(S3DCHAR('}'));

		return result;
	}
}
