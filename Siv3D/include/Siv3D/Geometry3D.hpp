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
# include <array>
# include "Common.hpp"
# include "Vertex3D.hpp"
# include "Sphere.hpp"
# include "Box.hpp"
# include "OrientedBox.hpp"
# include "Mat4x4.hpp"

namespace DirectX
{
	struct BoundingSphere;
	struct BoundingBox;
	struct BoundingOrientedBox;
}

namespace s3d
{
	namespace Geometry3D
	{
		[[nodiscard]]
		Sphere BoundingSphere(const Array<Float3>& points) noexcept;

		[[nodiscard]]
		Sphere BoundingSphere(const Vertex3D* vertices, size_t count) noexcept;

		[[nodiscard]]
		Sphere BoundingSphere(const Array<Vertex3D>& vertices) noexcept;

		[[nodiscard]]
		Box BoundingBox(const Array<Float3>& points) noexcept;

		[[nodiscard]]
		Box BoundingBox(const Vertex3D* vertices, size_t count) noexcept;

		[[nodiscard]]
		Box BoundingBox(const Array<Vertex3D>& vertices) noexcept;

		[[nodiscard]]
		OrientedBox BoundingOrientedBox(const Array<Float3>& points) noexcept;

		[[nodiscard]]
		OrientedBox BoundingOrientedBox(const Vertex3D* vertices, size_t count) noexcept;

		[[nodiscard]]
		OrientedBox BoundingOrientedBox(const Array<Vertex3D>& vertices) noexcept;

		[[nodiscard]]
		Sphere TransformBoundingSphere(const Sphere& sphere, const Mat4x4& matrix) noexcept;

		[[nodiscard]]
		Box TransformBoundingBox(const Box& box, const Mat4x4& matrix) noexcept;

		[[nodiscard]]
		OrientedBox TransformBoundingOrientedBox(const OrientedBox& box, const Mat4x4& matrix) noexcept;

		[[nodiscard]]
		Sphere MergeBoundingSpheres(const Sphere& a, const Sphere& b) noexcept;

		[[nodiscard]]
		Box MergeBoundingBoxes(const Box& a, const Box& b) noexcept;




		[[nodiscard]]
		std::array<Vec3, 8> GetCorners(const Box& box) noexcept;

		[[nodiscard]]
		std::array<Vec3, 8> GetCorners(const OrientedBox& box) noexcept;

		[[nodiscard]]
		std::array<Vec3, 8> GetCorners(const ViewFrustum& frustum) noexcept;

		//////////////////////////////////////////////////
		//
		//	Sphere intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		bool Intersects(const Sphere& a, const Vec3& b) noexcept;

		[[nodiscard]]
		bool Intersects(const Sphere& a, const Triangle3D& b) noexcept;

		[[nodiscard]]
		bool Intersects(const Sphere& a, const Sphere& b) noexcept;

		[[nodiscard]]
		bool Intersects(const Sphere& a, const Box& b) noexcept;

		[[nodiscard]]
		bool Intersects(const Sphere& a, const OrientedBox& b) noexcept;

		[[nodiscard]]
		bool Intersects(const Sphere& a, const ViewFrustum& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Box intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		bool Intersects(const Box& a, const Vec3& b) noexcept;

		[[nodiscard]]
		bool Intersects(const Box& a, const Triangle3D& b) noexcept;

		[[nodiscard]]
		bool Intersects(const Box& a, const Sphere& b) noexcept;

		[[nodiscard]]
		bool Intersects(const Box& a, const Box& b) noexcept;

		[[nodiscard]]
		bool Intersects(const Box& a, const OrientedBox& b) noexcept;

		[[nodiscard]]
		bool Intersects(const Box& a, const ViewFrustum& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	OrientedBox intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		bool Intersects(const OrientedBox& a, const Vec3& b) noexcept;

		[[nodiscard]]
		bool Intersects(const OrientedBox& a, const Triangle3D& b) noexcept;

		[[nodiscard]]
		bool Intersects(const OrientedBox& a, const Sphere& b) noexcept;

		[[nodiscard]]
		bool Intersects(const OrientedBox& a, const Box& b) noexcept;

		[[nodiscard]]
		bool Intersects(const OrientedBox& a, const OrientedBox& b) noexcept;

		[[nodiscard]]
		bool Intersects(const OrientedBox& a, const ViewFrustum& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	ViewFrustum intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		bool Intersects(const ViewFrustum& a, const Vec3& b) noexcept;

		[[nodiscard]]
		bool Intersects(const ViewFrustum& a, const Triangle3D& b) noexcept;

		[[nodiscard]]
		bool Intersects(const ViewFrustum& a, const Sphere& b) noexcept;

		[[nodiscard]]
		bool Intersects(const ViewFrustum& a, const Box& b) noexcept;

		[[nodiscard]]
		bool Intersects(const ViewFrustum& a, const OrientedBox& b) noexcept;

		[[nodiscard]]
		bool Intersects(const ViewFrustum& a, const ViewFrustum& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Sphere contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		bool Contains(const Sphere& a, const Vec3& b) noexcept;

		[[nodiscard]]
		bool Contains(const Sphere& a, const Triangle3D& b) noexcept;

		[[nodiscard]]
		bool Contains(const Sphere& a, const Sphere& b) noexcept;

		[[nodiscard]]
		bool Contains(const Sphere& a, const Box& b) noexcept;

		[[nodiscard]]
		bool Contains(const Sphere& a, const OrientedBox& b) noexcept;

		[[nodiscard]]
		bool Contains(const Sphere& a, const ViewFrustum& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Box contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		bool Contains(const Box& a, const Vec3& b) noexcept;

		[[nodiscard]]
		bool Contains(const Box& a, const Triangle3D& b) noexcept;

		[[nodiscard]]
		bool Contains(const Box& a, const Sphere& b) noexcept;

		[[nodiscard]]
		bool Contains(const Box& a, const Box& b) noexcept;

		[[nodiscard]]
		bool Contains(const Box& a, const OrientedBox& b) noexcept;

		[[nodiscard]]
		bool Contains(const Box& a, const ViewFrustum& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	OrientedBox contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		bool Contains(const OrientedBox& a, const Vec3& b) noexcept;

		[[nodiscard]]
		bool Contains(const OrientedBox& a, const Triangle3D& b) noexcept;

		[[nodiscard]]
		bool Contains(const OrientedBox& a, const Sphere& b) noexcept;

		[[nodiscard]]
		bool Contains(const OrientedBox& a, const Box& b) noexcept;

		[[nodiscard]]
		bool Contains(const OrientedBox& a, const OrientedBox& b) noexcept;

		[[nodiscard]]
		bool Contains(const OrientedBox& a, const ViewFrustum& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	ViewFrustum contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		bool Contains(const ViewFrustum& a, const Vec3& b) noexcept;

		[[nodiscard]]
		bool Contains(const ViewFrustum& a, const Triangle3D& b) noexcept;

		[[nodiscard]]
		bool Contains(const ViewFrustum& a, const Sphere& b) noexcept;

		[[nodiscard]]
		bool Contains(const ViewFrustum& a, const Box& b) noexcept;

		[[nodiscard]]
		bool Contains(const ViewFrustum& a, const OrientedBox& b) noexcept;

		[[nodiscard]]
		bool Contains(const ViewFrustum& a, const ViewFrustum& b) noexcept;
	}

	namespace detail
	{
		[[nodiscard]]
		Sphere ToSphere(const DirectX::BoundingSphere& sphere) noexcept;

		[[nodiscard]]
		Box ToBox(const DirectX::BoundingBox& box) noexcept;

		[[nodiscard]]
		OrientedBox ToOrientedBox(const DirectX::BoundingOrientedBox& box) noexcept;

		[[nodiscard]]
		DirectX::BoundingSphere FromSphere(const Sphere& sphere) noexcept;

		[[nodiscard]]
		DirectX::BoundingBox FromBox(const Box& box) noexcept;

		[[nodiscard]]
		DirectX::BoundingOrientedBox FromOrientedBox(const OrientedBox& box) noexcept;
	}
}
