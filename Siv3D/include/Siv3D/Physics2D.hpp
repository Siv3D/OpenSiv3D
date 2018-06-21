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

# pragma once
# include "Fwd.hpp"
# include "Optional.hpp"
# include "Array.hpp"
# include "PointVector.hpp"
# include "Line.hpp"
# include "LineString.hpp"
# include "Circle.hpp"
# include "Rectangle.hpp"
# include "Triangle.hpp"
# include "Quad.hpp"
# include "Polygon.hpp"
# include "MultiPolygon.hpp"
# include "System.hpp"

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
	using P2BodyID = uint64;

	struct P2Material
	{
		double density = 1.0;

		double restitution = 0.1;

		double friction = 0.2;

		constexpr P2Material(None_t) {}

		constexpr P2Material(double _density = 1.0, double _restitution = 0.1, double _friction = 0.2)
			: density(_density)
			, restitution(_restitution)
			, friction(_friction) {}
	};

	struct P2Filter
	{
		uint16 categoryBits = 0b0000'0000'0000'0001;

		uint16 maskBits = 0b1111'1111'1111'1111;

		int16 groupIndex = 0;

		constexpr P2Filter(None_t) {}

		constexpr P2Filter(
			uint16 _categoryBits = 0b0000'0000'0000'0001,
			uint16 _maskBits = 0b1111'1111'1111'1111u,
			int16  _groupIndex = 0)
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

	class P2World
	{
	private:

		class CP2World;

		std::shared_ptr<CP2World> pImpl;

	public:

		P2World(const Vec2& gravity = Vec2(0.0, 9.8));

		void setSleepEnabled(bool enabled);

		[[nodiscard]] bool getSleepEnabled() const;

		void setGravity(const Vec2& gravity);

		[[nodiscard]] Vec2 getGravity() const;

		void shiftOrigin(const Vec2& newOrigin);

		void update(double timeStep = System::DeltaTime(), int32 velocityIterations = 6, int32 positionIterations = 2) const;

		[[nodiscard]] P2Body createEmpty(const Vec2& center, P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createLine(const Vec2& center, const Vec2& begin, const Vec2& end, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createLine(const Vec2& center, const Line& line, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createLineString(const Vec2& center, const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createClosedLineString(const Vec2& center, const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createCircle(const Vec2& center, double r, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createCircle(const Vec2& center, double r, const Vec2& offset, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createCircle(const Vec2& center, const Circle& circle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createRect(const Vec2& center, double size, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createRect(const Vec2& center, double w, double h, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createRect(const Vec2& center, const Vec2& size, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createRect(const Vec2& center, const Vec2& size, const Vec2& offset, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createRect(const Vec2& center, const RectF& rect, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createTriangle(const Vec2& center, double sides, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createTriangle(const Vec2& center, double sides, double angle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createTriangle(const Vec2& center, double sides, double angle, const Vec2& offset, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createTriangle(const Vec2& center, const Vec2& p0, const Vec2& p1, const Vec2& p2, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createTriangle(const Vec2& center, const Triangle& triangle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createQuad(const Vec2& center, const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createQuad(const Vec2& center, const Quad& quad, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createPolygon(const Vec2& center, const Polygon& polygon, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2Body createPolygons(const Vec2& center, const MultiPolygon& polygons, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		[[nodiscard]] P2RevoluteJoint createRevoluteJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos);

		[[nodiscard]] b2World* getWorldPtr() const;
	};

	class P2Body
	{
	private:

		class CP2Body;

		std::shared_ptr<CP2Body> pImpl;

		friend class P2World;

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

		P2Body& addRect(const RectF& rect, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& addTriangle(const Triangle& triangle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& addQuad(const Quad& quad, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& addPolygon(const Polygon& polygon, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		P2Body& addPolygons(const MultiPolygon& polygons, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter());

		void setSleepEnabled(bool enabled);

		[[nodiscard]] bool getSleepEnabled() const;

		void setAwake(bool awake);

		[[nodiscard]] bool isAwake() const;

		void setPos(double x, double y);

		void setPos(const Vec2& pos);

		void moveBy(double x, double y);

		void moveBy(const Vec2& v);

		void setAngle(double angle);

		void rotateBy(double angle);

		void setTransform(double x, double y, double angle);

		void setTransform(const Vec2& pos, double angle);

		void applyForce(const Vec2& force);

		void applyForce(const Vec2& force, const Vec2& offset);

		void applyForceAt(const Vec2& force, const Vec2& pos);

		void applyLinearImpulse(const Vec2& force);

		void applyLinearImpulse(const Vec2& force, const Vec2& offset);

		void applyLinearImpulseAt(const Vec2& force, const Vec2& pos);

		void applyTorque(double torque);

		void applyAngularImpulse(double torque);

		[[nodiscard]] 	Vec2 getPos() const;

		[[nodiscard]] double getAngle() const;

		[[nodiscard]] std::pair<Vec2, double> getTransform() const;

		void setVelocity(const Vec2& v);

		[[nodiscard]] Vec2 getVelocity() const;

		void setAngularVelocity(double omega);

		[[nodiscard]] double getAngularVelocity() const;

		void setDamping(double damping);

		[[nodiscard]] double getDamping() const;

		void setAngularDamping(double damping);

		[[nodiscard]] double getAngularDamping() const;

		void setGravityScale(double scale);

		[[nodiscard]] double getGravityScale() const;

		[[nodiscard]] double getMass() const;

		[[nodiscard]] double getInertia() const;

		void setBodyType(P2BodyType bodyType);

		[[nodiscard]] P2BodyType getBodyType() const;

		void setFixedRotation(bool fixedRotation);

		[[nodiscard]] bool isFixedRotation() const;

		void draw(const ColorF& color = Palette::White) const;

		void drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawWireframe(double thickness = 1.0, const ColorF& color = Palette::White) const;

		[[nodiscard]] size_t num_shapes() const;

		[[nodiscard]] P2Shape& shape(size_t index);

		[[nodiscard]] const P2Shape& shape(size_t index) const;
		
		[[nodiscard]] std::shared_ptr<P2Shape> shapePtr(size_t index) const;

		template <class PShape, std::enable_if_t<std::is_base_of_v<P2Shape, PShape>>* = nullptr>
		std::shared_ptr<PShape> shapeAs(size_t index) const
		{
			if (isEmpty())
			{
				throw std::out_of_range("P2Body::shapeAs() P2Body is empty.");
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

		virtual ~P2Shape() {}

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

		bool m_closed;

	public:

		P2LineString(b2Body& body, const LineString& lines, bool closed, const P2Material& material, const P2Filter& filter);

		[[nodiscard]] P2ShapeType getShapeType() const override;

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
	
	
	class P2RevoluteJoint
	{
	private:

		class CP2RevoluteJoint;

		std::shared_ptr<CP2RevoluteJoint> pImpl;

		friend class P2World;

		P2RevoluteJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos);

	public:

		P2RevoluteJoint() = default;

		void setMotorEnabled(bool enabled);

		[[nodiscard]] bool getMotorEnabled() const;

		void setMotorSpeed(double speed);

		[[nodiscard]] double getMotorSpeed() const;

		void setMaxMotorTorque(double torque);

		[[nodiscard]] double getMaxMotorTorque() const;
	};
}
