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
# include <Siv3D/SIMD_Float4.hpp>

namespace s3d
{
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
	}
}
