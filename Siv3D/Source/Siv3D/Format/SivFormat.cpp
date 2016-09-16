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
	static void AppendInt(wchar** p, const long value)
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

	void Formatter(FormatData& formatData, const Color& value)
	{
		const size_t bufferSize = 12 * 4 + 6;
		wchar buf[bufferSize];
		wchar* p = buf;

		*(p++) = L'(';
		AppendInt(&p, value.r);
		*(p++) = L',';
		AppendInt(&p, value.g);
		*(p++) = L',';
		AppendInt(&p, value.b);
		*(p++) = L',';
		AppendInt(&p, value.a);
		*(p++) = L')';

		formatData.string.append(buf, p - buf);
	}

	//void Formatter(FormatData& formatData, const ColorF& value)
	//{
	//	Formatter(formatData, value.rgba());
	//}

	//void Formatter(FormatData& formatData, const HSV& value)
	//{
	//	Formatter(formatData, value.asVec3());
	//}

	void Formatter(FormatData& formatData, const Point& value)
	{
		const size_t bufferSize = 12 * 2 + 4;
		wchar buf[bufferSize];
		wchar* p = buf;

		*(p++) = L'(';
		AppendInt(&p, value.x);
		*(p++) = L',';
		AppendInt(&p, value.y);
		*(p++) = L')';

		formatData.string.append(buf, p - buf);
	}

	void Formatter(FormatData& formatData, const Float2& value)
	{
		Formatter(formatData, Vec2(value));
	}

	void Formatter(FormatData& formatData, const Vec2& value)
	{
		formatData.string.push_back(L'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlace.value));
		formatData.string.push_back(L',');
		formatData.string.append(ToString(value.y, formatData.decimalPlace.value));
		formatData.string.push_back(L')');
	}
}
