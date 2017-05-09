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
# include <Siv3D/Rectangle.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	RectF LineString::calculateBoundingRect() const noexcept
	{
		if (isEmpty())
		{
			return RectF(0);
		}

		const Vec2* it = data();
		const Vec2* itEnd = it + size();

		double left = it->x;
		double top = it->y;
		double right = left;
		double bottom = top;
		++it;
		
		while (it != itEnd)
		{
			if (it->x < left)
			{
				left = it->x;
			}
			else if (right < it->x)
			{
				right = it->x;
			}

			if (it->y < top)
			{
				top = it->y;
			}
			else if (bottom < it->y)
			{
				bottom = it->y;
			}

			++it;
		}

		return RectF(left, top, right - left, bottom - top);
	}

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
