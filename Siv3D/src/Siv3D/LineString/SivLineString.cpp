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

# include <Siv3D/LineString.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	const LineString& LineString::draw(const ColorF& color) const
	{
		return draw(1.0, color);
	}

	const LineString& LineString::draw(const double thickness, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addLineString(
			data(),
			size(),
			s3d::none,
			static_cast<float>(thickness),
			false,
			color.toFloat4(),
			IsClosed::No
		);

		return *this;
	}

	const LineString& LineString::draw(const double thickness, const Array<ColorF>& colors) const
	{
		if (size() != colors.size())
		{
			return *this;
		}

		SIV3D_ENGINE(Renderer2D)->addLineString(
			data(),
			colors.data(),
			size(),
			s3d::none,
			static_cast<float>(thickness),
			false,
			IsClosed::No
		);

		return *this;
	}

	const LineString& LineString::drawClosed(const ColorF& color) const
	{
		return drawClosed(1.0, color);
	}

	const LineString& LineString::drawClosed(const double thickness, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addLineString(
			data(),
			size(),
			s3d::none,
			static_cast<float>(thickness),
			false,
			color.toFloat4(),
			IsClosed::Yes
		);

		return *this;
	}
}
