//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Format.hpp>
# include <Siv3D/Color.hpp>
# include <Siv3D/HSV.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	namespace detail
	{
		void AppendInt(wchar** p, const long value)
		{
			bool negative;
			unsigned long val;

			if (value < 0)
			{
				negative = true;
				val = -value;
			}
			else
			{
				negative = false;
				val = value;
			}

			wchar buffer[12];
			wchar* pos = &buffer[11];
			*pos = L'\0';

			do
			{
				*(--pos) = L'0' + static_cast<wchar>(val % 10);

				val = val / 10;

			} while (val != 0);

			if (negative)
			{
				*(--pos) = L'-';
			}

			const size_t length = &buffer[11] - pos;

			::memcpy(*p, pos, length * sizeof(wchar));

			*p += length;
		}
	}
}
