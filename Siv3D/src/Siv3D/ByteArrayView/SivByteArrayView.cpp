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

# include <Siv3D/ByteArrayView.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Byte.hpp>
# include <Siv3D/Format.hpp>

namespace s3d
{
	namespace detail
	{
		constexpr char ToHexU4(const uint8 value_0_15, const bool upperCase)
		{
			constexpr char s[2][16] = {
				{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' },
				{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' }
			};

			return s[upperCase][value_0_15];
		}
	}

	ByteArrayView::size_type ByteArrayView::copyTo(void* const dst, const size_type size, const size_type pos) const
	{
		if (pos > m_size)
		{
			throw std::out_of_range("ByteArrayView::copy()");
		}

		const size_type len = std::min(size, m_size - pos);

		const Byte * src = m_data + pos;

		std::memcpy(dst, src, len);

		return len;
	}

	String ByteArrayView::toHex(const LetterCase letterCase, const String& sep, const String& begin, const String& end) const
	{
		const bool upperCase = (letterCase == LetterCase::Upper);
		auto it = this->begin(), itEnd = this->end();

		String result;
		result.reserve(1 + size() * 3);

		result.append(begin);

		bool isFirst = true;

		while (it != itEnd)
		{
			if (isFirst)
			{
				isFirst = false;
			}
			else
			{
				result.append(sep);
			}

			result.push_back(detail::ToHexU4(static_cast<uint8>(*it) >> 4, upperCase));
			result.push_back(detail::ToHexU4(static_cast<uint8>(*it) & 0xF, upperCase));

			++it;
		}

		result.append(end);

		return result;
	}
}
