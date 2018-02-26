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

# include <atomic>
# include <Siv3D/Physics2D.hpp>
# include <Siv3D/Graphics2D.hpp>
# include <Box2D/Box2D.h>

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

	class P2World::CP2World
	{
	private:

		b2World m_world;

		//ContactListener m_contactListner;

		std::atomic<P2BodyID> m_currentID = 0;

		P2BodyID generateNextID();

	public:

		CP2World(const Vec2& gravity);

		void update(double timeStep, int32 velocityIterations, int32 positionIterations);

		P2Body createEmpty(P2World& world, const Vec2& center, P2BodyType bodyType);

		P2Body createLine(P2World& world, const Vec2& center, const Line& line, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		P2Body createLineString(P2World& world, const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		P2Body createClosedLineString(P2World& world, const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		P2Body createCircle(P2World& world, const Vec2& center, const Circle& circle, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		P2Body createRect(P2World& world, const Vec2& center, const RectF& rect, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		P2Body createTriangle(P2World& world, const Vec2& center, const Triangle& triangle, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		P2Body createQuad(P2World& world, const Vec2& center, const Quad& quad, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		P2Body createPolygon(P2World& world, const Vec2& center, const Polygon& polygon, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		P2RevoluteJoint createRevoluteJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos);

		//const Array<PhysicsContact>& getContacts() const;

		b2World& getData();

		const b2World& getData() const;

		b2World* getWorldPtr();
	};

	class P2Body::CP2Body
	{
	private:

		P2World m_world;

		Array<std::shared_ptr<P2Shape>> m_shapes;

		b2Body* m_body = nullptr;

		P2BodyID m_id = 0;

		//PhysicsBodyInternalData* getInternalData();

	public:

		CP2Body() = default;

		CP2Body(P2World& world, P2BodyID id, const Vec2& center, P2BodyType bodyType);

		~CP2Body();

		P2BodyID id() const;

		void addLine(const Line& line, const P2Material& material, const P2Filter& filter);

		void addLineString(const LineString& lines, bool closed, const P2Material& material, const P2Filter& filter);

		void addCircle(const Circle& circle, const P2Material& material, const P2Filter& filter);

		void addRect(const RectF& rect, const P2Material& material, const P2Filter& filter);

		void addTriangle(const Triangle& triangle, const P2Material& material, const P2Filter& filter);

		void addQuad(const Quad& quad, const P2Material& material, const P2Filter& filter);

		void addPolygon(const Polygon& polygon, const P2Material& material, const P2Filter& filter);

		b2Body& getBody();

		const b2Body& getBody() const;

		b2Body* getBodyPtr() const;

		const Array<std::shared_ptr<P2Shape>>& getShapes() const;
	};

	class P2RevoluteJoint::CP2RevoluteJoint
	{
	private:

		b2RevoluteJoint * m_joint = nullptr;

		P2World m_world;

	public:

		CP2RevoluteJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos);

		~CP2RevoluteJoint();

		b2RevoluteJoint& getJoint();

		const b2RevoluteJoint& getJoint() const;
	};



	P2World::P2World(const Vec2& gravity)
		: pImpl(std::make_shared<CP2World>(gravity))
	{

	}

	void P2World::setSleepEnabled(const bool enabled)
	{
		pImpl->getData().SetAllowSleeping(enabled);
	}

	bool P2World::getSleepEnabled() const
	{
		return pImpl->getData().GetAllowSleeping();
	}

	void P2World::setGravity(const Vec2& gravity)
	{
		pImpl->getData().SetGravity(detail::ToB2Vec2(gravity));
	}

	Vec2 P2World::getGravity() const
	{
		return detail::ToVec2(pImpl->getData().GetGravity());
	}

	void P2World::shiftOrigin(const Vec2& newOrigin)
	{
		pImpl->getData().ShiftOrigin(detail::ToB2Vec2(newOrigin));
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

	P2Body P2World::createRect(const Vec2& center, double size, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createRect(*this, center, RectF(Arg::center(0, 0), size), material, filter, bodyType);
	}

	P2Body P2World::createRect(const Vec2& center, double w, double h, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createRect(*this, center, RectF(Arg::center(0, 0), w, h), material, filter, bodyType);
	}

	P2Body P2World::createRect(const Vec2& center, const Vec2& size, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createRect(*this, center, RectF(Arg::center(0, 0), size), material, filter, bodyType);
	}

	P2Body P2World::createRect(const Vec2& center, const Vec2& size, const Vec2& offset, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createRect(*this, center, RectF(Arg::center(offset), size), material, filter, bodyType);
	}

	P2Body P2World::createRect(const Vec2& center, const RectF& rect, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createRect(*this, center, rect, material, filter, bodyType);
	}

	P2Body P2World::createTriangle(const Vec2& center, double sides, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createTriangle(*this, center, Triangle(sides), material, filter, bodyType);
	}

	P2Body P2World::createTriangle(const Vec2& center, double sides, double angle, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createTriangle(*this, center, Triangle(sides, angle), material, filter, bodyType);
	}

	P2Body P2World::createTriangle(const Vec2& center, double sides, double angle, const Vec2& offset, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createTriangle(*this, center, Triangle(offset, sides, angle), material, filter, bodyType);
	}

	P2Body P2World::createTriangle(const Vec2& center, const Vec2& p0, const Vec2& p1, const Vec2& p2, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createTriangle(*this, center, Triangle(p0, p1, p2), material, filter, bodyType);
	}

	P2Body P2World::createTriangle(const Vec2& center, const Triangle& triangle, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createTriangle(*this, center, triangle, material, filter, bodyType);
	}

	P2Body P2World::createQuad(const Vec2& center, const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createQuad(*this, center, Quad(p0, p1, p2, p3), material, filter, bodyType);
	}

	P2Body P2World::createQuad(const Vec2& center, const Quad& quad, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createQuad(*this, center, quad, material, filter, bodyType);
	}


	P2Body P2World::createPolygon(const Vec2& center, const Polygon& polygon, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		return pImpl->createPolygon(*this, center, polygon, material, filter, bodyType);
	}

	P2RevoluteJoint P2World::createRevoluteJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos)
	{
		return pImpl->createRevoluteJoint(*this, bodyA, bodyB, anchorPos);
	}

	b2World* P2World::getWorldPtr() const
	{
		return pImpl->getWorldPtr();
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

	P2Body P2World::CP2World::createRect(P2World& world, const Vec2& center, const RectF& rect, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addRect(rect, material, filter);

		return body;
	}

	P2Body P2World::CP2World::createTriangle(P2World& world, const Vec2& center, const Triangle& triangle, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addTriangle(triangle, material, filter);

		return body;
	}

	P2Body P2World::CP2World::createQuad(P2World& world, const Vec2& center, const Quad& quad, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addQuad(quad, material, filter);

		return body;
	}

	P2Body P2World::CP2World::createPolygon(P2World& world, const Vec2& center, const Polygon& polygon, const P2Material& material, const P2Filter& filter, P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addPolygon(polygon, material, filter);

		return body;
	}

	P2RevoluteJoint P2World::CP2World::createRevoluteJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos)
	{
		return P2RevoluteJoint(world, bodyA, bodyB, anchorPos);
	}

	b2World& P2World::CP2World::getData()
	{
		return m_world;
	}

	const b2World& P2World::CP2World::getData() const
	{
		return m_world;
	}

	b2World* P2World::CP2World::getWorldPtr()
	{
		return &m_world;
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

	P2Body& P2Body::addRect(const RectF& rect, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addRect(rect, material, filter);

		return *this;
	}

	P2Body& P2Body::addTriangle(const Triangle& triangle, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addTriangle(triangle, material, filter);

		return *this;
	}

	P2Body& P2Body::addQuad(const Quad& quad, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addQuad(quad, material, filter);

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

	void P2Body::setSleepEnabled(bool enabled)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().SetSleepingAllowed(enabled);
	}

	bool P2Body::getSleepEnabled() const
	{
		if (isEmpty())
		{
			return true;
		}

		return pImpl->getBody().IsSleepingAllowed();
	}

	void P2Body::setAwake(bool awake)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().SetAwake(awake);
	}

	bool P2Body::isAwake() const
	{
		if (isEmpty())
		{
			return true;
		}

		return pImpl->getBody().IsAwake();
	}

	void P2Body::setPos(double x, double y)
	{
		setPos(Vec2(x, y));
	}

	void P2Body::setPos(const Vec2& pos)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().SetTransform(detail::ToB2Vec2(pos), pImpl->getBody().GetAngle());
	}

	void P2Body::moveBy(double x, double y)
	{
		moveBy(Vec2(x, y));
	}

	void P2Body::moveBy(const Vec2& v)
	{
		setPos(getPos() + v);
	}

	void P2Body::setAngle(double angle)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().SetTransform(pImpl->getBody().GetPosition(), static_cast<float32>(angle));
	}

	void P2Body::rotateBy(double angle)
	{
		setAngle(getAngle() + angle);
	}

	void P2Body::setTransform(double x, double y, double angle)
	{
		setTransform(Vec2(x, y), angle);
	}

	void P2Body::setTransform(const Vec2& pos, double angle)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().SetTransform(detail::ToB2Vec2(pos), static_cast<float32>(angle));
	}

	void P2Body::applyForce(const Vec2& force)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().ApplyForceToCenter(detail::ToB2Vec2(force), true);
	}

	void P2Body::applyForce(const Vec2& force, const Vec2& offset)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().ApplyForce(detail::ToB2Vec2(force), pImpl->getBody().GetWorldCenter() + detail::ToB2Vec2(offset), true);

	}

	void P2Body::applyForceAt(const Vec2& force, const Vec2& pos)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().ApplyForce(detail::ToB2Vec2(force), detail::ToB2Vec2(pos), true);
	}

	void P2Body::applyLinearImpulse(const Vec2& force)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().ApplyLinearImpulseToCenter(detail::ToB2Vec2(force), true);
	}

	void P2Body::applyLinearImpulse(const Vec2& force, const Vec2& offset)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().ApplyLinearImpulse(detail::ToB2Vec2(force), pImpl->getBody().GetWorldCenter() + detail::ToB2Vec2(offset), true);
	}

	void P2Body::applyLinearImpulseAt(const Vec2& force, const Vec2& pos)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().ApplyLinearImpulse(detail::ToB2Vec2(force), detail::ToB2Vec2(pos), true);
	}

	void P2Body::applyTorque(double torque)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().ApplyTorque(static_cast<float32>(torque), true);
	}

	void P2Body::applyAngularImpulse(double torque)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().ApplyAngularImpulse(static_cast<float32>(torque), true);
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

	std::pair<Vec2, double> P2Body::getTransform() const
	{
		if (isEmpty())
		{
			return{ Vec2(0,0), 0.0 };
		}

		return{ detail::ToVec2(pImpl->getBody().GetPosition()), pImpl->getBody().GetAngle() };
	}

	void P2Body::setVelocity(const Vec2& v)
	{
		if (isEmpty())
		{
			return;
		}

		return pImpl->getBody().SetLinearVelocity(detail::ToB2Vec2(v));
	}

	Vec2 P2Body::getVelocity() const
	{
		if (isEmpty())
		{
			return Vec2(0, 0);
		}

		return detail::ToVec2(pImpl->getBody().GetLinearVelocity());
	}

	void P2Body::setAngularVelocity(double omega)
	{
		if (isEmpty())
		{
			return;
		}

		return pImpl->getBody().SetAngularVelocity(static_cast<float32>(omega));
	}

	double P2Body::getAngularVelocity() const
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetAngularVelocity();
	}

	void P2Body::setDamping(double damping)
	{
		if(isEmpty())
		{
			return;
		}

		pImpl->getBody().SetLinearDamping(static_cast<float32>(damping));
	}

	double P2Body::getDamping() const
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetLinearDamping();
	}

	void P2Body::setAngularDamping(double damping)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().SetAngularDamping(static_cast<float32>(damping));
	}

	double P2Body::getAngularDamping() const
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetAngularDamping();
	}
	
	void P2Body::setGravityScale(double scale)
	{
		if (isEmpty())
		{
			return;
		}

		pImpl->getBody().SetGravityScale(static_cast<float32>(scale));
	}

	double P2Body::getGravityScale() const
	{
		if (isEmpty())
		{
			return 1.0;
		}

		return pImpl->getBody().GetGravityScale();
	}

	double P2Body::getMass() const
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetMass();
	}

	double P2Body::getInertia() const
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetInertia();
	}

	void P2Body::setBodyType(P2BodyType bodyType)
	{
		if (isEmpty())
		{
			return;
		}

		return pImpl->getBody().SetType(static_cast<b2BodyType>(bodyType));
	}

	P2BodyType P2Body::getBodyType() const
	{
		if (isEmpty())
		{
			return P2BodyType::Static;
		}

		return static_cast<P2BodyType>(pImpl->getBody().GetType());
	}

	void P2Body::setFixedRotation(bool fixedRotation)
	{
		if (isEmpty())
		{
			return;
		}

		return pImpl->getBody().SetFixedRotation(fixedRotation);
	}

	bool P2Body::isFixedRotation() const
	{
		if (isEmpty())
		{
			return false;
		}

		return pImpl->getBody().IsFixedRotation();
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

	size_t P2Body::num_shapes() const
	{
		if (isEmpty())
		{
			return 0;
		}

		return pImpl->getShapes().size();
	}

	P2Shape& P2Body::shape(size_t index)
	{
		if (isEmpty())
		{
			throw std::out_of_range("P2Body::shape() P2Body is empty.");
		}

		return *pImpl->getShapes()[index];
	}

	const P2Shape& P2Body::shape(size_t index) const
	{
		if (isEmpty())
		{
			throw std::out_of_range("P2Body::shape() P2Body is empty.");
		}

		return *pImpl->getShapes()[index];
	}

	std::shared_ptr<P2Shape> P2Body::shapePtr(const size_t index) const
	{
		return pImpl->getShapes()[index];
	}
	
	b2Body* P2Body::getBodyPtr() const
	{
		return pImpl->getBodyPtr();
	}


	void P2Shape::setDensity(double density)
	{
		for (auto& fixture : m_fixtures.fixtures)
		{
			fixture->SetDensity(static_cast<float32>(density));
		}
	}

	double P2Shape::getDensity() const
	{
		return m_fixtures.fixtures[0]->GetDensity();
	}

	void P2Shape::setFriction(double friction)
	{
		for (auto& fixture : m_fixtures.fixtures)
		{
			fixture->SetFriction(static_cast<float32>(friction));
		}
	}

	double P2Shape::getFriction() const
	{
		return m_fixtures.fixtures[0]->GetFriction();
	}

	void P2Shape::setRestitution(double restitution)
	{
		for (auto& fixture : m_fixtures.fixtures)
		{
			fixture->SetRestitution(static_cast<float32>(restitution));
		}
	}

	double P2Shape::getRestitution() const
	{
		return m_fixtures.fixtures[0]->GetRestitution();
	}

	void P2Shape::setFilter(const P2Filter& filter)
	{
		b2Filter filterData;
		filterData.categoryBits	= filter.categoryBits;
		filterData.maskBits		= filter.maskBits;
		filterData.groupIndex	= filter.groupIndex;

		for (auto& fixture : m_fixtures.fixtures)
		{
			fixture->SetFilterData(filterData);
		}
	}

	P2Filter P2Shape::getFilter() const
	{
		const auto& filterData = m_fixtures.fixtures[0]->GetFilterData();
		P2Filter filter;
		filter.categoryBits	= filterData.categoryBits;
		filter.maskBits		= filterData.maskBits;
		filter.groupIndex	= filterData.groupIndex;
		return filter;
	}



	P2Line::P2Line(b2Body& body, const Line& line, const P2Material& material, const P2Filter& filter)
		: m_pShape(std::make_unique<b2EdgeShape>())
	{
		m_pShape->Set(detail::ToB2Vec2(line.begin), detail::ToB2Vec2(line.end));

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(m_pShape.get(), material, filter);

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
		const Vec2 begin(m_pShape->m_vertex1.x * transform.q.c - m_pShape->m_vertex1.y * transform.q.s + transform.p.x, m_pShape->m_vertex1.x * transform.q.s + m_pShape->m_vertex1.y * transform.q.c + transform.p.y);
		const Vec2 end(m_pShape->m_vertex2.x * transform.q.c - m_pShape->m_vertex2.y * transform.q.s + transform.p.x, m_pShape->m_vertex2.x * transform.q.s + m_pShape->m_vertex2.y * transform.q.c + transform.p.y);
		return Line(begin, end);
	}



	P2LineString::P2LineString(b2Body& body, const LineString& lines, bool closed, const P2Material& material, const P2Filter& filter)
		: m_pShape(std::make_unique<b2ChainShape>())
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
			m_pShape->CreateLoop(points.data(), static_cast<int32>(points.size()));
		}
		else
		{
			m_pShape->CreateChain(points.data(), static_cast<int32>(points.size()));
		}

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(m_pShape.get(), material, filter);

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

		for (int32 i = 0; i < m_pShape->m_count - m_closed; ++i)
		{
			const b2Vec2& pos = m_pShape->m_vertices[i];
			m_lineString[i].set(pos.x * transform.q.c - pos.y*transform.q.s + transform.p.x, pos.x*transform.q.s + pos.y*transform.q.c + transform.p.y);
		}

		return m_lineString;
	}






	P2Circle::P2Circle(b2Body& body, const Circle& circle, const P2Material& material, const P2Filter& filter)
		: m_pShape(std::make_unique<b2CircleShape>())
	{
		m_pShape->m_radius = static_cast<float32>(circle.r);

		m_pShape->m_p.Set(static_cast<float32>(circle.x), static_cast<float32>(circle.y));

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(m_pShape.get(), material, filter);

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
		const b2Vec2& pos = m_pShape->m_p;
		return Circle(pos.x * transform.q.c - pos.y*transform.q.s + transform.p.x, pos.x*transform.q.s + pos.y*transform.q.c + transform.p.y, m_pShape->m_radius);
	}


	P2Rect::P2Rect(b2Body& body, const RectF& rect, const P2Material& material, const P2Filter& filter)
		: m_pShape(std::make_unique<b2PolygonShape>())
	{
		m_pShape->SetAsBox(static_cast<float32>(rect.w * 0.5f), static_cast<float32>(rect.h * 0.5f), detail::ToB2Vec2(rect.center()), 0.0f);

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(m_pShape.get(), material, filter);

		m_fixtures.fixtures.push_back(body.CreateFixture(&fixtureDef));
	}

	P2ShapeType P2Rect::getShapeType() const
	{
		return P2ShapeType::Rect;
	}

	void P2Rect::draw(const ColorF& color) const
	{
		getQuad().draw(color);
	}

	Quad P2Rect::getQuad() const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
		const b2Vec2& pos0 = m_pShape->m_vertices[0];
		const b2Vec2& pos1 = m_pShape->m_vertices[1];
		const b2Vec2& pos2 = m_pShape->m_vertices[2];
		const b2Vec2& pos3 = m_pShape->m_vertices[3];
		return Quad
		(
			pos0.x * transform.q.c - pos0.y*transform.q.s + transform.p.x, pos0.x*transform.q.s + pos0.y*transform.q.c + transform.p.y,
			pos1.x * transform.q.c - pos1.y*transform.q.s + transform.p.x, pos1.x*transform.q.s + pos1.y*transform.q.c + transform.p.y,
			pos2.x * transform.q.c - pos2.y*transform.q.s + transform.p.x, pos2.x*transform.q.s + pos2.y*transform.q.c + transform.p.y,
			pos3.x * transform.q.c - pos3.y*transform.q.s + transform.p.x, pos3.x*transform.q.s + pos3.y*transform.q.c + transform.p.y
		);
	}


	P2Triangle::P2Triangle(b2Body& body, const Triangle& triangle, const P2Material& material, const P2Filter& filter)
		: m_pShape(std::make_unique<b2PolygonShape>())
	{
		const b2Vec2 points[3] = { detail::ToB2Vec2(triangle.p0), detail::ToB2Vec2(triangle.p1), detail::ToB2Vec2(triangle.p2) };

		m_pShape->Set(points, 3);

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(m_pShape.get(), material, filter);

		m_fixtures.fixtures.push_back(body.CreateFixture(&fixtureDef));
	}

	P2ShapeType P2Triangle::getShapeType() const
	{
		return P2ShapeType::Triangle;
	}

	void P2Triangle::draw(const ColorF& color) const
	{
		getTriangle().draw(color);
	}

	Triangle P2Triangle::getTriangle() const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
		const b2Vec2& pos0 = m_pShape->m_vertices[0];
		const b2Vec2& pos1 = m_pShape->m_vertices[1];
		const b2Vec2& pos2 = m_pShape->m_vertices[2];
		return Triangle
		(
			pos0.x * transform.q.c - pos0.y*transform.q.s + transform.p.x, pos0.x*transform.q.s + pos0.y*transform.q.c + transform.p.y,
			pos1.x * transform.q.c - pos1.y*transform.q.s + transform.p.x, pos1.x*transform.q.s + pos1.y*transform.q.c + transform.p.y,
			pos2.x * transform.q.c - pos2.y*transform.q.s + transform.p.x, pos2.x*transform.q.s + pos2.y*transform.q.c + transform.p.y
		);
	}


	P2Quad::P2Quad(b2Body& body, const Quad& quad, const P2Material& material, const P2Filter& filter)
		: m_pShape(std::make_unique<b2PolygonShape>())
	{
		const b2Vec2 points[4] = { detail::ToB2Vec2(quad.p0), detail::ToB2Vec2(quad.p1), detail::ToB2Vec2(quad.p2), detail::ToB2Vec2(quad.p3) };

		m_pShape->Set(points, 4);

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(m_pShape.get(), material, filter);

		m_fixtures.fixtures.push_back(body.CreateFixture(&fixtureDef));
	}

	P2ShapeType P2Quad::getShapeType() const
	{
		return P2ShapeType::Quad;
	}

	void P2Quad::draw(const ColorF& color) const
	{
		getQuad().draw(color);
	}

	Quad P2Quad::getQuad() const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
		const b2Vec2& pos0 = m_pShape->m_vertices[0];
		const b2Vec2& pos1 = m_pShape->m_vertices[1];
		const b2Vec2& pos2 = m_pShape->m_vertices[2];
		const b2Vec2& pos3 = m_pShape->m_vertices[3];
		return Quad
		(
			pos0.x * transform.q.c - pos0.y*transform.q.s + transform.p.x, pos0.x*transform.q.s + pos0.y*transform.q.c + transform.p.y,
			pos1.x * transform.q.c - pos1.y*transform.q.s + transform.p.x, pos1.x*transform.q.s + pos1.y*transform.q.c + transform.p.y,
			pos2.x * transform.q.c - pos2.y*transform.q.s + transform.p.x, pos2.x*transform.q.s + pos2.y*transform.q.c + transform.p.y,
			pos3.x * transform.q.c - pos3.y*transform.q.s + transform.p.x, pos3.x*transform.q.s + pos3.y*transform.q.c + transform.p.y
		);
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
		m_body = world.getWorldPtr()->CreateBody(&bodyDef);
	}

	P2Body::CP2Body::~CP2Body()
	{
		if (!m_body)
		{
			return;
		}

		m_world.getWorldPtr()->DestroyBody(m_body);
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

	void P2Body::CP2Body::addRect(const RectF& rect, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Rect>(*m_body, rect, material, filter));
	}

	void P2Body::CP2Body::addTriangle(const Triangle& triangle, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Triangle>(*m_body, triangle, material, filter));
	}

	void P2Body::CP2Body::addQuad(const Quad& quad, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Quad>(*m_body, quad, material, filter));
	}

	void P2Body::CP2Body::addPolygon(const Polygon& polygon, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Polygon>(*m_body, polygon, material, filter));
	}

	b2Body& P2Body::CP2Body::getBody()
	{
		assert(m_body);

		return *m_body;
	}

	const b2Body& P2Body::CP2Body::getBody() const
	{
		assert(m_body);

		return *m_body;
	}

	b2Body* P2Body::CP2Body::getBodyPtr() const
	{
		assert(m_body);

		return m_body;
	}

	const Array<std::shared_ptr<P2Shape>>& P2Body::CP2Body::getShapes() const
	{
		return m_shapes;
	}

	P2RevoluteJoint::P2RevoluteJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos)
		: pImpl(std::make_shared<CP2RevoluteJoint>(world, bodyA, bodyB, anchorPos))
	{

	}

	void P2RevoluteJoint::setMotorEnabled(bool enabled)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getJoint().EnableMotor(enabled);
	}

	bool P2RevoluteJoint::getMotorEnabled() const
	{
		if (!pImpl)
		{
			return false;
		}

		return pImpl->getJoint().IsMotorEnabled();
	}

	void P2RevoluteJoint::setMotorSpeed(double speed)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getJoint().SetMotorSpeed(static_cast<float32>(speed));
	}

	double P2RevoluteJoint::getMotorSpeed() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMotorSpeed();
	}

	void P2RevoluteJoint::setMaxMotorTorque(double torque)
	{
		if (!pImpl)
		{
			return;
		}

		pImpl->getJoint().SetMaxMotorTorque(static_cast<float32>(torque));
	}

	double P2RevoluteJoint::getMaxMotorTorque() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMaxMotorTorque();
	}

	P2RevoluteJoint::CP2RevoluteJoint::CP2RevoluteJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos)
		: m_world(world)
	{
		b2RevoluteJointDef def;
		def.Initialize(bodyA.getBodyPtr(), bodyB.getBodyPtr(), detail::ToB2Vec2(anchorPos));
		m_joint = static_cast<b2RevoluteJoint*>(world.getWorldPtr()->CreateJoint(&def));
	}

	P2RevoluteJoint::CP2RevoluteJoint::~CP2RevoluteJoint()
	{
		if (!m_joint)
		{
			return;
		}

		m_world.getWorldPtr()->DestroyJoint(m_joint);
	}

	b2RevoluteJoint& P2RevoluteJoint::CP2RevoluteJoint::getJoint()
	{
		assert(m_joint);

		return *m_joint;
	}

	const b2RevoluteJoint& P2RevoluteJoint::CP2RevoluteJoint::getJoint() const
	{
		assert(m_joint);

		return *m_joint;
	}
}
