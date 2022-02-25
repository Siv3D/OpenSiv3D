//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

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
	/// @brief 物体 P2Body に与えられる一意の ID の型
	using P2BodyID = uint32;

	struct P2Material;
	struct P2Filter;
	enum class P2BodyType : uint8;
	enum class P2ShapeType : uint8;
	struct P2ContactPair;
	struct P2Contact;
	class P2Collision;
	class P2World;
	class P2Body;
	class P2Shape;
	class P2Line;
	class P2LineString;
	class P2Circle;
	class P2Rect;
	class P2Triangle;
	class P2Quad;
	class P2Polygon;
	class P2PivotJoint;
	class P2DistanceJoint;
	class P2SliderJoint;
	class P2WheelJoint;
	class P2MouseJoint;

	namespace detail
	{
		class P2WorldDetail;
		class P2ContactListener;
		class P2PivotJointDetail;
		class P2DistanceJointDetail;
		class P2SliderJointDetail;
		class P2WheelJointDetail;
		class P2MouseJointDetail;
	}
}
