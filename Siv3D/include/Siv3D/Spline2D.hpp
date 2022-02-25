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

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "PointVector.hpp"
# include "2DShapes.hpp"
# include "LineString.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	struct SplineIndex
	{
		size_t i = 0;

		double t = 0.0;
	};

	class Spline2D
	{
	public:

		struct CSpline2
		{
			Vec4 xb;
			Vec4 yb;
		};

		SIV3D_NODISCARD_CXX20
		Spline2D() = default;

		SIV3D_NODISCARD_CXX20
		explicit Spline2D(const Array<Vec2>& points, double tension = 0.0);

		SIV3D_NODISCARD_CXX20
		Spline2D(const Array<Vec2>& points, CloseRing closeRing, double tension = 0.0);

		[[nodiscard]]
		size_t size() const noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool isRing() const noexcept;

		void clear() noexcept;

		void swap(Spline2D& other) noexcept;

		[[nodiscard]]
		RectF fastBoundingRect(size_t i) const;

		[[nodiscard]]
		RectF boundingRect(size_t i) const;

		[[nodiscard]]
		double length(size_t i, double maxError = 0.01) const;

		[[nodiscard]]
		double length(size_t i, double t0, double t1, double maxError = 0.01) const;

		[[nodiscard]]
		Vec2 position(size_t i, double t) const;

		[[nodiscard]]
		Vec2 position(SplineIndex si) const;

		[[nodiscard]]
		Vec2 velocity(size_t i, double t) const;

		[[nodiscard]]
		Vec2 velocity(SplineIndex si) const;

		[[nodiscard]]
		Vec2 acceleration(size_t i, double t) const;

		[[nodiscard]]
		Vec2 acceleration(SplineIndex si) const;

		[[nodiscard]]
		double curvature(size_t i, double t) const;

		[[nodiscard]]
		double curvature(SplineIndex si) const;

		[[nodiscard]]
		SplineIndex findNearest(Vec2 pos) const;

		[[nodiscard]]
		Array<std::pair<SplineIndex, SplineIndex>> findSelfIntersections(double tolerance = 0.1) const;

		[[nodiscard]]
		Array<std::pair<SplineIndex, SplineIndex>> findIntersections(const Spline2D& other, double tolerance = 0.1) const;

		[[nodiscard]]
		SplineIndex advance(SplineIndex si, double dl) const;

		[[nodiscard]]
		SplineIndex advanceWrap(SplineIndex si, double dl) const;

		[[nodiscard]]
		SplineIndex advanceMirror(SplineIndex si, double dl, int32& direction) const;

		[[nodiscard]]
		LineString asLineString(int32 quality = 24) const;

		[[nodiscard]]
		Polygon calculateRoundBuffer(double distance, int32 quality = 24, int32 bufferQuality = 24) const;

		const Spline2D& draw(const ColorF& color = Palette::White, int32 quality = 24) const;

		const Spline2D& draw(double thickness, const ColorF& color = Palette::White, int32 quality = 24) const;

		const Spline2D& draw(double thickness, std::function<ColorF(SplineIndex)> colorFunc, int32 quality = 24) const;

		//const Spline2D& draw(double thickness, const Array<ColorF>& colors, int32 quality = 24) const;

		const Spline2D& draw(const LineStyle& style, double thickness, const ColorF& color = Palette::White, int32 quality = 24) const;

	private:

		Array<CSpline2> m_splinesBuffer;

		size_t m_offset = 0;

		size_t m_size = 0;

		bool m_isRing = false;
	};
}

template <>
inline void std::swap(s3d::Spline2D& a, s3d::Spline2D& b) noexcept;

# include "detail/Spline2D.ipp"
