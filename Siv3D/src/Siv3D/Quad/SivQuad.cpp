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

# include <Siv3D/2DShapes.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	const Quad& Quad::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addQuad(FloatQuad{ p0, p1, p2, p3 }, color.toFloat4());

		return *this;
	}

	const Quad& Quad::draw(const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		SIV3D_ENGINE(Renderer2D)->addQuad(FloatQuad{ p0, p1, p2, p3 },
			{ color0.toFloat4(), color1.toFloat4(), color2.toFloat4(), color3.toFloat4() });

		return *this;
	}

	void Quad::_Formatter(FormatData& formatData, const Quad& value)
	{
		formatData.string.append(U"(("_sv);

		formatData.string.append(ToString(value.p0.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p0.y, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(value.p1.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p1.y, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(value.p2.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p2.y, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(value.p3.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p3.y, formatData.decimalPlaces.value));
		formatData.string.append(U"))"_sv);
	}
}
