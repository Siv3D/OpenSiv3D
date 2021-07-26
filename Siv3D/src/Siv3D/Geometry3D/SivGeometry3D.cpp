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

# include <Siv3D/Geometry3D.hpp>
# include <Siv3D/SIMD_Float4.hpp>

namespace s3d
{
	namespace detail
	{
		Box ToBox(const DirectX::BoundingBox& box) noexcept
		{
			return
			{
				{ box.Center.x, box.Center.y, box.Center.z },
				{ (box.Extents.x * 2.0), (box.Extents.y * 2.0), (box.Extents.z * 2.0) }
			};
		}

		Sphere ToSphere(const DirectX::BoundingSphere& sphere) noexcept
		{
			return
			{
				{ sphere.Center.x, sphere.Center.y, sphere.Center.z },
				sphere.Radius
			};
		}

		DirectX::BoundingBox FromBox(const Box& box) noexcept
		{
			return DirectX::BoundingBox{
				DirectX::XMFLOAT3{ static_cast<float>(box.center.x), static_cast<float>(box.center.y), static_cast<float>(box.center.z) },
				DirectX::XMFLOAT3{ static_cast<float>(box.size.x * 0.5), static_cast<float>(box.size.y * 0.5), static_cast<float>(box.size.z * 0.5) },
			};
		}

		DirectX::BoundingSphere FromSphere(const Sphere& sphere) noexcept
		{
			return DirectX::BoundingSphere{
				DirectX::XMFLOAT3{ static_cast<float>(sphere.center.x), static_cast<float>(sphere.center.y), static_cast<float>(sphere.center.z) },
				static_cast<float>(sphere.r),
			};
		}
	}

	namespace Geometry3D
	{
		Sphere BoundingSphere(const Array<Vertex3D>& vertices) noexcept
		{
			if (not vertices)
			{
				return Sphere{ 0.0 };
			}

			DirectX::BoundingSphere sphere;

			DirectX::BoundingSphere::CreateFromPoints(
				sphere,
				vertices.size(),
				static_cast<const DirectX::XMFLOAT3*>(static_cast<const void*>(vertices.data())),
				sizeof(Vertex3D)
			);

			return detail::ToSphere(sphere);
		}

		Box BoundingBox(const Array<Vertex3D>& vertices) noexcept
		{
			if (not vertices)
			{
				return Box{ 0.0 };
			}

			DirectX::BoundingBox box;

			DirectX::BoundingBox::CreateFromPoints(
				box,
				vertices.size(),
				static_cast<const DirectX::XMFLOAT3*>(static_cast<const void*>(vertices.data())),
				sizeof(Vertex3D)
			);

			return detail::ToBox(box);
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
