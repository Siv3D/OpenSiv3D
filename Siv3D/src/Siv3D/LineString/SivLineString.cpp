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
# include <Siv3D/Spline.hpp>
# include <Siv3D/Spline2D.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		LineString CatmullRom(const LineString& lines, int32 interpolation, const CloseRing closeRing)
		{
			const size_t linesSize = lines.size();

			if ((linesSize < 2) || (interpolation < 2))
			{
				return lines;
			}

			// [Siv3D ToDo] 最適化

			Array<Vec2> points;
			{
				const Vec2* pSrc = lines.data();

				points.reserve(linesSize + (closeRing ? 3 : 2));

				if (closeRing)
				{
					points.push_back(pSrc[linesSize - 1]);
				}
				else
				{
					points.push_back(pSrc[0]);
				}

				points.insert(points.end(), lines.begin(), lines.end());

				if (closeRing)
				{
					points.push_back(pSrc[0]);
					points.push_back(pSrc[1]);
				}
				else
				{
					points.push_back(pSrc[linesSize - 1]);
				}
			}

			LineString splinePoints;
			{
				const Vec2* pSrc = points.data();

				splinePoints.reserve((points.size() - 3) * interpolation + 1);

				for (size_t i = 1; i < points.size() - 2; ++i)
				{
					const bool isLast = ((i + 1) == points.size() - 2);

					for (int32 t = 0; t < (interpolation + isLast); ++t)
					{
						const Vec2 p = Spline::CatmullRom(pSrc[i - 1], pSrc[i], pSrc[i + 1], pSrc[i + 2], t / static_cast<double>(interpolation));

						splinePoints.push_back(p);
					}
				}
			}

			return splinePoints;
		}
	}

	LineString LineString::catmullRom(const int32 interpolation) const
	{
		return detail::CatmullRom(*this, interpolation, CloseRing::No);
	}

	LineString LineString::catmullRomClosed(const int32 interpolation) const
	{
		return detail::CatmullRom(*this, interpolation, CloseRing::Yes);
	}

	double LineString::calculateLength() const noexcept
	{
		const size_t n = num_lines();
		const Vec2* pData = data();
		double length = 0.0;

		for (size_t i = 0; i < n; ++i)
		{
			length += (pData[i].distanceFrom(pData[i + 1]));
		}

		return length;
	}

	Vec2 LineString::calculatePointFromOrigin(const double distanceFromOrigin) const
	{
		if (isEmpty())
		{
			throw std::out_of_range("LineString::calculatePointFromOrigin() line is empty");
		}

		if (distanceFromOrigin <= 0.0)
		{
			return front();
		}

		const size_t n = num_lines();
		const Vec2* pData = data();
		double currentLength = 0.0;

		for (size_t i = 0; i < n; ++i)
		{
			const double length = (pData[i].distanceFrom(pData[i + 1]));

			if (distanceFromOrigin <= (currentLength + length))
			{
				return pData[i] + (pData[i + 1] - pData[i]).setLength(distanceFromOrigin - currentLength);
			}

			currentLength += length;
		}

		return back();
	}

	Spline2D LineString::asSpline(const CloseRing closeRing) const
	{
		return{ *this, closeRing };
	}

	const LineString& LineString::draw(const ColorF& color) const
	{
		return draw(1.0, color);
	}

	const LineString& LineString::draw(const double thickness, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addLineString(
			LineStyle::Default,
			data(),
			size(),
			s3d::none,
			static_cast<float>(thickness),
			false,
			color.toFloat4(),
			CloseRing::No
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
			CloseRing::No
		);

		return *this;
	}

	const LineString& LineString::draw(const LineStyle& style, const double thickness, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addLineString(
			style,
			data(),
			size(),
			s3d::none,
			static_cast<float>(thickness),
			false,
			color.toFloat4(),
			CloseRing::No
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
			LineStyle::Default,
			data(),
			size(),
			s3d::none,
			static_cast<float>(thickness),
			false,
			color.toFloat4(),
			CloseRing::Yes
		);

		return *this;
	}

	const LineString& LineString::drawClosed(const double thickness, const Array<ColorF>& colors) const
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
			CloseRing::Yes
		);

		return *this;
	}

	const LineString& LineString::drawClosed(const LineStyle& style, const double thickness, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addLineString(
			style,
			data(),
			size(),
			s3d::none,
			static_cast<float>(thickness),
			false,
			color.toFloat4(),
			CloseRing::Yes
		);

		return *this;
	}
}
