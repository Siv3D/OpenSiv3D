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

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"

namespace s3d
{
	struct Bezier3
	{
		Vec2 p0;

		Vec2 p1;

		Vec2 p2;

		Vec2 p3;

		Bezier3() = default;

		constexpr Bezier3(const Vec2& _p0, const Vec2& _p1, const Vec2& _p2, const Vec2& _p3) noexcept;

		[[nodiscard]]
		Vec2 getPos(double t) const noexcept;

		[[nodiscard]]
		Vec2 getTangent(double t) const noexcept;

		[[nodiscard]]
		LineString getLineString(uint32 quality = 24) const;

		[[nodiscard]]
		LineString getLineString(double start, double end, uint32 quality = 24) const;

		template <class Shape2DType>
		[[nodiscard]]
		constexpr bool intersects(const Shape2DType& other) const;

		template <class Shape2DType>
		[[nodiscard]]
		Optional<Array<Vec2>> intersectsAt(const Shape2DType& other) const;

		//const Bezier3& paint(Image& dst, const Color& color) const;

		//const Bezier3& paint(Image& dst, int32 thickness, const Color& color) const;

		//const Bezier3& overwrite(Image& dst, const Color& color, bool antialiased = true) const;

		//const Bezier3& overwrite(Image& dst, int32 thickness, const Color& color, bool antialiased = true) const;

		//const Bezier3& draw(const ColorF& color = Palette::White, uint32 quality = 24) const;

		//const Bezier3& draw(double thickness, const ColorF& color = Palette::White, uint32 quality = 24) const;
	};

	struct Bezier3Path
	{
	public:

		Bezier3Path() = default;

		explicit Bezier3Path(const Bezier3& bezier) noexcept;

		void setT(const double t) noexcept;

		[[nodiscard]]
		double getT() const noexcept;

		double advance(double distance, int32 quality = 8) noexcept;
	
	private:

		Vec2 m_v0;
		
		Vec2 m_v1;
		
		Vec2 m_v2;

		double m_t = 0.0;
	};
}

# include "detail/Bezier3.ipp"
