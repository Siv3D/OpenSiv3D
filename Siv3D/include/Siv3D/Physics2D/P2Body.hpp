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
# include <memory>
# include "../Common.hpp"
# include "../2DShapesFwd.hpp"
# include "../ColorHSV.hpp"
# include "../PredefinedYesNo.hpp"
# include "P2Fwd.hpp"
# include "P2Material.hpp"
# include "P2Filter.hpp"

namespace s3d
{
	class P2Body
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2Body();

		[[nodiscard]]
		P2BodyID id() const noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		void release();

		P2Body& addLine(const Line& localPos, OneSided oneSided, const P2Material& material = {}, const P2Filter& filter = {});

		P2Body& addLineString(const LineString& localPos, OneSided oneSided, const P2Material& material = {}, const P2Filter& filter = {});

		P2Body& addClosedLineString(const LineString& localPos, OneSided oneSided, const P2Material& material = {}, const P2Filter& filter = {});

		P2Body& addCircle(const Circle& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		P2Body& addCircleSensor(const Circle& localPos, const P2Filter& filter = {});

		P2Body& addRect(const RectF& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		P2Body& addTriangle(const Triangle& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		P2Body& addQuad(const Quad& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		P2Body& addPolygon(const Polygon& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		P2Body& addPolygons(const MultiPolygon& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		P2Body& setSleepEnabled(bool enabled) noexcept;

		[[nodiscard]]
		bool getSleepEnabled() const noexcept;

		P2Body& setAwake(bool awake) noexcept;

		[[nodiscard]]
		bool isAwake() const noexcept;

		P2Body& setPos(double x, double y) noexcept;

		P2Body& setPos(Vec2 pos) noexcept;

		P2Body& moveBy(double x, double y) noexcept;

		P2Body& moveBy(Vec2 v) noexcept;

		P2Body& setAngle(double angle) noexcept;

		P2Body& rotateBy(double angle) noexcept;

		P2Body& setTransform(double x, double y, double angle) noexcept;

		P2Body& setTransform(Vec2 pos, double angle) noexcept;

		P2Body& applyForce(Vec2 force) noexcept;

		P2Body& applyForce(Vec2 force, Vec2 offset) noexcept;

		P2Body& applyForceAt(Vec2 force, Vec2 pos) noexcept;

		P2Body& applyLinearImpulse(Vec2 force) noexcept;

		P2Body& applyLinearImpulse(Vec2 force, Vec2 offset) noexcept;

		P2Body& applyLinearImpulseAt(Vec2 force, Vec2 pos) noexcept;

		P2Body& applyTorque(double torque) noexcept;

		P2Body& applyAngularImpulse(double torque) noexcept;

		[[nodiscard]]
		Vec2 getPos() const noexcept;

		[[nodiscard]]
		double getAngle() const noexcept;

		[[nodiscard]]
		std::pair<Vec2, double> getTransform() const noexcept;

		P2Body& setVelocity(Vec2 v) noexcept;

		[[nodiscard]]
		Vec2 getVelocity() const noexcept;

		P2Body& setAngularVelocity(double omega) noexcept;

		[[nodiscard]]
		double getAngularVelocity() const noexcept;

		P2Body& setDamping(double damping) noexcept;

		[[nodiscard]]
		double getDamping() const noexcept;

		P2Body& setAngularDamping(double damping) noexcept;

		[[nodiscard]]
		double getAngularDamping() const noexcept;

		P2Body& setGravityScale(double scale) noexcept;

		[[nodiscard]]
		double getGravityScale() const noexcept;

		[[nodiscard]]
		double getMass() const noexcept;

		[[nodiscard]]
		double getInertia() const noexcept;

		P2Body& setBodyType(P2BodyType bodyType) noexcept;

		[[nodiscard]]
		P2BodyType getBodyType() const noexcept;

		P2Body& setFixedRotation(bool fixedRotation) noexcept;

		[[nodiscard]]
		bool isFixedRotation() const noexcept;

		const P2Body& draw(const ColorF& color = Palette::White) const;

		const P2Body& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		const P2Body& drawWireframe(double thickness = 1.0, const ColorF& color = Palette::White) const;

		[[nodiscard]]
		size_t num_shapes() const noexcept;

		[[nodiscard]]
		P2Shape& shape(size_t index);

		[[nodiscard]]
		const P2Shape& shape(size_t index) const;

		[[nodiscard]]
		const std::shared_ptr<P2Shape>& getPtr(size_t index) const noexcept;

		template <class PShape, std::enable_if_t<std::is_base_of_v<P2Shape, PShape>>* = nullptr>
		std::shared_ptr<PShape> as(size_t index) const;

	private:

		class P2BodyDetail;

		std::shared_ptr<P2BodyDetail> pImpl;

		friend class detail::P2WorldDetail;
		friend class detail::P2ContactListener;
		friend class detail::P2PivotJointDetail;
		friend class detail::P2DistanceJointDetail;
		friend class detail::P2SliderJointDetail;
		friend class detail::P2WheelJointDetail;
		friend class detail::P2MouseJointDetail;

		SIV3D_NODISCARD_CXX20
		P2Body(const std::shared_ptr<detail::P2WorldDetail>& world, P2BodyID id, const Vec2& center, P2BodyType bodyType);

		[[nodiscard]]
		std::weak_ptr<P2BodyDetail> getWeakPtr() const;
	};
}

# include "detail/P2Body.ipp"
