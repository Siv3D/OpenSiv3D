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

# include <Siv3D/LineString.hpp>
# include <Siv3D/Optional.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	const LineString& LineString::draw(const ColorF& color, const bool isClosed) const
	{
		return draw(1.0, color, isClosed);
	}

	const LineString& LineString::draw(double thickness, const ColorF& color, const bool isClosed) const
	{
		if (size() < 2)
		{
			return *this;
		}

		Siv3DEngine::GetRenderer2D()->addLineString(
			data(),
			static_cast<uint32>(size()),
			s3d::none,
			static_cast<float>(thickness),
			false,
			Float4(color.r, color.g, color.b, color.a),
			isClosed
		);

		return *this;
	}
}
