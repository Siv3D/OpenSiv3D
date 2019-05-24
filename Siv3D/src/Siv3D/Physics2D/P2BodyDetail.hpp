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
# include <Siv3D/Physics2D.hpp>
# include <Box2D/Box2D.h>

namespace s3d
{
	class P2Body::P2BodyDetail
	{
	private:

		P2World m_world;

		Array<std::shared_ptr<P2Shape>> m_shapes;

		b2Body* m_body = nullptr;

		P2BodyID m_id = 0;

	public:

		P2BodyDetail() = default;

		P2BodyDetail(P2World& world, P2BodyID id, const Vec2& center, P2BodyType bodyType);

		~P2BodyDetail();

		[[nodiscard]] P2BodyID id() const;

		void addLine(const Line& line, const P2Material& material, const P2Filter& filter);

		void addLineString(const LineString& lines, bool closed, const P2Material& material, const P2Filter& filter);

		void addCircle(const Circle& circle, const P2Material& material, const P2Filter& filter);

		void addRect(const RectF& rect, const P2Material& material, const P2Filter& filter);

		void addTriangle(const Triangle& triangle, const P2Material& material, const P2Filter& filter);

		void addQuad(const Quad& quad, const P2Material& material, const P2Filter& filter);

		void addPolygon(const Polygon& polygon, const P2Material& material, const P2Filter& filter);

		[[nodiscard]] b2Body& getBody();

		[[nodiscard]] const b2Body& getBody() const;

		[[nodiscard]] b2Body* getBodyPtr() const;

		[[nodiscard]] const Array<std::shared_ptr<P2Shape>>& getShapes() const;

		void setUserData(P2BodyDetail* data);
	};
}
