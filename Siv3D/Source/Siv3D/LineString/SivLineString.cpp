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
# include <Siv3D/Spline.hpp>
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

	LineString LineString::catmullRom(const bool isClosed, const int32 interpolation) const
	{
		if (size() < 2)
		{
			return *this;
		}

		// [Siv3D ToDo] 最適化

		Array<Vec2> points;
		{
			points.reserve(size() + 2 + isClosed);

			if (isClosed)
			{
				points.push_back((*this)[size() - 1]);
			}
			else
			{
				points.push_back((*this)[0]);
			}

			for (const auto& point : *this)
			{
				points.push_back(point);
			}

			if (isClosed)
			{
				points.push_back((*this)[0]);
				points.push_back((*this)[1]);
			}
			else
			{
				points.push_back((*this)[size() - 1]);
			}
		}

		LineString splinePoints;
		{
			splinePoints.reserve((points.size() - 3)*interpolation + 1);

			for (size_t i = 1; i < points.size() - 2; ++i)
			{
				const bool isLast = (i + 1) == points.size() - 2;

				for (int32 t = 0; t < (interpolation + isLast); ++t)
				{
					const Vec2 p = Spline::CatmullRom(points[i - 1], points[i], points[i + 1], points[i + 2], t / static_cast<double>(interpolation));

					splinePoints.push_back(p);
				}
			}
		}

		return splinePoints;
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

	void LineString::drawCatmullRom(const double thickness, const ColorF& color, const bool isClosed, const int32 interpolation) const
	{
		catmullRom(isClosed, interpolation).draw(thickness, color, false);
	}
}
