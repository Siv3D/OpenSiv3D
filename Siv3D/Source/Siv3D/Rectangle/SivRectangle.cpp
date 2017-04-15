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
# include <Siv3D/FloatRect.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::draw(const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addRect(FloatRect(x, y, x + w, y + h), Float4(color.r, color.g, color.b, color.a));

		return *this;
	}

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

	template Rect;

	template RectF;
}
