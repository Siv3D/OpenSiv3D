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

# include <Siv3D/Geometry3D.hpp>
# include <Siv3D/Triangle3D.hpp>
# include <Siv3D/ViewFrustum.hpp>
# include <Siv3D/SIMD_Float4.hpp>
# include <Siv3D/SIMDCollision.hpp>

namespace s3d
{
	namespace detail
	{
		constexpr std::array<size_t, 8> OrientedBoxCornerIndices =
		{
			7, 6, 4, 5, 3, 2, 0, 1
		};

		constexpr std::array<size_t, 8> FrustumCornerIndices =
		{
			0, 1, 3, 2, 4, 5, 7, 6
		};
	}

	namespace Geometry3D
	{
		Sphere BoundingSphere(const Array<Float3>& points) noexcept
		{
			if (not points)
			{
				return Sphere{ 0.0 };
			}

			DirectX::BoundingSphere sphere;

			DirectX::BoundingSphere::CreateFromPoints(
				sphere,
				points.size(),
				static_cast<const DirectX::XMFLOAT3*>(static_cast<const void*>(points.data())),
				sizeof(Float3)
			);

			return detail::ToSphere(sphere);
		}

		Sphere BoundingSphere(const Vertex3D* vertices, const size_t count) noexcept
		{
			if ((not vertices) || (count == 0))
			{
				return Sphere{ 0.0 };
			}

			DirectX::BoundingSphere sphere;

			DirectX::BoundingSphere::CreateFromPoints(
				sphere,
				count,
				static_cast<const DirectX::XMFLOAT3*>(static_cast<const void*>(vertices)),
				sizeof(Vertex3D)
			);

			return detail::ToSphere(sphere);
		}

		Sphere BoundingSphere(const Array<Vertex3D>& vertices) noexcept
		{
			return BoundingSphere(vertices.data(), vertices.size());
		}

		Box BoundingBox(const Array<Float3>& points) noexcept
		{
			if (not points)
			{
				return Box{ 0.0 };
			}

			DirectX::BoundingBox box;

			DirectX::BoundingBox::CreateFromPoints(
				box,
				points.size(),
				static_cast<const DirectX::XMFLOAT3*>(static_cast<const void*>(points.data())),
				sizeof(Float3)
			);

			return detail::ToBox(box);
		}

		Box BoundingBox(const Vertex3D* vertices, size_t count) noexcept
		{
			if ((not vertices) || (count == 0))
			{
				return Box{ 0.0 };
			}

			DirectX::BoundingBox box;

			DirectX::BoundingBox::CreateFromPoints(
				box,
				count,
				static_cast<const DirectX::XMFLOAT3*>(static_cast<const void*>(vertices)),
				sizeof(Vertex3D)
			);

			return detail::ToBox(box);
		}

		Box BoundingBox(const Array<Vertex3D>& vertices) noexcept
		{
			return BoundingBox(vertices.data(), vertices.size());
		}

		OrientedBox BoundingOrientedBox(const Array<Float3>& points) noexcept
		{
			if (not points)
			{
				return OrientedBox{ 0.0 };
			}

			DirectX::BoundingOrientedBox box;

			DirectX::BoundingOrientedBox::CreateFromPoints(
				box,
				points.size(),
				static_cast<const DirectX::XMFLOAT3*>(static_cast<const void*>(points.data())),
				sizeof(Float3)
			);

			return detail::ToOrientedBox(box);
		}

		OrientedBox BoundingOrientedBox(const Vertex3D* vertices, const size_t count) noexcept
		{
			if ((not vertices) || (count == 0))
			{
				return Box{ 0.0 };
			}

			DirectX::BoundingOrientedBox box;

			DirectX::BoundingOrientedBox::CreateFromPoints(
				box,
				count,
				static_cast<const DirectX::XMFLOAT3*>(static_cast<const void*>(vertices)),
				sizeof(Vertex3D)
			);

			return detail::ToOrientedBox(box);
		}

		OrientedBox BoundingOrientedBox(const Array<Vertex3D>& vertices) noexcept
		{
			return BoundingOrientedBox(vertices.data(), vertices.size());
		}

		Sphere TransformBoundingSphere(const Sphere& sphere, const Mat4x4& matrix) noexcept
		{
			DirectX::BoundingSphere result;

			detail::FromSphere(sphere).Transform(result, matrix);

			return detail::ToSphere(result);
		}

		Box TransformBoundingBox(const Box& box, const Mat4x4& matrix) noexcept
		{
			DirectX::BoundingBox result;

			detail::FromBox(box).Transform(result, matrix);

			return detail::ToBox(result);
		}

		OrientedBox TransformBoundingOrientedBox(const OrientedBox& box, const Mat4x4& matrix) noexcept
		{
			DirectX::BoundingOrientedBox result;

			detail::FromOrientedBox(box).Transform(result, matrix);

			return detail::ToOrientedBox(result);
		}

		Sphere MergeBoundingSpheres(const Sphere& a, const Sphere& b) noexcept
		{
			DirectX::BoundingSphere result;

			DirectX::BoundingSphere::CreateMerged(result, detail::FromSphere(a), detail::FromSphere(b));

			return detail::ToSphere(result);
		}

		Box MergeBoundingBoxes(const Box& a, const Box& b) noexcept
		{
			DirectX::BoundingBox result;

			DirectX::BoundingBox::CreateMerged(result, detail::FromBox(a), detail::FromBox(b));

			return detail::ToBox(result);
		}



		std::array<Vec3, 8> GetCorners(const Box& box) noexcept
		{
			const Vec3 s = (box.size * 0.5);

			return{
				box.center.movedBy(-s.x,  s.y, -s.z),
				box.center.movedBy( s.x,  s.y, -s.z),
				box.center.movedBy(-s.x, -s.y, -s.z),
				box.center.movedBy( s.x, -s.y, -s.z),
			
				box.center.movedBy(-s.x,  s.y, s.z),
				box.center.movedBy( s.x,  s.y, s.z),
				box.center.movedBy(-s.x, -s.y, s.z),
				box.center.movedBy( s.x, -s.y, s.z),
			};
		}

		std::array<Vec3, 8> GetCorners(const OrientedBox& box) noexcept
		{
			std::array<DirectX::XMFLOAT3, 8> corners;

			detail::FromOrientedBox(box).GetCorners(corners.data());

			std::array<Vec3, 8> results;

			for (size_t i = 0; i < 8; ++i)
			{
				const auto& corner = corners[detail::OrientedBoxCornerIndices[i]];

				results[i].set(corner.x, corner.y, corner.z);
			}

			return results;
		}
		
		std::array<Vec3, 8> GetCorners(const ViewFrustum& frustum) noexcept
		{
			std::array<DirectX::XMFLOAT3, 8> corners;

			frustum.getData().GetCorners(corners.data());

			std::array<Vec3, 8> results;

			for (size_t i = 0; i < 8; ++i)
			{
				const auto& corner = corners[detail::FrustumCornerIndices[i]];

				results[i].set(corner.x, corner.y, corner.z);
			}

			return results;
		}

		//////////////////////////////////////////////////
		//
		//	Sphere intersects ...
		//
		//////////////////////////////////////////////////

		bool Intersects(const Sphere& a, const Vec3& b) noexcept
		{
			const double distanceSq = b.distanceFromSq(a.center);
			const double radiusSq = (a.r * a.r);
			return (distanceSq <= radiusSq);
		}

		bool Intersects(const Sphere& a, const Triangle3D& b) noexcept
		{
			const auto sphere = detail::FromSphere(a);
			return sphere.Intersects(b.p0, b.p1, b.p2);
		}

		bool Intersects(const Sphere& a, const Sphere& b) noexcept
		{
			const double distanceSq = a.center.distanceFrom(b.center);
			const double radiusSum = (a.r + b.r);
			return (distanceSq <= (radiusSum * radiusSum));
		}

		bool Intersects(const Sphere& a, const Box& b) noexcept
		{
			return detail::FromBox(b).Intersects(detail::FromSphere(a));
		}

		bool Intersects(const Sphere& a, const OrientedBox& b) noexcept
		{
			return detail::FromOrientedBox(b).Intersects(detail::FromSphere(a));
		}

		bool Intersects(const Sphere& a, const ViewFrustum& b) noexcept
		{
			return b.getData().Intersects(detail::FromSphere(a));
		}

		//////////////////////////////////////////////////
		//
		//	Box intersects ...
		//
		//////////////////////////////////////////////////

		bool Intersects(const Box& a, const Vec3& b) noexcept
		{
			return (detail::FromBox(a).Contains(SIMD_Float4{ b, 0.0f }) == DirectX::CONTAINS);
		}

		bool Intersects(const Box& a, const Triangle3D& b) noexcept
		{
			const auto box = detail::FromBox(a);
			return box.Intersects(b.p0, b.p1, b.p2);
		}

		bool Intersects(const Box& a, const Sphere& b) noexcept
		{
			return Intersects(b, a);
		}

		bool Intersects(const Box& a, const Box& b) noexcept
		{
			if (((a.size.x + b.size.x) * 0.5) < Abs(a.center.x - b.center.x))
			{
				return false;
			}

			if (((a.size.y + b.size.y) * 0.5) < Abs(a.center.y - b.center.y))
			{
				return false;
			}

			if (((a.size.z + b.size.z) * 0.5) < Abs(a.center.z - b.center.z))
			{
				return false;
			}

			return true;
		}

		bool Intersects(const Box& a, const OrientedBox& b) noexcept
		{
			const auto box = detail::FromBox(a);
			return box.Intersects(detail::FromOrientedBox(b));
		}

		bool Intersects(const Box& a, const ViewFrustum& b) noexcept
		{
			const auto box = detail::FromBox(a);
			return box.Intersects(b.getData());
		}

		//////////////////////////////////////////////////
		//
		//	OrientedBox intersects ...
		//
		//////////////////////////////////////////////////

		bool Intersects(const OrientedBox& a, const Vec3& b) noexcept
		{
			return (detail::FromOrientedBox(a).Contains(SIMD_Float4{ b, 0.0f }) == DirectX::CONTAINS);
		}

		bool Intersects(const OrientedBox& a, const Triangle3D& b) noexcept
		{
			const auto box = detail::FromOrientedBox(a);
			return box.Intersects(b.p0, b.p1, b.p2);
		}

		bool Intersects(const OrientedBox& a, const Sphere& b) noexcept
		{
			return Intersects(b, a);
		}

		bool Intersects(const OrientedBox& a, const Box& b) noexcept
		{
			return Intersects(b, a);
		}

		bool Intersects(const OrientedBox& a, const OrientedBox& b) noexcept
		{
			const auto box = detail::FromOrientedBox(a);
			return box.Intersects(detail::FromOrientedBox(b));
		}

		bool Intersects(const OrientedBox& a, const ViewFrustum& b) noexcept
		{
			const auto box = detail::FromOrientedBox(a);
			return box.Intersects(b.getData());
		}

		//////////////////////////////////////////////////
		//
		//	ViewFrustum intersects ...
		//
		//////////////////////////////////////////////////

		bool Intersects(const ViewFrustum& a, const Vec3& b) noexcept
		{
			const auto result = a.getData().Contains(SIMD_Float4{ b, 0.0f });
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Intersects(const ViewFrustum& a, const Triangle3D& b) noexcept
		{
			return a.getData().Intersects(b.p0, b.p1, b.p2);
		}

		bool Intersects(const ViewFrustum& a, const Sphere& b) noexcept
		{
			return Intersects(b, a);
		}

		bool Intersects(const ViewFrustum& a, const Box& b) noexcept
		{
			return Intersects(b, a);
		}

		bool Intersects(const ViewFrustum& a, const OrientedBox& b) noexcept
		{
			return Intersects(b, a);
		}

		bool Intersects(const ViewFrustum& a, const ViewFrustum& b) noexcept
		{
			return a.getData().Intersects(b.getData());
		}

		//////////////////////////////////////////////////
		//
		//	Sphere contains ...
		//
		//////////////////////////////////////////////////

		bool Contains(const Sphere& a, const Vec3& b) noexcept
		{
			const double distanceSq = b.distanceFromSq(a.center);
			const double radiusSq = (a.r * a.r);
			return (distanceSq < radiusSq);
		}

		bool Contains(const Sphere& a, const Triangle3D& b) noexcept
		{
			const auto sphere = detail::FromSphere(a);
			const auto result = sphere.Contains(b.p0, b.p1, b.p2);
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const Sphere& a, const Sphere& b) noexcept
		{
			return (b.r < a.r)
				&& (a.center.distanceFromSq(b.center) <= ((a.r - b.r) * (a.r - b.r)));
		}

		bool Contains(const Sphere& a, const Box& b) noexcept
		{
			const auto sphere = detail::FromSphere(a);
			const auto result = sphere.Contains(detail::FromBox(b));
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const Sphere& a, const OrientedBox& b) noexcept
		{
			const auto sphere = detail::FromSphere(a);
			const auto result = sphere.Contains(detail::FromOrientedBox(b));
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const Sphere& a, const ViewFrustum& b) noexcept
		{
			const auto sphere = detail::FromSphere(a);
			const auto result = sphere.Contains(b.getData());
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		//////////////////////////////////////////////////
		//
		//	Box contains ...
		//
		//////////////////////////////////////////////////

		bool Contains(const Box& a, const Vec3& b) noexcept
		{
			return (detail::FromBox(a).Contains(SIMD_Float4{ b, 0.0f }) == DirectX::CONTAINS);
		}

		bool Contains(const Box& a, const Triangle3D& b) noexcept
		{
			const auto box = detail::FromBox(a);
			const auto result = box.Contains(b.p0, b.p1, b.p2);
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const Box& a, const Sphere& b) noexcept
		{
			const auto box = detail::FromBox(a);
			const auto result = box.Contains(detail::FromSphere(b));
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const Box& a, const Box& b) noexcept
		{
			const auto box = detail::FromBox(a);
			const auto result = box.Contains(detail::FromBox(b));
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const Box& a, const OrientedBox& b) noexcept
		{
			const auto box = detail::FromBox(a);
			const auto result = box.Contains(detail::FromOrientedBox(b));
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const Box& a, const ViewFrustum& b) noexcept
		{
			const auto box = detail::FromBox(a);
			const auto result = box.Contains(b.getData());
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		//////////////////////////////////////////////////
		//
		//	OrientedBox contains ...
		//
		//////////////////////////////////////////////////

		bool Contains(const OrientedBox& a, const Vec3& b) noexcept
		{
			return (detail::FromOrientedBox(a).Contains(SIMD_Float4{ b, 0.0f }) == DirectX::CONTAINS);
		}

		bool Contains(const OrientedBox& a, const Triangle3D& b) noexcept
		{
			const auto box = detail::FromOrientedBox(a);
			const auto result = box.Contains(b.p0, b.p1, b.p2);
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const OrientedBox& a, const Sphere& b) noexcept
		{
			const auto box = detail::FromOrientedBox(a);
			const auto result = box.Contains(detail::FromSphere(b));
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const OrientedBox& a, const Box& b) noexcept
		{
			const auto box = detail::FromOrientedBox(a);
			const auto result = box.Contains(detail::FromBox(b));
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const OrientedBox& a, const OrientedBox& b) noexcept
		{
			const auto box = detail::FromOrientedBox(a);
			const auto result = box.Contains(detail::FromOrientedBox(b));
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const OrientedBox& a, const ViewFrustum& b) noexcept
		{
			const auto box = detail::FromOrientedBox(a);
			const auto result = box.Contains(b.getData());
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		//////////////////////////////////////////////////
		//
		//	ViewFrustum contains ...
		//
		//////////////////////////////////////////////////

		bool Contains(const ViewFrustum& a, const Vec3& b) noexcept
		{
			return Intersects(a, b);
		}

		bool Contains(const ViewFrustum& a, const Triangle3D& b) noexcept
		{
			const auto result = a.getData().Contains(b.p0, b.p1, b.p2);
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const ViewFrustum& a, const Sphere& b) noexcept
		{
			const auto result = a.getData().Contains(detail::FromSphere(b));
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const ViewFrustum& a, const Box& b) noexcept
		{
			const auto result = a.getData().Contains(detail::FromBox(b));
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const ViewFrustum& a, const OrientedBox& b) noexcept
		{
			const auto result = a.getData().Contains(detail::FromOrientedBox(b));
			return (result == DirectX::ContainmentType::CONTAINS);
		}

		bool Contains(const ViewFrustum& a, const ViewFrustum& b) noexcept
		{
			const auto result = a.getData().Contains(b.getData());
			return (result == DirectX::ContainmentType::CONTAINS);
		}
	}

	namespace detail
	{
		Sphere ToSphere(const DirectX::BoundingSphere& sphere) noexcept
		{
			return
			{
				{ sphere.Center.x, sphere.Center.y, sphere.Center.z },
				sphere.Radius
			};
		}

		Box ToBox(const DirectX::BoundingBox& box) noexcept
		{
			return
			{
				{ box.Center.x, box.Center.y, box.Center.z },
				{ (box.Extents.x * 2.0), (box.Extents.y * 2.0), (box.Extents.z * 2.0) }
			};
		}

		OrientedBox ToOrientedBox(const DirectX::BoundingOrientedBox& box) noexcept
		{
			return
			{
				{ box.Center.x, box.Center.y, box.Center.z },
				{ (box.Extents.x * 2.0), (box.Extents.y * 2.0), (box.Extents.z * 2.0) },
				Quaternion{ box.Orientation.x, box.Orientation.y, box.Orientation.z, box.Orientation.w }
			};
		}

		DirectX::BoundingSphere FromSphere(const Sphere& sphere) noexcept
		{
			return DirectX::BoundingSphere{
				DirectX::XMFLOAT3{ static_cast<float>(sphere.center.x), static_cast<float>(sphere.center.y), static_cast<float>(sphere.center.z) },
				static_cast<float>(sphere.r),
			};
		}

		DirectX::BoundingBox FromBox(const Box& box) noexcept
		{
			return DirectX::BoundingBox{
				DirectX::XMFLOAT3{ static_cast<float>(box.center.x), static_cast<float>(box.center.y), static_cast<float>(box.center.z) },
				DirectX::XMFLOAT3{ static_cast<float>(box.size.x * 0.5), static_cast<float>(box.size.y * 0.5), static_cast<float>(box.size.z * 0.5) },
			};
		}

		DirectX::BoundingOrientedBox FromOrientedBox(const OrientedBox& box) noexcept
		{
			const Float4 q = box.orientation.toFloat4();

			return DirectX::BoundingOrientedBox{
				DirectX::XMFLOAT3{ static_cast<float>(box.center.x), static_cast<float>(box.center.y), static_cast<float>(box.center.z) },
				DirectX::XMFLOAT3{ static_cast<float>(box.size.x * 0.5), static_cast<float>(box.size.y * 0.5), static_cast<float>(box.size.z * 0.5) },
				DirectX::XMFLOAT4{ q.x, q.y, q.z, q.w },
			};
		}
	}
}
