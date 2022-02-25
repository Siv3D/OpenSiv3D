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
# include "../Common.hpp"
# include "../ColorHSV.hpp"
# include "P2Fwd.hpp"
# include "P2ShapeType.hpp"

namespace s3d
{
	class P2Shape
	{
	public:

		virtual ~P2Shape() = default;

		virtual P2ShapeType getShapeType() const noexcept = 0;

		virtual const P2Shape& draw(const ColorF& color) const = 0;

		virtual const P2Shape& drawFrame(double thickness, const ColorF& color) const = 0;

		virtual const P2Shape& drawWireframe(double thickness, const ColorF& color) const = 0;

		void setDensity(double density) noexcept;

		[[nodiscard]]
		double getDensity() const noexcept;

		void setRestitution(double restitution) noexcept;

		[[nodiscard]]
		double getRestitution() const noexcept;

		void setFriction(double friction) noexcept;

		[[nodiscard]]
		double getFriction() const noexcept;

		void setRestitutionThreshold(double restitutionThreshold) noexcept;

		[[nodiscard]]
		double getRestitutionThreshold() const noexcept;

		void setFilter(const P2Filter& filter) noexcept;

		[[nodiscard]]
		P2Filter getFilter() const noexcept;
	
	protected:

		// Body の破棄時に自動的に解放される
		Array<b2Fixture*> m_fixtures;
	};
}
