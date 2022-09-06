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

# include <Siv3D/Ray.hpp>
# include <Siv3D/Sphere.hpp>
# include <Siv3D/Plane.hpp>
# include <Siv3D/InfinitePlane.hpp>
# include <Siv3D/Box.hpp>
# include <Siv3D/OrientedBox.hpp>
# include <Siv3D/ViewFrustum.hpp>
# include <Siv3D/Cylinder.hpp>
# include <Siv3D/Cone.hpp>
# include <Siv3D/FormatFloat.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		inline constexpr float Dot2(const Float3 v) noexcept
		{
			return v.dot(v);
		}
	}

	///////////////////////////////////////////////////////////////
	//
	//

	//
	//	DirectXMath
	//
	//	The MIT License(MIT)
	//
	//	Copyright(c) 2011 - 2020 Microsoft Corp
	//
	//	Permission is hereby granted, free of charge, to any person obtaining a copy of this
	//	softwareand associated documentation files(the "Software"), to deal in the Software
	//	without restriction, including without limitation the rights to use, copy, modify,
	//	merge, publish, distribute, sublicense, and /or sell copies of the Software, and to
	//	permit persons to whom the Software is furnished to do so, subject to the following
	//	conditions :
	//
	//	The above copyright noticeand this permission notice shall be included in all copies
	//	or substantial portions of the Software.
	//
	//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	//	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	//	PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	//	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	//	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
	//	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

	Optional<float> Ray::intersects(const Triangle3D& triangle) const
	{
		float dist;

		if (DirectX::TriangleTests::Intersects(origin, direction, triangle.p0, triangle.p1, triangle.p2, dist))
		{
			return dist;
		}
		else
		{
			return none;
		}
	}

	Optional<float> Ray::intersects(const Sphere& sphere) const
	{
		using namespace DirectX;

		assert(DirectX::Internal::XMVector3IsUnit(direction));

		XMVECTOR vCenter = SIMD_Float4{ sphere.center, 0.0f };
		XMVECTOR vRadius = SIMD_Float4{ static_cast<float>(sphere.r) };

		// l is the vector from the ray origin to the center of the sphere.
		XMVECTOR l = XMVectorSubtract(vCenter, origin);

		// s is the projection of the l onto the ray direction.
		XMVECTOR s = XMVector3Dot(l, direction);

		XMVECTOR l2 = XMVector3Dot(l, l);

		XMVECTOR r2 = XMVectorMultiply(vRadius, vRadius);

		// m2 is squared distance from the center of the sphere to the projection.
		XMVECTOR m2 = XMVectorNegativeMultiplySubtract(s, s, l2);

		XMVECTOR NoIntersection;

		// If the ray origin is outside the sphere and the center of the sphere is
		// behind the ray origin there is no intersection.
		NoIntersection = XMVectorAndInt(XMVectorLess(s, XMVectorZero()), XMVectorGreater(l2, r2));

		// If the squared distance from the center of the sphere to the projection
		// is greater than the radius squared the ray will miss the sphere.
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorGreater(m2, r2));

		// The ray hits the sphere, compute the nearest intersection point.
		XMVECTOR q = XMVectorSqrt(XMVectorSubtract(r2, m2));
		XMVECTOR t1 = XMVectorSubtract(s, q);
		XMVECTOR t2 = XMVectorAdd(s, q);

		XMVECTOR OriginInside = XMVectorLessOrEqual(l2, r2);
		XMVECTOR t = XMVectorSelect(t1, t2, OriginInside);

		if (XMVector4NotEqualInt(NoIntersection, XMVectorTrueInt()))
		{
			// Store the x-component to *pDist.
			float dist;
			XMStoreFloat(&dist, t);
			return dist;
		}

		return none;
	}

	Optional<float> Ray::intersects(const Plane& plane) const
	{
		return intersects(Box{ plane.center, Vec3{ plane.size.x, 0.0f, plane.size.y } });
	}

	Optional<float> Ray::intersects(const InfinitePlane& plane) const
	{
		const Float3 o = origin.xyz();
		const Float3 d = direction.xyz();
		const Float4 p = plane.value.toFloat4();
		return -(o.dot(p.xyz()) + p.w) / d.dot(p.xyz());
	}

	Optional<float> Ray::intersects(const Box& aabb) const
	{
		using namespace DirectX;

		assert(DirectX::Internal::XMVector3IsUnit(direction));

		// Load the box.
		XMVECTOR vCenter = SIMD_Float4{ aabb.center, 0.0f };
		XMVECTOR vExtents = SIMD_Float4{ (aabb.size * 0.5), 0.0f };

		// Adjust ray origin to be relative to center of the box.
		XMVECTOR TOrigin = XMVectorSubtract(vCenter, origin);

		// Compute the dot product againt each axis of the box.
		// Since the axii are (1,0,0), (0,1,0), (0,0,1) no computation is necessary.
		XMVECTOR AxisDotOrigin = TOrigin;
		XMVECTOR AxisDotDirection = direction;

		// if (fabs(AxisDotDirection) <= Epsilon) the ray is nearly parallel to the slab.
		XMVECTOR IsParallel = XMVectorLessOrEqual(XMVectorAbs(AxisDotDirection), g_RayEpsilon);

		// Test against all three axii simultaneously.
		XMVECTOR InverseAxisDotDirection = XMVectorReciprocal(AxisDotDirection);
		XMVECTOR t1 = XMVectorMultiply(XMVectorSubtract(AxisDotOrigin, vExtents), InverseAxisDotDirection);
		XMVECTOR t2 = XMVectorMultiply(XMVectorAdd(AxisDotOrigin, vExtents), InverseAxisDotDirection);

		// Compute the max of min(t1,t2) and the min of max(t1,t2) ensuring we don't
		// use the results from any directions parallel to the slab.
		XMVECTOR t_min = XMVectorSelect(XMVectorMin(t1, t2), g_FltMin, IsParallel);
		XMVECTOR t_max = XMVectorSelect(XMVectorMax(t1, t2), g_FltMax, IsParallel);

		// t_min.x = maximum( t_min.x, t_min.y, t_min.z );
		// t_max.x = minimum( t_max.x, t_max.y, t_max.z );
		t_min = XMVectorMax(t_min, XMVectorSplatY(t_min));  // x = max(x,y)
		t_min = XMVectorMax(t_min, XMVectorSplatZ(t_min));  // x = max(max(x,y),z)
		t_max = XMVectorMin(t_max, XMVectorSplatY(t_max));  // x = min(x,y)
		t_max = XMVectorMin(t_max, XMVectorSplatZ(t_max));  // x = min(min(x,y),z)

		// if ( t_min > t_max ) return false;
		XMVECTOR NoIntersection = XMVectorGreater(XMVectorSplatX(t_min), XMVectorSplatX(t_max));

		// if ( t_max < 0.0f ) return false;
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorLess(XMVectorSplatX(t_max), XMVectorZero()));

		// if (IsParallel && (-Extents > AxisDotOrigin || Extents < AxisDotOrigin)) return false;
		XMVECTOR ParallelOverlap = XMVectorInBounds(AxisDotOrigin, vExtents);
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorAndCInt(IsParallel, ParallelOverlap));

		if (!DirectX::Internal::XMVector3AnyTrue(NoIntersection))
		{
			// Store the x-component to *pDist
			float dist;
			XMStoreFloat(&dist, t_min);
			return dist;
		}

		return none;
	}

	Optional<float> Ray::intersects(const OrientedBox& obb) const
	{
		using namespace DirectX;

		assert(DirectX::Internal::XMVector3IsUnit(direction));

		static const XMVECTORU32 SelectY = { { { XM_SELECT_0, XM_SELECT_1, XM_SELECT_0, XM_SELECT_0 } } };
		static const XMVECTORU32 SelectZ = { { { XM_SELECT_0, XM_SELECT_0, XM_SELECT_1, XM_SELECT_0 } } };

		// Load the box.
		XMVECTOR vCenter = SIMD_Float4{ obb.center, 0.0f };
		XMVECTOR vExtents = SIMD_Float4{ (obb.size * 0.5), 0.0f };
		XMVECTOR vOrientation = obb.orientation;

		assert(DirectX::Internal::XMQuaternionIsUnit(vOrientation));

		// Get the boxes normalized side directions.
		XMMATRIX R = XMMatrixRotationQuaternion(vOrientation);

		// Adjust ray origin to be relative to center of the box.
		XMVECTOR TOrigin = XMVectorSubtract(vCenter, origin);

		// Compute the dot product againt each axis of the box.
		XMVECTOR AxisDotOrigin = XMVector3Dot(R.r[0], TOrigin);
		AxisDotOrigin = XMVectorSelect(AxisDotOrigin, XMVector3Dot(R.r[1], TOrigin), SelectY);
		AxisDotOrigin = XMVectorSelect(AxisDotOrigin, XMVector3Dot(R.r[2], TOrigin), SelectZ);

		XMVECTOR AxisDotDirection = XMVector3Dot(R.r[0], direction);
		AxisDotDirection = XMVectorSelect(AxisDotDirection, XMVector3Dot(R.r[1], direction), SelectY);
		AxisDotDirection = XMVectorSelect(AxisDotDirection, XMVector3Dot(R.r[2], direction), SelectZ);

		// if (fabs(AxisDotDirection) <= Epsilon) the ray is nearly parallel to the slab.
		XMVECTOR IsParallel = XMVectorLessOrEqual(XMVectorAbs(AxisDotDirection), g_RayEpsilon);

		// Test against all three axes simultaneously.
		XMVECTOR InverseAxisDotDirection = XMVectorReciprocal(AxisDotDirection);
		XMVECTOR t1 = XMVectorMultiply(XMVectorSubtract(AxisDotOrigin, vExtents), InverseAxisDotDirection);
		XMVECTOR t2 = XMVectorMultiply(XMVectorAdd(AxisDotOrigin, vExtents), InverseAxisDotDirection);

		// Compute the max of min(t1,t2) and the min of max(t1,t2) ensuring we don't
		// use the results from any directions parallel to the slab.
		XMVECTOR t_min = XMVectorSelect(XMVectorMin(t1, t2), g_FltMin, IsParallel);
		XMVECTOR t_max = XMVectorSelect(XMVectorMax(t1, t2), g_FltMax, IsParallel);

		// t_min.x = maximum( t_min.x, t_min.y, t_min.z );
		// t_max.x = minimum( t_max.x, t_max.y, t_max.z );
		t_min = XMVectorMax(t_min, XMVectorSplatY(t_min));  // x = max(x,y)
		t_min = XMVectorMax(t_min, XMVectorSplatZ(t_min));  // x = max(max(x,y),z)
		t_max = XMVectorMin(t_max, XMVectorSplatY(t_max));  // x = min(x,y)
		t_max = XMVectorMin(t_max, XMVectorSplatZ(t_max));  // x = min(min(x,y),z)

		// if ( t_min > t_max ) return false;
		XMVECTOR NoIntersection = XMVectorGreater(XMVectorSplatX(t_min), XMVectorSplatX(t_max));

		// if ( t_max < 0.0f ) return false;
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorLess(XMVectorSplatX(t_max), XMVectorZero()));

		// if (IsParallel && (-Extents > AxisDotOrigin || Extents < AxisDotOrigin)) return false;
		XMVECTOR ParallelOverlap = XMVectorInBounds(AxisDotOrigin, vExtents);
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorAndCInt(IsParallel, ParallelOverlap));

		if (!DirectX::Internal::XMVector3AnyTrue(NoIntersection))
		{
			// Store the x-component to *pDist
			float dist;
			XMStoreFloat(&dist, t_min);
			return dist;
		}

		return none;
	}

	Optional<float> Ray::intersects(const ViewFrustum& frustum) const
	{
		using namespace DirectX;
		const auto& f = frustum.getData();

		// If ray starts inside the frustum, return a distance of 0 for the hit
		if (f.Contains(origin) == CONTAINS)
		{
			return 0.0f;
		}

		// Build the frustum planes.
		XMVECTOR Planes[6];
		Planes[0] = XMVectorSet(0.0f, 0.0f, -1.0f, f.Near);
		Planes[1] = XMVectorSet(0.0f, 0.0f, 1.0f, -f.Far);
		Planes[2] = XMVectorSet(1.0f, 0.0f, -f.RightSlope, 0.0f);
		Planes[3] = XMVectorSet(-1.0f, 0.0f, f.LeftSlope, 0.0f);
		Planes[4] = XMVectorSet(0.0f, 1.0f, -f.TopSlope, 0.0f);
		Planes[5] = XMVectorSet(0.0f, -1.0f, f.BottomSlope, 0.0f);

		// Load origin and orientation of the frustum.
		XMVECTOR frOrigin = XMLoadFloat3(&f.Origin);
		XMVECTOR frOrientation = XMLoadFloat4(&f.Orientation);

		// This algorithm based on "Fast Ray-Convex Polyhedron Intersectin," in James Arvo, ed., Graphics Gems II pp. 247-250
		float tnear = -FLT_MAX;
		float tfar = FLT_MAX;

		for (size_t i = 0; i < 6; ++i)
		{
			XMVECTOR Plane = DirectX::Internal::XMPlaneTransform(Planes[i], frOrientation, frOrigin);
			Plane = XMPlaneNormalize(Plane);

			XMVECTOR AxisDotOrigin = XMPlaneDotCoord(Plane, origin);
			XMVECTOR AxisDotDirection = XMVector3Dot(Plane, direction);

			if (XMVector3LessOrEqual(XMVectorAbs(AxisDotDirection), g_RayEpsilon))
			{
				// Ray is parallel to plane - check if ray origin is inside plane's
				if (XMVector3Greater(AxisDotOrigin, g_XMZero))
				{
					// Ray origin is outside half-space.
					return none;
				}
			}
			else
			{
				// Ray not parallel - get distance to plane.
				float vd = XMVectorGetX(AxisDotDirection);
				float vn = XMVectorGetX(AxisDotOrigin);
				float t = -vn / vd;
				if (vd < 0.0f)
				{
					// Front face - T is a near point.
					if (t > tfar)
					{
						return none;
					}
					if (t > tnear)
					{
						// Hit near face.
						tnear = t;
					}
				}
				else
				{
					// back face - T is far point.
					if (t < tnear)
					{
						return none;
					}
					if (t < tfar)
					{
						// Hit far face.
						tfar = t;
					}
				}
			}
		}

		// Survived all tests.
		// Note: if ray originates on polyhedron, may want to change 0.0f to some
		// epsilon to avoid intersecting the originating face.
		float distance = (tnear >= 0.0f) ? tnear : tfar;
		if (distance >= 0.0f)
		{
			return distance;
		}

		return none;
	}

	//
	//
	///////////////////////////////////////////////////////////////

	Optional<float> Ray::intersects(const Cylinder& cylinder) const
	{
		// https://www.iquilezles.org/www/articles/intersectors/intersectors.htm

		const Float3 ro = origin.xyz();
		const Float3 rd = direction.xyz();
		const Float3 d = (cylinder.orientation * Float3{ 0, static_cast<float>(cylinder.h), 0 });
		const Float3 pa = (cylinder.center + (d * 0.5f));
		const Float3 pb = (cylinder.center - (d * 0.5f));
		const float ra = static_cast<float>(cylinder.r);

		const Float3 ca = pb - pa;
		const Float3 oc = ro - pa;
		float caca = ca.dot(ca);
		float card = ca.dot(rd);
		float caoc = ca.dot(oc);
		float a = caca - card * card;
		float b = caca * oc.dot(rd) - caoc * card;
		float c = caca * oc.dot(oc) - caoc * caoc - ra * ra * caca;
		float h = b * b - a * c;
		
		if (h < 0.0f)
		{
			return none;
		}

		h = std::sqrt(h);

		float t = (-b - h) / a;
		
		// body
		float y = caoc + t * card;
		if ((0.0f < y) && (y < caca))
		{
			return static_cast<float>(t);
		}

		// caps
		t = (((y < 0.0f) ? 0.0f : caca) - caoc) / card;
		
		if (std::abs(b + a * t) < h)
		{
			return t;
		}
		
		return none;
	}

	Optional<float> Ray::intersects(const Cone& cone) const
	{
		// https://www.iquilezles.org/www/articles/intersectors/intersectors.htm

		const Float3 ro = origin.xyz();
		const Float3 rd = direction.xyz();
		const Float3 d = (cone.orientation * Float3{ 0, static_cast<float>(cone.h), 0 });
		const Float3 pa = (cone.center + d);
		const Float3 pb = cone.center;
		constexpr float ra = 0.0f;
		const float rb = static_cast<float>(cone.r);

		const Float3 ba = pb - pa;
		const Float3 oa = ro - pa;
		const Float3 ob = ro - pb;
		const float m0 = ba.dot(ba);
		const float m1 = oa.dot(ba);
		const float m2 = rd.dot(ba);
		const float m3 = rd.dot(oa);
		const float m5 = oa.dot(oa);
		const float m9 = ob.dot(ba);

		// caps
		if (m1 < 0.0f)
		{
			if (detail::Dot2(oa * m2 - rd * m1) < (ra * ra * m2 * m2))
			{
				return (-m1 / m2);
			}
		}
		else if (0.0f < m9)
		{
			float t = (-m9 / m2);
			
			if (detail::Dot2(ob + rd * t) < (rb * rb))
			{
				return t;
			}
		}

		// body
		float rr = ra - rb;
		float hy = m0 + rr * rr;
		float k2 = m0 * m0 - m2 * m2 * hy;
		float k1 = m0 * m0 * m3 - m1 * m2 * hy + m0 * ra * (rr * m2 * 1.0f);
		float k0 = m0 * m0 * m5 - m1 * m1 * hy + m0 * ra * (rr * m1 * 2.0f - m0 * ra);
		float h = k1 * k1 - k2 * k0;
		
		if (h < 0.0f)
		{
			return none;
		}
		
		float t = (-k1 - std::sqrt(h)) / k2;
		float y = m1 + t * m2;
		
		if ((y < 0.0) || (m0 < y))
		{
			return none;
		}
		
		return t;
	}

	Optional<Float3> Ray::intersectsAt(const Triangle3D& triangle) const
	{
		float dist;

		if (DirectX::TriangleTests::Intersects(origin, direction, triangle.p0, triangle.p1, triangle.p2, dist))
		{
			return point_at(dist);
		}
		else
		{
			return none;
		}
	}

	Optional<Float3> Ray::intersectsAt(const Sphere& sphere) const
	{
		if (const auto dist = intersects(sphere))
		{
			return point_at(*dist);
		}
		else
		{
			return none;
		}
	}

	Optional<Float3> Ray::intersectsAt(const Plane& plane) const
	{
		return intersectsAt(Box{ plane.center, Vec3{ plane.size.x, 0.0f, plane.size.y } });
	}

	Optional<Float3> Ray::intersectsAt(const InfinitePlane& plane) const
	{
		if (const auto dist = intersects(plane))
		{
			return point_at(*dist);
		}
		else
		{
			return none;
		}
	}

	Optional<Float3> Ray::intersectsAt(const Box& aabb) const
	{
		if (const auto dist = intersects(aabb))
		{
			return point_at(*dist);
		}
		else
		{
			return none;
		}
	}

	Optional<Float3> Ray::intersectsAt(const OrientedBox& obb) const
	{
		if (const auto dist = intersects(obb))
		{
			return point_at(*dist);
		}
		else
		{
			return none;
		}
	}

	Optional<Float3>SIV3D_VECTOR_CALL Ray::intersectsAt(const ViewFrustum& frustum) const
	{
		if (const auto dist = intersects(frustum))
		{
			return point_at(*dist);
		}
		else
		{
			return none;
		}
	}

	Optional<Float3> Ray::intersectsAt(const Cylinder& cylinder) const
	{
		if (const auto dist = intersects(cylinder))
		{
			return point_at(*dist);
		}
		else
		{
			return none;
		}
	}

	Optional<Float3> Ray::intersectsAt(const Cone& cone) const
	{
		if (const auto dist = intersects(cone))
		{
			return point_at(*dist);
		}
		else
		{
			return none;
		}
	}

	void Formatter(FormatData& formatData, const Ray& value)
	{
		const Float4 o = value.origin.toFloat4();
		const Float4 d = value.direction.toFloat4();

		formatData.string.append(U"(("_sv);

		formatData.string.append(ToString(o.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(o.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(o.z, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(d.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(d.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(d.z, formatData.decimalPlaces.value));

		formatData.string.append(U"))"_sv);
	}
}
