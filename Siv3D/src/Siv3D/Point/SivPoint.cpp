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

# include <Siv3D/PointVector.hpp>
# include <Siv3D/FormatInt.hpp>

namespace s3d
{
	void Point::_Formatter(FormatData& formatData, const Point& value)
	{
		const size_t bufferSize = (detail::Int32Width * 2) + 4 + 1;
		char32 buf[bufferSize];
		char32* p = buf;

		*(p++) = U'(';
		detail::AppendInt32(&p, value.x);
		*(p++) = U',';
		*(p++) = U' ';
		detail::AppendInt32(&p, value.y);
		*(p++) = U')';

		formatData.string.append(buf, p - buf);
	}
}
