//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/ColorHSV.hpp>
# include <Siv3D/FormatInt.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		inline double RemoveSRGBCurve(double x)
		{
			return ((x < 0.04045) ? (x / 12.92) : std::pow((x + 0.055) / 1.055, 2.4));
		}

		[[nodiscard]]
		inline double ApplySRGBCurve(double x)
		{
			return ((x < 0.0031308) ? (12.92 * x) : (1.055 * std::pow(x, (1.0 / 2.4)) - 0.055));
		}
	}

	void Formatter(FormatData& formatData, const Color& value)
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

	ColorF ColorF::removeSRGBCurve() const noexcept
	{
		return{
			detail::RemoveSRGBCurve(r),
			detail::RemoveSRGBCurve(g),
			detail::RemoveSRGBCurve(b),
			a
		};
	}

	ColorF ColorF::applySRGBCurve() const noexcept
	{
		return{
			detail::ApplySRGBCurve(r),
			detail::ApplySRGBCurve(g),
			detail::ApplySRGBCurve(b),
			a
		};
	}

	void Formatter(FormatData& formatData, const ColorF& value)
	{
		Formatter(formatData, value.toVec4());
	}
}
