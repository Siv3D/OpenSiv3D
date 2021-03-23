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
# include "../Common.hpp"
# include "../ColorHSV.hpp"
# include "P2Fwd.hpp"
# include "P2Fixture.hpp"
# include "P2ShapeType.hpp"

namespace s3d
{
	class P2Shape
	{
	public:

		virtual ~P2Shape() = default;

		virtual P2ShapeType getShapeType() const noexcept = 0;

		virtual void draw(const ColorF& color) const = 0;

		virtual void drawFrame(double thickness, const ColorF& color) const = 0;

		virtual void drawWireframe(double thickness, const ColorF& color) const = 0;

		void setDensity(double density) noexcept;

		[[nodiscard]]
		double getDensity() const noexcept;

		void setFriction(double friction) noexcept;

		[[nodiscard]]
		double getFriction() const noexcept;

		void setRestitution(double restitution) noexcept;

		[[nodiscard]]
		double getRestitution() const noexcept;

		void setFilter(const P2Filter& filter) noexcept;

		[[nodiscard]]
		P2Filter getFilter() const noexcept;
	
	protected:

		P2Fixture m_fixtures;
	};
}
