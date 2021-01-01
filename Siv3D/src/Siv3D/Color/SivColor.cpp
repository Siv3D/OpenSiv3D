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

# include <Siv3D/Color.hpp>
# include <Siv3D/FormatInt.hpp>

namespace s3d
{
	void Color::_Formatter(FormatData& formatData, const Color& value)
	{
		const size_t bufferSize = (detail::Uint32Width * 4) + 8 + 1;
		char32 buf[bufferSize];
		char32* p = buf;

		*(p++) = U'(';
		detail::AppendInt32(&p, value.r);
		*(p++) = U',';
		*(p++) = U' ';
		detail::AppendInt32(&p, value.g);
		*(p++) = U',';
		*(p++) = U' ';
		detail::AppendInt32(&p, value.b);
		*(p++) = U',';
		*(p++) = U' ';
		detail::AppendInt32(&p, value.a);
		*(p++) = U')';

		formatData.string.append(buf, p - buf);
	}
}

