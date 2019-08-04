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

# include <Siv3D/Physics2D.hpp>
# include <Siv3D/Circle.hpp>
# include <Siv3D/Triangle.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/MultiPolygon.hpp>
# include "Physics2DUtility.hpp"
# include "P2WorldDetail.hpp"
# include "P2BodyDetail.hpp"
# include "P2PivotJointDetail.hpp"
# include "P2DistanceJointDetail.hpp"
# include "P2RopeJointDetail.hpp"
# include "P2SliderJointDetail.hpp"
# include "P2WheelJointDetail.hpp"

namespace s3d
{
	std::array<P2Contact, 2>::const_iterator P2Collision::begin() const noexcept
	{
		return contacts.begin();
	}

	std::array<P2Contact, 2>::const_iterator P2Collision::end() const noexcept
	{
		return contacts.begin() + num_contacts;
	}

	////////////////////////////////////////////////
	//
	// P2World
	//
	////////////////////////////////////////////////

	P2World::P2World(const double gravity)
		: P2World(Vec2(0.0, gravity))
	{

	}

	P2World::P2World(const Vec2& gravity)
		: pImpl(std::make_shared<P2WorldDetail>(gravity))
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

	void P2World::setGravity(const double gravity)
	{
		setGravity(Vec2(0.0, gravity));
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

	P2Body P2World::createDummy(const Vec2& center, const P2BodyType bodyType)
	{
		return pImpl->createDummy(*this, center, bodyType);
	}

	P2Body P2World::createLine(const Vec2& center, const Line& line, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		return pImpl->createLine(*this, center, line, material, filter, bodyType);
	}

	P2Body P2World::createLineString(const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		return pImpl->createLineString(*this, center, lines, material, filter, bodyType);
	}

	P2Body P2World::createClosedLineString(const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		return pImpl->createClosedLineString(*this, center, lines, material, filter, bodyType);
	}

	P2Body P2World::createCircle(const Vec2& center, double r, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		return pImpl->createCircle(*this, center, Circle(r), material, filter, bodyType);
	}

	P2Body P2World::createCircle(const Vec2& center, const Circle& circle, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		return pImpl->createCircle(*this, center, circle, material, filter, bodyType);
	}

	P2Body P2World::createRect(const Vec2& center, const SizeF& size, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		return pImpl->createRect(*this, center, RectF(Arg::center(0, 0), size), material, filter, bodyType);
	}

	P2Body P2World::createRect(const Vec2& center, const RectF& rect, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		return pImpl->createRect(*this, center, rect, material, filter, bodyType);
	}

	P2Body P2World::createTriangle(const Vec2& center, const Triangle& triangle, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		return pImpl->createTriangle(*this, center, triangle, material, filter, bodyType);
	}

	P2Body P2World::createQuad(const Vec2& center, const Quad& quad, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		return pImpl->createQuad(*this, center, quad, material, filter, bodyType);
	}

	P2Body P2World::createPolygon(const Vec2& center, const Polygon& polygon, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		return pImpl->createPolygon(*this, center, polygon, material, filter, bodyType);
	}

	P2Body P2World::createPolygons(const Vec2& center, const MultiPolygon& polygons, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		const size_t num_polygons = polygons.size();

		if (num_polygons == 0)
		{
			return createDummy(center, bodyType);
		}
		else if (num_polygons == 1)
		{
			return createPolygon(center, polygons.front(), material, filter, bodyType);
		}
		else
		{
			P2Body body = createPolygon(center, polygons.front(), material, filter, bodyType);

			for (size_t i = 1; i < num_polygons; ++i)
			{
				body.addPolygon(polygons[i], material, filter);
			}

			return body;
		}
	}

	P2Body P2World::createStaticDummy(const Vec2& center)
	{
		return createDummy(center, P2BodyType::Static);
	}

	P2Body P2World::createStaticLine(const Vec2& center, const Line& line, const P2Material& material, const P2Filter& filter)
	{
		return createLine(center, line, material, filter, P2BodyType::Static);
	}

	P2Body P2World::createStaticLineString(const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter)
	{
		return createLineString(center, lines, material, filter, P2BodyType::Static);
	}

	P2Body P2World::createStaticClosedLineString(const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter)
	{
		return createClosedLineString(center, lines, material, filter, P2BodyType::Static);
	}

	P2Body P2World::createStaticCircle(const Vec2& center, double r, const P2Material& material, const P2Filter& filter)
	{
		return createCircle(center, r, material, filter, P2BodyType::Static);
	}

	P2Body P2World::createStaticCircle(const Vec2& center, const Circle& circle, const P2Material& material, const P2Filter& filter)
	{
		return createCircle(center, circle, material, filter, P2BodyType::Static);
	}

	P2Body P2World::createStaticRect(const Vec2& center, const SizeF& size, const P2Material& material, const P2Filter& filter)
	{
		return createRect(center, size, material, filter, P2BodyType::Static);
	}

	P2Body P2World::createStaticRect(const Vec2& center, const RectF& rect, const P2Material& material, const P2Filter& filter)
	{
		return createRect(center, rect, material, filter, P2BodyType::Static);
	}

	P2Body P2World::createStaticTriangle(const Vec2& center, const Triangle& triangle, const P2Material& material, const P2Filter& filter)
	{
		return createTriangle(center, triangle, material, filter, P2BodyType::Static);
	}

	P2Body P2World::createStaticQuad(const Vec2& center, const Quad& quad, const P2Material& material, const P2Filter& filter)
	{
		return createQuad(center, quad, material, filter, P2BodyType::Static);
	}
	
	P2Body P2World::createStaticPolygon(const Vec2& center, const Polygon& polygon, const P2Material& material, const P2Filter& filter)
	{
		return createPolygon(center, polygon, material, filter, P2BodyType::Static);
	}

	P2Body P2World::createStaticPolygons(const Vec2& center, const MultiPolygon& polygons, const P2Material& material, const P2Filter& filter)
	{
		return createPolygons(center, polygons, material, filter, P2BodyType::Static);
	}


	P2Body P2World::createKinematicDummy(const Vec2& center)
	{
		return createDummy(center, P2BodyType::Kinematic);
	}

	P2Body P2World::createKinematicLine(const Vec2& center, const Line& line, const P2Material& material, const P2Filter& filter)
	{
		return createLine(center, line, material, filter, P2BodyType::Kinematic);
	}

	P2Body P2World::createKinematicLineString(const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter)
	{
		return createLineString(center, lines, material, filter, P2BodyType::Kinematic);
	}

	P2Body P2World::createKinematicClosedLineString(const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter)
	{
		return createClosedLineString(center, lines, material, filter, P2BodyType::Kinematic);
	}

	P2Body P2World::createKinematicCircle(const Vec2& center, double r, const P2Material& material, const P2Filter& filter)
	{
		return createCircle(center, r, material, filter, P2BodyType::Kinematic);
	}

	P2Body P2World::createKinematicCircle(const Vec2& center, const Circle& circle, const P2Material& material, const P2Filter& filter)
	{
		return createCircle(center, circle, material, filter, P2BodyType::Kinematic);
	}

	P2Body P2World::createKinematicRect(const Vec2& center, const SizeF& size, const P2Material& material, const P2Filter& filter)
	{
		return createRect(center, size, material, filter, P2BodyType::Kinematic);
	}

	P2Body P2World::createKinematicRect(const Vec2& center, const RectF& rect, const P2Material& material, const P2Filter& filter)
	{
		return createRect(center, rect, material, filter, P2BodyType::Kinematic);
	}

	P2Body P2World::createKinematicTriangle(const Vec2& center, const Triangle& triangle, const P2Material& material, const P2Filter& filter)
	{
		return createTriangle(center, triangle, material, filter, P2BodyType::Kinematic);
	}

	P2Body P2World::createKinematicQuad(const Vec2& center, const Quad& quad, const P2Material& material, const P2Filter& filter)
	{
		return createQuad(center, quad, material, filter, P2BodyType::Kinematic);
	}

	P2Body P2World::createKinematicPolygon(const Vec2& center, const Polygon& polygon, const P2Material& material, const P2Filter& filter)
	{
		return createPolygon(center, polygon, material, filter, P2BodyType::Kinematic);
	}

	P2Body P2World::createKinematicPolygons(const Vec2& center, const MultiPolygon& polygons, const P2Material& material, const P2Filter& filter)
	{
		return createPolygons(center, polygons, material, filter, P2BodyType::Kinematic);
	}


	P2Body P2World::createDynamicDummy(const Vec2& center)
	{
		return createDummy(center, P2BodyType::Dynamic);
	}

	P2Body P2World::createDynamicLine(const Vec2& center, const Line& line, const P2Material& material, const P2Filter& filter)
	{
		return createLine(center, line, material, filter, P2BodyType::Dynamic);
	}

	P2Body P2World::createDynamicLineString(const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter)
	{
		return createLineString(center, lines, material, filter, P2BodyType::Dynamic);
	}

	P2Body P2World::createDynamicClosedLineString(const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter)
	{
		return createClosedLineString(center, lines, material, filter, P2BodyType::Dynamic);
	}

	P2Body P2World::createDynamicCircle(const Vec2& center, double r, const P2Material& material, const P2Filter& filter)
	{
		return createCircle(center, r, material, filter, P2BodyType::Dynamic);
	}

	P2Body P2World::createDynamicCircle(const Vec2& center, const Circle& circle, const P2Material& material, const P2Filter& filter)
	{
		return createCircle(center, circle, material, filter, P2BodyType::Dynamic);
	}

	P2Body P2World::createDynamicRect(const Vec2& center, const SizeF& size, const P2Material& material, const P2Filter& filter)
	{
		return createRect(center, size, material, filter, P2BodyType::Dynamic);
	}

	P2Body P2World::createDynamicRect(const Vec2& center, const RectF& rect, const P2Material& material, const P2Filter& filter)
	{
		return createRect(center, rect, material, filter, P2BodyType::Dynamic);
	}

	P2Body P2World::createDynamicTriangle(const Vec2& center, const Triangle& triangle, const P2Material& material, const P2Filter& filter)
	{
		return createTriangle(center, triangle, material, filter, P2BodyType::Dynamic);
	}

	P2Body P2World::createDynamicQuad(const Vec2& center, const Quad& quad, const P2Material& material, const P2Filter& filter)
	{
		return createQuad(center, quad, material, filter, P2BodyType::Dynamic);
	}

	P2Body P2World::createDynamicPolygon(const Vec2& center, const Polygon& polygon, const P2Material& material, const P2Filter& filter)
	{
		return createPolygon(center, polygon, material, filter, P2BodyType::Dynamic);
	}

	P2Body P2World::createDynamicPolygons(const Vec2& center, const MultiPolygon& polygons, const P2Material& material, const P2Filter& filter)
	{
		return createPolygons(center, polygons, material, filter, P2BodyType::Dynamic);
	}


	P2PivotJoint P2World::createPivotJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos)
	{
		return pImpl->createPivotJoint(*this, bodyA, bodyB, anchorPos);
	}

	P2DistanceJoint P2World::createDistanceJoint(const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, const double length)
	{
		return pImpl->createDistanceJoint(*this, bodyA, anchorPosA, bodyB, anchorPosB, length);
	}

	P2RopeJoint P2World::createRopeJoint(const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, const double maxLength)
	{
		return pImpl->createRopeJoint(*this, bodyA, anchorPosA, bodyB, anchorPosB, maxLength);
	}

	P2SliderJoint P2World::createSliderJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos, const Vec2& normalizedAxis)
	{
		return pImpl->createSliderJoint(*this, bodyA, bodyB, anchorPos, normalizedAxis);
	}

	const HashTable<P2ContactPair, P2Collision>& P2World::getCollisions() const
	{
		return pImpl->getCollisions();
	}

	b2World* P2World::getWorldPtr() const
	{
		return pImpl->getWorldPtr();
	}

	////////////////////////////////////////////////
	//
	// P2Body
	//
	////////////////////////////////////////////////

	P2Body::P2Body()
		: pImpl(std::make_shared<P2BodyDetail>())
	{

	}

	P2Body::P2Body(P2World& world, P2BodyID id, const Vec2& center, const P2BodyType bodyType)
		: pImpl(std::make_shared<P2BodyDetail>(world, id, center, bodyType))
	{
		pImpl->setUserData(pImpl.get());
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

	P2Body& P2Body::addRect(const SizeF& size, const P2Material& material, const P2Filter& filter)
	{
		return addRect(RectF(Arg::center(0.0, 0.0), size), material, filter);
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

	P2Body& P2Body::addPolygons(const MultiPolygon& polygons, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		for (const auto& polygon : polygons)
		{
			pImpl->addPolygon(polygon, material, filter);
		}

		return *this;
	}

	P2Body& P2Body::setSleepEnabled(bool enabled)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetSleepingAllowed(enabled);
		return *this;
	}

	bool P2Body::getSleepEnabled() const
	{
		if (isEmpty())
		{
			return true;
		}

		return pImpl->getBody().IsSleepingAllowed();
	}

	P2Body& P2Body::setAwake(const bool awake)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetAwake(awake);
		return *this;
	}

	bool P2Body::isAwake() const
	{
		if (isEmpty())
		{
			return true;
		}

		return pImpl->getBody().IsAwake();
	}

	P2Body& P2Body::setPos(const double x, const double y)
	{
		return setPos(Vec2(x, y));
	}

	P2Body& P2Body::setPos(const Vec2& pos)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetTransform(detail::ToB2Vec2(pos), pImpl->getBody().GetAngle());
		return *this;
	}

	P2Body& P2Body::moveBy(const double x, const double y)
	{
		return moveBy(Vec2(x, y));
	}

	P2Body& P2Body::moveBy(const Vec2& v)
	{
		return setPos(getPos() + v);
	}

	P2Body& P2Body::setAngle(const double angle)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetTransform(pImpl->getBody().GetPosition(), static_cast<float32>(angle));
		return *this;
	}

	P2Body& P2Body::rotateBy(const double angle)
	{
		return setAngle(getAngle() + angle);
	}

	P2Body& P2Body::setTransform(const double x, const double y, const double angle)
	{
		return setTransform(Vec2(x, y), angle);
	}

	P2Body& P2Body::setTransform(const Vec2& pos, const double angle)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetTransform(detail::ToB2Vec2(pos), static_cast<float32>(angle));
		return *this;
	}

	P2Body& P2Body::applyForce(const Vec2& force)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyForceToCenter(detail::ToB2Vec2(force), true);
		return *this;
	}

	P2Body& P2Body::applyForce(const Vec2& force, const Vec2& offset)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyForce(detail::ToB2Vec2(force), pImpl->getBody().GetWorldCenter() + detail::ToB2Vec2(offset), true);
		return *this;
	}

	P2Body& P2Body::applyForceAt(const Vec2& force, const Vec2& pos)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyForce(detail::ToB2Vec2(force), detail::ToB2Vec2(pos), true);
		return *this;
	}

	P2Body& P2Body::applyLinearImpulse(const Vec2& force)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyLinearImpulseToCenter(detail::ToB2Vec2(force), true);
		return *this;
	}

	P2Body& P2Body::applyLinearImpulse(const Vec2& force, const Vec2& offset)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyLinearImpulse(detail::ToB2Vec2(force), pImpl->getBody().GetWorldCenter() + detail::ToB2Vec2(offset), true);
		return *this;
	}

	P2Body& P2Body::applyLinearImpulseAt(const Vec2& force, const Vec2& pos)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyLinearImpulse(detail::ToB2Vec2(force), detail::ToB2Vec2(pos), true);
		return *this;
	}

	P2Body& P2Body::applyTorque(const double torque)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyTorque(static_cast<float32>(torque), true);
		return *this;
	}

	P2Body& P2Body::applyAngularImpulse(const double torque)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyAngularImpulse(static_cast<float32>(torque), true);
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

	std::pair<Vec2, double> P2Body::getTransform() const
	{
		if (isEmpty())
		{
			return{ Vec2(0,0), 0.0 };
		}

		return{ detail::ToVec2(pImpl->getBody().GetPosition()), pImpl->getBody().GetAngle() };
	}

	P2Body& P2Body::setVelocity(const Vec2& v)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetLinearVelocity(detail::ToB2Vec2(v));
		return *this;
	}

	Vec2 P2Body::getVelocity() const
	{
		if (isEmpty())
		{
			return Vec2(0, 0);
		}

		return detail::ToVec2(pImpl->getBody().GetLinearVelocity());
	}

	P2Body& P2Body::setAngularVelocity(const double omega)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetAngularVelocity(static_cast<float32>(omega));
		return *this;
	}

	double P2Body::getAngularVelocity() const
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetAngularVelocity();
	}

	P2Body& P2Body::setDamping(double damping)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetLinearDamping(static_cast<float32>(damping));
		return *this;
	}

	double P2Body::getDamping() const
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetLinearDamping();
	}

	P2Body& P2Body::setAngularDamping(const double damping)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetAngularDamping(static_cast<float32>(damping));
		return *this;
	}

	double P2Body::getAngularDamping() const
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetAngularDamping();
	}

	P2Body& P2Body::setGravityScale(const double scale)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetGravityScale(static_cast<float32>(scale));
		return *this;
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

	P2Body& P2Body::setBodyType(P2BodyType bodyType)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetType(static_cast<b2BodyType>(bodyType));
		return *this;
	}

	P2BodyType P2Body::getBodyType() const
	{
		if (isEmpty())
		{
			return P2BodyType::Static;
		}

		return static_cast<P2BodyType>(pImpl->getBody().GetType());
	}

	P2Body& P2Body::setFixedRotation(const bool fixedRotation)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetFixedRotation(fixedRotation);
		return *this;
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

	void P2Body::drawFrame(const double thickness, const ColorF& color) const
	{
		if (isEmpty())
		{
			return;
		}

		for (const auto& shape : pImpl->getShapes())
		{
			shape->drawFrame(thickness, color);
		}
	}

	void P2Body::drawWireframe(const double thickness, const ColorF& color) const
	{
		if (isEmpty())
		{
			return;
		}

		for (const auto& shape : pImpl->getShapes())
		{
			shape->drawWireframe(thickness, color);
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

	P2Shape& P2Body::shape(const size_t index)
	{
		if (isEmpty())
		{
			throw std::out_of_range("P2Body::shape() P2Body is empty.");
		}

		return *pImpl->getShapes()[index];
	}

	const P2Shape& P2Body::shape(const size_t index) const
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

	////////////////////////////////////////////////
	//
	// P2Shape
	//
	////////////////////////////////////////////////

	void P2Shape::setDensity(const double density)
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

	void P2Shape::setFriction(const double friction)
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

	void P2Shape::setRestitution(const double restitution)
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

	////////////////////////////////////////////////
	//
	// P2Line
	//
	////////////////////////////////////////////////

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
		getLine().draw(detail::P2LineThickness / Graphics2D::GetMaxScaling(), color);
	}

	void P2Line::drawFrame(const double thickness, const ColorF& color) const
	{
		getLine().draw(thickness / Graphics2D::GetMaxScaling(), color);
	}

	void P2Line::drawWireframe(const double thickness, const ColorF& color) const
	{
		drawFrame(thickness, color);
	}

	Line P2Line::getLine() const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
		return Line(detail::CalcVec2(m_pShape->m_vertex1, transform), detail::CalcVec2(m_pShape->m_vertex2, transform));
	}

	////////////////////////////////////////////////
	//
	// P2LineString
	//
	////////////////////////////////////////////////

	P2LineString::P2LineString(b2Body& body, const LineString& lines, const bool closed, const P2Material& material, const P2Filter& filter)
		: m_pShape(std::make_unique<b2ChainShape>())
		, m_closed(closed)
	{
		Array<b2Vec2> points(lines.size());

		for (size_t i = 0; i < lines.size(); ++i)
		{
			points[i].Set(static_cast<float32>(lines[i].x), static_cast<float32>(lines[i].y));
		}

		m_lineString.resize(points.size() + m_closed);

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

	bool P2LineString::isClosed() const
	{
		return m_closed;
	}

	void P2LineString::draw(const ColorF& color) const
	{
		if (m_closed)
		{
			getLineString().drawClosed(detail::P2LineThickness / Graphics2D::GetMaxScaling(), color);
		}
		else
		{
			getLineString().draw(detail::P2LineThickness / Graphics2D::GetMaxScaling(), color);
		}
	}

	void P2LineString::drawFrame(const double thickness, const ColorF& color) const
	{
		if (m_closed)
		{
			getLineString().drawClosed(thickness / Graphics2D::GetMaxScaling(), color);
		}
		else
		{
			getLineString().draw(thickness / Graphics2D::GetMaxScaling(), color);
		}
	}

	void P2LineString::drawWireframe(const double thickness, const ColorF& color) const
	{
		drawFrame(thickness, color);
	}

	const LineString& P2LineString::getLineString() const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
		Vec2* pDst = m_lineString.data();
		const b2Vec2* pSrc = m_pShape->m_vertices;

		for (int32 i = 0; i < m_pShape->m_count; ++i)
		{
			*pDst++ = detail::CalcVec2(*pSrc++, transform);
		}

		return m_lineString;
	}

	////////////////////////////////////////////////
	//
	// P2Circle
	//
	////////////////////////////////////////////////

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

	void P2Circle::drawFrame(const double thickness, const ColorF& color) const
	{
		getCircle().drawFrame(thickness / Graphics2D::GetMaxScaling(), color);
	}

	void P2Circle::drawWireframe(const double thickness, const ColorF& color) const
	{
		drawFrame(thickness, color);
	}

	Circle P2Circle::getCircle() const
	{
		return Circle(detail::CalcVec2(m_pShape->m_p, m_fixtures.fixtures[0]->GetBody()->GetTransform()), m_pShape->m_radius);
	}

	////////////////////////////////////////////////
	//
	// P2Rect
	//
	////////////////////////////////////////////////

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

	void P2Rect::draw(const ColorF(&colors)[4]) const
	{
		getQuad().draw(colors[0], colors[1], colors[2], colors[3]);
	}

	void P2Rect::draw(Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const
	{
		draw({ *topColor, *topColor, *bottomColor, *bottomColor });
	}

	void P2Rect::draw(Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const
	{
		draw({ *leftColor, *rightColor, *rightColor, *leftColor });
	}

	void P2Rect::drawFrame(const double thickness, const ColorF& color) const
	{
		getQuad().drawFrame(thickness / Graphics2D::GetMaxScaling(), color);
	}

	void P2Rect::drawWireframe(const double thickness, const ColorF& color) const
	{
		getQuad().drawFrame(thickness / Graphics2D::GetMaxScaling(), color);
	}

	Quad P2Rect::getQuad() const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
		return Quad(
			detail::CalcVec2(m_pShape->m_vertices[0], transform),
			detail::CalcVec2(m_pShape->m_vertices[1], transform),
			detail::CalcVec2(m_pShape->m_vertices[2], transform),
			detail::CalcVec2(m_pShape->m_vertices[3], transform));
	}

	////////////////////////////////////////////////
	//
	// P2Triangle
	//
	////////////////////////////////////////////////

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

	void P2Triangle::drawFrame(const double thickness, const ColorF& color) const
	{
		getTriangle().drawFrame(thickness / Graphics2D::GetMaxScaling(), color);
	}

	void P2Triangle::drawWireframe(const double thickness, const ColorF& color) const
	{
		drawFrame(thickness, color);
	}

	Triangle P2Triangle::getTriangle() const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
		return Triangle(
			detail::CalcVec2(m_pShape->m_vertices[0], transform),
			detail::CalcVec2(m_pShape->m_vertices[1], transform),
			detail::CalcVec2(m_pShape->m_vertices[2], transform));
	}

	////////////////////////////////////////////////
	//
	// P2Quad
	//
	////////////////////////////////////////////////

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

	void P2Quad::drawFrame(const double thickness, const ColorF& color) const
	{
		getQuad().drawFrame(thickness / Graphics2D::GetMaxScaling(), color);
	}

	void P2Quad::drawWireframe(const double thickness, const ColorF& color) const
	{
		drawFrame(thickness, color);
	}

	Quad P2Quad::getQuad() const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();
		return Quad(
			detail::CalcVec2(m_pShape->m_vertices[0], transform),
			detail::CalcVec2(m_pShape->m_vertices[1], transform),
			detail::CalcVec2(m_pShape->m_vertices[2], transform),
			detail::CalcVec2(m_pShape->m_vertices[3], transform));
	}

	////////////////////////////////////////////////
	//
	// P2Polygon
	//
	////////////////////////////////////////////////

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

	void P2Polygon::drawFrame(const double thickness, const ColorF& color) const
	{
		getPolygon().drawFrame(thickness / Graphics2D::GetMaxScaling(), color);
	}

	void P2Polygon::drawWireframe(const double thickness, const ColorF& color) const
	{
		getPolygon().drawWireframe(thickness / Graphics2D::GetMaxScaling(), color);
	}

	Polygon P2Polygon::getPolygon() const
	{
		const b2Transform& transform = m_fixtures.fixtures[0]->GetBody()->GetTransform();

		return m_basePolygon.transformed(transform.q.s, transform.q.c, Vec2(transform.p.x, transform.p.y));
	}

	////////////////////////////////////////////////
	//
	// P2PivotJoint
	//
	////////////////////////////////////////////////

	P2PivotJoint::P2PivotJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos)
		: pImpl(std::make_shared<P2PivotJointDetail>(world, bodyA, bodyB, anchorPos))
	{

	}

	Vec2 P2PivotJoint::getAnchorPos() const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorA());
	}

	double P2PivotJoint::getJointAngle() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointAngle();
	}

	double P2PivotJoint::getJointAngleSpeed() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointSpeed();
	}

	P2PivotJoint& P2PivotJoint::setLimitEnabled(const bool enabled)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().EnableLimit(enabled);
		return *this;
	}

	bool P2PivotJoint::getLimitEnabled() const
	{
		if (!pImpl)
		{
			return false;
		}

		return pImpl->getJoint().IsLimitEnabled();
	}

	P2PivotJoint& P2PivotJoint::setLimits(const double lower, const double upper)
	{
		if (!pImpl)
		{
			return * this;
		}

		pImpl->getJoint().SetLimits(static_cast<float32>(lower), static_cast<float32>(upper));
		return *this;
	}

	std::pair<double, double> P2PivotJoint::getLimits() const
	{
		if (!pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return{ pImpl->getJoint().GetLowerLimit(), pImpl->getJoint().GetLowerLimit() };
	}

	P2PivotJoint& P2PivotJoint::setMotorEnabled(const bool enabled)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().EnableMotor(enabled);
		return *this;
	}

	bool P2PivotJoint::getMotorEnabled() const
	{
		if (!pImpl)
		{
			return false;
		}

		return pImpl->getJoint().IsMotorEnabled();
	}

	P2PivotJoint& P2PivotJoint::setMotorSpeed(const double speed)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMotorSpeed(static_cast<float32>(speed));
		return *this;
	}

	double P2PivotJoint::getMotorSpeed() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMotorSpeed();
	}

	P2PivotJoint& P2PivotJoint::setMaxMotorTorque(const double torque)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMaxMotorTorque(static_cast<float32>(torque));
		return *this;
	}

	double P2PivotJoint::getMaxMotorTorque() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMaxMotorTorque();
	}

	Vec2 P2PivotJoint::getReactionForce(const double inv_dt) const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetReactionForce(static_cast<float32>(inv_dt)));
	}

	double P2PivotJoint::getReactionTorque(const double inv_dt) const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetReactionTorque(static_cast<float32>(inv_dt));
	}

	double P2PivotJoint::getMotorTorque(const double inv_dt) const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMotorTorque(static_cast<float32>(inv_dt));
	}

	void P2PivotJoint::draw(const ColorF& color) const
	{
		if (!pImpl)
		{
			return;
		}

		const Vec2 anchorPos = detail::ToVec2(pImpl->getJoint().GetAnchorA());
		Circle(anchorPos, detail::P2AnchorR / Graphics2D::GetMaxScaling()).draw(color);
	}

	////////////////////////////////////////////////
	//
	// P2DistanceJoint
	//
	////////////////////////////////////////////////

	P2DistanceJoint::P2DistanceJoint(P2World& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, const double length)
		: pImpl(std::make_shared<P2DistanceJointDetail>(world, bodyA, anchorPosA, bodyB, anchorPosB, length))
	{

	}

	Vec2 P2DistanceJoint::getAnchorPosA() const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorA());
	}

	Vec2 P2DistanceJoint::getAnchorPosB() const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorB());
	}

	Vec2 P2DistanceJoint::getReactionForce(const double inv_dt) const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetReactionForce(static_cast<float32>(inv_dt)));
	}

	double P2DistanceJoint::getReactionTorque(const double inv_dt) const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetReactionTorque(static_cast<float32>(inv_dt));
	}

	P2DistanceJoint& P2DistanceJoint::setLength(const double length)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetLength(static_cast<float32>(length));
		return *this;
	}

	double P2DistanceJoint::getLength() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetLength();
	}

	P2DistanceJoint& P2DistanceJoint::setFrequencyHz(const double hz)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetFrequency(static_cast<float32>(hz));
		return *this;
	}

	double P2DistanceJoint::getFrequencyHz() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetFrequency();
	}

	P2DistanceJoint& P2DistanceJoint::setDampingRatio(const double ratio)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetDampingRatio(static_cast<float32>(ratio));
		return *this;
	}

	double P2DistanceJoint::getDampingRatio() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetDampingRatio();
	}

	void P2DistanceJoint::draw(const ColorF& color) const
	{
		if (!pImpl)
		{
			return;
		}

		const Vec2 anchorPosA = detail::ToVec2(pImpl->getJoint().GetAnchorA());
		const Vec2 anchorPosB = detail::ToVec2(pImpl->getJoint().GetAnchorB());

		const double scale = 1.0 / Graphics2D::GetMaxScaling();
		Circle(anchorPosA, detail::P2AnchorR * scale).draw(color);
		Circle(anchorPosB, detail::P2AnchorR * scale).draw(color);
		Line(anchorPosA, anchorPosB).draw(detail::P2LineThickness * scale, color);
	}

	////////////////////////////////////////////////
	//
	// P2RopeJoint
	//
	////////////////////////////////////////////////

	P2RopeJoint::P2RopeJoint(P2World& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, const double maxLength)
		: pImpl(std::make_shared<P2RopeJointDetail>(world, bodyA, anchorPosA, bodyB, anchorPosB, maxLength))
	{

	}

	Vec2 P2RopeJoint::getAnchorPosA() const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorA());
	}

	Vec2 P2RopeJoint::getAnchorPosB() const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorB());
	}

	Vec2 P2RopeJoint::getReactionForce(const double inv_dt) const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetReactionForce(static_cast<float32>(inv_dt)));
	}

	double P2RopeJoint::getReactionTorque(const double inv_dt) const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetReactionTorque(static_cast<float32>(inv_dt));
	}

	P2RopeJoint& P2RopeJoint::setMaxLength(const double maxLength)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMaxLength(static_cast<float32>(maxLength));
		return *this;
	}

	double P2RopeJoint::getMaxLength() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMaxLength();
	}

	void P2RopeJoint::draw(const ColorF& color) const
	{
		if (!pImpl)
		{
			return;
		}

		const Vec2 anchorPosA = detail::ToVec2(pImpl->getJoint().GetAnchorA());
		const Vec2 anchorPosB = detail::ToVec2(pImpl->getJoint().GetAnchorB());

		const double scale = 1.0 / Graphics2D::GetMaxScaling();
		Circle(anchorPosA, detail::P2AnchorR * scale).draw(color);
		Circle(anchorPosB, detail::P2AnchorR * scale).draw(color);
		Line(anchorPosA, anchorPosB).draw(detail::P2LineThickness * scale, color);
	}

	////////////////////////////////////////////////
	//
	// P2SliderJoint
	//
	////////////////////////////////////////////////

	P2SliderJoint::P2SliderJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos, const Vec2& normalizedAxis)
		: pImpl(std::make_shared<P2SliderJointDetail>(world, bodyA, bodyB, anchorPos, normalizedAxis))
	{

	}

	Vec2 P2SliderJoint::getAnchorPosA() const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorA());
	}

	Vec2 P2SliderJoint::getAnchorPosB() const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorB());
	}

	double P2SliderJoint::getJointTranslation() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointTranslation();
	}

	double P2SliderJoint::getJointSpeed() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointSpeed();
	}

	P2SliderJoint& P2SliderJoint::setLimitEnabled(const bool enabled)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().EnableLimit(enabled);
		return *this;
	}

	bool P2SliderJoint::getLimitEnabled() const
	{
		if (!pImpl)
		{
			return false;
		}

		return pImpl->getJoint().IsLimitEnabled();
	}

	P2SliderJoint& P2SliderJoint::setLimits(const double lower, const double upper)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetLimits(static_cast<float32>(lower), static_cast<float32>(upper));
		return *this;
	}

	std::pair<double, double> P2SliderJoint::getLimits() const
	{
		if (!pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return{ pImpl->getJoint().GetLowerLimit(), pImpl->getJoint().GetLowerLimit() };
	}

	P2SliderJoint& P2SliderJoint::setMotorEnabled(const bool enabled)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().EnableMotor(enabled);
		return *this;
	}

	bool P2SliderJoint::getMotorEnabled() const
	{
		if (!pImpl)
		{
			return false;
		}

		return pImpl->getJoint().IsMotorEnabled();
	}

	P2SliderJoint& P2SliderJoint::setMotorSpeed(const double speed)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMotorSpeed(static_cast<float32>(speed));
		return *this;
	}

	double P2SliderJoint::getMotorSpeed() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMotorSpeed();
	}

	P2SliderJoint& P2SliderJoint::setMaxMotorForce(const double force)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMaxMotorForce(static_cast<float32>(force));
		return *this;
	}

	double P2SliderJoint::getMaxMotorForce() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMaxMotorForce();
	}

	double P2SliderJoint::getMotorForce(const double inv_dt) const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMotorForce(static_cast<float32>(inv_dt));
	}

	Vec2 P2SliderJoint::getReactionForce(const double inv_dt) const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetReactionForce(static_cast<float32>(inv_dt)));
	}

	double P2SliderJoint::getReactionTorque(const double inv_dt) const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetReactionTorque(static_cast<float32>(inv_dt));
	}

	void P2SliderJoint::draw(const ColorF& color) const
	{
		if (!pImpl)
		{
			return;
		}

		const Vec2 anchorPosA = detail::ToVec2(pImpl->getJoint().GetAnchorA());
		const Vec2 anchorPosB = detail::ToVec2(pImpl->getJoint().GetAnchorB());

		const double scale = 1.0 / Graphics2D::GetMaxScaling();
		Circle(anchorPosA, detail::P2AnchorR * scale).draw(color);
		Circle(anchorPosB, detail::P2AnchorR * scale).draw(color);
		Line(anchorPosA, anchorPosB).draw(detail::P2LineThickness * scale, color);
	}

	////////////////////////////////////////////////
	//
	// P2WheelJoint
	//
	////////////////////////////////////////////////

	P2WheelJoint::P2WheelJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchor, const Vec2& axis)
		: pImpl(std::make_shared<P2WheelJointDetail>(world, bodyA, bodyB, anchor, axis))
	{

	}

	Vec2 P2WheelJoint::getAnchorPosA() const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorA());
	}

	Vec2 P2WheelJoint::getAnchorPosB() const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorB());
	}

	Vec2 P2WheelJoint::getReactionForce(const double inv_dt) const
	{
		if (!pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetReactionForce(static_cast<float32>(inv_dt)));
	}

	double P2WheelJoint::getReactionTorque(const double inv_dt) const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetReactionTorque(static_cast<float32>(inv_dt));
	}

	double P2WheelJoint::getJointTranslation() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointTranslation();
	}

	double P2WheelJoint::getJointLinearSpeed() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointLinearSpeed();
	}

	double P2WheelJoint::getJointAngle() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointAngle();
	}

	double P2WheelJoint::getJointAngularSpeed() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointAngularSpeed();
	}

	P2WheelJoint& P2WheelJoint::setMotorEnabled(const bool enabled)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().EnableMotor(enabled);
		return *this;
	}

	bool P2WheelJoint::getMotorEnabled() const
	{
		if (!pImpl)
		{
			return false;
		}

		return pImpl->getJoint().IsMotorEnabled();
	}

	P2WheelJoint& P2WheelJoint::setMotorSpeed(const double speed)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMotorSpeed(static_cast<float32>(speed));
		return *this;
	}

	double P2WheelJoint::getMotorSpeed() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMotorSpeed();
	}

	P2WheelJoint& P2WheelJoint::setMaxMotorTorque(const double torque)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMaxMotorTorque(static_cast<float32>(torque));
		return *this;
	}

	double P2WheelJoint::getMaxMotorTorque() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMaxMotorTorque();
	}

	double P2WheelJoint::getMotorTorque(const double inv_dt) const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMotorTorque(static_cast<float32>(inv_dt));
	}

	P2WheelJoint& P2WheelJoint::setSpringFrequencyHz(const double hz)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetSpringFrequencyHz(static_cast<float32>(hz));
		return *this;
	}

	double P2WheelJoint::getSpringFrequencyHz() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetSpringFrequencyHz();
	}

	P2WheelJoint& P2WheelJoint::setSpringDampingRatio(const double ratio)
	{
		if (!pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetSpringDampingRatio(static_cast<float32>(ratio));
		return *this;
	}

	double P2WheelJoint::getSpringDampingRatio() const
	{
		if (!pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetSpringDampingRatio();
	}

	void P2WheelJoint::draw(const ColorF& color) const
	{
		if (!pImpl)
		{
			return;
		}

		const Vec2 anchorPosA = detail::ToVec2(pImpl->getJoint().GetAnchorA());
		const Vec2 anchorPosB = detail::ToVec2(pImpl->getJoint().GetAnchorB());

		const double scale = 1.0 / Graphics2D::GetMaxScaling();
		Circle(anchorPosA, detail::P2AnchorR * scale).draw(color);
		Circle(anchorPosB, detail::P2AnchorR * scale).draw(color);
		Line(anchorPosA, anchorPosB).draw(detail::P2LineThickness * scale, color);
	}
}
