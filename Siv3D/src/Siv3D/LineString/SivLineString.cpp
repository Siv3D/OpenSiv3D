//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/LineString.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/Spline.hpp>
# include <Siv3D/Spline2D.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Interpolation.hpp>
# include <Siv3D/Formatter.hpp>
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

	LineString::value_type& LineString::choice()
	{
		return choice(GetDefaultRNG());
	}

	const LineString::value_type& LineString::choice() const
	{
		return choice(GetDefaultRNG());
	}

	size_t LineString::count(const value_type& value) const
	{
		return m_data.count(value);
	}

	LineString& LineString::fill(const value_type& value)
	{
		m_data.fill(value);

		return *this;
	}

	String LineString::join(const StringView sep, const StringView begin, const StringView end) const
	{
		return m_data.join(sep, begin, end);
	}

	LineString& LineString::append(const Array<value_type>& other)
	{
		m_data.insert(end(), other.begin(), other.end());

		return *this;
	}

	LineString& LineString::append(const LineString& other)
	{
		m_data.insert(end(), other.begin(), other.end());

		return *this;
	}

	LineString& LineString::remove(const value_type& value)
	{
		m_data.remove(value);

		return *this;
	}

	LineString& LineString::remove_at(const size_t index)
	{
		m_data.remove_at(index);

		return *this;
	}

	LineString& LineString::reverse()
	{
		m_data.reverse();

		return *this;
	}

	LineString LineString::reversed() const
	{
		return LineString(rbegin(), rend());
	}

	LineString& LineString::shuffle()
	{
		m_data.shuffle();

		return *this;
	}

	LineString LineString::slice(const size_t index) const
	{
		if (index >= size())
		{
			return{};
		}

		return LineString(begin() + index, end());
	}

	LineString LineString::slice(const size_t index, const size_t length) const
	{
		if (index >= size())
		{
			return{};
		}

		return LineString(begin() + index, begin() + Min(index + length, size()));
	}

	LineString& LineString::unique_consecutive()
	{
		erase(std::unique(begin(), end()), end());

		return *this;
	}

	LineString LineString::uniqued_consecutive() const&
	{
		LineString result;

		std::unique_copy(begin(), end(), std::back_inserter(result));

		return result;
	}

	LineString LineString::uniqued_consecutive()&&
	{
		erase(std::unique(begin(), end()), end());

		shrink_to_fit();

		return std::move(*this);
	}

	Vec2 LineString::normalAtPoint(const size_t index, const CloseRing closeRing) const
	{
		if (size() < 2)
		{
			return{ Math::NaN, Math::NaN };
		}

		if (size() <= index)
		{
			throw std::out_of_range("LineString::normalAtPoint() index out of range");
		}

		const size_t n = size();
		const Vec2* pSrc = data();
		const Vec2 curr = pSrc[index];
		Vec2 prev, next;

		if (index == 0)
		{
			if (closeRing)
			{
				prev = pSrc[n - 2];
				next = pSrc[index + 1];
			}
			else
			{
				prev = pSrc[0];
				next = pSrc[index + 1];
			}
		}
		else if (index == (n - 1))
		{
			if (closeRing)
			{
				prev = pSrc[index - 1];
				next = pSrc[0];
			}
			else
			{
				prev = pSrc[index - 1];
				next = pSrc[(n - 1)];
			}
		}
		else
		{
			prev = pSrc[index - 1];
			next = pSrc[index + 1];
		}

		const double a0 = (curr - prev).getAngle();
		const double a1 = (next - curr).getAngle();
		return Circular{ 1, (Math::LerpAngle(a0, a1, 0.5) - Math::HalfPi) };
	}

	Vec2 LineString::normalAtLine(const size_t index, const CloseRing closeRing) const
	{
		if (size() < 2)
		{
			return{ Math::NaN, Math::NaN };
		}

		const bool hasCloseLine = static_cast<bool>(closeRing);

		if ((size() - 1 + hasCloseLine) <= index)
		{
			throw std::out_of_range("LineString::normalAtLine() index out of range");
		}

		const size_t num_lines = (size() - 1);
		const Vec2* pSrc = data();
		const Vec2 curr = pSrc[index];
		Vec2 next;

		if (closeRing)
		{
			if (index == num_lines)
			{
				next = pSrc[0];
			}
			else
			{
				next = pSrc[index + 1];
			}
		}
		else
		{
			next = pSrc[index + 1];
		}

		const Vec2 v = (next - curr).normalized();
		
		return{ v.y, -v.x };
	}

	LineString LineString::movedBy(const double x, const double y) const
	{
		LineString lines{ *this };

		lines.moveBy(x, y);

		return lines;
	}

	LineString LineString::movedBy(const Vec2 v) const
	{
		return movedBy(v.x, v.y);
	}

	LineString& LineString::moveBy(const double x, const double y) noexcept
	{
		for (auto& point : *this)
		{
			point.moveBy(x, y);
		}

		return *this;
	}

	LineString& LineString::moveBy(const Vec2 v) noexcept
	{
		return moveBy(v.x, v.y);
	}

	LineString LineString::scaled(const double s) const
	{
		LineString result{ *this };

		for (auto& point : result)
		{
			point *= s;
		}

		return result;
	}

	LineString LineString::scaled(const double sx, const double sy) const
	{
		return scaled(Vec2{ sx, sy });
	}

	LineString LineString::scaled(const Vec2 s) const
	{
		LineString result{ *this };

		for (auto& point : result)
		{
			point *= s;
		}

		return result;
	}

	LineString& LineString::scale(const double s)
	{
		for (auto& point : m_data)
		{
			point *= s;
		}

		return *this;
	}

	LineString& LineString::scale(const double sx, const double sy)
	{
		return scale(Vec2{ sx, sy });
	}

	LineString& LineString::scale(const Vec2 s)
	{
		for (auto& point : m_data)
		{
			point *= s;
		}

		return *this;
	}

	LineString LineString::scaledAt(const Vec2 pos, const double s) const
	{
		LineString result{ *this };

		for (auto& point : result)
		{
			point = (pos + (point - pos) * s);
		}

		return result;
	}

	LineString LineString::scaledAt(const Vec2 pos, const double sx, const double sy) const
	{
		return scaledAt(pos, Vec2{ sx, sy });
	}

	LineString LineString::scaledAt(const Vec2 pos, const Vec2 s) const
	{
		LineString result{ *this };

		for (auto& point : result)
		{
			point = (pos + (point - pos) * s);
		}

		return result;
	}

	LineString& LineString::scaleAt(const Vec2 pos, const double s)
	{
		for (auto& point : m_data)
		{
			point = (pos + (point - pos) * s);
		}

		return *this;
	}

	LineString& LineString::scaleAt(const Vec2 pos, const double sx, const double sy)
	{
		return scaleAt(pos, Vec2{ sx, sy });
	}

	LineString& LineString::scaleAt(const Vec2 pos, const Vec2 s)
	{
		for (auto& point : m_data)
		{
			point = (pos + (point - pos) * s);
		}

		return *this;
	}

	RectF LineString::computeBoundingRect() const noexcept
	{
		return Geometry2D::BoundingRect(*this);
	}

	LineString LineString::catmullRom(const int32 interpolation) const
	{
		return detail::CatmullRom(*this, interpolation, CloseRing::No);
	}

	LineString LineString::catmullRom(const CloseRing closeRing, const int32 interpolation) const
	{
		return detail::CatmullRom(*this, interpolation, closeRing);
	}

	double LineString::calculateLength(const CloseRing closeRing) const noexcept
	{
		const size_t n = num_lines();
		const Vec2* pData = data();
		double length = 0.0;

		for (size_t i = 0; i < n; ++i)
		{
			length += (pData[i].distanceFrom(pData[i + 1]));
		}

		if (closeRing)
		{
			length += (pData[n]).distanceFrom(pData[0]);
		}

		return length;
	}

	Vec2 LineString::calculatePointFromOrigin(const double distanceFromOrigin, const CloseRing closeRing) const
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

		if (closeRing)
		{
			const double length = (pData[n]).distanceFrom(pData[0]);

			if (distanceFromOrigin <= (currentLength + length))
			{
				return pData[n] + (pData[0] - pData[n]).setLength(distanceFromOrigin - currentLength);
			}

			return front();
		}
		else
		{
			return back();
		}
	}

	LineString LineString::extractLineString(double distanceFromOrigin, const CloseRing closeRing) const
	{
		if (size() < 2)
		{
			return{};
		}

		if (closeRing)
		{
			const size_t lineCount = (num_lines() + 1);

			Array<double> lineLengths(lineCount);
			{
				for (size_t i = 0; i < lineCount; ++i)
				{
					lineLengths[i] = line(i, closeRing).length();
				}
			}

			const double lineStringLength = lineLengths.sum();

			distanceFromOrigin = Math::Fmod(distanceFromOrigin, lineStringLength);

			if (distanceFromOrigin < 0.0)
			{
				distanceFromOrigin += lineStringLength;
			}

			const double distanceToTargetFromOrigin = (distanceFromOrigin + lineStringLength);

			LineString result;
			double accumulatedLength = 0.0;
			const Vec2* pSrc = data();

			for (size_t n = 0; n < (lineCount * 2); ++n)
			{
				const size_t i = (n % lineCount);
				const Vec2 pFrom = pSrc[i];
				const Vec2 pTo = pSrc[(i + 1) % lineCount];
				const double len = lineLengths[i];

				if (not result)
				{
					if (distanceFromOrigin <= (accumulatedLength + len))
					{
						const Vec2 start = (pFrom + (pTo - pFrom).withLength(distanceFromOrigin - accumulatedLength));
						result << start;

						if (distanceToTargetFromOrigin <= (accumulatedLength + len))
						{
							const Vec2 goal = (pFrom + (pTo - pFrom).withLength(distanceToTargetFromOrigin - accumulatedLength));
							result << goal;
							break;
						}

						if (result.back() != pTo)
						{
							result << pTo;
						}
					}
				}
				else
				{
					if (distanceToTargetFromOrigin <= (accumulatedLength + len))
					{
						const Vec2 goal = (pFrom + (pTo - pFrom).withLength(distanceToTargetFromOrigin - accumulatedLength));
						result << goal;
						break;
					}

					result << pTo;
				}

				accumulatedLength += len;
			}

			return result;
		}
		else
		{
			const size_t lineCount = num_lines();

			Array<double> lineLengths(lineCount);
			{
				for (size_t i = 0; i < lineCount; ++i)
				{
					lineLengths[i] = line(i).length();
				}
			}

			const double lineStringLength = lineLengths.sum();

			distanceFromOrigin = Clamp(distanceFromOrigin, 0.0, lineStringLength);

			LineString result;
			double accumulatedLength = 0.0;
			const Vec2* pSrc = data();

			for (size_t i = 0; i < lineCount; ++i)
			{
				const Vec2 pFrom = pSrc[i];
				const Vec2 pTo = pSrc[i + 1];
				const double len = lineLengths[i];

				if (not result)
				{
					if (distanceFromOrigin <= (accumulatedLength + len))
					{
						const Vec2 start = (pFrom + (pTo - pFrom).withLength(distanceFromOrigin - accumulatedLength));
						result << start;

						if (result.back() != pTo)
						{
							result << pTo;
						}
					}
				}
				else
				{
					result << pTo;
				}

				accumulatedLength += len;
			}

			return result;
		}
	}

	LineString LineString::extractLineString(double distanceFromOrigin, double length, const CloseRing closeRing) const
	{
		if (size() < 2)
		{
			return{};
		}

		if (closeRing)
		{
			const size_t lineCount = (num_lines() + 1);

			Array<double> lineLengths(lineCount);
			{
				for (size_t i = 0; i < lineCount; ++i)
				{
					lineLengths[i] = line(i, closeRing).length();
				}
			}

			const double lineStringLength = lineLengths.sum();

			double from, to;
			{
				if (length < 0.0)
				{
					from = (distanceFromOrigin + length);
					to = distanceFromOrigin;
				}
				else
				{
					from = distanceFromOrigin;
					to = (distanceFromOrigin + length);
				}
			}
			distanceFromOrigin = Math::Fmod(from, lineStringLength);
			
			if (distanceFromOrigin < 0.0)
			{
				distanceFromOrigin += lineStringLength;
			}

			double distanceToTargetFromOrigin = Math::Fmod(to, lineStringLength);

			if (distanceToTargetFromOrigin < 0.0)
			{
				distanceToTargetFromOrigin += lineStringLength;
			}

			if (distanceToTargetFromOrigin < distanceFromOrigin)
			{
				distanceToTargetFromOrigin += lineStringLength;
			}

			LineString result;
			double accumulatedLength = 0.0;
			const Vec2* pSrc = data();

			for (size_t n = 0; n < (lineCount * 2); ++n)
			{
				const size_t i = (n % lineCount);
				const Vec2 pFrom = pSrc[i];
				const Vec2 pTo = pSrc[(i + 1) % lineCount];
				const double len = lineLengths[i];
				
				if (not result)
				{
					if (distanceFromOrigin <= (accumulatedLength + len))
					{
						const Vec2 start = (pFrom + (pTo - pFrom).withLength(distanceFromOrigin - accumulatedLength));
						result << start;

						if (distanceToTargetFromOrigin <= (accumulatedLength + len))
						{
							const Vec2 goal = (pFrom + (pTo - pFrom).withLength(distanceToTargetFromOrigin - accumulatedLength));
							result << goal;
							break;
						}

						if (result.back() != pTo)
						{
							result << pTo;
						}
					}
				}
				else
				{
					if (distanceToTargetFromOrigin <= (accumulatedLength + len))
					{
						const Vec2 goal = (pFrom + (pTo - pFrom).withLength(distanceToTargetFromOrigin - accumulatedLength));
						result << goal;
						break;
					}

					result << pTo;
				}

				accumulatedLength += len;
			}

			return result;
		}
		else
		{
			const size_t lineCount = num_lines();

			Array<double> lineLengths(lineCount);
			{
				for (size_t i = 0; i < lineCount; ++i)
				{
					lineLengths[i] = line(i).length();
				}
			}

			const double lineStringLength = lineLengths.sum();
			
			double from, to;
			{
				if (length < 0.0)
				{
					from = (distanceFromOrigin + length);
					to = distanceFromOrigin;
				}
				else
				{
					from = distanceFromOrigin;
					to = (distanceFromOrigin + length);
				}
			}
			distanceFromOrigin = Clamp(from, 0.0, lineStringLength);
			const double distanceToTargetFromOrigin = Clamp(to, 0.0, lineStringLength);

			LineString result;
			double accumulatedLength = 0.0;
			const Vec2* pSrc = data();

			for (size_t i = 0; i < lineCount; ++i)
			{
				const Vec2 pFrom = pSrc[i];
				const Vec2 pTo = pSrc[i + 1];
				const double len = lineLengths[i];

				if (not result)
				{
					if (distanceFromOrigin <= (accumulatedLength + len))
					{
						const Vec2 start = (pFrom + (pTo - pFrom).withLength(distanceFromOrigin - accumulatedLength));
						result << start;

						if (distanceToTargetFromOrigin <= (accumulatedLength + len))
						{
							const Vec2 goal = (pFrom + (pTo - pFrom).withLength(distanceToTargetFromOrigin - accumulatedLength));
							result << goal;
							break;
						}

						if (result.back() != pTo)
						{
							result << pTo;
						}
					}
				}
				else
				{
					if (distanceToTargetFromOrigin <= (accumulatedLength + len))
					{
						const Vec2 goal = (pFrom + (pTo - pFrom).withLength(distanceToTargetFromOrigin - accumulatedLength));
						result << goal;
						break;
					}

					result << pTo;
				}

				accumulatedLength += len;
			}

			return result;
		}
	}

	Array<Vec2> LineString::computeNormals(const CloseRing closeRing) const
	{
		Array<Vec2> normals(size());

		const size_t n = size();
		const Vec2* pSrc = data();
		Vec2* pDst = normals.data();

		if (closeRing)
		{
			for (size_t i = 0; i < n; ++i)
			{
				const Vec2 prev = (i == 0) ? pSrc[n - 2] : pSrc[i - 1];
				const Vec2 curr = pSrc[i];
				const Vec2 next = (i == (n - 1)) ? pSrc[0] : pSrc[i + 1];
				const double a0 = (curr - prev).getAngle();
				const double a1 = (next - curr).getAngle();
				pDst[i] = Circular{ 1, (Math::LerpAngle(a0, a1, 0.5) - Math::HalfPi) };
			}
		}
		else
		{
			for (size_t i = 0; i < n; ++i)
			{
				const Vec2 prev = (i == 0) ? pSrc[0] : pSrc[i - 1];
				const Vec2 curr = pSrc[i];
				const Vec2 next = (i == (n - 1)) ? pSrc[i] : pSrc[i + 1];
				const double a0 = (curr - prev).getAngle();
				const double a1 = (next - curr).getAngle();
				pDst[i] = Circular{ 1, (Math::LerpAngle(a0, a1, 0.5) - Math::HalfPi) };
			}
		}

		return normals;
	}

	Spline2D LineString::asSpline(const CloseRing closeRing) const
	{
		return{ *this, closeRing };
	}

	const LineString& LineString::paint(Image& dst, const Color& color) const
	{
		return paint(dst, 1, color);
	}

	const LineString& LineString::paintClosed(Image& dst, const Color& color) const
	{
		return paintClosed(dst, 1, color);
	}

	const LineString& LineString::overwrite(Image& dst, const Color& color, const Antialiased antialiased) const
	{
		return overwrite(dst, 1, color, antialiased);
	}

	const LineString& LineString::overwriteClosed(Image& dst, const Color& color, const Antialiased antialiased) const
	{
		return overwriteClosed(dst, 1, color, antialiased);
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
		if (size() < 2)
		{
			return *this;
		}

		const bool isRing = (front() == back());

		SIV3D_ENGINE(Renderer2D)->addLineString(
			LineStyle::Default,
			data(),
			(size() - isRing),
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

		if (size() < 2)
		{
			return *this;
		}

		const bool isRing = (front() == back());

		SIV3D_ENGINE(Renderer2D)->addLineString(
			data(),
			colors.data(),
			(size() - isRing),
			s3d::none,
			static_cast<float>(thickness),
			false,
			CloseRing::Yes
		);

		return *this;
	}

	const LineString& LineString::drawClosed(const LineStyle& style, const double thickness, const ColorF& color) const
	{
		if (size() < 2)
		{
			return *this;
		}

		const bool isRing = (front() == back());

		SIV3D_ENGINE(Renderer2D)->addLineString(
			style,
			data(),
			(size() - isRing),
			s3d::none,
			static_cast<float>(thickness),
			false,
			color.toFloat4(),
			CloseRing::Yes
		);

		return *this;
	}

	void Formatter(FormatData& formatData, const LineString& value)
	{
		Formatter(formatData, value.begin(), value.end());
	}
}
