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

# include <Siv3D/Physics2D/P2Body.hpp>
# include <Siv3D/Physics2D/P2BodyType.hpp>
# include <Siv3D/Physics2D/P2Shape.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/MultiPolygon.hpp>
# include "P2BodyDetail.hpp"

namespace s3d
{
	P2Body::P2Body()
		: pImpl{ std::make_shared<P2BodyDetail>() } {}

	P2Body::P2Body(const std::shared_ptr<detail::P2WorldDetail>& world, const P2BodyID id, const Vec2& center, const P2BodyType bodyType)
		: pImpl{ std::make_shared<P2BodyDetail>(world, id, center, bodyType) } {}

	P2BodyID P2Body::id() const noexcept
	{
		return pImpl->id();
	}

	bool P2Body::isEmpty() const noexcept
	{
		return (pImpl->id() == 0);
	}

	void P2Body::release()
	{
		if (isEmpty())
		{
			return;
		}

		pImpl = std::make_shared<P2BodyDetail>();
	}

	P2Body::operator bool() const noexcept
	{
		return (pImpl->id() != 0);
	}

	P2Body& P2Body::addLine(const Line& localPos, const OneSided oneSided, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addLine(localPos, oneSided, material, filter);

		return *this;
	}

	P2Body& P2Body::addLineSensor(const Line& localPos, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addLineSensor(localPos, filter);

		return *this;
	}

	P2Body& P2Body::addLineString(const LineString& localPos, const OneSided oneSided, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		if (localPos.size() < 2)
		{
			return *this;
		}

		pImpl->addLineString(localPos, CloseRing::No, oneSided, material, filter);

		return *this;
	}

	P2Body& P2Body::addLineStringSensor(const LineString& localPos, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		if (localPos.size() < 2)
		{
			return *this;
		}

		pImpl->addLineStringSensor(localPos, CloseRing::No, filter);

		return *this;
	}

	P2Body& P2Body::addClosedLineString(const LineString& localPos, const OneSided oneSided, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		if (localPos.size() < 2)
		{
			return *this;
		}

		pImpl->addLineString(localPos, CloseRing::Yes, oneSided, material, filter);

		return *this;
	}

	P2Body& P2Body::addClosedLineStringSensor(const LineString& localPos, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		if (localPos.size() < 2)
		{
			return *this;
		}

		pImpl->addLineStringSensor(localPos, CloseRing::Yes, filter);

		return *this;
	}

	P2Body& P2Body::addCircle(const Circle& localPos, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addCircle(localPos, material, filter);

		return *this;
	}

	P2Body& P2Body::addCircleSensor(const Circle& localPos, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addCircleSensor(localPos, filter);

		return *this;
	}

	P2Body& P2Body::addRect(const RectF& localPos, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addRect(localPos, material, filter);

		return *this;
	}

	P2Body& P2Body::addRectSensor(const RectF& localPos, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addRectSensor(localPos, filter);

		return *this;
	}

	P2Body& P2Body::addTriangle(const Triangle& localPos, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addTriangle(localPos, material, filter);

		return *this;
	}

	P2Body& P2Body::addTriangleSensor(const Triangle& localPos, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addTriangleSensor(localPos, filter);

		return *this;
	}

	P2Body& P2Body::addQuad(const Quad& localPos, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addQuad(localPos, material, filter);

		return *this;
	}

	P2Body& P2Body::addQuadSensor(const Quad& localPos, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addQuadSensor(localPos, filter);

		return *this;
	}

	P2Body& P2Body::addPolygon(const Polygon& localPos, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addPolygon(localPos, material, filter);

		return *this;
	}

	P2Body& P2Body::addPolygonSensor(const Polygon& localPos, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->addPolygonSensor(localPos, filter);

		return *this;
	}

	P2Body& P2Body::addPolygons(const MultiPolygon& localPos, const P2Material& material, const P2Filter& filter)
	{
		if (isEmpty())
		{
			return *this;
		}

		for (const auto& polygon : localPos)
		{
			pImpl->addPolygon(polygon, material, filter);
		}

		return *this;
	}

	P2Body& P2Body::setSleepEnabled(const bool enabled) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetSleepingAllowed(enabled);
		return *this;
	}

	bool P2Body::getSleepEnabled() const noexcept
	{
		if (isEmpty())
		{
			return true;
		}

		return pImpl->getBody().IsSleepingAllowed();
	}

	P2Body& P2Body::setAwake(const bool awake) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetAwake(awake);
		return *this;
	}

	bool P2Body::isAwake() const noexcept
	{
		if (isEmpty())
		{
			return true;
		}

		return pImpl->getBody().IsAwake();
	}

	P2Body& P2Body::setPos(const double x, const double y) noexcept
	{
		return setPos(Vec2{ x, y });
	}

	P2Body& P2Body::setPos(const Vec2 pos) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetTransform(detail::ToB2Vec2(pos), pImpl->getBody().GetAngle());
		return *this;
	}

	P2Body& P2Body::moveBy(const double x, const double y) noexcept
	{
		return moveBy(Vec2{ x, y });
	}

	P2Body& P2Body::moveBy(const Vec2 v) noexcept
	{
		return setPos(getPos() + v);
	}

	P2Body& P2Body::setAngle(const double angle) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetTransform(pImpl->getBody().GetPosition(), static_cast<float>(angle));
		return *this;
	}

	P2Body& P2Body::rotateBy(const double angle) noexcept
	{
		return setAngle(getAngle() + angle);
	}

	P2Body& P2Body::setTransform(const double x, const double y, const double angle) noexcept
	{
		return setTransform(Vec2{ x, y }, angle);
	}

	P2Body& P2Body::setTransform(const Vec2 pos, const double angle) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetTransform(detail::ToB2Vec2(pos), static_cast<float>(angle));
		return *this;
	}

	P2Body& P2Body::applyForce(const Vec2 force) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyForceToCenter(detail::ToB2Vec2(force), true);
		return *this;
	}

	P2Body& P2Body::applyForce(const Vec2 force, const Vec2 offset) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyForce(detail::ToB2Vec2(force), pImpl->getBody().GetWorldCenter() + detail::ToB2Vec2(offset), true);
		return *this;
	}

	P2Body& P2Body::applyForceAt(const Vec2 force, const Vec2 pos) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyForce(detail::ToB2Vec2(force), detail::ToB2Vec2(pos), true);
		return *this;
	}

	P2Body& P2Body::applyLinearImpulse(const Vec2 force) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyLinearImpulseToCenter(detail::ToB2Vec2(force), true);
		return *this;
	}

	P2Body& P2Body::applyLinearImpulse(const Vec2 force, const Vec2 offset) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyLinearImpulse(detail::ToB2Vec2(force), pImpl->getBody().GetWorldCenter() + detail::ToB2Vec2(offset), true);
		return *this;
	}

	P2Body& P2Body::applyLinearImpulseAt(const Vec2 force, const Vec2 pos) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyLinearImpulse(detail::ToB2Vec2(force), detail::ToB2Vec2(pos), true);
		return *this;
	}

	P2Body& P2Body::applyTorque(const double torque) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyTorque(static_cast<float>(torque), true);
		return *this;
	}

	P2Body& P2Body::applyAngularImpulse(const double torque) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().ApplyAngularImpulse(static_cast<float>(torque), true);
		return *this;
	}

	Vec2 P2Body::getPos() const noexcept
	{
		if (isEmpty())
		{
			return{ 0, 0 };
		}

		return detail::ToVec2(pImpl->getBody().GetPosition());
	}

	double P2Body::getAngle() const noexcept
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetAngle();
	}

	std::pair<Vec2, double> P2Body::getTransform() const noexcept
	{
		if (isEmpty())
		{
			return{ Vec2{ 0, 0 }, 0.0 };
		}

		return{ detail::ToVec2(pImpl->getBody().GetPosition()), pImpl->getBody().GetAngle() };
	}

	P2Body& P2Body::setVelocity(const Vec2 v) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetLinearVelocity(detail::ToB2Vec2(v));
		return *this;
	}

	Vec2 P2Body::getVelocity() const noexcept
	{
		if (isEmpty())
		{
			return{ 0, 0 };
		}

		return detail::ToVec2(pImpl->getBody().GetLinearVelocity());
	}

	P2Body& P2Body::setAngularVelocity(const double omega) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetAngularVelocity(static_cast<float>(omega));
		return *this;
	}

	double P2Body::getAngularVelocity() const noexcept
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetAngularVelocity();
	}

	P2Body& P2Body::setDamping(const double damping) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetLinearDamping(static_cast<float>(damping));
		return *this;
	}

	double P2Body::getDamping() const noexcept
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetLinearDamping();
	}

	P2Body& P2Body::setAngularDamping(const double damping) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetAngularDamping(static_cast<float>(damping));
		return *this;
	}

	double P2Body::getAngularDamping() const noexcept
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetAngularDamping();
	}

	P2Body& P2Body::setGravityScale(const double scale) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetGravityScale(static_cast<float>(scale));
		return *this;
	}

	double P2Body::getGravityScale() const noexcept
	{
		if (isEmpty())
		{
			return 1.0;
		}

		return pImpl->getBody().GetGravityScale();
	}

	double P2Body::getMass() const noexcept
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetMass();
	}

	double P2Body::getInertia() const noexcept
	{
		if (isEmpty())
		{
			return 0.0;
		}

		return pImpl->getBody().GetInertia();
	}

	P2Body& P2Body::setBodyType(const P2BodyType bodyType) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetType(static_cast<b2BodyType>(bodyType));
		return *this;
	}

	P2BodyType P2Body::getBodyType() const noexcept
	{
		if (isEmpty())
		{
			return P2BodyType::Static;
		}

		return static_cast<P2BodyType>(pImpl->getBody().GetType());
	}

	P2Body& P2Body::setBullet(const bool bullet) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetBullet(bullet);
		return *this;
	}

	bool P2Body::isBullet() const noexcept
	{
		if (isEmpty())
		{
			return false;
		}

		return pImpl->getBody().IsBullet();
	}

	P2Body& P2Body::setFixedRotation(const bool fixedRotation) noexcept
	{
		if (isEmpty())
		{
			return *this;
		}

		pImpl->getBody().SetFixedRotation(fixedRotation);
		return *this;
	}

	bool P2Body::isFixedRotation() const noexcept
	{
		if (isEmpty())
		{
			return false;
		}

		return pImpl->getBody().IsFixedRotation();
	}

	const P2Body& P2Body::draw(const ColorF& color) const
	{
		if (isEmpty())
		{
			return *this;
		}

		for (const auto& shape : pImpl->getShapes())
		{
			shape->draw(color);
		}

		return *this;
	}

	const P2Body& P2Body::drawFrame(const double thickness, const ColorF& color) const
	{
		if (isEmpty())
		{
			return *this;
		}

		for (const auto& shape : pImpl->getShapes())
		{
			shape->drawFrame(thickness, color);
		}

		return *this;
	}

	const P2Body& P2Body::drawWireframe(const double thickness, const ColorF& color) const
	{
		if (isEmpty())
		{
			return *this;
		}

		for (const auto& shape : pImpl->getShapes())
		{
			shape->drawWireframe(thickness, color);
		}

		return *this;
	}

	size_t P2Body::num_shapes() const noexcept
	{
		if (isEmpty())
		{
			return 0;
		}

		return pImpl->getShapes().size();
	}

	P2Shape& P2Body::shape(const size_t index)
	{
		if (num_shapes() <= index)
		{
			throw std::out_of_range{ "P2Body::shape(): index out out range" };
		}

		return *pImpl->getShapes()[index];
	}

	const P2Shape& P2Body::shape(const size_t index) const
	{
		if (num_shapes() <= index)
		{
			throw std::out_of_range{ "P2Body::shape(): index out out range" };
		}

		return *pImpl->getShapes()[index];
	}

	const std::shared_ptr<P2Shape>& P2Body::getPtr(const size_t index) const noexcept
	{
		return pImpl->getShapes()[index];
	}

	std::weak_ptr<P2Body::P2BodyDetail> P2Body::getWeakPtr() const
	{
		return pImpl;
	}
}
