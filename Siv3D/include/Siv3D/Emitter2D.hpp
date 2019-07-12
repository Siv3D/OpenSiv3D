//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "Polygon.hpp"
# include "Distribution.hpp"

namespace s3d
{
	struct Emission2D
	{
		Vec2 position;
		Vec2 velocity;
	};

	struct IEmitter2D
	{
		virtual ~IEmitter2D() = default;

		virtual Emission2D emit(const Vec2& emitterPosition, double startSpeed) = 0;

		virtual void drawDebug(const Vec2& emitterPosition) const = 0;
	};

	struct CircleEmitter2D : IEmitter2D
	{
		double sourceRadius = 5.0;
		double r = 20.0;
		bool randomDirection = false;
		bool fromShell = false;

		Emission2D emit(const Vec2& emitterPosition, double startSpeed) override;

		void drawDebug(const Vec2& emitterPosition) const override;
	};

	struct ArcEmitter2D : IEmitter2D
	{
		double sourceRadius = 5.0;
		double r = 20.0;
		double direction = 0;
		double angle = 45;
		bool randomDirection = false;
		bool fromShell = false;

		Emission2D emit(const Vec2& emitterPosition, double startSpeed) override;

		void drawDebug(const Vec2& emitterPosition) const override;
	};

	struct RectEmitter2D : IEmitter2D
	{
		double sourceRadius = 5.0;
		double width = 100.0;
		double height = 100.0;
		bool randomDirection = false;
		bool fromShell = false;

		Emission2D emit(const Vec2& emitterPosition, double startSpeed) override;

		void drawDebug(const Vec2& emitterPosition) const override;
	};

	struct PolygonEmitter2D : IEmitter2D
	{
	private:

		Polygon m_polygon;

		DiscreteDistribution m_triangleWeights;

	public:

		double sourceRadius = 5.0;

		explicit PolygonEmitter2D(const Polygon& polygon);

		Emission2D emit(const Vec2& emitterPosition, double startSpeed) override;

		void drawDebug(const Vec2& emitterPosition) const override;
	};
}
