//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Physics2D/P2Body.hpp>
# include <Siv3D/PredefinedYesNo.hpp>
# include "P2Common.hpp"

namespace s3d
{
	class P2Body::P2BodyDetail
	{
	public:

		P2BodyDetail() = default;

		P2BodyDetail(const std::shared_ptr<detail::P2WorldDetail>& world, P2BodyID id, const Vec2& center, P2BodyType bodyType);

		~P2BodyDetail();

		[[nodiscard]]
		P2BodyID id() const noexcept;

		void addLine(const Line& localPos, OneSided oneSided, const P2Material& material, const P2Filter& filter);

		void addLineSensor(const Line& localPos, const P2Filter& filter);

		void addLineString(const LineString& localPos, CloseRing closeRing, OneSided oneSided, const P2Material& material, const P2Filter& filter);

		void addLineStringSensor(const LineString& localPos, CloseRing closeRing, const P2Filter& filter);

		void addCircle(const Circle& localPos, const P2Material& material, const P2Filter& filter);

		void addCircleSensor(const Circle& localPos, const P2Filter& filter);

		void addRect(const RectF& localPos, const P2Material& material, const P2Filter& filter);

		void addRectSensor(const RectF& localPos, const P2Filter& filter);

		void addTriangle(const Triangle& localPos, const P2Material& material, const P2Filter& filter);

		void addTriangleSensor(const Triangle& localPos, const P2Filter& filter);

		void addQuad(const Quad& localPos, const P2Material& material, const P2Filter& filter);

		void addQuadSensor(const Quad& localPos, const P2Filter& filter);

		void addPolygon(const Polygon& polygon, const P2Material& material, const P2Filter& filter);

		void addPolygonSensor(const Polygon& polygon, const P2Filter& filter);

		[[nodiscard]]
		b2Body& getBody() noexcept;

		[[nodiscard]]
		const b2Body& getBody() const noexcept;

		[[nodiscard]]
		b2Body* getBodyPtr() const;

		[[nodiscard]]
		const Array<std::shared_ptr<P2Shape>>& getShapes() const noexcept;

	private:

		std::shared_ptr<detail::P2WorldDetail> m_world;

		P2BodyID m_id = 0;

		b2Body* m_body = nullptr;

		Array<std::shared_ptr<P2Shape>> m_shapes;
	};
}
