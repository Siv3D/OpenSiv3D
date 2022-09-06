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

# include <Siv3D/Polygon.hpp>
# include <Siv3D/Shape2D.hpp>
# include <Siv3D/FastMath.hpp>
# include <Siv3D/Buffer2D.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/HashSet.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Unicode.hpp>
# include "PolygonDetail.hpp"
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4267)
# include <ThirdParty/boost/geometry/extensions/algorithms/dissolve.hpp>
# include <ThirdParty/boost/geometry/extensions/multi/algorithms/dissolve.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static bool HasSamePoints(const Vec2* pVertex, const size_t vertexSize)
		{
			return (HashSet<Vec2>(pVertex, pVertex + vertexSize).size() != vertexSize);
		}

		[[nodiscard]]
		constexpr PolygonFailureType Convert(const boost::geometry::validity_failure_type failure) noexcept
		{
			// https://www.boost.org/doc/libs/1_72_0/libs/geometry/doc/html/geometry/reference/enumerations/validity_failure_type.html
			switch (failure)
			{
			case boost::geometry::no_failure:
				return PolygonFailureType::OK;
			case boost::geometry::failure_few_points:
				return PolygonFailureType::FewPoints;
			case boost::geometry::failure_wrong_topological_dimension:
				return PolygonFailureType::WrongTopologicalDimension;
			case boost::geometry::failure_spikes:
				return PolygonFailureType::Spikes;
			case boost::geometry::failure_duplicate_points:
				return PolygonFailureType::DuplicatePoints;
			case boost::geometry::failure_not_closed:
				return PolygonFailureType::NotClosed;
			case boost::geometry::failure_self_intersections:
				return PolygonFailureType::SelfIntersections;
			case boost::geometry::failure_wrong_orientation:
				return PolygonFailureType::WrongOrientation;
			case boost::geometry::failure_interior_rings_outside:
				return PolygonFailureType::InteriorRingsOutside;
			case boost::geometry::failure_nested_interior_rings:
				return PolygonFailureType::NestedInteriorRings;
			case boost::geometry::failure_disconnected_interior:
				return PolygonFailureType::DisconnectedInterior;
			case boost::geometry::failure_intersecting_interiors:
				return PolygonFailureType::IntersectingInteriors;
			case boost::geometry::failure_wrong_corner_order:
				return PolygonFailureType::WrongCornerOrder;
			case boost::geometry::failure_invalid_coordinate:
				return PolygonFailureType::InvalidCoordinate;
			default:
				return PolygonFailureType::Unknown;
			}
		}
	}

	Polygon::Polygon()
		: pImpl{ std::make_unique<PolygonDetail>() }
	{

	}

	Polygon::Polygon(const Polygon& polygon)
		: pImpl{ std::make_unique<PolygonDetail>(*polygon.pImpl) }
	{

	}

	Polygon::Polygon(Polygon&& polygon) noexcept
		: pImpl{ std::move(polygon.pImpl) }
	{
		polygon.pImpl = std::make_unique<PolygonDetail>();
	}

	Polygon::Polygon(const Vec2* outer, const size_t size, Array<Array<Vec2>> holes, const SkipValidation skipValidation)
		: pImpl{ std::make_unique<PolygonDetail>(outer, size, std::move(holes), skipValidation) }
	{

	}

	Polygon::Polygon(const Array<Vec2>& outer, Array<Array<Vec2>> holes, const SkipValidation skipValidation)
		: pImpl{ std::make_unique<PolygonDetail>(outer.data(), outer.size(), std::move(holes), skipValidation) }
	{

	}

	Polygon::Polygon(const Array<Vec2>& outer, const Array<TriangleIndex>& indices, const RectF& boundingRect, const SkipValidation skipValidation)
		: pImpl{ std::make_unique<PolygonDetail>(outer.data(), outer.size(), indices, boundingRect, skipValidation) }
	{

	}

	Polygon::Polygon(const Array<Vec2>& outer, Array<Array<Vec2>> holes, const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const RectF& boundingRect, const SkipValidation skipValidation)
		: pImpl{ std::make_unique<PolygonDetail>(outer, std::move(holes), vertices, indices, boundingRect, skipValidation) }
	{

	}

	Polygon::Polygon(std::initializer_list<Vec2> outer, const SkipValidation skipValidation)
		: pImpl{ std::make_unique<PolygonDetail>(outer.begin(), outer.size(), Array<Array<Vec2>>{}, skipValidation) }
	{

	}

	Polygon::Polygon(const Shape2D& shape)
		: pImpl(std::make_unique<PolygonDetail>(shape.vertices().data(), shape.vertices().size(), shape.indices()))
	{

	}

	Polygon::~Polygon()
	{

	}

	Polygon& Polygon::operator =(const Polygon& polygon)
	{
		*pImpl = *polygon.pImpl;
		
		return *this;
	}

	Polygon& Polygon::operator =(Polygon&& polygon) noexcept
	{
		pImpl = std::move(polygon.pImpl);

		return *this;
	}

	bool Polygon::isEmpty() const noexcept
	{
		return pImpl->outer().isEmpty();
	}

	Polygon::operator bool() const noexcept
	{
		return (not pImpl->outer().isEmpty());
	}

	bool Polygon::hasHoles() const noexcept
	{
		return (not pImpl->inners().isEmpty());
	}

	size_t Polygon::num_holes() const noexcept
	{
		return pImpl->inners().size();
	}

	void Polygon::swap(Polygon& polygon) noexcept
	{
		std::swap(pImpl, polygon.pImpl);
	}

	const Array<Vec2>& Polygon::outer() const noexcept
	{
		return pImpl->outer();
	}

	const Array<Array<Vec2>>& Polygon::inners() const noexcept
	{
		return pImpl->inners();
	}

	const Array<Float2>& Polygon::vertices() const noexcept
	{
		return pImpl->vertices();
	}

	const Array<TriangleIndex>& Polygon::indices() const noexcept
	{
		return pImpl->indices();
	}

	const RectF& Polygon::boundingRect() const noexcept
	{
		return pImpl->boundingRect();
	}

	size_t Polygon::num_triangles() const noexcept
	{
		return pImpl->indices().size();
	}

	Triangle Polygon::triangle(const size_t index) const
	{
		const auto& indices = pImpl->indices();

		if (index >= indices.size())
		{
			throw std::out_of_range("Polygon::triangle(): index out of range");
		}

		const auto& vertices = pImpl->vertices();
		const auto& triangleIndex = indices[index];
	
		return{ vertices[triangleIndex.i0], vertices[triangleIndex.i1], vertices[triangleIndex.i2] };
	}

	bool Polygon::addHole(const RectF& rect)
	{
		if (isEmpty())
		{
			return false;
		}

		Array<Array<Vec2>> inners(Arg::reserve = (pImpl->inners().size() + 1));
		{
			inners.append(pImpl->inners());
			inners.push_back(Array<Vec2>{ rect.tl(), rect.bl(), rect.br(), rect.tr() });
		}

		Polygon result{ pImpl->outer(), std::move(inners) };

		if (not result)
		{
			return false;
		}
		
		*this = std::move(result);

		return true;
	}

	bool Polygon::addHole(const Triangle& triangle)
	{
		if (isEmpty())
		{
			return false;
		}

		Array<Array<Vec2>> inners(Arg::reserve = (pImpl->inners().size() + 1));
		{
			inners.append(pImpl->inners());
			inners.push_back(Array<Vec2>{ triangle.p0, triangle.p2, triangle.p1 });
		}

		Polygon result{ pImpl->outer(), std::move(inners) };

		if (not result)
		{
			return false;
		}

		*this = std::move(result);

		return true;
	}

	bool Polygon::addHole(const Quad& quad)
	{
		if (isEmpty())
		{
			return false;
		}

		Array<Array<Vec2>> inners(Arg::reserve = (pImpl->inners().size() + 1));
		{
			inners.append(pImpl->inners());
			inners.push_back(Array<Vec2>{ quad.p0, quad.p3, quad.p2, quad.p1 });
		}

		Polygon result{ pImpl->outer(), std::move(inners) };

		if (not result)
		{
			return false;
		}

		*this = std::move(result);

		return true;
	}

	bool Polygon::addHole(const Circle& circle, const uint32 quality)
	{
		if (isEmpty())
		{
			return false;
		}

		const uint32 n = Max(quality, 3u);

		Array<Vec2> vertices(n, circle.center);
		{
			Vec2* pPos = vertices.data();

			const double d = (-Math::TwoPi / n);

			for (uint32 i = 0; i < n; ++i)
			{
				*pPos += Circular{ circle.r, (i * d) }.fastToVec2();
				++pPos;
			}
		}

		Array<Array<Vec2>> inners(Arg::reserve = (pImpl->inners().size() + 1));
		{
			inners.append(pImpl->inners());
			inners.push_back(std::move(vertices));
		}

		Polygon result{ pImpl->outer(), std::move(inners) };

		if (not result)
		{
			return false;
		}

		*this = std::move(result);

		return true;
	}

	bool Polygon::addHole(const Ellipse& ellipse, const uint32 quality)
	{
		if (isEmpty())
		{
			return false;
		}

		const uint32 n = Max(quality, 3u);

		Array<Vec2> vertices(n, ellipse.center);
		{
			Vec2* pPos = vertices.data();
			const double d = (-Math::TwoPi / n);

			for (uint32 i = 0; i < n; ++i)
			{
				const double rad = (i * d);
				const auto [s, c] = FastMath::SinCos(rad);
				pPos->moveBy(ellipse.a * c, ellipse.b * s);
				++pPos;
			}
		}

		Array<Array<Vec2>> inners(Arg::reserve = (pImpl->inners().size() + 1));
		{
			inners.append(pImpl->inners());
			inners.push_back(std::move(vertices));
		}

		Polygon result{ pImpl->outer(), std::move(inners) };

		if (not result)
		{
			return false;
		}

		*this = std::move(result);

		return true;
	}

	bool Polygon::addHole(const RoundRect& roundRect, const uint32 quality)
	{
		if (isEmpty())
		{
			return false;
		}

		Array<Array<Vec2>> inners(Arg::reserve = (pImpl->inners().size() + 1));
		{
			inners.append(pImpl->inners());
			Array<Vec2> hole = roundRect.outerVertices(quality);
			hole.reverse();
			inners.push_back(std::move(hole));
		}

		Polygon result{ pImpl->outer(), std::move(inners) };

		if (not result)
		{
			return false;
		}

		*this = std::move(result);

		return true;
	}

	bool Polygon::addHole(Array<Vec2> hole)
	{
		if (isEmpty())
		{
			return false;
		}

		if (hole.size() < 3)
		{
			return false;
		}

		if (Geometry2D::IsClockwise(hole))
		{
			hole.reverse();
		}

		Array<Array<Vec2>> inners(Arg::reserve = (pImpl->inners().size() + 1));
		{
			inners.append(pImpl->inners());
			inners.push_back(std::move(hole));
		}

		Polygon result{ pImpl->outer(), std::move(inners) };

		if (not result)
		{
			return false;
		}

		*this = std::move(result);

		return true;
	}

	bool Polygon::addHoles(Array<Array<Vec2>> holes)
	{
		if (isEmpty())
		{
			return false;
		}

		holes.remove_if([](const Array<Vec2>& hole) { return (hole.size() < 3); });

		if (not holes)
		{
			return false;
		}

		for (auto& hole : holes)
		{
			if (Geometry2D::IsClockwise(hole))
			{
				hole.reverse();
			}
		}

		Array<Array<Vec2>> inners(Arg::reserve = (pImpl->inners().size() + holes.size()));
		{
			inners.append(pImpl->inners());
			inners.append(holes);
		}

		Polygon result{ pImpl->outer(), std::move(inners) };

		if (not result)
		{
			return false;
		}

		*this = std::move(result);

		return true;
	}

	Polygon Polygon::movedBy(const double x, const double y) const
	{
		return movedBy(Vec2{ x, y });
	}

	Polygon Polygon::movedBy(const Vec2 v) const
	{
		Polygon result{ *this };

		result.moveBy(v);

		return result;
	}

	Polygon& Polygon::moveBy(const double x, const double y) noexcept
	{
		return moveBy(Vec2{ x, y });
	}

	Polygon& Polygon::moveBy(const Vec2 v) noexcept
	{
		pImpl->moveBy(v);

		return *this;
	}

	Polygon Polygon::rotated(const double angle) const
	{
		return rotatedAt(Vec2{ 0, 0 }, angle);
	}

	Polygon Polygon::rotatedAt(const double x, const double y, const double angle) const
	{
		return rotatedAt(Vec2{ x, y }, angle);
	}

	Polygon Polygon::rotatedAt(const Vec2 pos, const double angle) const
	{
		Polygon result{ *this };

		result.rotateAt(pos, angle);

		return result;
	}

	Polygon& Polygon::rotate(const double angle)
	{
		return rotateAt(Vec2{ 0, 0 }, angle);
	}

	Polygon& Polygon::rotateAt(const double x, const double y, const double angle)
	{
		return rotateAt(Vec2{ x, y }, angle);
	}

	Polygon& Polygon::rotateAt(const Vec2 pos, const double angle)
	{
		pImpl->rotateAt(pos, angle);

		return *this;
	}

	Polygon Polygon::transformed(const double s, const double c, const Vec2& pos) const
	{
		Polygon result{ *this };

		result.transform(s, c, pos);

		return result;
	}

	Polygon& Polygon::transform(const double s, const double c, const Vec2& pos)
	{
		pImpl->transform(s, c, pos);

		return *this;
	}

	Polygon Polygon::scaled(const double s) const
	{
		Polygon result{ *this };

		result.scale(s);

		return result;
	}

	Polygon Polygon::scaled(const double sx, double sy) const
	{
		return scaled(Vec2{ sx, sy });
	}

	Polygon Polygon::scaled(const Vec2 s) const
	{
		Polygon result{ *this };

		result.scale(s);

		return result;
	}

	Polygon& Polygon::scale(const double s)
	{
		pImpl->scale(s);

		return *this;
	}

	Polygon& Polygon::scale(const double sx, const double sy)
	{
		return scale(Vec2{ sx, sy });
	}

	Polygon& Polygon::scale(const Vec2 s)
	{
		pImpl->scale(s);

		return *this;
	}

	Polygon Polygon::scaledAt(const Vec2 pos, const double s) const
	{
		Polygon result{ *this };

		result.scaleAt(pos, s);

		return result;
	}

	Polygon& Polygon::scaleAt(const Vec2 pos, const double s)
	{
		pImpl->scaleAt(pos, s);

		return *this;
	}

	Polygon Polygon::scaledAt(const Vec2 pos, const double sx, const double sy) const
	{
		return scaledAt(pos, Vec2{ sx, sy });
	}

	Polygon Polygon::scaledAt(const Vec2 pos, const Vec2 s) const
	{
		Polygon result{ *this };

		result.scaleAt(pos, s);

		return result;
	}

	Polygon& Polygon::scaleAt(const Vec2 pos, const double sx, const double sy)
	{
		return scaleAt(pos, Vec2{ sx, sy });
	}

	Polygon& Polygon::scaleAt(const Vec2 pos, const Vec2 s)
	{
		pImpl->scaleAt(pos, s);

		return *this;
	}

	double Polygon::area() const noexcept
	{
		return pImpl->area();
	}

	double Polygon::perimeter() const noexcept
	{
		return pImpl->perimeter();
	}

	Vec2 Polygon::centroid() const
	{
		return pImpl->centroid();
	}

	Polygon Polygon::computeConvexHull() const
	{
		return pImpl->computeConvexHull();
	}

	Polygon Polygon::calculateBuffer(const double distance) const
	{
		if (distance == 0.0)
		{
			return *this;
		}

		return pImpl->calculateBuffer(distance);
	}

	Polygon Polygon::calculateRoundBuffer(const double distance) const
	{
		if (distance == 0.0)
		{
			return *this;
		}

		return pImpl->calculateRoundBuffer(distance);
	}

	Polygon Polygon::simplified(const double maxDistance) const
	{
		if (maxDistance <= 0.0)
		{
			return *this;
		}

		return pImpl->simplified(maxDistance);
	}

	LineString Polygon::outline(const CloseRing closeRing) const
	{
		const auto& out = outer();

		if (out.isEmpty())
		{
			return{};
		}

		if (closeRing)
		{
			LineString points;
			points.reserve(out.size() + 1);
			points.append(out);
			points.push_back(out.front());
			return points;
		}
		else
		{
			return LineString{ out };
		}
	}

	LineString Polygon::outline(double distanceFromOrigin, double length) const
	{
		if (length <= 0.0)
		{
			distanceFromOrigin += length;
			length = -length;
		}

		const auto& out = outer();
		const size_t N = out.size();
		Array<double> lens(N);
		{
			for (size_t i = 0; i < (N - 1); ++i)
			{
				lens[i] = out[i].distanceFrom(out[i + 1]);
			}

			lens[N - 1] = out[N - 1].distanceFrom(out[0]);
		}
		const double perim = lens.sum();

		distanceFromOrigin = Math::Fmod(distanceFromOrigin, perim) + (distanceFromOrigin < 0 ? perim : 0);
		length = Min(length, perim);
		const double distanceToTarget = (distanceFromOrigin + length);

		LineString points;
		double currentLength = 0.0;

		for (size_t n = 0; n < (N * 2); ++n)
		{
			const size_t i = (n % N);
			const double len = lens[i];
			const Vec2 pFrom = out[i];
			const Vec2 pTo = out[(N <= (i + 1)) ? (i - (N - 1)) : (i + 1)];

			if (not points)
			{
				if ((distanceFromOrigin <= (currentLength + len)))
				{
					const Vec2 origin = pFrom + (pTo - pFrom)
						.setLength(distanceFromOrigin - currentLength);
					points << origin;

					if (distanceToTarget <= (currentLength + len))
					{
						const Vec2 target = pFrom + (pTo - pFrom)
							.setLength(distanceToTarget - currentLength);
						points << target;
						break;
					}

					points << pTo;
				}
			}
			else
			{
				if (distanceToTarget <= (currentLength + len))
				{
					const Vec2 target = pFrom + (pTo - pFrom)
						.setLength(distanceToTarget - currentLength);
					points << target;
					break;
				}

				points << pTo;
			}

			currentLength += len;
		}

		return points;
	}

	bool Polygon::append(const RectF& other)
	{
		return pImpl->append(other);
	}

	bool Polygon::append(const Polygon& other)
	{
		return pImpl->append(other);
	}

	bool Polygon::intersects(const Line& other) const
	{
		return pImpl->intersects(other);
	}

	bool Polygon::intersects(const Rect& other) const
	{
		return pImpl->intersects(other);
	}

	bool Polygon::intersects(const RectF& other) const
	{
		return pImpl->intersects(other);
	}

	bool Polygon::intersects(const Polygon& other) const
	{
		return pImpl->intersects(*other.pImpl);
	}

	bool Polygon::leftClicked() const noexcept
	{
		return (MouseL.down() && mouseOver());
	}

	bool Polygon::leftPressed() const noexcept
	{
		return (MouseL.pressed() && mouseOver());
	}

	bool Polygon::leftReleased() const noexcept
	{
		return (MouseL.up() && mouseOver());
	}

	bool Polygon::rightClicked() const noexcept
	{
		return (MouseR.down() && mouseOver());
	}

	bool Polygon::rightPressed() const noexcept
	{
		return (MouseR.pressed() && mouseOver());
	}

	bool Polygon::rightReleased() const noexcept
	{
		return (MouseR.up() && mouseOver());
	}

	bool Polygon::mouseOver() const noexcept
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const Polygon& Polygon::draw(const ColorF& color) const
	{
		pImpl->draw(color);

		return *this;
	}

	void Polygon::draw(const double x, const double y, const ColorF& color) const
	{
		draw(Vec2{ x, y }, color);
	}

	void Polygon::draw(const Vec2& pos, const ColorF& color) const
	{
		pImpl->draw(pos, color);
	}

	void Polygon::drawTransformed(double angle, const Vec2& pos, const ColorF& color) const
	{
		const auto [s, c] = FastMath::SinCos(angle);
		drawTransformed(s, c, pos, color);
	}

	void Polygon::drawTransformed(const double s, const double c, const Vec2& pos, const ColorF& color) const
	{
		pImpl->drawTransformed(s, c, pos, color);
	}

	const Polygon& Polygon::drawFrame(const double thickness, const ColorF& color) const
	{
		pImpl->drawFrame(thickness, color);

		return *this;
	}

	void Polygon::drawFrame(const double x, const double y, const double thickness, const ColorF& color) const
	{
		drawFrame(Vec2{ x, y }, thickness, color);
	}

	void Polygon::drawFrame(const Vec2& pos, const double thickness, const ColorF& color) const
	{
		pImpl->drawFrame(pos, thickness, color);
	}

	const Polygon& Polygon::drawWireframe(const double thickness, const ColorF& color) const
	{
		if (isEmpty())
		{
			return *this;
		}

		const auto& indices = pImpl->indices();
		const Float2* pVertex = pImpl->vertices().data();
		const TriangleIndex* pIndex = indices.data();
		const TriangleIndex* const pIndexEnd = (pIndex + indices.size());
		const Float4 colorF = color.toFloat4();

		while (pIndex != pIndexEnd)
		{
			const Float2 points[3] = { pVertex[pIndex->i0], pVertex[pIndex->i1], pVertex[pIndex->i2] };

			SIV3D_ENGINE(Renderer2D)->addPolygonFrame(points, 3, static_cast<float>(thickness), colorF);

			++pIndex;
		}

		return *this;
	}

	void Polygon::drawWireframe(const double x, const double y, const double thickness, const ColorF& color) const
	{
		drawWireframe(Vec2{ x, y }, thickness, color);
	}

	void Polygon::drawWireframe(const Vec2& pos, const double thickness, const ColorF& color) const
	{
		if (isEmpty())
		{
			return;
		}

		const auto& indices = pImpl->indices();
		const Float2* pVertex = pImpl->vertices().data();
		const TriangleIndex* pIndex = indices.data();
		const TriangleIndex* const pIndexEnd = (pIndex + indices.size());
		const Float4 colorF = color.toFloat4();
		const Float2 offset = pos;

		while (pIndex != pIndexEnd)
		{
			const Float2 points[3] = {
				(pVertex[pIndex->i0] + offset),
				(pVertex[pIndex->i1] + offset),
				(pVertex[pIndex->i2] + offset)
			};

			SIV3D_ENGINE(Renderer2D)->addPolygonFrame(points, 3, static_cast<float>(thickness), colorF);

			++pIndex;
		}
	}

	Buffer2D Polygon::toBuffer2D(const Vec2& uvOrigin, const Vec2& uvScale) const
	{
		return Buffer2D{ *this, uvOrigin, uvScale };
	}

	Buffer2D Polygon::toBuffer2D(const Arg::center_<Vec2> uvCenter, const Vec2& uvScale) const
	{
		return Buffer2D{ *this, uvCenter, uvScale };
	}

	Buffer2D Polygon::toBuffer2D(const Arg::center_<Vec2> uvCenter, const Vec2& uvScale, const double uvRotation) const
	{
		return Buffer2D{ *this, uvCenter, uvScale, uvRotation };
	}

	Buffer2D Polygon::toBuffer2D(const Mat3x2& uvMat) const
	{
		return Buffer2D{ *this, uvMat };
	}

	PolygonFailureType Polygon::Validate(const Vec2* pVertex, const size_t vertexSize, const Array<Array<Vec2>>& holes)
	{
		CwOpenPolygon polygon;
		auto& outer = polygon.outer();
		{
			outer.assign(pVertex, pVertex + vertexSize);

			polygon.inners().reserve(holes.size());

			for (const auto& hole : holes)
			{
				polygon.inners().emplace_back(hole.begin(), hole.end());
			}
		}

		boost::geometry::validity_failure_type failure;
		bool valid = boost::geometry::is_valid(polygon, failure);

		if (valid)
		{
			// 頂点の重複は boost::geometry::is_valid() で取得できないので、
			// HashSet を使って計算
			if (detail::HasSamePoints(outer.data(), outer.size()))
			{
				valid = false;
				failure = boost::geometry::failure_duplicate_points;
			}
		}

		if (valid)
		{
			for (const auto& inner : polygon.inners())
			{
				if (detail::HasSamePoints(inner.data(), inner.size()))
				{
					valid = false;
					failure = boost::geometry::failure_duplicate_points;
				}
			}
		}

		return detail::Convert(failure);
	}

	PolygonFailureType Polygon::Validate(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes)
	{
		return Validate(vertices.data(), vertices.size(), holes);
	}

	Array<Polygon> Polygon::Correct(const Vec2* pVertex, const size_t vertexSize, const Array<Array<Vec2>>& holes)
	{
		CwOpenPolygon polygon;
		polygon.outer().assign(pVertex, pVertex + vertexSize);

		for (const auto& hole : holes)
		{
			polygon.inners().emplace_back(hole.begin(), hole.end());
		}

		{
			boost::geometry::validity_failure_type failure;
			bool valid = boost::geometry::is_valid(polygon, failure);

			if (valid)
			{
				// 頂点の重複は boost::geometry::is_valid() で取得できないので、
				// HashSet を使って計算
				if (detail::HasSamePoints(polygon.outer().data(), polygon.outer().size()))
				{
					valid = false;
					failure = boost::geometry::failure_duplicate_points;
				}
			}

			if (valid)
			{
				for (const auto& inner : polygon.inners())
				{
					if (detail::HasSamePoints(inner.data(), inner.size()))
					{
						valid = false;
						failure = boost::geometry::failure_duplicate_points;
					}
				}
			}

			// OK
			if (valid)
			{
				return{ Polygon(pVertex, vertexSize, holes) };
			}
		}

		// dissolve
		using MultiCwOpenPolygon = boost::geometry::model::multi_polygon<CwOpenPolygon>;
		boost::geometry::correct(polygon);
		MultiCwOpenPolygon solvedPolygons;
		boost::geometry::dissolve(polygon, solvedPolygons);

		Array<Polygon> results;

		for (const auto& solvedPolygon : solvedPolygons)
		{
			Array<Array<Vec2>> retHoles;

			for (const auto& hole : solvedPolygon.inners())
			{
				retHoles.emplace_back(hole.begin(), hole.end());
			}

			if (Validate(solvedPolygon.outer(), retHoles) == PolygonFailureType::OK)
			{
				results.emplace_back(solvedPolygon.outer(), retHoles);
			}
		}

		return results;
	}

	Array<Polygon> Polygon::Correct(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes)
	{
		return Correct(vertices.data(), vertices.size(), holes);
	}

	Polygon Polygon::CorrectOne(const Vec2* pVertex, const size_t vertexSize, const Array<Array<Vec2>>& holes)
	{
		Array<Polygon> polygons = Correct(pVertex, vertexSize, holes);

		if (not polygons)
		{
			return{};
		}

		size_t index = 0;
		double maxArea = polygons.front().area();

		for (size_t i = 1; i < polygons.size(); ++i)
		{
			const double area = polygons[i].area();

			if (maxArea < area)
			{
				index = i;
				maxArea = area;
			}
		}

		return polygons[index];
	}

	Polygon Polygon::CorrectOne(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes)
	{
		return CorrectOne(vertices.data(), vertices.size(), holes);
	}

	void Formatter(FormatData& formatData, const Polygon& value)
	{
		std::stringstream ss;
		
		ss << value;
		
		formatData.string.append(Unicode::WidenAscii(ss.str()));
	}
}
