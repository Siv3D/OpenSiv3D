//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Physics2D.hpp>
# include <Siv3D/Graphics2D.hpp>

namespace s3d
{
	namespace detail
	{
		inline constexpr Vec2 ToVec2(const b2Vec2& b2Vec2)
		{
			return{ b2Vec2.x, b2Vec2.y };
		}

		inline b2Vec2 ToB2Vec2(const Vec2& vec2)
		{
			return b2Vec2(static_cast<float32>(vec2.x), static_cast<float32>(vec2.y));
		}

		static b2FixtureDef MakeFixtureDef(b2Shape* shape, const P2Material& material, const P2Filter& filter)
		{
			b2FixtureDef fixtureDef;
			fixtureDef.shape = shape;
			fixtureDef.density = static_cast<float32>(material.density);
			fixtureDef.friction = static_cast<float32>(material.friction);
			fixtureDef.restitution = static_cast<float32>(material.restitution);
			fixtureDef.filter.categoryBits = filter.categoryBits;
			fixtureDef.filter.maskBits = filter.maskBits;
			fixtureDef.filter.groupIndex = filter.groupIndex;
			return fixtureDef;
		}
	}

	P2World::P2World(const Vec2& gravity)
		: pImpl(std::make_shared<CP2World>(gravity))
	{

	}

	void P2World::setSleepEnabled(const bool enabled)
	{
		pImpl->setSleepEnabled(enabled);
	}

	bool P2World::getSleepEnabled() const
	{
		return pImpl->getSleepEnabled();
	}

	void P2World::setGravity(const Vec2& gravity)
	{
		pImpl->setGravity(gravity);
	}

	Vec2 P2World::getGravity() const
	{
		return pImpl->getGravity();
	}

	void P2World::update(const double timeStep, const int32 velocityIterations, const int32 positionIterations) const
	{
		return pImpl->update(timeStep, velocityIterations, positionIterations);
	}

	P2Body P2World::createEmpty(const Vec2& center, P2BodyType bodyType)
	{
		return pImpl->createEmpty(*this, center, bodyType);
	}

	P2Body P2World::createLine(const Vec2& center, const Vec2& begin, const Vec2& end, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createLine(*this, center, Line(begin, end), material, filter, bodyType);
	}

	P2Body P2World::createLine(const Vec2& center, const Line& line, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createLine(*this, center, line, material, filter, bodyType);
	}

	P2Body P2World::createLineString(const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createLineString(*this, center, lines, material, filter, bodyType);
	}

	P2Body P2World::createClosedLineString(const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createClosedLineString(*this, center, lines, material, filter, bodyType);
	}

	P2Body P2World::createCircle(const Vec2& center, double r, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createCircle(*this, center, Circle(r), material, filter, bodyType);
	}

	P2Body P2World::createCircle(const Vec2& center, double r, const Vec2& offset, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createCircle(*this, center, Circle(offset, r), material, filter, bodyType);
	}

	P2Body P2World::createCircle(const Vec2& center, const Circle& circle, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createCircle(*this, center, circle, material, filter, bodyType);
	}

	P2Body P2World::createPolygon(const Vec2& center, const Polygon& polygon, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createPolygon(*this, center, polygon, material, filter, bodyType);
	}



	b2World& P2World::getData()
	{
		return pImpl->getData();
	}



	P2BodyID P2World::CP2World::generateNextID()
	{
		return ++m_currentID;
	}

	P2World::CP2World::CP2World(const Vec2& gravity)
		: m_world(detail::ToB2Vec2(gravity))
	{
		//m_world->SetContactListener(&m_contactListner);
	}

	void P2World::CP2World::setSleepEnabled(bool enabled)
	{
		m_world.SetAllowSleeping(enabled);
	}

	bool P2World::CP2World::getSleepEnabled() const
	{
		return m_world.GetAllowSleeping();
	}

	void P2World::CP2World::setGravity(const Vec2& gravity)
	{
		m_world.SetGravity(detail::ToB2Vec2(gravity));
	}

	Vec2 P2World::CP2World::getGravity() const
	{
		return detail::ToVec2(m_world.GetGravity());
	}

	void P2World::CP2World::update(double timeStep, int32 velocityIterations, int32 positionIterations)
	{
		m_world.Step(static_cast<float32>(timeStep), velocityIterations, positionIterations);
	}

	P2Body P2World::CP2World::createEmpty(P2World& world, const Vec2& center, P2BodyType bodyType)
	{
		return P2Body(world, generateNextID(), center, bodyType);
	}

	P2Body P2World::CP2World::createLine(P2World& world, const Vec2& center, const Line& line, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addLine(line, material, filter);

		return body;
	}

	P2Body P2World::CP2World::createLineString(P2World& world, const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addLineString(lines, material, filter);

		return body;
	}

	P2Body P2World::CP2World::createClosedLineString(P2World& world, const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addClosedLineString(lines, material, filter);

		return body;
	}

	P2Body P2World::CP2World::createCircle(P2World& world, const Vec2& center, const Circle& circle, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addCircle(circle, material, filter);

		return body;
	}

	P2Body P2World::CP2World::createPolygon(P2World& world, const Vec2& center, const Polygon& polygon, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addPolygon(polygon, material, filter);

		return body;
	}

	b2World& P2World::CP2World::getData()
	{
		return m_world;
	}


	P2Body::P2Body()
		: pImpl(std::make_shared<CP2Body>())
	{

	}

	P2Body::P2Body(P2World& world, P2BodyID id, const Vec2& center, const P2BodyType bodyType)
		: pImpl(std::make_shared<CP2Body>(world, id, center, bodyType))
	{

	}

	P2BodyID P2Body::id() const
	{
		return pImpl->id();
	}

	bool P2Body::isEmpty() const
	{
		return (pImpl->id() == 0);
	}

	P2Body::operator bool() const
	{
		return !isEmpty();
	}

	P2Body& P2Body::addLine(const Line& line, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addLine(line, material, filter);

		return *this;
	}

	P2Body& P2Body::addLineString(const LineString& lines, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addLineString(lines, false, material, filter);

		return *this;
	}

	P2Body& P2Body::addClosedLineString(const LineString& lines, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addLineString(lines, true, material, filter);

		return *this;
	}

	P2Body& P2Body::addCircle(const Circle& circle, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addCircle(circle, material, filter);

		return *this;
	}

	P2Body& P2Body::addPolygon(const Polygon& polygon, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addPolygon(polygon, material, filter);

		return *this;
	}


	Vec2 P2Body::getPos() const
	{
		if (isEmpty())
		{
			return Vec2(0, 0);
		}

		return detail::ToVec2(pImpl->getBody().GetPosition());
	}

	double P2Body::getAngle() const
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetAngle();
	}

	void P2Body::draw(const ColorF& color) const
	{
		if (isEmpty())
		{
			return;
		}

		for (const auto& shape : pImpl->getShapes())
		{
			shape->draw(color);
		}
	}





	P2Line::P2Line(b2Body& body, const Line& line, const P2Material& material, const P2Filter& filter)
	{
		m_shape.Set(detail::ToB2Vec2(line.begin), detail::ToB2Vec2(line.end));

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(&m_shape, material, filter);

		m_fixtures.fixtures.push_back(body.CreateFixture(&fixtureDef));
	}

	P2ShapeType P2Line::getShapeType() const
	{
		return P2ShapeType::Line;
	}

	void P2Line::draw(const ColorF& color) const
	{
		getLine().draw(3.0 / Graphics2D::GetMaxScaling(), color);
	}

	Line P2Line::getLine() const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
		const Vec2 begin(m_shape.m_vertex1.x * transform.q.c - m_shape.m_vertex1.y * transform.q.s + transform.p.x, m_shape.m_vertex1.x * transform.q.s + m_shape.m_vertex1.y * transform.q.c + transform.p.y);
		const Vec2 end(m_shape.m_vertex2.x * transform.q.c - m_shape.m_vertex2.y * transform.q.s + transform.p.x, m_shape.m_vertex2.x * transform.q.s + m_shape.m_vertex2.y * transform.q.c + transform.p.y);
		return Line(begin, end);
	}



	P2LineString::P2LineString(b2Body& body, const LineString& lines, bool closed, const P2Material& material, const P2Filter& filter)
	{
		Array<b2Vec2> points(lines.size());

		for (size_t i = 0; i < lines.size(); ++i)
		{
			points[i].Set(static_cast<float32>(lines[i].x), static_cast<float32>(lines[i].y));
		}

		m_closed = closed;

		m_lineString.assign(lines.begin(), lines.end());

		if (closed)
		{
			m_shape.CreateLoop(points.data(), static_cast<int32>(points.size()));
		}
		else
		{
			m_shape.CreateChain(points.data(), static_cast<int32>(points.size()));
		}

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(&m_shape, material, filter);

		m_fixtures.fixtures.push_back(body.CreateFixture(&fixtureDef));
	}

	P2ShapeType P2LineString::getShapeType() const
	{
		return P2ShapeType::LineString;
	}

	void P2LineString::draw(const ColorF& color) const
	{
		getLineString().draw(3.0 / Graphics2D::GetMaxScaling(), color, m_closed);
	}

	const LineString& P2LineString::getLineString() const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();

		for (int32 i = 0; i < m_shape.m_count - m_closed; ++i)
		{
			const b2Vec2& pos = m_shape.m_vertices[i];
			m_lineString[i].set(pos.x * transform.q.c - pos.y*transform.q.s + transform.p.x, pos.x*transform.q.s + pos.y*transform.q.c + transform.p.y);
		}

		return m_lineString;
	}






	P2Circle::P2Circle(b2Body& body, const Circle& circle, const P2Material& material, const P2Filter& filter)
	{
		m_shape.m_radius = static_cast<float32>(circle.r);

		m_shape.m_p.Set(static_cast<float32>(circle.x), static_cast<float32>(circle.y));

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(&m_shape, material, filter);

		m_fixtures.fixtures.push_back(body.CreateFixture(&fixtureDef));
	}

	P2ShapeType P2Circle::getShapeType() const
	{
		return P2ShapeType::Circle;
	}

	void P2Circle::draw(const ColorF& color) const
	{
		getCircle().draw(color);
	}

	Circle P2Circle::getCircle() const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
		const b2Vec2& pos = m_shape.m_p;
		return Circle(pos.x * transform.q.c - pos.y*transform.q.s + transform.p.x, pos.x*transform.q.s + pos.y*transform.q.c + transform.p.y, m_shape.m_radius);
	}




	P2Polygon::P2Polygon(b2Body& body, const Polygon& polygon, const P2Material& material, const P2Filter& filter)
		: m_basePolygon(polygon)
	{
		b2PolygonShape m_shape;

		for (size_t i = 0; i < polygon.num_triangles(); ++i)
		{
			const auto triangle = polygon.triangle(i);

			const b2Vec2 points[3] = { detail::ToB2Vec2(triangle.p0), detail::ToB2Vec2(triangle.p1), detail::ToB2Vec2(triangle.p2) };

			m_shape.Set(points, 3);

			const b2FixtureDef fixtureDef = detail::MakeFixtureDef(&m_shape, material, filter);

			m_fixtures.fixtures.push_back(body.CreateFixture(&fixtureDef));
		}
	}

	P2ShapeType P2Polygon::getShapeType() const
	{
		return P2ShapeType::Polygon;
	}

	void P2Polygon::draw(const ColorF& color) const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();

		m_basePolygon.drawTransformed(transform.q.s, transform.q.c, Vec2(transform.p.x, transform.p.y), color);
	}

	Polygon P2Polygon::getPolygon() const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();

		return m_basePolygon.transformed(transform.q.s, transform.q.c, Vec2(transform.p.x, transform.p.y));
	}



	P2Body::CP2Body::CP2Body(P2World& world, P2BodyID id, const Vec2& center, P2BodyType bodyType)
		: m_world(world)
		, m_id(id)
	{
		b2BodyDef bodyDef;
		bodyDef.type = static_cast<b2BodyType>(bodyType);
		bodyDef.position = detail::ToB2Vec2(center);
		m_body = world.getData().CreateBody(&bodyDef);
	}

	P2Body::CP2Body::~CP2Body()
	{
		if (!m_body)
		{
			return;
		}

		m_world.getData().DestroyBody(m_body);
	}

	P2BodyID P2Body::CP2Body::id() const
	{
		return m_id;
	}

	void P2Body::CP2Body::addLine(const Line& line, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Line>(*m_body, line, material, filter));
	}

	void P2Body::CP2Body::addLineString(const LineString& lines, bool closed, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2LineString>(*m_body, lines, closed, material, filter));
	}

	void P2Body::CP2Body::addCircle(const Circle& circle, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Circle>(*m_body, circle, material, filter));
	}

	void P2Body::CP2Body::addPolygon(const Polygon& polygon, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Polygon>(*m_body, polygon, material, filter));
	}

	const b2Body& P2Body::CP2Body::getBody() const
	{
		assert(m_body);

		return *m_body;
	}

	const Array<std::shared_ptr<P2Shape>>& P2Body::CP2Body::getShapes() const
	{
		return m_shapes;
	}
}
