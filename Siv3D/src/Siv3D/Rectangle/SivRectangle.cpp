//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/2DShapes.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/FormatData.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->test_renderRectangle(*this, color);

		return *this;
	}

	template <>
	void Rect::_Formatter(FormatData& formatData, const Rect& value)
	{
		formatData.string.push_back(U'(');
		formatData.string.append(ToString(value.x));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.y));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.w));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.h));
		formatData.string.push_back(U')');
	}

	template <>
	void RectF::_Formatter(FormatData& formatData, const RectF& value)
	{
		formatData.string.push_back(U'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.w, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.h, formatData.decimalPlaces.value));
		formatData.string.push_back(U')');
	}

	template struct Rectangle<Point>;
	template struct Rectangle<Vec2>;
}
