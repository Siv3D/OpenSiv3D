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
# include "IEmitter2D.hpp"
# include "Polygon.hpp"
# include "DiscreteDistribution.hpp"

namespace s3d
{
	struct PolygonEmitter2D : IEmitter2D
	{
	public:

		double sourceRadius = 5.0;

		explicit PolygonEmitter2D(Polygon&& polygon);

		explicit PolygonEmitter2D(const Polygon& polygon);

		Emission2D emit(const Vec2& emitterPosition, double startSpeed) override;

		void drawDebug(const Vec2& emitterPosition) const override;

	private:

		Polygon m_polygon;

		DiscreteDistribution m_triangleWeights;
	};
}
