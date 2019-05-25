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
# include "Optional.hpp"
# include "PointVector.hpp"
# include "LineString.hpp"
# include "Polygon.hpp"
# include "Scene.hpp"
# include "HashTable.hpp"

// Box2D forward declaration
class b2World;
class b2Body;
class b2Fixture;
class b2EdgeShape;
class b2ChainShape;
class b2CircleShape;
class b2PolygonShape;

namespace s3d
{
	using P2BodyID = uint32;

	struct P2Material
	{
		double density = 1.0;

		double restitution = 0.1;

		double friction = 0.2;

		constexpr P2Material(None_t) noexcept {}

		constexpr P2Material(double _density = 1.0, double _restitution = 0.1, double _friction = 0.2) noexcept
			: density(_density)
			, restitution(_restitution)
			, friction(_friction) {}
	};

	struct P2Filter
	{
		uint16 categoryBits = 0b0000'0000'0000'0001;

		uint16 maskBits = 0b1111'1111'1111'1111;

		int16 groupIndex = 0;

		constexpr P2Filter(None_t) noexcept {}

		constexpr P2Filter(
			uint16 _categoryBits = 0b0000'0000'0000'0001,
			uint16 _maskBits = 0b1111'1111'1111'1111u,
			int16  _groupIndex = 0) noexcept
			: categoryBits(_categoryBits)
			, maskBits(_maskBits)
			, groupIndex(_groupIndex) {}
	};

	enum class P2BodyType
	{
		Static,

		Kinematic,

		Dynamic
	};

	enum class P2ShapeType
	{
		Line,

		LineString,

		Circle,

		Rect,

		Triangle,

		Quad,

		Polygon
	};

	struct P2ContactPair
	{
		P2BodyID a, b;

		[[nodiscard]] constexpr bool operator ==(const P2ContactPair& other) const noexcept
		{
			return a == other.a && b == other.b;
		}

		[[nodiscard]] constexpr bool operator !=(const P2ContactPair& other) const noexcept
		{
			return a != other.a || b != other.b;
		}
	};

	struct P2Contact
	{
		Vec2 point;
		double normalImpulse = 0.0;
		double tangentImpulse = 0.0;
		void clearImpulse() noexcept
		{
			normalImpulse = tangentImpulse = 0.0;
		}
	};

	struct P2Collision
	{
		std::array<P2Contact, 2> contacts;

		Vec2 normal = Vec2(0, 0);

		uint32 _internal_count = 1;

		uint32 num_contacts = 0;

		explicit operator bool() const noexcept
		{
			return (num_contacts != 0);
		}

		[[nodiscard]] std::array<P2Contact, 2>::const_iterator begin() const noexcept;

		[[nodiscard]] std::array<P2Contact, 2>::const_iterator end() const noexcept;
	};

	class P2World
	{
	private:

		class P2WorldDetail;

		std::shared_ptr<P2WorldDetail> pImpl;

	public:

		explicit P2World(double gravity = 9.8);

		explicit P2World(const Vec2& gravity);

		void setSleepEnabled(bool enabled);

		[[nodiscard]] bool getSleepEnabled() const;

		void setGravity(double gravity);

		void setGravity(const Vec2& gravity);

		[[nodiscard]] Vec2 getGravity() const;

		void shiftOrigin(const Vec2& newOrigin);

		void update(double timeStep = Scene::DeltaTime(), int32 velocityIterations = 6, int32 positionIterations = 2) const;

		[[nodiscard]] P2Body createDummy(const Vec2& center, P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createLine(const Vec2& center, const Line& line, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createLineString(const Vec2& center, const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createClosedLineString(const Vec2& center, const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createCircle(const Vec2& center, double r, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createCircle(const Vec2& center, const Circle& circle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createRect(const Vec2& center, const SizeF& size, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createRect(const Vec2& center, const RectF& rect, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createTriangle(const Vec2& center, const Triangle& triangle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createQuad(const Vec2& center, const Quad& quad, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createPolygon(const Vec2& center, const Polygon& polygon, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createPolygons(const Vec2& center, const MultiPolygon& polygons, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createStaticDummy(const Vec2& center);
		[[nodiscard]] P2Body createStaticLine(const Vec2& center, const Line& line, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createStaticLineString(const Vec2& center, const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());	
		[[nodiscard]] P2Body createStaticClosedLineString(const Vec2& center, const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createStaticCircle(const Vec2& center, double r, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createStaticCircle(const Vec2& center, const Circle& circle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createStaticRect(const Vec2& center, const SizeF& size, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createStaticRect(const Vec2& center, const RectF& rect, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createStaticTriangle(const Vec2& center, const Triangle& triangle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createStaticQuad(const Vec2& center, const Quad& quad, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createStaticPolygon(const Vec2& center, const Polygon& polygon, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createStaticPolygons(const Vec2& center, const MultiPolygon& polygons, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		[[nodiscard]] P2Body createKinematicDummy(const Vec2& center);
		[[nodiscard]] P2Body createKinematicLine(const Vec2& center, const Line& line, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createKinematicLineString(const Vec2& center, const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createKinematicClosedLineString(const Vec2& center, const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createKinematicCircle(const Vec2& center, double r, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createKinematicCircle(const Vec2& center, const Circle& circle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createKinematicRect(const Vec2& center, const SizeF& size, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createKinematicRect(const Vec2& center, const RectF& rect, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createKinematicTriangle(const Vec2& center, const Triangle& triangle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createKinematicQuad(const Vec2& center, const Quad& quad, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createKinematicPolygon(const Vec2& center, const Polygon& polygon, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createKinematicPolygons(const Vec2& center, const MultiPolygon& polygons, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		[[nodiscard]] P2Body createDynamicDummy(const Vec2& center);
		[[nodiscard]] P2Body createDynamicLine(const Vec2& center, const Line& line, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createDynamicLineString(const Vec2& center, const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createDynamicClosedLineString(const Vec2& center, const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createDynamicCircle(const Vec2& center, double r, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createDynamicCircle(const Vec2& center, const Circle& circle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createDynamicRect(const Vec2& center, const SizeF& size, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createDynamicRect(const Vec2& center, const RectF& rect, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createDynamicTriangle(const Vec2& center, const Triangle& triangle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createDynamicQuad(const Vec2& center, const Quad& quad, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createDynamicPolygon(const Vec2& center, const Polygon& polygon, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());
		[[nodiscard]] P2Body createDynamicPolygons(const Vec2& center, const MultiPolygon& polygons, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		[[nodiscard]] P2PivotJoint createPivotJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos);
		[[nodiscard]] P2DistanceJoint createDistanceJoint(const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, double length);
		[[nodiscard]] P2RopeJoint createRopeJoint(const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, double maxLength);
		[[nodiscard]] P2SliderJoint createSliderJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos, const Vec2& normalizedAxis);

		[[nodiscard]] const HashTable<P2ContactPair, P2Collision>& getCollisions() const;

		[[nodiscard]] b2World* getWorldPtr() const;
	};

	class P2Body
	{
	private:

		class P2BodyDetail;

		std::shared_ptr<P2BodyDetail> pImpl;

		friend class P2World;
		friend class P2ContactListener;

		P2Body(P2World& world, P2BodyID id, const Vec2& center, P2BodyType bodyType);

	public:

		P2Body();

		[[nodiscard]] P2BodyID id() const;

		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] explicit operator bool() const;

		P2Body& addLine(const Line& line, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& addLineString(const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& addClosedLineString(const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& addCircle(const Circle& circle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& addRect(const SizeF& size, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& addRect(const RectF& rect, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& addTriangle(const Triangle& triangle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& addQuad(const Quad& quad, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& addPolygon(const Polygon& polygon, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& addPolygons(const MultiPolygon& polygons, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& setSleepEnabled(bool enabled);

		[[nodiscard]] bool getSleepEnabled() const;

		P2Body& setAwake(bool awake);

		[[nodiscard]] bool isAwake() const;

		P2Body& setPos(double x, double y);

		P2Body& setPos(const Vec2& pos);

		P2Body& moveBy(double x, double y);

		P2Body& moveBy(const Vec2& v);

		P2Body& setAngle(double angle);

		P2Body& rotateBy(double angle);

		P2Body& setTransform(double x, double y, double angle);

		P2Body& setTransform(const Vec2& pos, double angle);

		P2Body& applyForce(const Vec2& force);

		P2Body& applyForce(const Vec2& force, const Vec2& offset);

		P2Body& applyForceAt(const Vec2& force, const Vec2& pos);

		P2Body& applyLinearImpulse(const Vec2& force);

		P2Body& applyLinearImpulse(const Vec2& force, const Vec2& offset);

		P2Body& applyLinearImpulseAt(const Vec2& force, const Vec2& pos);

		P2Body& applyTorque(double torque);

		P2Body& applyAngularImpulse(double torque);

		[[nodiscard]] Vec2 getPos() const;

		[[nodiscard]] double getAngle() const;

		[[nodiscard]] std::pair<Vec2, double> getTransform() const;

		P2Body& setVelocity(const Vec2& v);

		[[nodiscard]] Vec2 getVelocity() const;

		P2Body& setAngularVelocity(double omega);

		[[nodiscard]] double getAngularVelocity() const;

		P2Body& setDamping(double damping);

		[[nodiscard]] double getDamping() const;

		P2Body& setAngularDamping(double damping);

		[[nodiscard]] double getAngularDamping() const;

		P2Body& setGravityScale(double scale);

		[[nodiscard]] double getGravityScale() const;

		[[nodiscard]] double getMass() const;

		[[nodiscard]] double getInertia() const;

		P2Body& setBodyType(P2BodyType bodyType);

		[[nodiscard]] P2BodyType getBodyType() const;

		P2Body& setFixedRotation(bool fixedRotation);

		[[nodiscard]] bool isFixedRotation() const;

		void draw(const ColorF& color = Palette::White) const;

		void drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawWireframe(double thickness = 1.0, const ColorF& color = Palette::White) const;

		[[nodiscard]] size_t num_shapes() const;

		[[nodiscard]] P2Shape& shape(size_t index);

		[[nodiscard]] const P2Shape& shape(size_t index) const;

		[[nodiscard]] std::shared_ptr<P2Shape> shapePtr(size_t index) const;

		template <class PShape, std::enable_if_t<std::is_base_of_v<P2Shape, PShape>>* = nullptr>
		std::shared_ptr<PShape> as(size_t index) const
		{
			if (isEmpty())
			{
				throw std::out_of_range("P2Body::as() P2Body is empty.");
			}

			return std::dynamic_pointer_cast<PShape>(shapePtr(index));
		}

		[[nodiscard]] b2Body* getBodyPtr() const;
	};

	struct P2Fixture
	{
		Array<b2Fixture*> fixtures;
	};

	class P2Shape
	{
	protected:

		P2Fixture m_fixtures;

	public:

		virtual ~P2Shape() = default;

		virtual P2ShapeType getShapeType() const = 0;

		virtual void draw(const ColorF& color) const = 0;

		virtual void drawFrame(double thickness, const ColorF& color) const = 0;

		virtual void drawWireframe(double thickness, const ColorF& color) const = 0;

		void setDensity(double density);

		[[nodiscard]] double getDensity() const;

		void setFriction(double friction);

		[[nodiscard]] double getFriction() const;

		void setRestitution(double restitution);

		[[nodiscard]] double getRestitution() const;

		void setFilter(const P2Filter& filter);

		[[nodiscard]] P2Filter getFilter() const;
	};

	class P2Line : public P2Shape
	{
	private:

		std::unique_ptr<b2EdgeShape> m_pShape;

	public:

		P2Line(b2Body& body, const Line& line, const P2Material& material, const P2Filter& filter);

		[[nodiscard]] P2ShapeType getShapeType() const override;

		void draw(const ColorF& color = Palette::White) const override;

		void drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		void drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]] Line getLine() const;
	};

	class P2LineString : public P2Shape
	{
	private:

		std::unique_ptr<b2ChainShape> m_pShape;

		mutable LineString m_lineString;

		bool m_closed = false;

	public:

		P2LineString(b2Body& body, const LineString& lines, bool closed, const P2Material& material, const P2Filter& filter);

		[[nodiscard]] P2ShapeType getShapeType() const override;

		[[nodiscard]] bool isClosed() const;

		void draw(const ColorF& color = Palette::White) const override;

		void drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		void drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]] const LineString& getLineString() const;
	};

	class P2Circle : public P2Shape
	{
	private:

		std::unique_ptr<b2CircleShape> m_pShape;

	public:

		P2Circle(b2Body& body, const Circle& circle, const P2Material& material, const P2Filter& filter);

		[[nodiscard]] P2ShapeType getShapeType() const override;

		void draw(const ColorF& color = Palette::White) const override;

		void drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		void drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]] Circle getCircle() const;
	};

	class P2Rect : public P2Shape
	{
	private:

		std::unique_ptr<b2PolygonShape> m_pShape;

	public:

		P2Rect(b2Body& body, const RectF& rect, const P2Material& material, const P2Filter& filter);

		[[nodiscard]] P2ShapeType getShapeType() const override;

		void draw(const ColorF& color = Palette::White) const override;

		void draw(const ColorF(&colors)[4]) const;

		void draw(Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		void draw(Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;

		void drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		void drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]] Quad getQuad() const;
	};

	class P2Triangle : public P2Shape
	{
	private:

		std::unique_ptr<b2PolygonShape> m_pShape;

	public:

		P2Triangle(b2Body& body, const Triangle& triangle, const P2Material& material, const P2Filter& filter);

		[[nodiscard]] P2ShapeType getShapeType() const override;

		void draw(const ColorF& color = Palette::White) const override;

		void drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		void drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]] Triangle getTriangle() const;
	};

	class P2Quad : public P2Shape
	{
	private:

		std::unique_ptr<b2PolygonShape> m_pShape;

	public:

		P2Quad(b2Body& body, const Quad& quad, const P2Material& material, const P2Filter& filter);

		[[nodiscard]] P2ShapeType getShapeType() const override;

		void draw(const ColorF& color = Palette::White) const override;

		void drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		void drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]] Quad getQuad() const;
	};

	class P2Polygon : public P2Shape
	{
	private:

		Polygon m_basePolygon;

	public:

		P2Polygon(b2Body& body, const Polygon& polygon, const P2Material& material, const P2Filter& filter);

		[[nodiscard]] P2ShapeType getShapeType() const override;

		void draw(const ColorF& color = Palette::White) const override;

		void drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		void drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]] Polygon getPolygon() const;
	};

	class P2PivotJoint
	{
	private:

		class P2PivotJointDetail;

		std::shared_ptr<P2PivotJointDetail> pImpl;

		friend class P2World;

		P2PivotJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos);

	public:

		P2PivotJoint() = default;

		[[nodiscard]] Vec2 getAnchorPos() const;

		[[nodiscard]] double getJointAngle() const;

		[[nodiscard]] double getJointAngleSpeed() const;

		P2PivotJoint& setLimitEnabled(bool enabled);

		[[nodiscard]] bool getLimitEnabled() const;

		P2PivotJoint& setLimits(double lower, double upper);

		[[nodiscard]] std::pair<double, double> getLimits() const;

		P2PivotJoint& setMotorEnabled(bool enabled);

		[[nodiscard]] bool getMotorEnabled() const;

		P2PivotJoint& setMotorSpeed(double speed);

		[[nodiscard]] double getMotorSpeed() const;

		P2PivotJoint& setMaxMotorTorque(double torque);

		[[nodiscard]] double getMaxMotorTorque() const;

		[[nodiscard]] Vec2 getReactionForce(double inv_dt) const;

		[[nodiscard]] double getReactionTorque(double inv_dt) const;

		[[nodiscard]] double getMotorTorque(double inv_dt) const;

		void draw(const ColorF& color = Palette::White) const;
	};


	class P2DistanceJoint
	{
	private:

		class P2DistanceJointDetail;

		std::shared_ptr<P2DistanceJointDetail> pImpl;

		friend class P2World;

		P2DistanceJoint(P2World& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, double length);

	public:

		P2DistanceJoint() = default;

		[[nodiscard]] Vec2 getAnchorPosA() const;

		[[nodiscard]] Vec2 getAnchorPosB() const;

		[[nodiscard]] Vec2 getReactionForce(double inv_dt) const;

		[[nodiscard]] double getReactionTorque(double inv_dt) const;

		P2DistanceJoint& setLength(double length);

		[[nodiscard]] double getLength() const;

		P2DistanceJoint& setFrequencyHz(double hz);

		[[nodiscard]] double getFrequencyHz() const;

		P2DistanceJoint& setDampingRatio(double ratio);

		[[nodiscard]] double getDampingRatio() const;

		void draw(const ColorF& color = Palette::White) const;
	};

	class P2RopeJoint
	{
	private:

		class P2RopeJointDetail;

		std::shared_ptr<P2RopeJointDetail> pImpl;

		friend class P2World;

		P2RopeJoint(P2World& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, double maxLength);

	public:

		P2RopeJoint() = default;

		[[nodiscard]] Vec2 getAnchorPosA() const;

		[[nodiscard]] Vec2 getAnchorPosB() const;

		[[nodiscard]] Vec2 getReactionForce(double inv_dt) const;

		[[nodiscard]] double getReactionTorque(double inv_dt) const;

		P2RopeJoint& setMaxLength(double maxLength);

		[[nodiscard]] double getMaxLength() const;

		void draw(const ColorF& color = Palette::White) const;
	};

	class P2SliderJoint
	{
	private:

		class P2SliderJointDetail;

		std::shared_ptr<P2SliderJointDetail> pImpl;

		friend class P2World;

		P2SliderJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos, const Vec2& normalizedAxis);

	public:

		P2SliderJoint() = default;

		[[nodiscard]] Vec2 getAnchorPosA() const;

		[[nodiscard]] Vec2 getAnchorPosB() const;

		[[nodiscard]] Vec2 getReactionForce(double inv_dt) const;

		[[nodiscard]] double getReactionTorque(double inv_dt) const;

		[[nodiscard]] double getJointTranslation() const;

		[[nodiscard]] double getJointSpeed() const;

		P2SliderJoint& setLimitEnabled(bool enabled);

		[[nodiscard]] bool getLimitEnabled() const;

		P2SliderJoint& setLimits(double lower, double upper);

		[[nodiscard]] std::pair<double, double> getLimits() const;

		P2SliderJoint& setMotorEnabled(bool enabled);

		[[nodiscard]] bool getMotorEnabled() const;

		P2SliderJoint& setMotorSpeed(double speed);

		[[nodiscard]] double getMotorSpeed() const;

		P2SliderJoint& setMaxMotorForce(double force);

		[[nodiscard]] double getMaxMotorForce() const;

		[[nodiscard]] double getMotorForce(double inv_dt) const;

		void draw(const ColorF& color = Palette::White) const;
	};


	class P2WheelJoint
	{
	private:

		class P2WheelJointDetail;

		std::shared_ptr<P2WheelJointDetail> pImpl;

		friend class P2World;

		P2WheelJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchor, const Vec2& axis);

	public:

		P2WheelJoint() = default;

		[[nodiscard]] Vec2 getAnchorPosA() const;

		[[nodiscard]] Vec2 getAnchorPosB() const;

		[[nodiscard]] Vec2 getReactionForce(double inv_dt) const;

		[[nodiscard]] double getReactionTorque(double inv_dt) const;

		[[nodiscard]] double getJointTranslation() const;

		[[nodiscard]] double getJointLinearSpeed() const;

		[[nodiscard]] double getJointAngle() const;

		[[nodiscard]] double getJointAngularSpeed() const;

		P2WheelJoint& setMotorEnabled(bool enabled);

		[[nodiscard]] bool getMotorEnabled() const;

		P2WheelJoint& setMotorSpeed(double speed);

		[[nodiscard]] double getMotorSpeed() const;

		P2WheelJoint& setMaxMotorTorque(double torque);

		[[nodiscard]] double getMaxMotorTorque() const;

		[[nodiscard]] double getMotorTorque(double inv_dt) const;

		P2WheelJoint& setSpringFrequencyHz(double hz);
		
		[[nodiscard]] double getSpringFrequencyHz() const;

		P2WheelJoint& setSpringDampingRatio(double ratio);
		
		[[nodiscard]] double getSpringDampingRatio() const;

		void draw(const ColorF& color = Palette::White) const;
	};
}

namespace std
{
	template <>
	struct hash<s3d::P2ContactPair>
	{
		[[nodiscard]] size_t operator()(const s3d::P2ContactPair& keyVal) const noexcept
		{
			return hash<s3d::uint64>()(*((s3d::uint64*)&keyVal));
		}
	};
}
