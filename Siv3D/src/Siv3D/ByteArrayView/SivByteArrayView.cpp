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
# include <Siv3D/Format.hpp>

namespace s3d
{
	namespace detail
	{
		constexpr wchar_t ToHexU4(const uint8 value_0_15)
		{
			constexpr char s[16] = {
				'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
			};

			return s[value_0_15];
		}
	}

	String ByteArrayView::toHex() const
	{
		auto it = begin(), itEnd = end();

		String result;
		result.reserve(1 + size() * 3);

		result.push_back(U'{');

		bool isFirst = true;

		while (it != itEnd)
		{
			if (isFirst)
			{
				isFirst = false;
			}
			else
			{
				result.push_back(U',');
			}

			result.push_back(detail::ToHexU4(static_cast<uint8>(*it) >> 4));
			result.push_back(detail::ToHexU4(static_cast<uint8>(*it) & 0xF));

			++it;
		}

		result.push_back(U'}');

		return result;
	}
}
