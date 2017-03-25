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

# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Format.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const Rect& value)
	{
		const size_t bufferSize = 12 * 4 + 6;
		wchar buf[bufferSize];
		wchar* p = buf;

		*(p++) = L'(';
		detail::AppendInt(&p, value.x);
		*(p++) = L',';
		detail::AppendInt(&p, value.y);
		*(p++) = L',';
		detail::AppendInt(&p, value.w);
		*(p++) = L',';
		detail::AppendInt(&p, value.h);
		*(p++) = L')';

		formatData.string.append(buf, p - buf);
	}

	void Formatter(FormatData& formatData, const RectF& value)
	{
		Formatter(formatData, Vec4(value.x, value.y, value.w, value.h));
	}
}
