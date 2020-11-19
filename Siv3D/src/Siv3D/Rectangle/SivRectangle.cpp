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
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addRect(FloatRect{ x, y, (x + w), (y + h) }, color.toFloat4());

		return *this;
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::draw(const ColorF(&colors)[4]) const
	{
		SIV3D_ENGINE(Renderer2D)->addRect(FloatRect{ x, y, (x + w), (y + h) },
			{ colors[0].toFloat4(), colors[1].toFloat4(), colors[2].toFloat4(), colors[3].toFloat4() });

		return *this;
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::draw(const Arg::top_<ColorF> topColor, const Arg::bottom_<ColorF> bottomColor) const
	{
		const Float4 color0 = topColor->toFloat4();
		const Float4 color1 = bottomColor->toFloat4();

		SIV3D_ENGINE(Renderer2D)->addRect(FloatRect{ x, y, (x + w), (y + h) },
			{ color0, color0, color1, color1 });

		return *this;
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::draw(const Arg::left_<ColorF> leftColor, const Arg::right_<ColorF> rightColor) const
	{
		const Float4 color0 = leftColor->toFloat4();
		const Float4 color1 = rightColor->toFloat4();

		SIV3D_ENGINE(Renderer2D)->addRect(FloatRect{ x, y, (x + w), (y + h) },
			{ color0, color1, color1, color0 });

		return *this;
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::drawFrame(const double thickness, const ColorF& color) const
	{
		return drawFrame((thickness * 0.5), (thickness * 0.5), color);
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::drawFrame(const double thickness, const ColorF& innerColor, const ColorF& outerColor) const
	{
		return drawFrame((thickness * 0.5), (thickness * 0.5), innerColor, outerColor);
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::drawFrame(const double innerThickness, const double outerThickness, const ColorF& color) const
	{
		const Float4 color0 = color.toFloat4();

		SIV3D_ENGINE(Renderer2D)->addRectFrame(
			FloatRect{ (x + innerThickness), (y + innerThickness), (x + w - innerThickness), (y + h - innerThickness) },
			static_cast<float>(innerThickness + outerThickness),
			color0, color0);

		return *this;
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::drawFrame(const double innerThickness, const double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const
	{
		SIV3D_ENGINE(Renderer2D)->addRectFrame(
			FloatRect{ (x + innerThickness), (y + innerThickness), (x + w - innerThickness), (y + h - innerThickness) },
			static_cast<float>(innerThickness + outerThickness),
			innerColor.toFloat4(), outerColor.toFloat4());

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
