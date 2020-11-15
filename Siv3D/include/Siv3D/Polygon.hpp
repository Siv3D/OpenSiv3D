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

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "PolygonFailureType.hpp"
# include "Vertex2D.hpp"
# include "Triangle.hpp"
# include "TriangleIndex.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	class Polygon
	{
	public:

		Polygon();

		Polygon(const Polygon& polygon);

		Polygon(Polygon&& polygon) noexcept;

		Polygon(const Vec2* outer, size_t size, Array<Array<Vec2>> holes = {}, SkipValidation skipValidation = SkipValidation::No);

		explicit Polygon(const Array<Vec2>& outer, Array<Array<Vec2>> holes = {}, SkipValidation skipValidation = SkipValidation::No);

		Polygon(const Array<Vec2>& outer, const Array<TriangleIndex>& indices, const RectF& boundingRect, SkipValidation skipValidation = SkipValidation::No);

		Polygon(const Array<Vec2>& outer, Array<Array<Vec2>> holes, const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const RectF& boundingRect, SkipValidation skipValidation = SkipValidation::No);

		explicit Polygon(std::initializer_list<Vec2> outer, SkipValidation skipValidation = SkipValidation::No);

		//Polygon(const Shape2D& shape);

		~Polygon();

		Polygon& operator =(const Polygon& polygon);

		Polygon& operator =(Polygon&& polygon) noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool hasHoles() const noexcept;

		[[nodiscard]]
		size_t num_holes() const noexcept;

		void swap(Polygon& polygon) noexcept;

		[[nodiscard]]
		const Array<Vec2>& outer() const noexcept;

		[[nodiscard]]
		const Array<Array<Vec2>>& inners() const noexcept;

		[[nodiscard]]
		const Array<Float2>& vertices() const noexcept;

		[[nodiscard]]
		const Array<TriangleIndex>& indices() const noexcept ;

		[[nodiscard]]
		const RectF& boundingRect() const noexcept;

		[[nodiscard]]
		size_t num_triangles() const noexcept;

		[[nodiscard]]
		Triangle triangle(size_t index) const;

		Polygon& addHole(Array<Vec2> hole, SkipValidation skipValidation = SkipValidation::No);

		Polygon& addHoles(Array<Array<Vec2>> holes, SkipValidation skipValidation = SkipValidation::No);

		[[nodiscard]]
		Polygon movedBy(double x, double y) const;

		[[nodiscard]]
		Polygon movedBy(Vec2 v) const;

		Polygon& moveBy(double x, double y) noexcept;

		Polygon& moveBy(Vec2 v) noexcept;

		[[nodiscard]]
		static PolygonFailureType Validate(const Vec2* pVertex, size_t vertexSize, const Array<Array<Vec2>>& holes = {});

		[[nodiscard]]
		static PolygonFailureType Validate(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes = {});

	private:

		class PolygonDetail;

		std::unique_ptr<PolygonDetail> pImpl;
	};
}

# include "detail/Polygon.ipp"
